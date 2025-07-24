#ifndef _CIRCULO_H
#define _CIRCULO_H

#include "smutreap.h"

/*
 * Cria um circulo com id=i, x=x, y=y, raio=r, cor da borda=corb e cor de 
 * preenchimento=corp
 */
Info criaCirculo(int i, double x, double y, double r, char* corb, char* corp);

/* 
 * Move o circulo i para a posicao (x,y)
 */
void moveCirc(Info i, double x, double y);

int getCircId(Info i);
double getCircx(Info i);
double getCircy(Info i);
double getCircRaio(Info i);
char* getCircCorb(Info i);
char* getCircCorp(Info i);

#endif
