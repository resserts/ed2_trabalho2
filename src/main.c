#include "graph.h"
#include "smutreap.h"
#include "svg.h"
#include "geo.h"
#include "via.h"

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
               i++;
               strcpy(geo, argv[i]);
               strcpy(arq, geo);
               arq[strlen(arq)-4]='\0';
          }else if(strcmp(argv[i], "-e")==0){
               i++;
               strcpy(BED, argv[i]);
               if(BED[strlen(BED)-1]!='/'){
                    strcat(BED, "/");
               }
          }else if(strcmp(argv[i], "-o")==0){
               i++;
               strcpy(BSD, argv[i]);
               if(BSD[strlen(BSD)-1]!='/'){
                    strcat(BSD, "/");
               }
          }else if(strcmp(argv[i], "-q")==0){
               i++;
               strcpy(query, argv[i]);
          }else if(strcmp(argv[i], "-v")==0){
               i++;
               strcpy(via, argv[i]);
          }     
     }

     SmuTreap smut=newSmuTreap(10, 1.1, 0.0001, 10000);
     char geoArq[MAX_PATH_LEN];
     strcpy(geoArq, BED);
     strcat(geoArq, geo);
     comandosGeo(smut, geoArq);

     char viaArq[MAX_PATH_LEN];
     strcpy(viaArq, BED);
     strcat(viaArq, via);
     Graph g=comandosVia(viaArq);

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
     gerarSvg(smut, svgArq, NULL);

     return 0;
}
