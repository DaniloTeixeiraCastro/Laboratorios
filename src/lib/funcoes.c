/**
 * @file funcoes.c
 * @brief Implementação das funções do sistema de gestão do espaço social
 * @author [G36 - Epoca Especial]
 * @date 2025-06-20
 */

#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Estado global do controle de refeições
struct ControleRefeicao valorRefeicao = {5.00, "29.06.2025"};
int refeicoes_servidas_por_dia = 0;
char dia_atual[11] = "";

// Variáveis globais para as listas
NodeFunc* funcionarios = NULL;
NodeEmenta* ementas = NULL;
NodeEscolha* escolhas = NULL;

/**
 * @brief Atualiza a variável global das ementas
 * @param nova_lista Nova lista de ementas
 */
void atualizarEmentas(NodeEmenta* nova_lista) {
    // Libera memória da lista antiga se existir
    if (ementas != NULL) {
        NodeEmenta* atual = ementas;
        while (atual != NULL) {
            NodeEmenta* prox = atual->prox;
            free(atual);
            atual = prox;
        }
    }
    ementas = nova_lista;
}

/**
 * @brief Obtém a lista global de ementas
 * @return Ponteiro para a lista de ementas
 */
NodeEmenta* obterEmentas() {
    return ementas;
}

/**
 * @brief Compara duas datas no formato DD.MM.AAAA
 * @param data1 Primeira data
 * @param data2 Segunda data
 * @return 1 se data1 > data2, -1 se data1 < data2, 0 se são iguais
 */
int compararDatas(const char* data1, const char* data2) {
    int dia1, mes1, ano1, dia2, mes2, ano2;
    sscanf(data1, "%d.%d.%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d.%d.%d", &dia2, &mes2, &ano2);
    
    if (ano1 > ano2) return 1;
    if (ano1 < ano2) return -1;
    if (mes1 > mes2) return 1;
    if (mes1 < mes2) return -1;
    if (dia1 > dia2) return 1;
    if (dia1 < dia2) return -1;
    return 0;
}

/**
 * @brief Limpa o buffer do teclado
 * @details Remove caracteres residuais do buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Pausa a execução do programa até que o usuário pressione Enter
 * @details Exibe uma mensagem e aguarda input do usuário
 */
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
    system("cls");    
}

/**
 * @brief Inicializa o controle de refeições
 * @details Configura o valor inicial da refeição e reseta o contador diário
 */
