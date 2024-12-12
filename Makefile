# Nome do executável
EXEC = main

# Compilador
CC = mpicc

# Flags do compilador
CFLAGS = -Wall -Wextra -O2

N = 8000000

NP = 4

# Arquivos fonte
SRC = main.c multi_partition.c util.c chrono.c

# Arquivos objeto gerados a partir dos arquivos fonte
OBJ = $(SRC:.c=.o)

# Regra padrão para compilar o projeto
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para rodar o programa com MPI
run: $(EXEC)
	mpirun -np $(NP) ./$(EXEC) $(N)

# Regra para verificar memória com Valgrind (para um processo local)
valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes ./$(EXEC) $(N)
