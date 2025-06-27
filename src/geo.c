#include "geo.h"
#include "retangulo.h"
#include "circulo.h"
#include "linha.h"
#include "quadra.h"
#include "svg.h"
#include "smutreap.h"
#include "texto.h"
#include "boundingBox.h"
#include <stdio.h>
#include <string.h>

void comandosGeo(SmuTreap t, char* fn){
     printf("arquivo geo: %s\n", fn);
     FILE* f=fopen(fn, "r");
     if(f==NULL){
          printf("não foi possível acessar arquivo geo\n");
          return;
     }
     char comando[5];
     while(fscanf(f, "%s", comando)!=EOF){
          printf("entro while\n");
          printf("comando: %s\n", comando);
          if(strcmp(comando, "cq")==0){
               char strW[30];
               char cfill[30];
               char cstrk[30];
               fscanf(f, "%s", strW);
               fscanf(f, "%s", cfill);
               fscanf(f, "%s", cstrk);
               mudaEstiloQuad(strW, cfill, cstrk);
          }else if(strcmp(comando, "q")==0){
               char cep[60];
               double x, y;
               double w, h;
               char corb[30];
               char corp[30];
               fscanf(f, "%s" , cep);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               fscanf(f, "%lf" , &w);
               fscanf(f, "%lf" , &h);
               insertSmuT(t, x, y, criaQuadra(cep, x, y, w, h), QUADRA, &calculabb);
          }else if(strcmp(comando, "c")==0){
               int i;
               double x, y;
               double r;
               char corb[30];
               char corp[30];
               fscanf(f, "%i" , &i);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               fscanf(f, "%lf" , &r);
               fscanf(f, "%s" , corb);
               fscanf(f, "%s" , corp);
               insertSmuT(t, x, y, criaCirculo(i, x, y, r, corb, corp), CIRCULO, &calculabb);
          }else if(strcmp(comando, "l")==0){
               int i;
               double x, y;
               double x2, y2;
               char cor[30];
               fscanf(f, "%i" , &i);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               fscanf(f, "%lf" , &x2);
               fscanf(f, "%lf" , &y2);
               fscanf(f, "%s" , cor);
               insertSmuT(t, x, y, criaLinha(i, x, y, x2, y2, cor), LINHA, &calculabb);
          }else if(strcmp(comando, "t")==0){
               int i;
               double x, y;
               char corb[30];
               char corp[30];
               char a;
               char texto[256];
               fscanf(f, "%i" , &i);
               fscanf(f, "%lf" , &x);
               fscanf(f, "%lf" , &y);
               fscanf(f, "%s" , corb);
               fscanf(f, "%s" , corp);
               fscanf(f, " %c" , &a);
               fscanf(f, "%s" , texto);
               int len=strlen(texto);
               for(int i=0; i<len-1; i++){
                    texto[i]=texto[i+1];
               }
               texto[len-2]='\0';
               insertSmuT(t, x, y, criaTexto(i, x, y, corb, corp, a, texto), TEXTO, &calculabb);
          }
     }

     fclose(f);
}
