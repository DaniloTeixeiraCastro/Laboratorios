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
- Modularização do código, organizado em ficheiros .h e .c
- Makefile para compilação e execução
- Doxygen para documentação técnica
- LaTeX para documentação em PDF

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
├── Doxyfile              # Configuração do Doxygen para documentação
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

## 🤝 Estratégia de Colaboração e Divisão de Tarefas
O desenvolvimento do projeto foi realizado de forma colaborativa, utilizando o repositório Git para garantir o versionamento e integração contínua do código. As tarefas foram distribuídas da seguinte forma:

- **Filipe Ferreira:** Estruturas de dados, funções de manipulação de listas ligadas, validação de dados e documentação técnica (Doxygen).
- **Danilo Castro:** Implementação do menu principal, integração das funcionalidades, testes de carregamento de dados e geração de relatórios.
- **Vitor Leite:** Gestão de ementas e escolhas, estatísticas, tratamento de ficheiros e documentação em LaTeX.

O grupo utilizou branches para desenvolvimento paralelo, revisões de código via pull requests e reuniões semanais para alinhamento das tarefas. A integração das contribuições foi feita através de merges frequentes, garantindo que todos os membros participassem ativamente em todas as fases do projeto.

## 🏁 Conclusão
O projeto permitiu consolidar conhecimentos de programação em C, gestão de memória, modularização, documentação técnica e colaboração em equipa. O sistema desenvolvido cumpre os requisitos propostos, apresenta robustez na validação de dados e flexibilidade na análise estatística. O uso de ferramentas como Git, Doxygen e LaTeX contribuiu para a organização, qualidade e apresentação do trabalho.
