# Sistema de Gestão do Espaço Social 🏢

## 📋 Índice
- [Sobre o Projecto](#sobre-o-projecto)
- [Funcionalidades](#funcionalidades)
- [Estrutura do Projecto](#estrutura-do-projecto)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Instalação e Execução](#instalação-e-execução)
- [Documentação](#documentação)
- [Equipa](#equipa)

## 🎯 Sobre o Projecto
Este projecto foi desenvolvido no âmbito da unidade curricular de Laboratórios de Informática do curso de Engenharia de Sistemas Informáticos no Instituto Politécnico do Cávado e do Ave. Consiste num sistema de gestão para um espaço social, permitindo a gestão eficiente de funcionários, ementas e escolhas de refeições.

## ⚙️ Funcionalidades
### Gestão de Funcionários
- Carregamento de dados dos funcionários

### Gestão de Ementas
- Carregamento de ementas semanais
- Visualização de refeições requeridas e disponíveis
- Gestão do planeamento alimentar

### Sistema de Refeições
- Carregamento das escolhas dos utentes
- Listagem de refeições por dia
- Consulta personalizada por utente
- Relatórios semanais e por intervalo de datas
- Estatísticas sobre a média de calorias consumidas


## 🛠️ Tecnologias Utilizadas
- Linguagem C
- Bibliotecas standard C
- Estruturas de dados dinâmicas (listas ligadas)
- Sistema de ficheiros para persistência de dados
- LaTeX para documentação técnica

## 📝 Instalação e Execução

### Pré-requisitos
1. **MinGW (para Windows)**
   - Download do [MinGW Installer](https://sourceforge.net/projects/mingw/)
   - Durante a instalação, selecionar:
     - mingw32-base
     - mingw32-gcc-g++
     - mingw32-make
   - Adicionar o MinGW ao PATH do sistema:
     1. Abrir o Painel de Controlo
     2. Sistema e Segurança > Sistema
     3. Configurações avançadas de sistema
     4. Variáveis de ambiente
     5. Em "Variáveis do sistema", encontrar PATH
     6. Adicionar: `C:\MinGW\bin`

2. **MiKTeX (para compilar o relatório)**
   - Download e instalar o [MiKTeX](https://miktex.org/download)

### Compilação e Execução

O projeto possui dois Makefiles:
1. `src/Makefile`: Para compilar o programa em C
2. `doc/latex/Makefile`: Para compilar o relatório em LaTeX

#### Compilar o Programa (pasta raiz do projeto)
```bash
# Navegar até a pasta raiz do projeto
cd Laboratorios

# Compilar o programa
mingw32-make

# Limpar arquivos compilados
mingw32-make clean

# Recompilar todo o projeto
mingw32-make rebuild

# Compilar e executar
mingw32-make run
```

#### Compilar o Relatório (pasta doc/latex)
```bash
# Naveguar até a pasta do relatório
cd doc/latex

# Compilar o PDF
mingw32-make

# Limpar arquivos temporários
mingw32-make clean

# Recompilar o relatório
mingw32-make rebuild
```

**Nota**: No Windows, usar `mingw32-make` em vez de apenas `make`

### 📁 Estrutura do Projeto
```
.
├── doc/                   # Documentação com o relatório
│   ├── html/              # Documentação em HTML
│   │   └── index.html     # Página inicial da documentação
│   └── latex/             # Documentação em LaTeX
│       ├── Makefile       # Makefile para compilar o relatório LaTeX
│       └── refman.pdf     # Documentação em PDF do relatório LaTeX
├── data/                  # Arquivos de dados
│   ├── funcionarios.txt   # Dados dos funcionários
│   ├── ementas.txt        # Ementas semanais
│   └── menu_escolhido.txt # Escolhas dos utentes
├── Relatorio/             # Documentação gerada pelo Doxygen
│   └── Laboratorio.pdf    # Documentação em PDF
├── Makefile               # Makefile principal para compilar e executar o projeto
└── src/                   # Código fonte da solução
    ├── include/           # Arquivos de cabeçalho (.h)
    │   └── estruturas.h   # Definições das estruturas de dados
    ├── lib/               # Bibliotecas
    │   └── funcoes.c      # Implementação das funções
    └── main.c             # Programa principal
```

## 👥 Equipa - grupo *36*
- Filipe Ferreira (25275)
- Danilo Castro (25447)
- Vitor Leite (25453)

## 📝 Notas Adicionais
- O sistema foi desenvolvido com foco na eficiência e facilidade de utilização
- Implementa boas práticas de programação e gestão de memória
- Inclui validação de dados e tratamento de erros
- Documentação técnica completa disponível no relatório em LaTeX
