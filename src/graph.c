#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "lista.h"

typedef struct {
     char nome[MAX_STR_LEN];
     Lista adjacentes;
     double x, y;
     Info info;
}NodeSt;
typedef struct {
     char nome[MAX_STR_LEN];
     char ldir[MAX_STR_LEN];
     char lesq[MAX_STR_LEN];
     Node n1, n2;
     double comp;
     double vm;
     Info info;
}EdgeSt;
typedef struct {
     bool directed;
     int maxNodes;
     NodeSt* nodes;
     Lista* edges;
}GraphSt;

Graph createGraph(int nVert, bool directed){
     GraphSt* gt=malloc(sizeof(GraphSt));
     gt->directed=directed;
     gt->maxNodes=nVert;
     gt->nodes=calloc(sizeof(NodeSt), gt->maxNodes);
     gt->edges=calloc(sizeof(Lista), gt->maxNodes);
     for(int i=0; i<gt->maxNodes; i++){
          gt->edges[i]=criaLista();
     }
     return gt;
}

int getMaxNodes(Graph g){
     GraphSt* gSt=g;
     return gSt->maxNodes;
}

int getTotalNodes(Graph g){
     GraphSt* gt=g;
     int totalNodes=0;
     for(int i=0; i<gt->maxNodes; i++){
          if(gt->nodes[i].nome[0]==0){
               break;
          }
          totalNodes++;
     }
     return totalNodes;
}

Node addNode(Graph g, double x, double y, char* nome, Info info){
     if(getTotalNodes(g)>=getMaxNodes(g)){
          printf("tacheio\n");
          return -1;
     }
     int id=getTotalNodes(g);
     GraphSt* gt=g;
     strcpy(gt->nodes[id].nome, nome);
     gt->nodes[id].info=info;
     gt->nodes[id].adjacentes=criaLista();
     gt->nodes[id].x=x;
     gt->nodes[id].y=y;
     return id;
}

Node getNode(Graph g, char* nome){
     GraphSt* gt=g;
     NodeSt* nt=g;
     for(int i=0; i<gt->maxNodes; i++){
          if(strcmp(gt->nodes[i].nome, nome)==0){
               return i;
          }
     }
     return -1;
}

double getNodeX(Graph g, Node n){
     GraphSt* gt=g;
     return gt->nodes[n].x;
}
double getNodeY(Graph g, Node n){
     GraphSt* gt=g;
     return gt->nodes[n].y;
}

Info getNodeInfo(Graph g, Node n){
     GraphSt* gt=g;
     return gt->nodes[n].info;
}


char *getNodeName(Graph g, Node n){
     GraphSt* gt=g;
     return gt->nodes[n].nome;
}


void setNodeInfo(Graph g, Node n, Info info){
     GraphSt* gt=g;
     gt->nodes[n].info=info;
}


Edge addEdge(Graph g, Node from, Node to, char* ldir, char* lesq, double cmp, double vm, char* nome, Info info){
     GraphSt* gt=g;
     EdgeSt* et=malloc(sizeof(EdgeSt));
     et->n1=from;
     et->n2=to;
     strcpy(et->ldir, ldir);
     strcpy(et->lesq, lesq);
     et->comp=cmp;
     et->vm=vm;
     strcpy(et->nome, nome);
     et->info=info;
     insertList(gt->edges[from], et, 0);     
     int* adj=malloc(sizeof(int));
     *adj=et->n2;
     insertList(gt->nodes[et->n1].adjacentes, adj, 0);
     return et;
}


Edge getEdge(Graph g, Node from, Node to){
     GraphSt* gt=g;
     for(int i=0; getValor(gt->edges[from], i); i++){
          EdgeSt* et=getValor(gt->edges[from], i);
          if(et->n1==from && et->n2==to){
               return et;
          }
     }
     return NULL;
}


Node getFromNode(Graph g, Edge e){
     EdgeSt* et=e;
     return et->n1;
}

  
Node getToNode(Graph g, Edge e){
     EdgeSt* et=e;
     return et->n2;
}


Info getEdgeInfo(Graph g, Edge e){
     EdgeSt* et=e;
     return et->info;
}


void setEdgeInfo(Graph g, Edge e, Info info){
     EdgeSt* et=e;
     et->info=info;
}

