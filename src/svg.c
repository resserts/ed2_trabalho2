#include "svg.h"
#include "lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "texto.h"
#include "quadra.h"
#include "smutreap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
     double x, y;
     char l;
}StLetra;

Letra criaLetra(double x, double y, char l){
     StLetra* letra=(StLetra*)malloc(sizeof(StLetra));
     letra->l=l;
     letra->x=x;
     letra->y=y;
}
void svgLetras(FILE* f, Lista letras){
     for(int i=0; getValor(letras, i); i++){
          StLetra* letra=getValor(letras, i);
          fprintf(f, "<text x=\"%f\" y=\"%f\" fill=\"#ff0000\" font-family=\"sans\" font-size=\"12px\" text-anchor=\"middle\" >%c</text>\n",letra->x, letra->y, letra->l);
     }
}

void svgNo(SmuTreap t, Node n, Info i, double x, double y, void *aux){
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
               if(getRetId(i)==-1){
                    fprintf(aux, "fill-opacity=\"0\" ");
               }
               fprintf(aux, "/>\n"); 
               break;
          case CIRCULO:
               fprintf(aux, "<circle cx=\"%f\" cy=\"%f\" r=\"%f\" stroke=\"%s\" fill=\"%s\" />\n",
                         x, y, getCircRaio(i), getCircCorb(i), getCircCorp(i));
               break;
          case LINHA:
               fprintf(aux, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",
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
void gerarSvg(SmuTreap t, char* fn, Lista letras){
     FILE* f=fopen(fn, "w");
     if(f==NULL){
          return;
     }

     fprintf(f, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
     fprintf(f, "<svg version=\"1.1\" xmlns=\"[http://www.w3.org/2000/svg](http://www.w3.org/2000/svg)\">\n");

     visitaProfundidadeSmuT(t, &svgNo, f);
     if(letras!=NULL){
          svgLetras(f, letras);
     }

     fprintf(f, "</svg>\n"); 
}
