#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "lista.h"

typedef struct {
     char nome[MAX_STR_LEN];
     double x, y;
     Info info;
}NodeSt;
typedef struct {
     bool habilitada;
     char nome[MAX_STR_LEN];
     char ldir[MAX_STR_LEN];
     char lesq[MAX_STR_LEN];
     Node n1, n2;
     double comp;
     double vm;
     Info info;
}EdgeSt;
typedef struct {
     char nome[MAX_STR_LEN];
     bool directed;
     int maxNodes;
     NodeSt* nodes;
     Lista* edges;
     Lista subGraphs;
}GraphSt;
typedef struct{
     char nome[MAX_STR_LEN];
     Node* nodes;
     Lista* edges;
     int nVerts;
}SubGraphSt;

Graph createGraph(int nVert, bool directed, char* nome){
     GraphSt* gt=malloc(sizeof(GraphSt));
     strcpy(gt->nome, nome);
     gt->directed=directed;
     gt->maxNodes=nVert;
     gt->nodes=calloc(sizeof(NodeSt), gt->maxNodes);
     gt->edges=calloc(sizeof(Lista), gt->maxNodes);
     for(int i=0; i<gt->maxNodes; i++){
          gt->edges[i]=criaLista();
     }
     gt->subGraphs=criaLista();
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
          return -1;
     }
     int id=getTotalNodes(g);
     GraphSt* gt=g;
     strcpy(gt->nodes[id].nome, nome);
     gt->nodes[id].info=info;
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
     et->habilitada=true;
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

double getEdgeComp(Graph g, Edge e){
     EdgeSt* et=e;
     return et->comp;
}


double getEdgeVelMedia(Graph g, Edge e){
     EdgeSt* et=e;
     return et->vm;
}


char* getEdgeName(Graph g, Edge e){
     EdgeSt* et=e;
     return et->nome;
}

char* getEdgeLDir(Graph g, Edge e){
     EdgeSt* et=e;
     return et->ldir;
}

char* getEdgeLEsq(Graph g, Edge e){
     EdgeSt* et=e;
     return et->lesq;
}


void setEdgeInfo(Graph g, Edge e, Info info){
     EdgeSt* et=e;
     et->info=info;
}


bool getEdgeHabil(Graph g, Edge e){
     EdgeSt* et=e;
     return et->habilitada;
}


void setEdgeHabil(Graph g, Edge e, bool setar){
     EdgeSt* et=e;
     et->habilitada=setar;
}