void removeEdge(Graph g, Edge e){
     GraphSt* gt=g;
     for(int i=0; getValor(gt->edges, i); i++){
          EdgeSt* et=getValor(gt->edges, i);
          if(et==e){
               for(int j=0; getValor(gt->nodes[et->n1].adjacentes, j); j++){
                    int* to=getValor(gt->nodes[et->n1].adjacentes, j);
                    if(*to==et->n2){
                         removeList(gt->nodes[et->n1].adjacentes, j);
                         free(to);
                         break;
                    }
               }
               removeList(gt->edges[et->n1], i);
               free(e);
          }
     }
}


bool isAdjacent(Graph g, Node from, Node to){
     if(getEdge(g, from, to)!=NULL){
          return true;
     }
     return false;
}


void adjacentNodes(Graph g, Node n, Lista nosAdjacentes){
     GraphSt* gt=g;
     for(int i=0; getValor(gt->nodes[n].adjacentes, i); i++){
          insertList(nosAdjacentes, getValor(gt->nodes[n].adjacentes, i), i);
     }
}


void adjacentEdges(Graph g, Node n, Lista arestasAdjacentes){
     GraphSt* gt=g;
     EdgeSt* et;
     for (int i=0; et=getValor(gt->edges[n], i); i++) {
          insertList(arestasAdjacentes, et, 0);
     }
}


void getNodeNames(Graph g, Lista nomesNodes){
     GraphSt* gt=g;
     int max=getTotalNodes(g);
     for(int i=0; i<max; i++){
          insertList(nomesNodes, gt->nodes[i].nome, i);
     }
}


void getEdges(Graph g, Lista arestas){
     GraphSt* gt=g;
     EdgeSt* et;
     for (int j=0; j<getMaxNodes(g); j++) {
          for (int i=0; et=getValor(gt->edges[j], i); i++) {
               insertList(arestas, et, i);
          }
     }
}

typedef struct{
     char cor;
     int td, tf;
     Node pai;
}dfsNInfo;

bool dfsaux(GraphSt* gt, Node n, dfsNInfo* infos, int* tempo, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge,
	 procEdge crossEdge, void *extra){

     *tempo=*tempo+1;
     infos[n].td=*tempo;
     infos[n].cor='c';
     Node* vis;
     double td, tf;
     //printf("simple dnfaux: %i\n", *tempo);
     for(int i=0; vis=getValor(gt->nodes[n].adjacentes, i); i++){
          if(infos[*vis].cor=='b'){
               infos[*vis].pai=n;
               treeEdge(gt, getEdge(gt, n, *vis), &td, &tf, extra);
               dfsaux(gt, *vis, infos, tempo, treeEdge, forwardEdge, returnEdge, crossEdge, extra);
          }else if(infos[*vis].cor=='c'){
               returnEdge(gt, getEdge(gt, n, *vis), &td, &tf, extra);
          }else{
               Node pai=infos[*vis].pai;
               bool cross=true;
               while (pai!=-1) {
                    if(pai=n){
                         forwardEdge(gt, getEdge(gt, n, *vis), &td, &tf, extra);
                         cross=false;
                         break;
                    }
                    pai=infos[pai].pai;
               }
               if(cross){
                    crossEdge(gt, getEdge(gt, n, *vis), &td, &tf, extra);
               }
          }

     }

     *tempo=*tempo+1;
     infos[n].tf=*tempo;
     infos[n].cor='p';
}
/*
   Faz percurso em profundidade sobre  g, a partir do no' node, classificando 
   as arestas do grafo, invocando a respectiva funcao.
      A busca em profundidade, eventualmente, pode produzir uma floresta.
   newTree e' invocada sempre que o percurso for retomado.
 */  
typedef bool (*procEdge)(Graph g, Edge e, double* td, double* tf, void *extra); 
typedef bool (*dfsRestarted)(Graph g, void *extra);
bool dfs(Graph g, Node n, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge,
	 procEdge crossEdge, dfsRestarted newTree, void *extra){
     GraphSt* gt=g;
     dfsNInfo* infos=(dfsNInfo*)malloc(sizeof(dfsNInfo) * getTotalNodes(g));
     for (int i=0; i<getTotalNodes(g); i++) {
          infos[i].cor='b';
          infos[i].td=0;
          infos[i].tf=0;
          infos[i].pai=-1;
     }
     int tempo=0;
     dfsaux(g, n, infos, &tempo, treeEdge, forwardEdge, returnEdge, crossEdge, extra);

     int totalNodes=getTotalNodes(g);
     for(int i=0; i<totalNodes; i++){
          if(infos[i].cor=='b'){
               if(newTree){
                    newTree(g, extra);
               }
          }

     }

     free(infos);
     return true;
}







