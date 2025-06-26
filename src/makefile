PROJ_NAME=ted
ALUNO=tiagoms
LIBS=
OBJETOS=main.o graph.o lista.o 
# compilador
CC=gcc

# Flags

CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration

LDFLAGS=-O0 -lm
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)
%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

#
# COLOCAR DEPENDENCIAS DE CADA MODULO
#
# Exemplo: suponha que o arquivo a.c possua os seguintes includes:
#
# #include "a.h"
# #include "b.h"
# #include "c.h"
#
# a.o: a.h b.h c.h a.c
#