void inicializarControleRefeicoes() {
    // Valor inicial da refeição já está definido na estrutura
    // Reseta o contador de refeições
    refeicoes_servidas_por_dia = 0;
    
    // Obtém a data atual
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(dia_atual, "%02d.%02d.%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}

/**
 * @brief Valida se é possível servir mais uma refeição no dia
 * @param dia Dia da semana para validação
 * @return 1 se pode servir, 0 se não pode
 */
int validarRefeicaoDia(const char* dia) {
    // Verifica se é um novo dia
    if (strcmp(dia_atual, dia) != 0) {
        // Nova data, reseta o contador
        refeicoes_servidas_por_dia = 0;
        strcpy(dia_atual, dia);
    }
    
    // Verifica se já atingiu o limite
    if (refeicoes_servidas_por_dia >= LIMITE_REFEICOES_DIARIO) {
        printf("\nERRO: Limite diário de refeições atingido!\n");
        printf("Máximo de %d refeições por dia.\n", LIMITE_REFEICOES_DIARIO);
        return 0;
    }
    
    // Incrementa o contador e retorna sucesso
    refeicoes_servidas_por_dia++;
    return 1;
}

// Estrutura para armazenar atualizações de valor
struct AtualizacaoValor {
    float valor;
    char data_inicio[11];
};

// Array para armazenar as atualizações de valor
#define MAX_ATUALIZACOES 10
static struct AtualizacaoValor atualizacoes[MAX_ATUALIZACOES];
static int num_atualizacoes = 0;

/**
 * @brief Atualiza o valor da refeição
 * @param novo_valor Novo valor da refeição
 */
void atualizarValorRefeicao(float novo_valor) {
    // Verifica se as ementas foram carregadas
    if (ementas == NULL) {
        printf("\nErro: Carregue as ementas primeiro (opcao 1.b)!\n");
        return;
    }
    
    // Pede a data de entrada em vigor do novo valor da refeição
    char data_inicio[11];
    printf("\nDigite a data de inicio que o novo valor entra em vigor (DD.MM.AAAA): ");
    scanf("%10s", data_inicio);
    limparBuffer();
    
    // Valida o formato da data
    if (strlen(data_inicio) != 10 || data_inicio[2] != '.' || data_inicio[5] != '.') {
        printf("\nErro: Formato de data invalido! Use DD.MM.AAAA\n");
        return;
    }
    
    // Valida se a data está dentro do período das ementas
    NodeEmenta* ementa = ementas;
    int data_valida = 0;
    
    while (ementa) {
        if (compararDatas(data_inicio, ementa->ementa.data) == 0) {
            data_valida = 1;
            break;
        }
        ementa = ementa->prox;
    }
    
    if (!data_valida) {
        printf("\nErro: Data nao corresponde a nenhuma data de ementa!\n");
        printf("Datas disponiveis: ");
        ementa = ementas;
        while (ementa) {
            printf("%s ", ementa->ementa.data);
            ementa = ementa->prox;
        }
        printf("\n");
        return;
    }
    
    // Verifica se já atingiu o limite de atualizações
    if (num_atualizacoes >= MAX_ATUALIZACOES) {
        printf("\nErro: Limite maximo de atualizacoes atingido!\n");
        return;
    }
    
    // Verifica se já existe uma atualização para esta data
    for (int i = 0; i < num_atualizacoes; i++) {
        if (strcmp(data_inicio, atualizacoes[i].data_inicio) == 0) {
            printf("\nErro: Ja existe uma atualizacao para esta data!\n");
            return;
        }
    }
    
    // Atualiza o valor e armazena a nova atualização
    atualizacoes[num_atualizacoes].valor = novo_valor;
    strcpy(atualizacoes[num_atualizacoes].data_inicio, data_inicio);
    
    // Atualiza a data da última atualização para a data de início
    strcpy(valorRefeicao.data_ultima_atualizacao, data_inicio);
    
    // Atualiza o valor atual da refeição
    valorRefeicao.valor = novo_valor;
    
    num_atualizacoes++;
    
    printf("\nValor da refeicao atualizado com sucesso!\n");
    
    // Mostra o valor atual da refeição
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                  Informacoes da Refeicao                     |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| Novo valor da refeicao: %.2f Euros\n", novo_valor);
    printf("| Data de entrada em vigor: %s\n", data_inicio);
    printf("+--------------------------------------------------------------+\n");
}

/**
 * @brief Mostra o valor atual da refeição
 */
void mostrarValorRefeicao() {
    printf("\nValor atual da refeicao: %.2f€\n", valorRefeicao.valor);
    printf("Ultima atualizacao: %s\n", valorRefeicao.data_ultima_atualizacao);
}



/**
 * @brief Cria um novo nó para a lista de funcionários
 * @param func Estrutura com os dados do funcionário
 * @return NodeFunc* Ponteiro para o novo nó criado ou NULL em caso de falha
 * @details Aloca memória dinamicamente para um novo nó e inicializa seus campos
 */
NodeFunc* criarNoFunc(Funcionario func) {
    NodeFunc* novoNo = (NodeFunc*)malloc(sizeof(NodeFunc));
    if (novoNo != NULL) {
        novoNo->func = func;
        novoNo->prox = NULL;
    }
    return novoNo;
}

/**
 * @brief Carrega dados dos funcionários a partir de um arquivo
 * @param filename Nome do arquivo contendo os dados dos funcionários
 * @return NodeFunc* Ponteiro para o início da lista de funcionários ou NULL em caso de erro
 * @details Lê o arquivo CSV com dados dos funcionários e cria uma lista ligada
 *          O arquivo deve estar no formato: numero;nome;nif;telefone
 */
NodeFunc* carregarFuncionarios(const char* filename) {
    printf("\n+================================================+\n");
    printf("|           Carregando Funcionarios              |\n");
    printf("+================================================+\n");

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return NULL;
    }

    NodeFunc* head = NULL;
    NodeFunc* atual = NULL;
    char linha[256];

    printf("+---------+----------------------+-------------+-------------+\n");
    printf("| Numero  | Nome                 | NIF         | Telefone    |\n");
    printf("+---------+----------------------+-------------+-------------+\n");

    int contador = 0;
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = 0;
        
        Funcionario func;
        char* token = strtok(linha, ";");
        
        if (token) {
            func.numero = atoi(token);
            token = strtok(NULL, ";");
            if (token) {
                strncpy(func.nome, token, MAX_NOME-1);
                token = strtok(NULL, ";");
                if (token) {
                    func.nif = atoi(token);
                    token = strtok(NULL, ";");
                    if (token) {
                        func.telefone = atoi(token);

                        printf("| %-7d | %-20s | %-11d | %-11d |\n",
                            func.numero, func.nome, func.nif, func.telefone);

                        NodeFunc* novoNo = criarNoFunc(func);
                        if (novoNo) {
                            if (!head) {
                                head = novoNo;
                                atual = novoNo;
                            } else {
                                atual->prox = novoNo;
                                atual = novoNo;
                            }
                            contador++;
                        }
                    }
                }
            }
        }
    }

    printf("+---------+----------------------+-------------+-------------+\n");
    printf("Total de funcionarios carregados: %d\n", contador);
    printf("+================================================+\n");

    fclose(file);
    return head;
}

