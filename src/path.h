#ifndef _PATH_H 
#define _PATH_H

#include "smutreap.h"

Info criaPath(int i, Lista pos, char* cor);

int getPathId(Info i);
Lista getPath(Info i);
char* getPathCor(Info i);

#endif
