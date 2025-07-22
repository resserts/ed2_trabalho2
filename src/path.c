#include "path.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
     int id;
     Lista pos;
     char cor[30];
     char corp[30];
}StPath;

Info criaPath(int i, Lista pos, char* cor){
     StPath* path=(StPath*)malloc(sizeof(StPath));
     path->id=i;
     path->pos=pos;
     strcpy(path->cor, cor);
     return path;
}

int getPathId(Info i){
     StPath* path=i;
     return path->id;
}
Lista getPath(Info i){
     StPath* path=i;
     return path->pos;
}
char* getPathCor(Info i){
     StPath* path=i;
     return path->cor;
}