/**
 * @brief Carrega dados das ementas a partir de um arquivo
 * @param filename Nome do arquivo contendo as ementas
 * @return NodeEmenta* Ponteiro para o início da lista de ementas ou NULL em caso de erro
 * @details Lê o arquivo CSV com dados das ementas e cria uma lista ligada
 *          O arquivo deve estar no formato: dia;data;prato_carne;calorias_carne;prato_peixe;calorias_peixe
 */
NodeEmenta* carregarEmentas(const char* filename) {
    printf("\n+================================================+\n");
    printf("|              Carregando Ementas                |\n");
    printf("+================================================+\n");

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return NULL;
    }

    NodeEmenta* head = NULL;
    NodeEmenta* atual = NULL;
    char linha[256];
    int contador = 0;

    printf("+--------+-------------+--------------------------------+--------+\n");
    printf("| Dia    | Data        | Prato                          | Cal.   |\n");
    printf("+--------+-------------+--------------------------------+--------+\n");

    int is_first = 1;
    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = 0;
        
        Ementa ementa;
        char* token = strtok(linha, ";");
        
        if (token) {
            strncpy(ementa.dia, token, sizeof(ementa.dia)-1);
            token = strtok(NULL, ";");
            if (token) {
                strncpy(ementa.data, token, sizeof(ementa.data)-1);

                // Adiciona linha de separador antes de cada nova data não vazia, exceto a primeira
                if (!is_first && ementa.dia[0] != '\0' && ementa.data[0] != '\0') {
                    printf("+--------+-------------+--------------------------------+--------+\n");
                }
                is_first = 0;

                // Prato de Peixe
                token = strtok(NULL, ";");
                if (token) {
                    strncpy(ementa.prato_peixe.nome, token, MAX_NOME-1);
                    token = strtok(NULL, ";");
                    if (token) {
                        ementa.prato_peixe.calorias = atoi(token);
                    }
                }
                // Prato de Carne
                token = strtok(NULL, ";");
                if (token) {
                    strncpy(ementa.prato_carne.nome, token, MAX_NOME-1);
                    token = strtok(NULL, ";");
                    if (token) {
                        ementa.prato_carne.calorias = atoi(token);
                    }
                }
                // Prato de Dieta
                token = strtok(NULL, ";");
                if (token) {
                    strncpy(ementa.prato_dieta.nome, token, MAX_NOME-1);
                    token = strtok(NULL, ";");
                    if (token) {
                        ementa.prato_dieta.calorias = atoi(token);
                    }
                }
                // Prato Vegetariano
                token = strtok(NULL, ";");
                if (token) {
                    strncpy(ementa.prato_vegetariano.nome, token, MAX_NOME-1);
                    token = strtok(NULL, ";");
                    if (token) {
                        ementa.prato_vegetariano.calorias = atoi(token);
                    }
                }

                // Imprime linha ímpar (peixe)
                printf("| %-6s | %-11s | %-30s | %-6d |\n",
                    ementa.dia, ementa.data, ementa.prato_peixe.nome, ementa.prato_peixe.calorias);
                // Imprime linha par (carne)
                printf("| %-6s | %-11s | %-30s | %-6d |\n",
                    "", "", ementa.prato_carne.nome, ementa.prato_carne.calorias);
                // Imprime linha dieta
                printf("| %-6s | %-11s | %-30s | %-6d |\n",
                    "", "", ementa.prato_dieta.nome, ementa.prato_dieta.calorias);
                // Imprime linha vegetariano
                printf("| %-6s | %-11s | %-30s | %-6d |\n",
                    "", "", ementa.prato_vegetariano.nome, ementa.prato_vegetariano.calorias);

                NodeEmenta* novoNo = (NodeEmenta*)malloc(sizeof(NodeEmenta));
                if (novoNo) {
                    novoNo->ementa = ementa;
                    novoNo->prox = NULL;
                    if (!head) {
                        head = novoNo;
                        atual = novoNo;
                    } else {
                        atual->prox = novoNo;
                        atual = novoNo;
                    }
                    contador++;
                }
            }
        }
    }

    printf("+--------+-------------+--------------------------------+--------+\n");
    printf("Ementa semanal carregada.\n");
    printf("+================================================+\n");

    fclose(file);
    return head;
}

