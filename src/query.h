#ifndef _QUERY_H
#define _QUERY_H
#include "smutreap.h"
#include "graph.h"

/* Executa os comandos do arquivo query fn sobre o Graph g, faz alteracoes 
 * na Smutreap t e na Lista paths e salva os arquivos gerados em saida.
 */
void comandosQuery(SmuTreap t, Graph g, Lista paths, char* fn, char* saida);

#endif
