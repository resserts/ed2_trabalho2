#include "query.h"
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
void comandosQuery(SmuTreap t, char* fn, char* saida){
     printf("arquivo query: %s\n", fn);
     FILE* f=fopen(fn, "r");
     if(f==NULL){
          printf("não foi possível acessar arquivo query\n");
          return;
     }
     Lista listas=criaLista();
     Posicao regs[11];
     char comando[10];
     while(fscanf(f, "%s", comando)!=EOF){
          printf("comando: %s\n", comando);
          if(strcmp(comando, "selr")==0){
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
               if(getInfosDentroRegiaoSmuT(t, x, y, x+w, y+h, &bbDentro, sel->l)){
                    printf("acho info");
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
               printf("x1: %lf\t y1: %lf\nx2: %lf\t y2: 10\n", regs[regId].x, regs[regId].y, regs[regId].x);
          }     
     }
     for (int i=0; getValor(listas, i); i++) {
          Selecao* sel=getValor(listas, i);
          killLista(sel->l);
          free(sel);
     }
     killLista(listas);

     fclose(f);
}
