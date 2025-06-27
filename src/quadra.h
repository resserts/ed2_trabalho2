#ifndef _QUADRA_H 
#define _QUADRA_H


#include "smutreap.h"

Info criaQuadra(char* cep, double x, double y, double w, double h);

void mudaEstiloQuad(char* strokeWidth, char* corb, char* corp);
char* getQuadCep(Info i);
double getQuadX(Info i);
double getQuadY(Info i);
double getQuadWidth(Info i);
double getQuadHeight(Info i);
char* getQuadStrokeWidth(Info i);
char* getQuadCorb(Info i);
char* getQuadCorp(Info i);

#endif