/**
 * @brief Carrega as escolhas dos utentes a partir de um arquivo
 * @param filename Nome do arquivo contendo as escolhas
 * @return NodeEscolha* Ponteiro para o início da lista de escolhas ou NULL em caso de erro
 * @details Lê o arquivo CSV com as escolhas e cria uma lista ligada
 *          O arquivo deve estar no formato: dia;num_funcionario;tipo_prato
 */
NodeEscolha* carregarEscolhas(const char* filename) {
    printf("\n+------------------------------------+\n");
    printf("|        Carregando Escolhas         |\n");
    printf("+------------------------------------+\n");

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return NULL;
    }

    NodeEscolha* head = NULL;
    NodeEscolha* atual = NULL;
    char linha[256];
    int contador = 0;

    printf("+---------+---------+---------------------+\n");
    printf("| Dia     | Func.   | Tipo de Prato       |\n");
    printf("+---------+---------+---------------------+\n");

    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = 0;
        
        Escolha escolha;
        char* token = strtok(linha, ";");
        
        if (token) {
            strncpy(escolha.dia, token, sizeof(escolha.dia)-1);
            token = strtok(NULL, ";");
            
            if (token) {
                escolha.num_funcionario = atoi(token);
                token = strtok(NULL, ";");
                
                if (token) {
                    escolha.tipo_prato = token[0];
                    const char* tipo_desc =
                        escolha.tipo_prato == 'C' ? "Carne" :
                        escolha.tipo_prato == 'P' ? "Peixe" :
                        escolha.tipo_prato == 'D' ? "Dieta" :
                        escolha.tipo_prato == 'V' ? "Vegetariano" : "Invalido";

                    printf("| %-7s | %-7d | %-19s |\n",
                        escolha.dia,
                        escolha.num_funcionario,
                        tipo_desc);

                    NodeEscolha* novoNo = (NodeEscolha*)malloc(sizeof(NodeEscolha));
                    if (novoNo) {
                        novoNo->escolha = escolha;
                        novoNo->prox = NULL;
                        
                        if (!head) {
                            head = novoNo;
                            atual = novoNo;
                        } else {
                            atual->prox = novoNo;
                            atual = novoNo;
                        }
                        contador++;
                    }
                }
            }
        }
    }

    printf("+---------+---------+---------------------+\n");
    printf("Total de escolhas carregadas: %d\n", contador);
    printf("+------------------------------------+\n");

    fclose(file);
    return head;
}

/**
 * @brief Liberta toda a memória alocada para as listas
 * @param funcionarios Ponteiro para a lista de funcionários
 * @param ementas Ponteiro para a lista de ementas
 * @param escolhas Ponteiro para a lista de escolhas
 * @details Percorre todas as listas libertando a memória alocada para cada nó
 */
void libertarMemoria(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas) {
    // Libertar lista de funcionarios
    while (funcionarios) {
        NodeFunc* temp = funcionarios;
        funcionarios = funcionarios->prox;
        free(temp);
    }

    // Libertar lista de ementas
    while (ementas) {
        NodeEmenta* temp = ementas;
        ementas = ementas->prox;
        free(temp);
    }

    // Libertar lista de escolhas
    while (escolhas) {
        NodeEscolha* temp = escolhas;
        escolhas = escolhas->prox;
        free(temp);
    }
}

