/**
 * @file main.c
 * @brief Sistema de Gestão do Espaço Social
 * @author [G36 - Epoca Especial]
 * @date 2025-06-20
 *
 * Este ficheiro implementa o menu principal do sistema, permitindo ao utilizador
 * carregar dados, consultar informações e efetuar operações relacionadas com a gestão
 * de refeições e utentes.
 */

#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Função principal do programa
 * @return 0 em caso de sucesso, outro valor em caso de erro
 *
 * Esta função apresenta o menu principal ao utilizador, permitindo-lhe:
 *  - Carregar dados dos funcionários
 *  - Carregar a ementa semanal
 *  - Carregar as escolhas dos utentes
 *  - Listar refeições requeridas por dia
 *  - Apresentar o resumo semanal de consumo por utente
 *  - Consultar refeições de um utente
 *  - Calcular médias de calorias
 *  - Gerar tabela semanal detalhada de um utente
 *  - Sair do programa
 *
 * O menu é apresentado em ciclo até o utilizador escolher a opção de sair.
 */
int main() {
    char opcao; /**< Variável que armazena a opção escolhida pelo utilizador no menu principal */
    
    // Inicializa o controlo de refeições (estrutura de dados global)
    inicializarControleRefeicoes();

    do {
        // Limpa o ecrã para melhor apresentação do menu
        system("cls");
        printf("\n=== Sistema de Gestao do Espaco Social ===\n");
        printf("------------------------------------------\n");
        printf("a. Carregar dados dos funcionarios\n");
        printf("b. Carregar ementa semanal\n");
        printf("c. Carregar escolhas dos utentes\n");
        printf("2. Listar refeicoes requeridas por dia\n");
        printf("3. Resumo semanal de consumo por utente\n");
        printf("4. Consultar refeicoes de um utente\n");
        printf("5. Calcular medias de calorias\n");
        printf("6. Gerar tabela semanal detalhada de um utente\n");
        printf("0. Sair\n");
        printf("------------------------------------------\n");
        printf("Escolha uma opcao: ");
        // Lê a opção do utilizador (aceita letras e números)
        scanf(" %c", &opcao);
        limparBuffer();

        switch(opcao) {
            case 'a': {
                /**
                 * @brief Carrega os dados dos funcionários a partir do ficheiro
                 *
                 * Se a leitura for bem-sucedida, atualiza a lista global de funcionários.
                 */
                NodeFunc* nova_lista_func = carregarFuncionarios("data/funcionarios.txt");
                if (nova_lista_func != NULL) {
                    funcionarios = nova_lista_func;
                    printf("\nDados dos funcionarios carregados com sucesso!\n");
                } else {
                    printf("\nErro ao carregar dados dos funcionarios!\n");
                }
                pausar();
                break;
            }
            case 'b': {
                /**
                 * @brief Carrega a ementa semanal a partir do ficheiro
                 *
                 * Se a leitura for bem-sucedida, atualiza a lista global de ementas.
                 */
                NodeEmenta* nova_lista_ementas = carregarEmentas("data/ementas.txt");
                if (nova_lista_ementas != NULL) {
                    atualizarEmentas(nova_lista_ementas);
                    printf("\nEmentas carregadas com sucesso!\n");
                } else {
                    printf("\nErro ao carregar ementas!\n");
                }
                pausar();
                break;
            }
            case 'c': {
                /**
                 * @brief Carrega as escolhas dos utentes a partir do ficheiro
                 *
                 * Se a leitura for bem-sucedida, atualiza a lista global de escolhas.
                 */
                NodeEscolha* nova_lista_escolhas = carregarEscolhas("data/menu_escolhido.txt");
                if (nova_lista_escolhas != NULL) {
                    escolhas = nova_lista_escolhas;
                    printf("\nEscolhas carregadas com sucesso!\n");
                } else {
                    printf("\nErro ao carregar escolhas!\n");
                }
                pausar();
                break;
            }
            case '2': {
                /**
                 * @brief Lista as refeições requeridas por dia
                 *
                 * Solicita ao utilizador o dia da semana e apresenta as refeições desse dia.
                 * Só é possível se todos os dados estiverem carregados.
                 */
                if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                    printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                    pausar();
                    break;
                }
                char dia[10]; /**< Armazena o dia da semana introduzido pelo utilizador */
                printf("Digite o dia da semana (2feira, 3feira, etc.): ");
                scanf("%s", dia);
                limparBuffer();
                listarRefeicoesDia(funcionarios, ementas, escolhas, dia);
                pausar();
                break;
            }
            case '3': {
                /**
                 * @brief Apresenta o resumo semanal de consumo por utente
                 *
                 * Só é possível se todos os dados estiverem carregados.
                 */
                if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                    printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                    pausar();
                    break;
                }
                listarRefeicoesServidasSemana(funcionarios, ementas, escolhas);
                pausar();
                break;
            }
            case '4': {
                /**
                 * @brief Consulta as refeições de um utente
                 *
                 * Permite ao utilizador consultar refeições por intervalo de datas ou semana completa.
                 * Só é possível se todos os dados estiverem carregados.
                 */
                if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                    printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                    pausar();
                    break;
                }
                int num_func, opcao_consulta; /**< Número do funcionário e opção de consulta */
                char data_inicio[11], data_fim[11]; /**< Datas para consulta por intervalo */
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
            case '5': {
                /**
                 * @brief Calcula as médias de calorias num intervalo de datas
                 *
                 * Só é possível se os dados de ementas e escolhas estiverem carregados.
                 */
                if (ementas == NULL || escolhas == NULL) {
                    printf("\nErro: Carregue os arquivos de ementas e escolhas primeiro (b e c)!\n");
                    pausar();
                    break;
                }
                char data_inicio[11], data_fim[11]; /**< Datas para o cálculo das médias */
                printf("Digite a data inicial (DD.MM.AAAA): ");
                scanf("%s", data_inicio);
                printf("Digite a data final (DD.MM.AAAA): ");
                scanf("%s", data_fim);                    
                limparBuffer();
                calcularMediasCalorias(ementas, escolhas, data_inicio, data_fim);
                pausar();
                break;
            }
            case '6': {
                /**
                 * @brief Gera a tabela semanal detalhada de um utente
                 *
                 * Só é possível se todos os dados estiverem carregados.
                 */
                if (funcionarios == NULL || ementas == NULL || escolhas == NULL) {
                    printf("\nErro: Carregue todos os arquivos primeiro (a, b e c)!\n");
                    pausar();
                    break;
                }
                int num_func; /**< Número do funcionário a consultar */
                printf("Digite o numero do funcionario: ");
                scanf("%d", &num_func);
                limparBuffer();
                gerarTabelaSemanalDetalhada(funcionarios, ementas, escolhas, num_func);
                pausar();
                break;
            }
            case '0':
                /**
                 * @brief Sai do programa, libertando toda a memória alocada
                 */
                printf("Programa encerrado.\n");
                libertarMemoria(funcionarios, ementas, escolhas);
                return 0;
            default:
                /**
                 * @brief Opção inválida introduzida pelo utilizador
                 */
                printf("Opcao invalida!\n");
        }
    } while(opcao != '0');

    // Liberta toda a memória alocada antes de terminar o programa
    libertarMemoria(funcionarios, ementas, escolhas);
    return 0;
}
