#ifndef _RETANGULO_H
#define _RETANGULO_H

#include "smutreap.h"

/* Retorna um retangulo com id=id, x=x, y=y, largura=w, altura=h, cor da borda=corb, cor de preenchimento=corp,
 * e transparencia=transp
 */ 
Info criaRetangulo(int id, double x, double y, double w, double h, char* corb, char* corp, char* transp);

/* Move o retangulo i para a posicao (x,y)
 */ 
void moveRet(Info i, double x, double y);
int getRetId(Info i);
double getRetX(Info i);
double getRetY(Info i);
double getRetWidth(Info i);
double getRetHeight(Info i);
char* getRetCorb(Info i);
char* getRetCorp(Info i);
char* getRetTransp(Info i);

#endif