/**
 * @brief Lista todas as refeições de um dia específico
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param dia Dia para listar as refeições
 * @details Mostra as escolhas de refeições feitas pelos funcionários em um determinado dia
 */
 void listarRefeicoesDia(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, const char* dia) {
    if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
        printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
        return;
    }

    // Valida o limite de refeições
    if (!validarRefeicaoDia(dia)) {
        return;
    }

    // Encontra a ementa do dia
    NodeEmenta* ementa_atual = ementas;
    while (ementa_atual != NULL && strcmp(ementa_atual->ementa.dia, dia) != 0) {
        ementa_atual = ementa_atual->prox;
    }

    if (ementa_atual == NULL) {
        printf("\nDia não encontrado na ementa!\n");
        return;
    }

    printf("Data: %s\n", ementa_atual->ementa.data);

    printf("\nPratos disponiveis:\n");
    printf("- Carne: %s (%d calorias)\n", ementa_atual->ementa.prato_carne.nome, ementa_atual->ementa.prato_carne.calorias);
    printf("- Peixe: %s (%d calorias)\n", ementa_atual->ementa.prato_peixe.nome, ementa_atual->ementa.prato_peixe.calorias);
    printf("- Dieta: %s (%d calorias)\n", ementa_atual->ementa.prato_dieta.nome, ementa_atual->ementa.prato_dieta.calorias);
    printf("- Vegetariano: %s (%d calorias)\n", ementa_atual->ementa.prato_vegetariano.nome, ementa_atual->ementa.prato_vegetariano.calorias);

    printf("\n+=============================================================+\n");
    printf("|               Refeicoes requeridas para %s              |\n", dia);
    printf("+=============================================================+\n");
    printf("+--------+----------------------+-----------------------------+\n");
    printf("| Func.  | Nome                 | Prato                       |\n");
    printf("+--------+----------------------+-----------------------------+\n");

    NodeEscolha* escolha_atual = escolhas;
    int total_refeicoes = 0;
    
    while (escolha_atual != NULL) {
        if (strcmp(escolha_atual->escolha.dia, dia) == 0) {
            // Valida e conta a refeição
            if (validarRefeicaoDia(dia)) {
                NodeFunc* func_atual = funcionarios;
                while (func_atual != NULL && func_atual->func.numero != escolha_atual->escolha.num_funcionario) {
                    func_atual = func_atual->prox;
                }
                if (func_atual != NULL) {
                    // Determina o nome do prato escolhido
                    const char* nome_prato = "";
                    switch (escolha_atual->escolha.tipo_prato) {
                        case 'C':
                            nome_prato = ementa_atual->ementa.prato_carne.nome;
                            break;
                        case 'P':
                            nome_prato = ementa_atual->ementa.prato_peixe.nome;
                            break;
                        case 'D':
                            nome_prato = ementa_atual->ementa.prato_dieta.nome;
                            break;
                        case 'V':
                            nome_prato = ementa_atual->ementa.prato_vegetariano.nome;
                            break;
                        default:
                            nome_prato = "Prato não especificado";
                    }
                    
                    printf("| %-6d | %-20s | %-27s |\n", 
                           func_atual->func.numero, 
                           func_atual->func.nome, 
                           nome_prato);                    total_refeicoes++;
                }
            }
        }
        escolha_atual = escolha_atual->prox;
    }
    // Mostra o número de refeições requeridas para o dia
    printf("+--------+----------------------+-----------------------------+\n");
    printf("\nTotal de refeicoes requeridas para %s: %d/%d\n", dia, total_refeicoes, LIMITE_REFEICOES_DIARIO);
    printf("____________________________________________________\n");
}

/**
 * @brief Lista o consumo semanal de refeições, dos utentes ordenados por ordem decrescente,
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @details Ordena e exibe os utentes com base no número de refeições escolhidas
 */
