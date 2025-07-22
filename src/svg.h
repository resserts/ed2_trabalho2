#ifndef _SVG_H
#define _SVG_H

#include "smutreap.h"
#include "graph.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"

enum tipo{RETANGULO, CIRCULO, LINHA, TEXTO, QUADRA, VERTICE, PATH};
typedef void* Letra;

Letra criaLetra(double x, double y, char l);
void gerarSvg(SmuTreap t, char* fn, Lista letras, Graph g);

#endif
