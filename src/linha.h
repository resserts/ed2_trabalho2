#ifndef _LINHA_H
#define _LINHA_H

#include "smutreap.h"

/* Retorna uma linha com id=i, x=x, y=y, x2=x2, y2=y2 e cor da borda=corb
 */
Info criaLinha(int i, double x, double y, double x2, double y2, char* corb);

/* Move a linha i para a posicao (x,y)
 */
void moveLinha(Info i, double x, double y);
int getLinhaId(Info i);
double getLinhax1(Info i);
double getLinhay1(Info i);
double getLinhax2(Info i);
double getLinhay2(Info i);
char* getLinhaCor(Info i);

#endif
