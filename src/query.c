#include "query.h"
#include "graph.h"
#include "path.h"
#include "retangulo.h"
#include "quadra.h"
#include "circulo.h"
#include "linha.h"
#include "svg.h"
#include "smutreap.h"
#include "texto.h"
#include "lista.h"
#include "boundingBox.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct{
     int n;
     Lista l;
}Selecao;
Selecao* criaSelecao(int n){
     Selecao* sel=(Selecao*)malloc(sizeof(Selecao));
     sel->l=criaLista();
     sel->n=n;
     return sel;
}

double getX(SmuTreap t, NodeSmut n){
     DescritorTipoInfo dt=getTypeInfoSrbT(t, n);
     Info i=getInfoSmuT(t, n);
     switch (dt) {
          case RETANGULO:
               return getRetX(i);
          case CIRCULO:
               return getCircx(i);
          case LINHA:
               return getLinhax1(i);
          case TEXTO:
               return getTxtx(i);
          case QUADRA:
               return getQuadX(i);
          default:
               return 0;
     }
}
double getY(SmuTreap t, NodeSmut n){
     DescritorTipoInfo dt=getTypeInfoSrbT(t, n);
     Info i=getInfoSmuT(t, n);
     switch (dt) {
          case QUADRA:
               return getQuadY(i);
          case RETANGULO:
               return getRetY(i);
          case CIRCULO:
               return getCircy(i);
          case LINHA:
               return getLinhay1(i);
          case TEXTO:
               return getTxty(i);
          default:
               return 0;
     }
}

bool getQuadra(SmuTreap t, NodeSmut n, Info i, double x, double y, void *aux){
     if(getTypeInfoSrbT(t, n)==QUADRA && strcmp(getQuadCep(i), aux)==0){
          return true;
     }
     return false;
}

typedef struct{
     double x, y;
}Posicao;
typedef struct{
     char nome[64];
     Lista curto;
     Lista rapido;
}Percurso;

double curtoWeight(Graph g, double pai, Edge e, Node objective){
     return pai+getEdgeComp(g, e);
}
double rapidoWeight(Graph g, double pai, Edge e, Node objective){
     return pai+(getEdgeComp(g, e)/getEdgeVelMedia(g, e));
}
double curtoCost(Graph g, double pai, Edge e, Node objective){
     return pai+getEdgeComp(g, e) + 
          (abs(getNodeX(g, getToNode(g, e))-getNodeX(g, objective)) + abs(getNodeY(g, getToNode(g, e))-getNodeY(g, objective)))/2.;
}
double rapidoCost(Graph g, double pai, Edge e, Node objective){
     return pai+(getEdgeComp(g, e)+ (abs(getNodeX(g, getToNode(g, e))-getNodeX(g, objective)) + 
                    abs(getNodeY(g, getToNode(g, e))-getNodeY(g, objective)))/4.)/(getEdgeVelMedia(g, e)*4.);
}

