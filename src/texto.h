#ifndef _TEXTO_H
#define _TEXTO_H

#include "smutreap.h"

/* Retorna um texto com id=i, x=x, y=y, cor da borda=corb, cor de preenchimento=corp,
 * posicao da ancora=a e conteudo=texto
 */ 
Info criaTexto(int i, double x, double y, char* corb, char* corp, char a, char* texto);

/* Muda o estilo no qual os proximos serao criados
 */
void mudaEstilo(char* fFamily, char* fWeight, char* fSize);

/* Move o texto i para posicao (x,y)
 */
void moveTxt(Info i, double x, double y);
int getTxtId(Info i);
double getTxtx(Info i);
double getTxty(Info i);
char* getTxtCorb(Info i);
char* getTxtCorp(Info i);
char getTxtPos(Info i);
char* getTxt(Info i);
char* getTxtFamily(Info i);
char* getTxtWeight(Info i);
char* getTxtSize(Info i);

#endif