void removeEdge(Graph g, Edge e){
     GraphSt* gt=g;
     for(int i=0; getValor(gt->edges, i); i++){
          EdgeSt* et=getValor(gt->edges, i);
          if(et==e){
               for(int j=0; getValor(gt->edges[et->n1], j); j++){
                    int* to=getValor(gt->edges[et->n1], j);
                    if(*to==et->n2){
                         removeList(gt->edges[et->n1], j);
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
     for(int i=0; getValor(gt->edges[n], i); i++){
          insertList(nosAdjacentes, getValor(gt->edges[n], i), i);
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
     EdgeSt* et;
     Node vis;
     double td, tf;
     //printf("simple dnfaux: %i\n", *tempo);
     for(int i=0; et=getValor(gt->edges[n], i); i++){
          vis=et->n2;
          if(infos[vis].cor=='b'){
               infos[vis].pai=n;
               treeEdge(gt, et, &td, &tf, extra);
               dfsaux(gt, vis, infos, tempo, treeEdge, forwardEdge, returnEdge, crossEdge, extra);
          }else if(infos[vis].cor=='c'){
               returnEdge(gt, et, &td, &tf, extra);
          }else{
               Node pai=infos[vis].pai;
               bool cross=true;
               while (pai!=-1) {
                    if(pai=n){
                         forwardEdge(gt, et, &td, &tf, extra);
                         cross=false;
                         break;
                    }
                    pai=infos[pai].pai;
               }
               if(cross){
                    crossEdge(gt, et, &td, &tf, extra);
               }
          }

     }

     *tempo=*tempo+1;
     infos[n].tf=*tempo;
     infos[n].cor='p';
}
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


typedef struct{
     char cor;
     int d;
     Node p;
}bfsInfo;
bool bfs(Graph g, Node n, Node discoverNode, void *extra){
     GraphSt* gt=g;
     bfsInfo* infos=(bfsInfo*)malloc(sizeof(bfsInfo)*getTotalNodes(g));
     for (int i=0; i<getTotalNodes(g); i++) {
          infos[i].cor='b';
          infos[i].d=99999999;
          infos[i].p=-1;
     }
     Lista fila=criaLista();
     infos[n].cor='c';
     infos[n].d=0;
     insertList(fila, &n, 9999999);
     Node* next;
     while (next=getValor(fila, 0)) {
          EdgeSt* et;
          for(int i=0; et=getValor(gt->edges[*next], i); i++){
               if(infos[et->n2].cor=='b'){
                    infos[et->n2].cor='c';
                    infos[et->n2].d=infos[*next].d+1;
                    infos[et->n2].p=*next;
                    insertList(fila, &et->n2, 9999999);
               }
          }
          removeList(fila, 0);
     }
     return true;
}

typedef struct{
     double w;
     double c;
     Node p;
}caminhoInfo;
Lista caminho(Graph g, Node from, Node to, nodeWeight nw, nodeWeight nc){
     GraphSt* gt=g;
     caminhoInfo* infos=(caminhoInfo*)malloc(sizeof(caminhoInfo)*getTotalNodes(g));
     for (int i=0; i<getTotalNodes(g); i++) {
          infos[i].w=99999999+i;
          infos[i].c=99999999+i;
          infos[i].p=-1;
     }
     infos[from].w=0;
     infos[from].c=0;
     Lista fila=criaLista();
     for(int i=0; i<getTotalNodes(g); i++){
          if(i!=from){
               Node* n=(Node*)malloc(sizeof(Node));
               *n=i;
               insertList(fila, n, 9999999);
          }
     }
     Node* next=(Node*)malloc(sizeof(Node));
     *next=from;
     insertList(fila, next, 0);
     double maiorTime=0;
     int tamanhoLista=0;
     while (getValor(fila, tamanhoLista)) {
          tamanhoLista++;
     }
     for (int w=0; (next=getValor(fila, 0)); w++) {
          if(*next==to){
               fila=criaLista();
               Node p=to;
               while(p>=0){
                    Node* n=(Node*)malloc(sizeof(Node));
                    *n=p;
                    insertList(fila, n, 0);
                    if(p==from){
                         return fila;
                    }
                    p=infos[p].p;
               }
               return NULL;
          }
          EdgeSt* et;
          removeList(fila, 0);
          tamanhoLista--;
          for(int i=0; (et=getValor(gt->edges[*next], i)) && et->habilitada; i++){
               double newWeight=nw(g, infos[*next].w, et, to);
               if(infos[et->n2].w>newWeight){
                    infos[et->n2].w=newWeight;
                    double newCost=nc(g, infos[*next].w, et, to);
                    infos[et->n2].p=*next;
                    Node* maior;
                    
                    clock_t maiorStart=clock();
                    Node* val;
                    int inserir=ceil(getTotalNodes(g)/2.);
                    int low=0;
                    int high=tamanhoLista-1;
                    int mid;
                    while(low<=high){
                         mid=low + (high-low)/2.;
                         val=getValor(fila, mid);
                         if(newCost>infos[*val].c){
                              if(newCost<=infos[*(Node*)getValor(fila, mid+1)].c){
                                   break;
                              }
                              low=mid+1;
                         }else{
                              high=mid-1;
                         }
                    }
                    inserir=mid;


                    low=0;
                    high=tamanhoLista;
                    while(low<=high){
                         mid=low + (high-low)/2.;
                         val=getValor(fila, mid);
                         if(et->n2==*val){
                              break;
                         }else if(infos[et->n2].c>infos[*val].c){
                              low=mid+1;
                         }else{
                              high=mid-1;
                         }
                    }
                    infos[et->n2].c=newCost;
                    Node* in=(Node*)malloc(sizeof(Node));
                    *in=*val;
                    insertList(fila, in, inserir);
                    removeList(fila, mid);
                    clock_t maiorEnd=clock();
                    maiorTime+=maiorEnd-maiorStart;
               }
          }
     }
     return NULL;
}


void killDG(Graph g){
     GraphSt* gt=g;
     for(int i=0; i<getTotalNodes(gt); i++){
          killLista(gt->edges[i]);
     }
     free(gt->nodes);
     free(gt);
}

void createSubgraphDG(Graph g, char *nomeSubgrafo, char *nomesVerts[], int nVert,
		       bool comArestas){
     GraphSt* gt=g;
     SubGraphSt* sgt=(SubGraphSt*)malloc(sizeof(SubGraphSt));
     strcpy(sgt->nome, nomeSubgrafo);
     sgt->nodes=(Node*)malloc(sizeof(Node)*nVert);
     for (int i=0; i<nVert; i++) {
          sgt->nodes[i]=getNode(g, nomesVerts[i]);
     }
     sgt->edges=(Lista*)malloc(sizeof(Lista)*getTotalNodes(g));
     for (int i=0; i<getTotalNodes(g); i++) {
          sgt->edges[i]=criaLista();
     }
     if(comArestas){
          for (int i=0; i<nVert; i++) {
               EdgeSt* et;
               for (int j=0; (et=getValor(gt->edges[sgt->nodes[i]], j)); j++) {
                    for (int k=0; k<nVert; k++) {
                         if(et->n2==sgt->nodes[k]){
                              insertList(sgt->edges[sgt->nodes[i]], et, 0);
                         }
                    }
               
               }
               
          }
     }
     sgt->nVerts=nVert;
     insertList(gt->subGraphs, sgt, 0);
}


bool nodeInSubgraph(SubGraphSt* sgt, Node n){
     for(int i=0; i<sgt->nVerts; i++){
          if(sgt->nodes[i]==n){
               return true;
          }
     }
     return false;
}

Edge includeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* et=e;
               if(nodeInSubgraph(sgt, et->n1) && nodeInSubgraph(sgt, et->n2)){
                    insertList(sgt->edges[et->n1], e, 0);
                    return e;
               }
          }
     }
     return NULL;
}

bool existsEdgeSDG(Graph g, char *nomeSubgrafo, Edge e){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* et=e;
               EdgeSt* aux;
               for (int j=0; (aux=getValor(sgt->edges[et->n1], j)); j++) {
                    if(et==aux){
                         return true;
                    }
               }
          }
     }
     return false;
}

