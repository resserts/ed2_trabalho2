#include "svg.h"
#include "graph.h"
#include "lista.h"
#include "path.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "quadra.h"
#include "path.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void svgPath(FILE* f, Lista paths, Graph g){
     Info path;
     for(int i=0; (path=getValor(paths, i)); i++){
          Lista perc=getPath(path);
          int desloc=0;
          if(getPathId(path)==1){
               desloc=5;

          }
          Node* n=getValor(perc, 0);
          fprintf(f, "<path d=\"M %f %f", getNodeX(g, *n)-desloc, getNodeY(g, *n)-desloc);
          for (int j=1; (n=getValor(perc, j)); j++) {
               fprintf(f, " L %f %f", getNodeX(g, *n)-desloc, getNodeY(g, *n)-desloc);
          }
          fprintf(f, "\" stroke=\"%s\" stroke-width=\"4\" fill=\"none\" />\n", getPathCor(path));

          n=getValor(perc, 0);
          fprintf(f, "<circle r=\"5\" fill=\"black\">\n");
          fprintf(f, "\t<animateMotion dur=\"10s\" repeatCount=\"indefinite\" path=\"M %f %f", getNodeX(g, *n)-desloc, getNodeY(g, *n)-desloc);
          for (int j=1; (n=getValor(perc, j)); j++) {
               fprintf(f, " L %f %f", getNodeX(g, *n)-desloc, getNodeY(g, *n)-desloc);
          }
          fprintf(f, "\" />\n</circle>\n");
     }
}

void graphSvg(Graph g, FILE* f){
     int total=getTotalNodes(g);
     for(int i=0; i<total; i++){
          fprintf(f, "<circle cx=\"%f\" cy=\"%f\" r=\"5\" stroke=\"blue\" fill=\"green\" />\n",
                         getNodeX(g, i), getNodeY(g, i));

     }
     /*
     Edge e;
     Lista arestas=criaLista();
     getEdges(g, arestas);
     for (int i=0; e=getValor(arestas, i); i++) {
          double fromX=getNodeX(g, getFromNode(g, e));
          double fromY=getNodeY(g, getFromNode(g, e));
          double toX=getNodeX(g, getToNode(g, e));
          double toY=getNodeY(g, getToNode(g, e));
          char cor[63]="black";
          if(fromX>toX){
               strcpy(cor, "purple");
          }else if(fromX<toX){
               strcpy(cor, "orange");
          }
          fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
                    fromX, fromY, toX, toY, cor);
     }
     */
}
void svgNo(SmuTreap t, NodeSmut n, Info i, double x, double y, void *aux){
     DescritorTipoInfo tipo=getTypeInfoSrbT(t, n);
     switch (tipo) {
          case QUADRA:
               fprintf(aux, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" ",
                         x, y, getQuadWidth(i), getQuadHeight(i), getQuadCorb(i), getQuadCorp(i));
               fprintf(aux, "/>\n"); 
               fprintf(aux, "<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" font-family=\"%s\" font-size=\"%s\" font-weight=\"%s\" text-anchor=\"%s\" >%s</text>\n",
                         x, y+12, "black", "black", "sans", 
                         "12.0pix", "normal", "start", getQuadCep(i));
               break;
          case RETANGULO:
               fprintf(aux, "<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" stroke=\"%s\" fill=\"%s\" ",
                         x, y, getRetWidth(i), getRetHeight(i), getRetCorb(i), getRetCorp(i));
               fprintf(aux, "fill-opacity=\"%s\" ", getRetTransp(i));
               fprintf(aux, "/>\n"); 
               break;
          case CIRCULO:
               fprintf(aux, "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
                         x, y, getCircRaio(i), getCircCorb(i), getCircCorp(i));
               break;
          case LINHA:
               fprintf(aux, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"5\" />\n",
                         x, y, getLinhax2(i), getLinhay2(i), getLinhaCor(i));
               break;
          case TEXTO:
               char* fontWeight=getTxtWeight(i);
               if(strcmp(fontWeight, "n")){
                    fontWeight="normal";
               }else if(strcmp(fontWeight, "b")){
                    fontWeight="bold";
               }else if(strcmp(fontWeight, "b+")){
                    fontWeight="bolder";
               }else if(strcmp(fontWeight, "l")){
                    fontWeight="lighter";
               }
               char a=getTxtPos(i);
               char anchor[15];
               if(a=='i'){
                    strcpy(anchor, "start");
               }else if(a=='m'){
                    strcpy(anchor, "middle");
               }else if(a=='f'){
                    strcpy(anchor, "end");
               }

               fprintf(aux, "<text x=\"%f\" y=\"%f\" stroke=\"%s\" fill=\"%s\" font-family=\"%s\" font-size=\"%s\" font-weight=\"%s\" text-anchor=\"%s\" >%s</text>\n",
                         x, y, getTxtCorb(i), getTxtCorp(i), getTxtFamily(i), 
                         getTxtSize(i), fontWeight, anchor, getTxt(i));
               break;
          default:
               break;
     }
}
bool treeEdge(Graph g, Edge e, double* td, double* tf, void *extra){
     double fromX=getNodeX(g, getFromNode(g, e));
     double fromY=getNodeY(g, getFromNode(g, e));
     double toX=getNodeX(g, getToNode(g, e));
     double toY=getNodeY(g, getToNode(g, e));
     char cor[63]="darkgreen";
     fprintf(extra, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-width=\"3\" />\n",
               fromX, fromY, toX, toY, cor);
}
bool returnEdge(Graph g, Edge e, double* td, double* tf, void *extra){
     double fromX=getNodeX(g, getFromNode(g, e));
     double fromY=getNodeY(g, getFromNode(g, e));
     double toX=getNodeX(g, getToNode(g, e));
     double toY=getNodeY(g, getToNode(g, e));
     char cor[63]="darkmagenta";
     fprintf(extra, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
               fromX, fromY, toX, toY, cor);
}
bool forwardEdge(Graph g, Edge e, double* td, double* tf, void *extra){
     double fromX=getNodeX(g, getFromNode(g, e));
     double fromY=getNodeY(g, getFromNode(g, e));
     double toX=getNodeX(g, getToNode(g, e));
     double toY=getNodeY(g, getToNode(g, e));
     char cor[63]="darkblue";
     fprintf(extra, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
               fromX, fromY, toX, toY, cor);
}
bool crossEdge(Graph g, Edge e, double* td, double* tf, void *extra){
     double fromX=getNodeX(g, getFromNode(g, e));
     double fromY=getNodeY(g, getFromNode(g, e));
     double toX=getNodeX(g, getToNode(g, e));
     double toY=getNodeY(g, getToNode(g, e));
     char cor[63]="black";
     fprintf(extra, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
               fromX, fromY, toX, toY, cor);
}
void gerarSvg(SmuTreap t, char* fn, Lista paths, Graph g){
     FILE* f=fopen(fn, "w");
     if(f==NULL){
          return;
     }

     fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
     fprintf(f, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n");

     visitaProfundidadeSmuT(t, &svgNo, f);
     if(paths!=NULL){
          svgPath(f, paths, g);
     }
     if(g!=NULL){
          //graphSvg(g, f);
          //dfs(g, 1, &treeEdge, &forwardEdge, &returnEdge, &crossEdge, NULL, f);
     }

     fprintf(f, "</svg>\n"); 
}
