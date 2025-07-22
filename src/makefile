PROJ_NAME=ted
ALUNO=tiagoms
LIBS=
OBJETOS=main.o smutreap.o query.o via.o boundingBox.o graph.o lista.o retangulo.o path.o quadra.o circulo.o texto.o linha.o svg.o geo.o 
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
