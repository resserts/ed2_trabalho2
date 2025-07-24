#ifndef _SVG_H
#define _SVG_H

#include "smutreap.h"
#include "graph.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"

/* Tipos possiveis das Infos
 */ 
enum tipo{RETANGULO, CIRCULO, LINHA, TEXTO, QUADRA, VERTICE, PATH};
//typedef void* Letra;

//Letra criaLetra(double x, double y, char l);
/* Gera um svg fn a partir da Smutreap t, da Lista paths e de Graph g
 */ 
void gerarSvg(SmuTreap t, char* fn, Lista paths, Graph g);

#endif
