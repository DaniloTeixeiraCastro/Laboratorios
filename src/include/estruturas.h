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
    int numero;
    char nome[MAX_NOME];
    int nif;
    int telefone;
} Funcionario;

// Estrutura para Prato
typedef struct {
    char nome[MAX_NOME];
    int calorias;
} Prato;

// Estrutura para Ementa
typedef struct {
    char dia[10];
    char data[11];
    Prato prato_carne;
    Prato prato_peixe;
    Prato prato_dieta;
    Prato prato_vegetariano;
} Ementa;

// Estrutura para Escolha
typedef struct {
    char dia[10];
    int num_funcionario;
    char tipo_prato; // 'C' para carne, 'P' para peixe...
} Escolha;

// Estrutura para armazenar o valor da refeição
struct ControleRefeicao {
    float valor;
    char data_ultima_atualizacao[11];
};

// Nó para lista de funcionários
typedef struct NodeFunc {
    Funcionario func;
    struct NodeFunc* prox;
} NodeFunc;

// Nó para lista de ementas
typedef struct NodeEmenta {
    Ementa ementa;
    struct NodeEmenta* prox;
} NodeEmenta;

// Nó para lista de escolhas
typedef struct NodeEscolha {
    Escolha escolha;
    struct NodeEscolha* prox;
} NodeEscolha;

// Protótipos das funções
NodeFunc* criarNoFunc(Funcionario func);
NodeFunc* carregarFuncionarios(const char* filename);
NodeEmenta* carregarEmentas(const char* filename);
NodeEscolha* carregarEscolhas(const char* filename);
void atualizarEmentas(NodeEmenta* nova_lista);
NodeEmenta* obterEmentas();
void listarRefeicoesDia(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, const char* dia);
void listarRefeicoesServidasSemana(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas);
void listarRefeicoesCalorias(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario, const char* data_inicio, const char* data_fim);
void calcularMediasCalorias(NodeEmenta* ementas, NodeEscolha* escolhas, const char* data_inicio, const char* data_fim);
void gerarTabelaSemanal(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario);
void gerarTabelaSemanalDetalhada(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas, int num_funcionario);
void libertarMemoria(NodeFunc* funcionarios, NodeEmenta* ementas, NodeEscolha* escolhas);

// Estruturas e funções para controle de refeições
void inicializarControleRefeicoes();
int validarRefeicaoDia(const char* dia);
void atualizarValorRefeicao(float novo_valor);
void mostrarValorRefeicao();

// Protótipos de funções uteis
void limparBuffer();
void pausar();

extern NodeFunc* funcionarios;
extern NodeEmenta* ementas;
extern NodeEscolha* escolhas;

#endif
