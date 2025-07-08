/**
 * @file estruturas.h
 * @brief Definições de estruturas e protótipos para o sistema de gestão do espaço social
 *
 * Este ficheiro contém as definições das estruturas de dados principais
 * (Funcionário, Prato, Ementa, Escolha, listas ligadas) e os protótipos
 * das funções utilizadas em todo o sistema.
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_LINE 256
#define LIMITE_REFEICOES_DIARIO 200

// Estrutura para Funcionário
typedef struct {
    int numero; /**< Número do funcionário */
    char nome[MAX_NOME]; /**< Nome do funcionário */
    int nif; /**< Número de Identificação Fiscal do funcionário */
    int telefone; /**< Número de telefone do funcionário */
} Funcionario;

/** Estrutura para Prato
 * 
 * Esta estrutura representa um prato disponível na ementa, contendo
 * informações sobre o seu nome e o número de calorias que possui.
 */
typedef struct {
    char nome[MAX_NOME]; /**< Nome do prato */
    int calorias; /**< Número de calorias do prato */
} Prato;

/** Estrutura para Ementa
 * 
 * A estrutura Ementa contém a descrição de uma ementa diária, incluindo
 * o dia da semana, a data e os pratos disponíveis: carne, peixe, dieta
 * e vegetariano.
 */
typedef struct {
    char dia[10]; /**< Dia da semana */
    char data[11]; /**< Data no formato AAAA-MM-DD */
    Prato prato_carne; /**< Prato de carne */
    Prato prato_peixe; /**< Prato de peixe */
    Prato prato_dieta; /**< Prato da dieta */
    Prato prato_vegetariano; /**< Prato vegetariano */
} Ementa;

/** Estrutura para Escolha
 * 
 * A estrutura Escolha regista a escolha de um funcionário para um determinado
 * dia, incluindo o tipo de prato selecionado (carne, peixe, etc.).
 */
typedef struct {
    char dia[10]; /**< Dia da semana */
    int num_funcionario; /**< Número do funcionário que fez a escolha */
    char tipo_prato; /**< Tipo de prato escolhido: 'C' para carne, 'P' para peixe, etc. */
} Escolha;

/** Estrutura para armazenar o valor da refeição
 * 
 * Esta estrutura é utilizada para controlar o valor monetário das refeições,
 * armazenando o valor atual e a data da última atualização.
 */
struct ControleRefeicao {
    float valor; /**< Valor da refeição */
    char data_ultima_atualizacao[11]; /**< Data da última atualização do valor */
};

// Nó para lista de funcionários
typedef struct NodeFunc {
    Funcionario func; /**< Estrutura do funcionário */
    struct NodeFunc* prox; /**< Ponteiro para o próximo nó da lista */
} NodeFunc;

// Nó para lista de ementas
typedef struct NodeEmenta {
    Ementa ementa; /**< Estrutura da ementa */
    struct NodeEmenta* prox; /**< Ponteiro para o próximo nó da lista */
} NodeEmenta;

// Nó para lista de escolhas
typedef struct NodeEscolha {
    Escolha escolha; /**< Estrutura da escolha */
    struct NodeEscolha* prox; /**< Ponteiro para o próximo nó da lista */
} NodeEscolha;

/** @brief Cria um novo nó para a lista de funcionários
 *
 * Esta função aloca memória para um novo nó da lista de funcionários,
 * inicializa os seus valores e devolve o ponteiro para o nó criado.
 *
 * @param func Estrutura do funcionário a ser armazenado no nó
 * @return Ponteiro para o novo nó da lista de funcionários
 */
NodeFunc* criarNoFunc(Funcionario func);

/** @brief Carrega a lista de funcionários a partir de um ficheiro
 *
 * Esta função lê um ficheiro com a informação dos funcionários e
 * cria a lista de funcionários correspondente.
 *
 * @param filename Nome do ficheiro a ser lido
 * @return Ponteiro para a lista de funcionários carregada
 */
NodeFunc* carregarFuncionarios(const char* filename);

/** @brief Carrega a lista de ementas a partir de um ficheiro
 *
 * Esta função lê um ficheiro com a informação das ementas e
 * cria a lista de ementas correspondente.
 *
 * @param filename Nome do ficheiro a ser lido
 * @return Ponteiro para a lista de ementas carregada
 */
NodeEmenta* carregarEmentas(const char* filename);

