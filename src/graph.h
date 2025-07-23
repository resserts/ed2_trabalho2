#ifndef _GRAPH__
#define _GRAPH__

/*
Um Grafo  G e' constituido por um conjunto de vertices V e 
um conjunto de arestas E, denotado por G=(V,E). 

Pode-se associar um dado a arestas e a vertices de G.
A cada vertice e' associado um nome.

Podem ser definidos subgrafos de um dado grafo. Um subgrafo pode ser entendido 
como uma vis�o (ou filtro) sobre o grafo original. Ou, ainda, um subgrafo 
define (delimita) uma "regi�o" do grafo a ser acessada.

Cada subgrafo possui um nome. Um grafo pode pode possuir v�rios subgrafos. 
Arestas podem ser acrescentas ou retiradas do subgrafo
Existem tambem outras operacoes que possibilitam percorrer o subgrafo,
invocando funcoes quando arestas do grafo 
sao "descobertas", podendo, inclusive, interromper o percurso.

Este modulo faz parte de um trabalho de Estrutura de Daddos do 
curso de Ciencia da Computacao da Universidade Estadual de Londrina.
E' expressamente proibido o uso de ferramentas de IA para a sua implementacao.
A documentacao deste modulo deve ser melhorada.
*/

#include <stdbool.h>

#include "lista.h"

typedef void *Graph;
typedef int Node;
typedef void *Edge;
typedef void *Info;

#define MAX_STR_LEN 255

/*
  Invocado quando uma aresta � "descoberta"/"percorrida"/"classificada". 
  Tambem informa os tempos de descoberta e finalizacao
 */
typedef bool (*procEdge)(Graph g, Edge e, double* td, double* tf, void *extra); 

/*
  Invocado quando percurso e' recomecado
 */
typedef bool (*dfsRestarted)(Graph g, void *extra);

typedef double (*nodeWeight)(Graph g, double pastWeight, Edge e, Node objective); 


/*
    Cria um grafo com, no maximo, "nVert" vertices.
 */
Graph createGraph(int nVert, bool directed);


/*
    Retorna numero maximo de vertices que grafo g pode conter.
 */
int getMaxNodes(Graph g);


/*
    Retorna numero total de vertices adicionados ao grafo gr.
 */
int getTotalNodes(Graph g);


/*
    Adiciona um novo v�rtice ao grafo "g" com o nome "nome".
 */
Node addNode(Graph g, double x, double y, char* nome, Info info);


/*
    Retorna no' cujo de nome e' "nome". 
 */
Node getNode(Graph g, char* nome);


double getNodeX(Graph g, Node n);
double getNodeY(Graph g, Node n);

/*
 */
Info getNodeInfo(Graph g, Node n);


/*
 */
char *getNodeName(Graph g, Node n);


/*
 */
void setNodeInfo(Graph g, Node n, Info info);


/*
 */
Edge addEdge(Graph g, Node from, Node to, char* ldir, char* lesq, double cmp, double vm, char* nome, Info info);


/*
 */
Edge getEdge(Graph g, Node from, Node to);


/*
 */
Node getFromNode(Graph g, Edge e);

  
/*
 */  
Node getToNode(Graph g, Edge e);


/*
 */
Info getEdgeInfo(Graph g, Edge e);

double getEdgeComp(Graph g, Edge e);


double getEdgeVelMedia(Graph g, Edge e);

char* getEdgeName(Graph g, Edge e);

char* getEdgeLDir(Graph g, Edge e);

char* getEdgeLEsq(Graph g, Edge e);

/*
 */
void setEdgeInfo(Graph g, Edge e, Info info);


bool getEdgeHabil(Graph g, Edge e);


void setEdgeHabil(Graph g, Edge e, bool setar);


/*
 */
void removeEdge(Graph g, Edge e);


/*
 */
bool isAdjacent(Graph g, Node from, Node to);


/* 
   Adiciona 'a lista "nosAdjacentes" os nos adjacentes 'a "Node n".
 */
void adjacentNodes(Graph g, Node n, Lista nosAdjacentes);


/*
   Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que,
   x == node.
 */
void adjacentEdges(Graph g, Node n, Lista arestasAdjacentes);


/*
   Insere na lista "nomesNodes" os nomes atribuidos aos nos do grafo.
 */
void getNodeNames(Graph g, Lista nomesNodes);


/*
   Insere na lista "arestas", as arestas de g.
 */
void getEdges(Graph g, Lista arestas);


/*
   Faz percurso em profundidade sobre  g, a partir do no' node, classificando 
   as arestas do grafo, invocando a respectiva funcao.
      A busca em profundidade, eventualmente, pode produzir uma floresta.
   newTree e' invocada sempre que o percurso for retomado.
 */  
bool dfs(Graph g, Node n, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge,
	 procEdge crossEdge, dfsRestarted newTree, void *extra);


/* Percorre o grafo g em largura, a partir do no' node. discoverNode e' usada
   para a aresta (x,y) usada para "descobrir" o y.
 */
bool bfs(Graph g, Node n, Node discoverNode, void *extra);



Lista caminho(Graph g, Node from, Node to, nodeWeight nw, nodeWeight nc);


/*
   Destroi o grafo "g".
 */
void killDG(Graph g);

/*
 **********************
 * SUB-GRAFOS
 **********************
/*
    Calcula o subgrafo composto  pelos vertices cujos nomes estao no vetor nomesVerts
(nVerts e' o tamanho deste vetor). Caso comAresta seja true calcula o subgrafo 
induzido pelos vertices em nomesVers
 */
void  createSubgraphDG(Graph g, char *nomeSubgrafo, char *nomesVerts[], int nVert,
		       bool comArestas);


/*
    Adiciona a aresta ao subgrafo.
 */
Edge includeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e);

/*
  Retorna verdadeiro se a aresta "e" pertence ao subgrafo "nomeSubgrafo" do grafo g; 
  falso, caso contrario.
 */
bool existsEdgeSDG(Graph g, char *nomeSubgrafo, Edge e);

/*
  Retira a aresta "e" do subgrafo "nomeSubgrafo". Ou seja, desfaz a correspondente 
  operacao includeEdgeSg previamente executada. 
  Note que a aresta  "e" NAO e' removida do grafo g.
 */
void excludeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e);

/*
   Adiciona 'a lista "arestaAdjacentes" as arestas (x,y), tal que:
   x == node; x pertence ao subgrafo "nomeSubgrafo", (x,y) tambem e' aresta
   do subgrafo.
 */
void adjacentEdgesSDG(Graph g, char *nomeSubgrafo, Node n, Lista arestasAdjacentes);

/*
   Adiciona 'a lista "lstNodes" (Lista<Node>) os n�s do subgrafo "nomeSubgrafo".
 */
void getAllNodesSDG(Graph g, char *nomeSubgrafo,  Lista lstNodes);

/*
   Adiciona 'a lista "lstEdges" (Lista<Edge>) as arestas do subgrafo "nomeSubgrafo".
 */
void getAllEdgesSDG(Graph g, char *nomeSubgrafo, Lista lstEdges);

/*
  Novo grafo.
 */
Graph produceGraph(Graph g, char* nomeSubgrafo);
#endif
