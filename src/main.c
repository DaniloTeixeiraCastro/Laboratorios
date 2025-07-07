/**
 * @file main.c
 * @brief Sistema de Gestão do Espaço Social
 * @author [G36 - Epoca Especial]
 * @date 2025-06-20
 */

#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Limpa o buffer do teclado
 * @details Remove caracteres residuais do buffer de entrada
 */


/**
 * @brief Função principal do programa
 * @return 0 em caso de sucesso, outro valor em caso de erro
 * @details Implementa o menu principal do sistema com as seguintes funcionalidades:
 *          - Carregamento de dados de funcionários
 *          - Carregamento de ementas semanais
 *          - Carregamento de escolhas dos utentes
 *          - Listagem de refeições por dia
 *          - Listagem de utentes ordenados
 *          - Consulta de refeições por utente
 *          - Cálculo de médias de calorias
 */
int main() {
    int opcao;
    char opcao_str[8];
    
    // Inicializa o controle de refeições
    inicializarControleRefeicoes();

    do {
        system("cls"); // Limpa a tela (Windows)
        printf("\n=== Sistema de Gestao do Espaco Social ===\n");
        printf("------------------------------------------\n");
        printf("1. Carregar dados\n");
        printf("2. Listar refeicoes requeridas por dia\n");
        printf("3. Resumo semanal de consumo por utente\n");
        printf("4. Consultar refeicoes de um utente\n");
        printf("5. Calcular medias de calorias\n");
        printf("6. Gerar tabela semanal detalhada de um utente\n");
        printf("0. Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%7s", opcao_str);
        limparBuffer();

        int opcao = atoi(opcao_str);
        if (opcao == 1) {
            char subopcao;
            do {
                system("cls");
                printf("\n--- Carregar dados ---\n");
                printf("a - Carregar dados dos funcionarios\n");
                printf("b - Carregar ementa semanal\n");
                printf("c - Carregar escolhas dos utentes\n");
                printf("0 - Voltar\n");
                printf("---------------------\n");
                printf("Escolha uma opcao: ");
                scanf(" %c", &subopcao);
                limparBuffer();
                switch(subopcao) {
                    case 'a':
                        NodeFunc* nova_lista_func = carregarFuncionarios("C:/Projetos/Labs/data/funcionarios.txt");
                        if (nova_lista_func != NULL) {
                            funcionarios = nova_lista_func;
                            printf("\nDados dos funcionarios carregados com sucesso!\n");
                        } else {
                            printf("\nErro ao carregar dados dos funcionarios!\n");
                        }
                        pausar();
                        break;
                    case 'b':
                        NodeEmenta* nova_lista_ementas = carregarEmentas("C:/Projetos/Labs/data/ementas.txt");
                        if (nova_lista_ementas != NULL) {
                            atualizarEmentas(nova_lista_ementas);
                            printf("\nEmentas carregadas com sucesso!\n");
                        } else {
                            printf("\nErro ao carregar ementas!\n");
                        }
                        pausar();
                        break;
                    case 'c':
                        NodeEscolha* nova_lista_escolhas = carregarEscolhas("C:/Projetos/Labs/data/menu_escolhido.txt");
                        if (nova_lista_escolhas != NULL) {
                            escolhas = nova_lista_escolhas;
                            printf("\nEscolhas carregadas com sucesso!\n");
                        } else {
                            printf("\nErro ao carregar escolhas!\n");
                        }
                        pausar();
                        break;
                    case '0':
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
            } while(subopcao != '0');
        } else {
            switch(opcao) {
                case 2: {
                    if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                        printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                        pausar();
                        break;
                    }
                    char dia[10];
                    printf("Digite o dia da semana (2feira, 3feira, etc.): ");
                    scanf("%s", dia);
                    limparBuffer();
                    listarRefeicoesDia(funcionarios, ementas, escolhas, dia);
                    pausar();
                    break;
                }
                case 3:
                    if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                        printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                        pausar();
                        break;
                    }
                    listarRefeicoesServidasSemana(funcionarios, ementas, escolhas);
                    pausar();
                    break;
                case 4: {
                    if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                        printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                        pausar();
                        break;
                    }
                    int num_func, opcao_consulta;
                    char data_inicio[11], data_fim[11];
                    printf("Digite o numero do funcionario: ");
                    scanf("%d", &num_func);
                    limparBuffer();
                    printf("\nEscolha o tipo de consulta:\n");
                    printf("1. Intervalo de datas especifico\n");
                    printf("2. Semana completa\n");
                    printf("Opcao: ");
                    scanf("%d", &opcao_consulta);
                    limparBuffer();
                    if (opcao_consulta == 1) {
                        printf("Digite a data inicial (DD.MM.AAAA): ");
                        scanf("%s", data_inicio);
                        printf("Digite a data final (DD.MM.AAAA): ");
                        scanf("%s", data_fim);
                        listarRefeicoesCalorias(funcionarios, ementas, escolhas, num_func, data_inicio, data_fim);
                    } else if (opcao_consulta == 2) {
                        gerarTabelaSemanal(funcionarios, ementas, escolhas, num_func);
                    } else {
                        printf("\nOpcao invalida!\n");
                    }
                    pausar();
                    break;
                }
                case 5: {
                    if (ementas == NULL || escolhas == NULL) {
                        printf("\nErro: Carregue os arquivos de ementas e escolhas primeiro (b e c)!\n");
                        pausar();
                        break;
                    }
                    char data_inicio[11], data_fim[11];
                    printf("Digite a data inicial (DD.MM.AAAA): ");
                    scanf("%s", data_inicio);
                    printf("Digite a data final (DD.MM.AAAA): ");
                    scanf("%s", data_fim);                    
                    limparBuffer();
                    calcularMediasCalorias(ementas, escolhas, data_inicio, data_fim);
                    pausar();
                    break;
                }
                case 6: {
                    if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                        printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                        pausar();
                        break;
                    }
                    int num_func;
                    printf("Digite o numero do funcionario: ");
                    scanf("%d", &num_func);
                    limparBuffer();
                    gerarTabelaSemanalDetalhada(funcionarios, ementas, escolhas, num_func);
                    pausar();
                    break;
                }
                case 7: {
                    mostrarValorRefeicao();
                    pausar();
                    break;
                }
                case 8: {
                    float novo_valor;
                    printf("Digite o novo valor da refeição (€): ");
                    scanf("%f", &novo_valor);
                    limparBuffer();
                    atualizarValorRefeicao(novo_valor);
                    pausar();
                    break;
                }
                case 0:
                    printf("Programa encerrado.\n");
                    libertarMemoria(funcionarios, ementas, escolhas);
                    return 0;
                default:
                    printf("Opcao invalida!\n");
            }
        }
    } while(opcao != 0);

    libertarMemoria(funcionarios, ementas, escolhas);
    return 0;
}