/** @brief Carrega a lista de escolhas a partir de um ficheiro
 *
 * Esta função lê um ficheiro com a informação das escolhas e
 * cria a lista de escolhas correspondente.
 *
 * @param filename Nome do ficheiro a ser lido
 * @return Ponteiro para a lista de escolhas carregada
 */
NodeEscolha* carregarEscolhas(const char* filename);

/** @brief Atualiza as ementas com uma nova lista
 *
 * Esta função substitui a lista atual de ementas por uma nova lista,
 * libertando a memória da lista antiga.
 *
 * @param nova_lista Ponteiro para a nova lista de ementas
 */
void atualizarEmentas(NodeEmenta* nova_lista);

/** @brief Obtém a lista atual de ementas
 *
 * Esta função devolve a lista atual de ementas.
 *
 * @return Ponteiro para a lista atual de ementas
 */
NodeEmenta* obterEmentas();

/** @brief Lista as refeições de um determinado dia
 *
 * Esta função exibe todas as refeições servidas num determinado dia,
 * para todos os funcionários.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param dia Dia para o qual se pretende listar as refeições
 */
void listarRefeicoesDia(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, const char* dia);

/** @brief Lista as refeições servidas durante uma semana
 *
 * Esta função exibe todas as refeições servidas durante uma semana,
 * para todos os funcionários.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 */
void listarRefeicoesServidasSemana(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas);

/** @brief Lista as refeições com um determinado número de calorias
 *
 * Esta função exibe todas as refeições que têm um número de calorias
 * dentro de um intervalo especificado, para um determinado funcionário
 * e intervalo de datas.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param num_funcionario Número do funcionário
 * @param data_inicio Data de início do intervalo
 * @param data_fim Data de fim do intervalo
 */
void listarRefeicoesCalorias(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario, const char* data_inicio, const char* data_fim);

/** @brief Calcula as médias de calorias das refeições
 *
 * Esta função calcula e exibe as médias de calorias das refeições
 * servidas dentro de um intervalo de datas especificado.
 *
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param data_inicio Data de início do intervalo
 * @param data_fim Data de fim do intervalo
 */
void calcularMediasCalorias(NodeEmenta* ementas, NodeEscolha* escolhas, const char* data_inicio, const char* data_fim);

/** @brief Gera uma tabela semanal de refeições
 *
 * Esta função gera uma tabela com todas as refeições servidas durante
 * uma semana, para um determinado funcionário.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param num_funcionario Número do funcionário
 */
void gerarTabelaSemanal(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario);

/** @brief Gera uma tabela semanal detalhada de refeições
 *
 * Esta função gera uma tabela detalhada com todas as refeições servidas
 * durante uma semana, incluindo informações sobre calorias, para um
 * determinado funcionário.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 * @param num_funcionario Número do funcionário
 */
void gerarTabelaSemanalDetalhada(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario);

/** @brief Liberta a memória utilizada pelas listas
 *
 * Esta função liberta a memória alocada para as listas de funcionários,
 * ementas e escolhas.
 *
 * @param funcionarios Lista de funcionários
 * @param ementas Lista de ementas
 * @param escolhas Lista de escolhas
 */
void libertarMemoria(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas);

/** @brief Inicializa o controlo de refeições
 *
 * Esta função inicializa o sistema de controlo de refeições, definindo
 * o valor padrão da refeição e a data da última atualização.
 */
void inicializarControleRefeicoes();

/** @brief Valida um dia para registo de refeição
 *
 * Esta função verifica se um determinado dia é válido para o registo
 * de uma refeição, com base nas regras do sistema.
 *
 * @param dia Dia da semana a ser validado
 * @return 1 se o dia for válido, 0 caso contrário
 */
int validarRefeicaoDia(const char* dia);

/** @brief Atualiza o valor da refeição
 *
 * Esta função atualiza o valor monetário da refeição, armazenando
 * a nova avaliação e a data da atualização.
 *
 * @param novo_valor Novo valor da refeição
 */
void atualizarValorRefeicao(float novo_valor);

/** @brief Mostra o valor atual da refeição
 *
 * Esta função exibe o valor monetário atual da refeição.
 */
void mostrarValorRefeicao();

// Protótipos de funções uteis
void limparBuffer();
void pausar();

extern NodeFunc* funcionarios;
extern NodeEmenta* ementas;
extern NodeEscolha* escolhas;

#endif
