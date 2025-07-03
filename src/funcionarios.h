/**
 * @file funcionarios.h
 * @brief Módulo de gestão de funcionários do sistema de refeições
 * @author [Seu Nome]
 * @date [Data]
 */

#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura que representa um funcionário
 */
typedef struct {
    int numero;         /**< Número identificador do funcionário */
    char nome[100];     /**< Nome completo do funcionário */
    char nif[10];       /**< NIF do funcionário */
    char telefone[15];  /**< Número de telefone do funcionário */
} Funcionario;

/**
 * @brief Estrutura de nó para lista ligada de funcionários
 */
typedef struct NodeFunc {
    Funcionario func;           /**< Dados do funcionário */
    struct NodeFunc* prox;      /**< Ponteiro para o próximo nó */
} NodeFunc;

/**
 * @brief Cria um novo nó de funcionário
 * @param func Estrutura Funcionario com os dados do funcionário
 * @return Ponteiro para o novo nó criado ou NULL em caso de erro
 */
NodeFunc* criarNoFunc(Funcionario func);

/**
 * @brief Carrega funcionários de um arquivo
 * @param filename Nome do arquivo a ser lido
 * @param formato_tab Flag indicando se o arquivo usa tabulação como separador
 * @return Ponteiro para o início da lista de funcionários ou NULL em caso de erro
 */
NodeFunc* carregarFuncionarios(const char* filename, int formato_tab);

/**
 * @brief Lista todos os funcionários cadastrados
 * @param lista Ponteiro para o início da lista de funcionários
 */
void listarFuncionarios(NodeFunc* lista);

/**
 * @brief Busca um funcionário pelo número
 * @param lista Ponteiro para o início da lista de funcionários
 * @param numero Número do funcionário a ser buscado
 * @return Ponteiro para o nó do funcionário encontrado ou NULL se não encontrado
 */
NodeFunc* buscarFuncionario(NodeFunc* lista, int numero);

/**
 * @brief Libera a memória alocada para a lista de funcionários
 * @param lista Ponteiro para o início da lista de funcionários
 */
void liberarFuncionarios(NodeFunc* lista);

/**
 * @brief Salva a lista de funcionários em arquivo
 * @param lista Ponteiro para o início da lista de funcionários
 * @param filename Nome do arquivo onde salvar
 * @param formato_bin Flag indicando se deve salvar em formato binário
 * @return 1 se sucesso, 0 se erro
 */
int salvarFuncionarios(NodeFunc* lista, const char* filename, int formato_bin);

#endif /* FUNCIONARIOS_H */