void excludeEdgeSDG(Graph g, char *nomeSubgrafo, Edge e){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* et=e;
               EdgeSt* aux;
               for (int j=0; (aux=getValor(sgt->edges[et->n1], j)); j++) {
                    if(et==aux){
                         removeList(sgt->edges[et->n1], i);
                    }
               }
          }
     }
}

void adjacentEdgesSDG(Graph g, char *nomeSubgrafo, Node n, Lista arestasAdjacentes){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* aux;
               for (int j=0; (aux=getValor(sgt->edges[n], j)); j++) {
                    insertList(arestasAdjacentes, aux, 0);
               }
          }
     }
}

void getAllNodesSDG(Graph g, char *nomeSubgrafo,  Lista lstNodes){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               for (int j=0; j<sgt->nVerts; j++) {
                    Node* n=(Node*)malloc(sizeof(Node));
                    *n=sgt->nodes[j];
                    insertList(lstNodes, n, 0);
               }
          }
     }
}

void getAllEdgesSDG(Graph g, char *nomeSubgrafo, Lista lstEdges){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* et;
               for (int j=0; j<getMaxNodes(g); j++) {
                    for (int k=0; (et=getValor(sgt->edges[j], k)); k++) {
                         insertList(lstEdges, et, k);
                    }
               }
          }
     }
}

Graph produceGraph(Graph g, char* nomeSubgrafo){
     GraphSt* gt=g;
     SubGraphSt* sgt;
     GraphSt* criado=createGraph(sgt->nVerts, true, nomeSubgrafo);
     for (int i=0; (sgt=getValor(gt->subGraphs, i)); i++) {
          if(strcmp(sgt->nome, nomeSubgrafo)){
               EdgeSt* et;
               for (int j=0; j<sgt->nVerts; j++) {
                    for (int k=0; (et=getValor(sgt->edges[sgt->nodes[j]], k)); k++) {
                         Node to;
                         for (int l=0; l<sgt->nVerts; l++) {
                              if(et->n2==sgt->nodes[l]){
                                   to=l;
                                   break;
                              }
                         }
                         addEdge(criado, j, to, et->ldir, et->lesq, et->comp, et->vm, et->nome, et->info);
                    }
               }
          }
     }
}
