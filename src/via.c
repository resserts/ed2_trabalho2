#include <stdio.h>
#include <string.h>

#include "via.h"
#include "graph.h"

#define MAX_STR_LEN 255

Graph comandosVia(char* fn){
     FILE* f=fopen(fn, "r");
     if(f==NULL){
          printf("não foi possível acessar arquivo via\n");
          return NULL;
     }
     int nVert; 
     fscanf(f, "%i", &nVert);

     Graph g=createGraph(nVert, true, "-");

     char comando[5];
     double compM=0;
     double compm=99;
     double velM=0;
     double velm=99;
     while(fscanf(f, "%s", comando)!=EOF){
          if(strcmp(comando, "e")==0){
               char v1[MAX_STR_LEN];
               char v2[MAX_STR_LEN];
               char ldir[MAX_STR_LEN];
               char lesq[MAX_STR_LEN];
               double comp;
               double velMedia;
               char nome[MAX_STR_LEN];
               fscanf(f, "%s", v1);
               fscanf(f, "%s", v2);
               fscanf(f, "%s", ldir);
               fscanf(f, "%s", lesq);
               fscanf(f, "%lf", &comp);
               fscanf(f, "%lf", &velMedia);
               fscanf(f, "%s", nome);
               if(velMedia>velM){
                    velM=velMedia;
               }else if(velMedia<velm){
                    velm=velMedia;
               }
               if(comp>compM){
                    compM=comp;
               }else if(comp<compm){
                    compm=comp;
               }
               addEdge(g, getNode(g, v1), getNode(g, v2), ldir, lesq, comp, velMedia, nome, NULL);
          }else if(strcmp(comando, "v")==0){
               char id[MAX_STR_LEN];
               double x, y;
               char corb[MAX_STR_LEN];
               char corp[MAX_STR_LEN];
               fscanf(f, "%s" , id);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               addNode(g, x, y, id, NULL);
          }     
     }

     fclose(f);
     return g;
}
