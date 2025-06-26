#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 255


int main(int argc, char* argv[]){
     printf("argc: %i\n", argc);
     char BED[MAX_PATH_LEN]="./";
     char BSD[MAX_PATH_LEN]="./";
     char geo[MAX_PATH_LEN];
     char query[MAX_PATH_LEN];
     char via[MAX_PATH_LEN];
     char arq[MAX_PATH_LEN];
     int prioMax=10000;
     int hitCount=3;
     double promotionRate=1.1;

     for(int i=1; i<argc; i++){
          printf("i: %i\n", i);
          printf("argv[i]: %s\n", argv[i]);
          if(strcmp(argv[i], "-f")==0){
               printf("entro comandos\n");
               i++;
               strcpy(geo, argv[i]);
               strcpy(arq, geo);
               arq[strlen(arq)-4]='\0';
          }else if(strcmp(argv[i], "-e")==0){
               i++;
               strcpy(BED, argv[i]);
          }else if(strcmp(argv[i], "-o")==0){
               i++;
               strcpy(BSD, argv[i]);
          }else if(strcmp(argv[i], "-q")==0){
               i++;
               strcpy(query, argv[i]);
          }else if(strcmp(argv[i], "-v")==0){
               i++;
               strcpy(query, argv[i]);
          }     
     }

     char geoArq[MAX_PATH_LEN];
     strcpy(geoArq, BED);
     strcat(geoArq, geo);

     char queryArq[MAX_PATH_LEN];
     strcpy(queryArq, BED);
     strcat(queryArq, query);
     char saida[MAX_PATH_LEN];
     strcpy(saida, BSD);
     strcat(saida, arq);

     char svgArq[MAX_PATH_LEN];
     strcpy(svgArq, BSD);
     strcat(svgArq, arq);
     strcat(svgArq, ".svg");

     return 0;
}
