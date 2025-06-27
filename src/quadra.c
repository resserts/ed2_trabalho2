#include "retangulo.h"

#include <stdlib.h>
#include <string.h>

typedef struct{
     char cep[64];
     double x, y;
     double w, h;
     char strokeWidth[30];
     char corb[30];
     char corp[30];
}StQuadra;

char strokeWidth[30]="1.0pix";
char corBorda[30]="black";
char corPreenchimento[30]="white";

Info criaQuadra(char* cep, double x, double y, double w, double h){
     StQuadra* ret= (StQuadra*)malloc(sizeof(StQuadra));
     strcpy(ret->cep, cep);
     ret->x=x;
     ret->y=y;
     ret->w=w;
     ret->h=h;
     strcpy(ret->strokeWidth, strokeWidth);
     strcpy(ret->corb, corBorda);
     strcpy(ret->corp, corPreenchimento);
     return ret;
}


void mudaEstiloQuad(char* strW, char* corp, char* corb){
     strcpy(strokeWidth, strW);
     strcpy(corBorda, corb);
     strcpy(corPreenchimento, corp);
}
char* getQuadCep(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->cep;
}
double getQuadX(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->x;
}
double getQuadY(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->y;
}
double getQuadWidth(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->w;
}
double getQuadHeight(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->h;
}
char* getQuadStrokeWidth(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->corb;
}
char* getQuadCorb(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->corb;
}
char* getQuadCorp(Info i){
     StQuadra* ret=(StQuadra*)i;
     return ret->corp;
}
