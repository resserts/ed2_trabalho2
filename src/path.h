#ifndef _PATH_H 
#define _PATH_H

#include "smutreap.h"

/* Retorna um path com id=i, posicoes=pos e cor=cor
 */
Info criaPath(int i, Lista pos, char* cor);

int getPathId(Info i);
Lista getPath(Info i);
char* getPathCor(Info i);

#endif