void listarRefeicoesServidasSemana(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas) {
    // Variáveis para cálculo dos totais
    int total_refeicoes = 0;
    float total_despesa = 0;

    // Mostra o valor atual da refeição
    printf("\n+--------------------------------------------------------------+\n");
    printf("|                  Informacoes da Refeicao                     |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("| Valor atual da refeicao: %.2f Euros                          |\n", valorRefeicao.valor);
    printf("| Ultima atualizacao: %s                               |\n", valorRefeicao.data_ultima_atualizacao);
    printf("+--------------------------------------------------------------+\n");
    
    // Pergunta se deseja atualizar o valor
    char resposta;
    do {
        printf("\nDeseja atualizar o valor da refeicao? (S/N): ");
        scanf(" %c", &resposta);
        limparBuffer();
        
        if (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n') {
            printf("\nErro: Resposta invalida! Por favor, digite S para Sim ou N para Nao.\n");
        }
    } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

    if (resposta == 'S' || resposta == 's') {
        float novo_valor;
        printf("\nDigite o novo valor da refeicao: ");
        scanf("%f", &novo_valor);
        limparBuffer();
        
        if (novo_valor > 0) {
            atualizarValorRefeicao(novo_valor);
            pausar();
        } else {
            printf("\nErro: Valor deve ser maior que zero!\n");
            pausar();
        }
    }

    printf("\n+==============================================================+\n");
    printf("|             Resumo semanal de Consumo por Utente             |\n");
    printf("+==============================================================+\n");

    // Criar array para contar refeicoes por funcionario
    int max_func = 0;
    NodeFunc* func = funcionarios;
    while (func) {
        if (func->func.numero > max_func)
            max_func = func->func.numero;
        func = func->prox;
    }

    int* contagem = (int*)calloc(max_func + 1, sizeof(int));
    if (!contagem) {
        printf("Erro: Falha na alocacao de memoria\n");
        return;
    }

    // Contar refeicoes por funcionario
    NodeEscolha* escolha = escolhas;
    while (escolha) {
        contagem[escolha->escolha.num_funcionario]++;
        escolha = escolha->prox;
    }

    printf("+---------+-------------------------+------------+-------------+\n");
    printf("| Func.   | Nome                    | Refeicoes  | Despesa (E) |\n");
    printf("+---------+-------------------------+------------+-------------+\n");

    // Imprimir resultados
    for (int i = max_func; i >= 1; i--) {
        if (contagem[i] > 0) {
            func = funcionarios;
            while (func) {
                if (func->func.numero == i) {
                    // Calcula a despesa total para este funcionário
                    float despesa_total = 0;
                    NodeEscolha* escolha_atual = escolhas;
                    
                    while (escolha_atual) {
                        if (escolha_atual->escolha.num_funcionario == i) {
                            NodeEmenta* ementa_atual = ementas;
                            while (ementa_atual) {
                                if (strcmp(escolha_atual->escolha.dia, ementa_atual->ementa.dia) == 0) {
                                    // Encontra o valor correto para esta data
                                    float valor_refeicao = 5.00; // Começa com o valor inicial
                                    
                                    // Procura a última atualização válida para esta data
                                    for (int j = num_atualizacoes - 1; j >= 0; j--) {
                                        if (compararDatas(ementa_atual->ementa.data, atualizacoes[j].data_inicio) >= 0) {
                                            valor_refeicao = atualizacoes[j].valor;
                                            break;
                                        }
                                    }
                                    
                                    despesa_total += valor_refeicao;
                                    break;
                                }
                                ementa_atual = ementa_atual->prox;
                            }
                        }
                        escolha_atual = escolha_atual->prox;
                    }
                    
                    printf("| %-7d | %-23s | %-10d | %-11.2f |\n",
                        func->func.numero,
                        func->func.nome,
                        contagem[i],
                        despesa_total);
                    
                    total_refeicoes += contagem[i];
                    total_despesa += despesa_total;
                    break;
                }
                func = func->prox;
            }
        }
    }
    
    // Mostra o número total de refeições e despesa
    printf("+---------+-------------------------+------------+-------------+\n");
    printf("\nTotal de refeicoes servidas na semana: %d\n", total_refeicoes);
    printf("Total de despesa: %.2f Euros\n", total_despesa);
    printf("____________________________________________________\n");
    
    // Libera a memória alocada
    free(contagem);
}

void listarRefeicoesCalorias(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, 
                            int num_funcionario, const char* data_inicio, const char* data_fim) {
    NodeFunc* func = funcionarios;
    while (func && func->func.numero != num_funcionario)
        func = func->prox;

    if (!func) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    printf("\n=== Refeicoes e Calorias do Funcionario %d - %s ===\n", 
           num_funcionario, func->func.nome);
    printf("Dia    | Prato                  | Calorias\n");
    printf("------------------------------------------\n");

    int total_calorias = 0;
    int total_refeicoes = 0;

    NodeEscolha* escolha = escolhas;
    while (escolha) {
        if (escolha->escolha.num_funcionario == num_funcionario) {
            NodeEmenta* ementa = ementas;
            while (ementa) {
                if (strcmp(ementa->ementa.dia, escolha->escolha.dia) == 0) {
                    const char* nome_prato;
                    int calorias;

                    if (escolha->escolha.tipo_prato == 'C') {
                        nome_prato = ementa->ementa.prato_carne.nome;
                        calorias = ementa->ementa.prato_carne.calorias;
                    } else {
                        nome_prato = ementa->ementa.prato_peixe.nome;
                        calorias = ementa->ementa.prato_peixe.calorias;
                    }

                    printf("%-6s | %-20s | %d\n",
                           ementa->ementa.dia,
                           nome_prato,
                           calorias);
                    
                    total_calorias += calorias;
                    total_refeicoes++;
                    break;
                }
                ementa = ementa->prox;
            }
        }
        escolha = escolha->prox;
    }

    printf("------------------------------------------\n");
    printf("Total de refeicoes: %d\n", total_refeicoes);
    printf("Media de calorias: %.2f\n", total_refeicoes > 0 ? (float)total_calorias/total_refeicoes : 0);
    printf("------------------------------------------\n");
}

/**
 * @brief Calcula as médias de calorias consumidas por dia
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param data_inicio Data inicial do período
 * @param data_fim Data final do período
 * @details Calcula e exibe a média de calorias consumidas por dia no período especificado
 */
void calcularMediasCalorias(NodeEmenta* ementas, NodeEscolha* escolhas, 
                           const char* data_inicio, const char* data_fim) {
    printf("\n=== Media de Calorias por Dia ===\n");
    printf("Dia    | Media de Calorias\n");
    printf("---------------------------\n");

    NodeEmenta* ementa = ementas;
    while (ementa) {
        // Verifica se a data está dentro do período especificado
        if (compararDatas(ementa->ementa.data, data_inicio) >= 0 && 
            compararDatas(ementa->ementa.data, data_fim) <= 0) {
            
            int total_calorias = 0;
            int num_refeicoes = 0;

            NodeEscolha* escolha = escolhas;
            while (escolha) {
                if (strcmp(escolha->escolha.dia, ementa->ementa.dia) == 0) {
                    // Calcula as calorias baseado no tipo de prato escolhido
                    switch(escolha->escolha.tipo_prato) {
                        case 'C':
                            total_calorias += ementa->ementa.prato_carne.calorias;
                            break;
                        case 'P':
                            total_calorias += ementa->ementa.prato_peixe.calorias;
                            break;
                        case 'V':
                            total_calorias += ementa->ementa.prato_vegetariano.calorias;
                            break;
                        case 'D':
                            total_calorias += ementa->ementa.prato_dieta.calorias;
                            break;
                    }
                    num_refeicoes++;
                }
                escolha = escolha->prox;
            }

            if (num_refeicoes > 0) {
                // Calcula a média considerando apenas as refeições consumidas
                float media = (float)total_calorias / num_refeicoes;
                printf("%-6s | %.2f\n", ementa->ementa.dia, media);
            }
        }
        ementa = ementa->prox;
    }
    printf("---------------------------\n");
}

/**
 * @brief Gera uma tabela semanal de refeições para um utente
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param num_funcionario Número do funcionário
 * @details Gera e exibe uma tabela com as escolhas de refeições do funcionário para a semana
 */
void gerarTabelaSemanal(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, 
                        int num_funcionario) {
    NodeFunc* func = funcionarios;
    while (func && func->func.numero != num_funcionario)
        func = func->prox;

    if (!func) {
        printf("Funcionario nao encontrado.\n");
        return;
    }

    printf("\n=== Ementa Semanal do Funcionario %d - %s ===\n", 
           num_funcionario, func->func.nome);
    printf("------------------------------------------\n");
    printf("Dia    | Prato                  | Calorias\n");
    printf("------------------------------------------\n");

    NodeEmenta* ementa = ementas;
    while (ementa) {
        NodeEscolha* escolha = escolhas;
        while (escolha) {
            if (escolha->escolha.num_funcionario == num_funcionario &&
                strcmp(escolha->escolha.dia, ementa->ementa.dia) == 0) {
                switch(escolha->escolha.tipo_prato) {
                    case 'C':
                        printf("%-6s | %-20s | %d\n",
                               ementa->ementa.dia,
                               ementa->ementa.prato_carne.nome,
                               ementa->ementa.prato_carne.calorias);
                        break;
                    case 'P':
                        printf("%-6s | %-20s | %d\n",
                               ementa->ementa.dia,
                               ementa->ementa.prato_peixe.nome,
                               ementa->ementa.prato_peixe.calorias);
                        break;
                    case 'V':
                        printf("%-6s | %-20s | %d\n",
                               ementa->ementa.dia,
                               ementa->ementa.prato_vegetariano.nome,
                               ementa->ementa.prato_vegetariano.calorias);
                        break;
                    case 'D':
                        printf("%-6s | %-20s | %d\n",
                               ementa->ementa.dia,
                               ementa->ementa.prato_dieta.nome,
                               ementa->ementa.prato_dieta.calorias);
                        break;
                }
                break;
            }
            escolha = escolha->prox;
        }
        ementa = ementa->prox;
    }
    printf("------------------------------------------\n");
}

/**
 * @brief Gera uma tabela semanal detalhada da ementa usufruída por um utente
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param num_funcionario Número do funcionário
 * @details Exibe uma tabela com colunas para cada tipo de prato e calorias, linhas de 2ª a 6ª feira
 */
void gerarTabelaSemanalDetalhada(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario) {
    const char* dias_semana[5] = {"2Feira", "3Feira", "4Feira", "5Feira", "6Feira"};
    NodeFunc* func = funcionarios;
    while (func && func->func.numero != num_funcionario)
        func = func->prox;
    if (!func) {
        printf("Funcionario nao encontrado.\n");
        return;
    }
    printf(" __________________________________________________________________________");
    printf("\n *****  Tabela Semanal Detalhada do Funcionario %d - %s  ***** \n", num_funcionario, func->func.nome);
    printf(" __________________________________________________________________________\n");
    printf("\n+================================================================================================================================================+\n");
    printf("| %-7s| %-24s| %5s | %-24s| %5s | %-24s| %5s | %-24s| %5s |\n",
        "Dia", "Peixe", "Cal.", "Carne", "Cal.", "Dieta", "Cal.", "Vegetariano", "Cal.");
    printf("+================================================================================================================================================+\n");
    for (int i = 0; i < 5; i++) {
        NodeEmenta* ementa = ementas;
        while (ementa && stricmp(ementa->ementa.dia, dias_semana[i]) != 0)
            ementa = ementa->prox;
        char peixe[50] = "", carne[50] = "", dieta[50] = "", veget[50] = "";
        int cal_peixe = 0, cal_carne = 0, cal_dieta = 0, cal_veget = 0;
        if (ementa) {
            NodeEscolha* escolha = escolhas;
            while (escolha) {
                if (escolha->escolha.num_funcionario == num_funcionario &&
                    strcmp(escolha->escolha.dia, ementa->ementa.dia) == 0) {
                    switch(escolha->escolha.tipo_prato) {
                        case 'P':
                            strncpy(peixe, ementa->ementa.prato_peixe.nome, sizeof(peixe)-1);
                            cal_peixe = ementa->ementa.prato_peixe.calorias;
                            break;
                        case 'C':
                            strncpy(carne, ementa->ementa.prato_carne.nome, sizeof(carne)-1);
                            cal_carne = ementa->ementa.prato_carne.calorias;
                            break;
                        case 'D':
                            strncpy(dieta, ementa->ementa.prato_dieta.nome, sizeof(dieta)-1);
                            cal_dieta = ementa->ementa.prato_dieta.calorias;
                            break;
                        case 'V':
                            strncpy(veget, ementa->ementa.prato_vegetariano.nome, sizeof(veget)-1);
                            cal_veget = ementa->ementa.prato_vegetariano.calorias;
                            break;
                    }
                    break;
                }
                escolha = escolha->prox;
            }
        }
        printf("| %-7s| %-24s| %5d | %-24s| %5d | %-24s| %5d | %-24s| %5d |\n",
            dias_semana[i],
            peixe, cal_peixe > 0 ? cal_peixe : 0,
            carne, cal_carne > 0 ? cal_carne : 0,
            dieta, cal_dieta > 0 ? cal_dieta : 0,
            veget, cal_veget > 0 ? cal_veget : 0);
            printf("+------------------------------------------------------------------------------------------------------------------------------------------------+\n");
        }
    }

// Função auxiliar para comparar strings ignorando maiúsculas/minúsculas
int stricmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
