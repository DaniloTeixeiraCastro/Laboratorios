# Makefile principal do projeto Laboratorios

# Diretórios
SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
INCLUDE_DIR = $(SRC_DIR)/include

# Arquivos fonte
MAIN_SRC = $(SRC_DIR)/main.c
LIB_SRC = $(LIB_DIR)/funcoes.c

# Arquivos de saída
EXECUTABLE = programa.exe

# Definição do compilador
CC = gcc

# Flags de compilação
CFLAGS = -g -Wall -Wextra -fdiagnostics-color=always

# Regra padrão
all: $(EXECUTABLE)

# Regra para compilação
$(EXECUTABLE): $(MAIN_SRC) $(LIB_SRC)
	$(CC) $(CFLAGS) $(MAIN_SRC) $(LIB_SRC) -I$(INCLUDE_DIR) -o $(EXECUTABLE)

# Limpeza
.PHONY: clean
clean:
	if exist $(EXECUTABLE) del $(EXECUTABLE)

# Limpeza completa
.PHONY: distclean
distclean: clean
	if exist $(SRC_DIR)\*.o del $(SRC_DIR)\*.o

# Recompilar todo o projeto
.PHONY: rebuild
rebuild: clean all

# Compilar e executar
.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)