void comandosQuery(SmuTreap t, Graph g, Lista paths, char* fn, char* saida){
     printf("arquivo query: %s\n", fn);
     FILE* f=fopen(fn, "r");
     if(f==NULL){
          printf("não foi possível acessar arquivo query\n");
          return;
     }
     Lista listas=criaLista();
     Lista percursos=criaLista();
     Posicao regs[11];
     char comando[10];
     for(int i=0; i<getTotalNodes(g); i++){
          Node* n=malloc(sizeof(Node));
          *n=i;
          insertSmuT(t, getNodeX(g, i), getNodeX(g, i), n, VERTICE, &calculabb);
     }
     FILE* fTxt=fopen(strcat(saida, ".txt"), "w");
     while(fscanf(f, "%s", comando)!=EOF){
          printf("comando: %s\n", comando);
          if(strcmp(comando, "alag")==0){
               int n;
               double x, y;
               double w, h;
               fscanf(f, "%i" , &n);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               fscanf(f, "%lf" , &w);
               fscanf(f, "%lf" , &h);
               Selecao* sel;
               for(int i=0; getValor(listas, i); i++){
                    sel=getValor(listas, i);
                    if(sel->n==n){
                         killLista(sel->l);
                         sel->l=criaLista();
                         goto seleciona;
                    }
               }
               sel=criaSelecao(n);
seleciona:
               //printf("x: %f, y: %f, w:");
               Lista arestas=criaLista();
               getEdges(g, arestas);
               Edge e;
               fprintf(fTxt, "\n\n==========alag==========\n");
               fprintf(fTxt, "Arestas desabilitadas:\n");
               for (int i=0; (e=getValor(arestas, i)); i++) {
                    Node to=getToNode(g, e);
                    if(getNodeX(g, to)>=x && getNodeX(g, to)<=x+w && getNodeY(g, to)>=y && getNodeY(g, to)<=y+h){
                         insertList(sel->l, e, 0);
                         if(getEdgeHabil(g, e)){
                              fprintf(fTxt, "%s:\t ldir=%s;\t lesq=%s\n", getEdgeName(g, e), getEdgeLDir(g, e), getEdgeLEsq(g, e));
                         }
                         setEdgeHabil(g, e, false);
                    }
               }

               insertSmuT(t, x, y, criaRetangulo(0, x, y, w, h, "#AA0044", "#AB37C8", "0.5"), RETANGULO, &calculabb);
               insertList(listas, sel, 0);
          }else if(strcmp(comando, "dren")==0){
               int n;
               fscanf(f, "%i" , &n);
               Selecao* sel;
               fprintf(fTxt, "\n\n==========dren==========\n");
               fprintf(fTxt, "Arestas reabilitadas:\n");
               for(int i=0; getValor(listas, i); i++){
                    sel=getValor(listas, i);
                    printf("%i==%i\n", sel->n, n);
                    if(sel->n==n){
                         printf("acho\n");
                         Edge e;
                         for(int i=0; (e=getValor(sel->l, i)); i++){
                              if(getEdgeHabil(g, e)){
                                   fprintf(fTxt, "%s:\t ldir=%s;\t lesq=%s\n", getEdgeName(g, e), getEdgeLDir(g, e), getEdgeLEsq(g, e));
                              }
                              setEdgeHabil(g, e, true);
                         }
                         break;
                    }
               }

          }else if(strcmp(comando, "@o?")==0){
               char reg[10];
               char cep[MAX_STR_LEN];
               char face;
               double num;
               fscanf(f, "%s" , reg);
               fscanf(f, "%s" , cep);
               fscanf(f, " %c" , &face);
               fscanf(f, "%lf" , &num);
               printf("@0? %s %s %c %lf\n", reg, cep, face, num);
               NodeSmut quadra=procuraNoSmuT(t, &getQuadra, cep);
               int regId=atoi(reg+1);
               switch (face) {
                    case 'N':
                         regs[regId].x=getX(t, quadra)+num;
                         regs[regId].y=getY(t, quadra)+getQuadHeight(getInfoSmuT(t, quadra));
                         break;
                    case 'S':
                         regs[regId].x=getX(t, quadra)+num;
                         regs[regId].y=getY(t, quadra);
                         break;
                    case 'L':
                         regs[regId].x=getX(t, quadra);
                         regs[regId].y=getY(t, quadra)+num;
                         break;
                    case 'O':
                         regs[regId].x=getX(t, quadra)+getQuadWidth(getInfoSmuT(t, quadra));
                         regs[regId].y=getY(t, quadra)+num;
                         break;
                    default:
                         break;
               }
               insertSmuT(t, regs[regId].x, regs[regId].y, 
                         criaLinha(0, regs[regId].x, regs[regId].y, regs[regId].x, 10, "darkred"), LINHA, &calculabb);
               insertSmuT(t, regs[regId].x, 10, 
                         criaTexto(0, regs[regId].x, 10, "black", "black", 'm', reg), TEXTO, &calculabb);

               fprintf(fTxt, "\n\n==========@o?==========\n");
               fprintf(fTxt, "%s = (%f, %f)\n", reg, regs[regId].x, regs[regId].y);
               //printf("x1: %lf\t y1: %lf\nx2: %lf\t y2: 10\n", regs[regId].x, regs[regId].y, regs[regId].x);
          }else if(strcmp(comando, "p?")==0){
               char np[32];
               char nome[MAX_STR_LEN];
               char reg1[32];
               char reg2[32];
               fscanf(f, "%s" , np);
               fscanf(f, "%s" , nome);
               fscanf(f, "%s" , reg1);
               fscanf(f, "%s" , reg2);
               int reg1Id=atoi(reg1+1);
               int reg2Id=atoi(reg2+1);
               double fromMenorDist=999999;
               double toMenorDist=999999;
               Node from;
               Node to;
               for(int i=0; i<getTotalNodes(g); i++){
                    double distFrom=pow(getNodeX(g, i)-regs[reg1Id].x, 2)+pow(getNodeY(g, i)-regs[reg1Id].y, 2);
                    if(distFrom<fromMenorDist){
                         from=i;
                         fromMenorDist=distFrom;
                    }
                    double distTo=pow(getNodeX(g, i)-regs[reg2Id].x, 2)+pow(getNodeY(g, i)-regs[reg2Id].y, 2);
                    if(distTo<toMenorDist){
                         to=i;
                         toMenorDist=distTo;
                    }
               }
               Percurso* percurso=(Percurso*)malloc(sizeof(Percurso));
               strcpy(percurso->nome, np);
               printf("from %i to %i\n", from, to);

               percurso->curto=caminho(g, from, to, &curtoWeight, &curtoWeight);
               percurso->rapido=caminho(g, from, to, &rapidoWeight, &rapidoWeight);
               insertList(percursos, percurso, 0);
               fprintf(fTxt, "\n\n==========p?==========\n");
               Node* nTo;
               Node* nFrom=getValor(percurso->curto, 0);
               fprintf(fTxt, "Caminho Curto ");
               for (int i=1; (nTo=getValor(percurso->curto, i)); i++) {
                    fprintf(fTxt, "=>(%.1f, %.1f)", getNodeX(g, *nTo), getNodeY(g, *nTo));
                    nFrom=nTo;
               }
               fprintf(fTxt, "\n\nCaminho Rapido ");
               for (int i=1; (nTo=getValor(percurso->rapido, i)); i++) {
                    fprintf(fTxt, "=>(%.1f, %.1f)", getNodeX(g, *nTo), getNodeY(g, *nTo));
                    nFrom=nTo;
               }
          }else if(strcmp(comando, "join")==0){
               char np[32];
               char np1[32];
               char np2[32];
               fscanf(f, "%s" , np);
               fscanf(f, "%s" , np1);
               fscanf(f, "%s" , np2);
               Percurso* per1=NULL;
               Percurso* p=NULL;
               for (int i=0; (p=getValor(percursos, i)); i++) {
                    if(strcmp(p->nome, np1)==0){
                         per1=p;
                         break;
                    }
               }
               if(per1==NULL){
                    continue;
               }
               Percurso* per2=NULL;
               for (int i=0; (p=getValor(percursos, i)); i++) {
                    if(strcmp(p->nome, np2)==0){
                         per2=p;
                         break;
                    }
               }
               if(per2==NULL){
                    continue;
               }
               printf("per1=%s\t per2=%s\n", per1->nome, per2->nome);
               Percurso* percurso=(Percurso*)malloc(sizeof(Percurso));
               strcpy(percurso->nome, np);
               percurso->curto=criaLista();
               percurso->rapido=criaLista();
               Node* n;
               for (int i=0; getValor(per1->curto, i); i++) {
                    n=getValor(per1->curto, i);
                    insertList(percurso->curto, n, 9999999);
               }
               for (int i=0; getValor(per1->rapido, i); i++) {
                    n=getValor(per1->rapido, i);
                    insertList(percurso->rapido, n, 9999999);
               }
               Lista jCurto=caminho(g, *n, *(Node*)getValor(per2->curto, 0), &curtoWeight, &curtoWeight);
               Lista jRapido=caminho(g, *n, *(Node*)getValor(per2->rapido, 0), &rapidoWeight, &rapidoWeight);
               for (int i=1; (n=getValor(jCurto, i)); i++) {
                    insertList(percurso->curto, n, 9999999);
               }
               for (int i=1; (n=getValor(jRapido, i)); i++) {
                    insertList(percurso->rapido, n, 9999999);
               }
               for (int i=1; (n=getValor(per2->curto, i)); i++) {
                    insertList(percurso->curto, n, 9999999);
               }
               for (int i=1; (n=getValor(per2->rapido, i)); i++) {
                    insertList(percurso->rapido, n, 9999999);
               }
               insertList(percursos, percurso, 0);
          }else if(strcmp(comando, "shw")==0){
               char np[32];
               char cmc[32];
               char cmr[32];
               fscanf(f, "%s" , np);
               fscanf(f, "%s" , cmc);
               fscanf(f, "%s" , cmr);
               Percurso* per;
               for(int i=0; per=getValor(percursos, i); i++){
                    printf("nome perc: %s\n", per->nome);
                    if(strcmp(per->nome, np)==0){
                         printf("vai inseri\n");
                         insertList(paths, criaPath(0, per->curto, cmc), 0);
                         printf("inseriu 1\n");
                         insertList(paths, criaPath(1, per->rapido, cmr), 0);
                         printf("inseriu otro\n");
                         break;
                    }
               }

          }    
     }
     for (int i=0; getValor(listas, i); i++) {
          Selecao* sel=getValor(listas, i);
          //killLista(sel->l);
          //free(sel);
     }
     killLista(listas);

     fclose(fTxt);
     fclose(f);
}
