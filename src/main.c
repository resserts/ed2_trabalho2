#include "graph.h"
#include "lista.h"
#include "smutreap.h"
#include "svg.h"
#include "geo.h"
#include "via.h"
#include "query.h"

#include <string.h>

#define MAX_PATH_LEN 255


int main(int argc, char* argv[]){
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
     for (int i=0; query[i]!='\0'; i++) {
          if(query[i]=='/'){
               query[i]='-';
          }
     }
     strcat(saida, query);
     saida[strlen(saida)-4]='\0';
     Lista paths=criaLista();
     comandosQuery(smut, g, paths, queryArq, saida);

     char svgArq[MAX_PATH_LEN];
     strcpy(svgArq, BSD);
     strcat(svgArq, query);
     svgArq[strlen(svgArq)-4]='\0';
     strcat(svgArq, ".svg");
     gerarSvg(smut, svgArq, paths, g);

     return 0;
}
