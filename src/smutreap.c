#include "smutreap.h"
#include "boundingBox.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <math.h>


typedef struct aux{
     double prioridade;
     double x,y;
     Info info;
     DescritorTipoInfo descritor;
     Info bbinfo;
     Info bbsa;
     struct aux* dir;
     struct aux* esq;
}StNode;
typedef struct {
     int hitCount;
     int maxPrio;
     double promotionRate;
     double epsilon;
     StNode* raiz;
}StSmutreap;

SmuTreap newSmuTreap(int hitCount, double promotionRate, double epsilon, int maxPrio){
     srand(time(NULL));
     StSmutreap* t=(StSmutreap*)malloc(sizeof(StSmutreap));
     if(hitCount>=1){
          t->hitCount=hitCount;
     }
     if(promotionRate>0){
          t->promotionRate=promotionRate;
     }
     t->maxPrio=maxPrio;
     t->epsilon=epsilon;
     t->raiz=NULL;
     printf("Smutreap criada\n");
     return t;
}

NodeSmut criaNo(double x, double y, Info i, DescritorTipoInfo d, int maxPrio){
     StNode* n=(StNode*)malloc(sizeof(StNode));
     n->prioridade=rand()%maxPrio;
     n->x=x;
     n->y=y;
     n->info=i;
     n->descritor=d;
     double bbx, bby, w, h;

     calculabb(d, i, &bbx, &bby, &w, &h);
     n->bbinfo=criabb(bbx, bby, w, h);
     n->bbsa=criabb(bbx, bby, w, h);
     n->dir=NULL;
     n->esq=NULL;
     return n;
}

double getPrioridade(StNode* r){
     if(r!=NULL){
          return r->prioridade;
     }
     return 0;
}

bool igual(double x, double y, StNode* r, double epsilon){
     if(fabs(x-r->x)<epsilon && fabs(y-r->y)<epsilon){
          return true;
     }else{
          return false;
     }
}
bool menor(double x, double y, StNode* r, double epsilon){
     if(x<r->x){
          return true;
     }else if(fabs(x-r->x)<epsilon && y<r->y){
          return true;
     }else{
          return false;
     }
}

StNode* rotaDireita(StNode* r){
     StNode* q=r->esq;
     StNode* aux=q->dir;
     q->dir=r;
     r->esq=aux;
     return q;
}
StNode* rotaEsquerda(StNode* r){
     StNode* q=r->dir;
     StNode* aux=q->esq;
     q->esq=r;
     r->dir=aux;
     return q;
}

StNode* rebalanceie(StNode* r){
     double prioE = getPrioridade(r->esq);
     double prioD = getPrioridade(r->dir);
     double prioR = getPrioridade(r);
     double maxPrioFilhos=(prioD>prioE) ? prioD : prioE;
     if(prioR>=maxPrioFilhos){
          return r;
     }

     StNode* nr;
     if(prioE>prioD){
          nr=rotaDireita(r);
     }else{
          nr=rotaEsquerda(r);
     }
     //printf("retorno %d\n", nr->prioridade);
     return nr;
}

void simetrica(StNode* raiz){
    if(raiz->esq!=NULL){
        simetrica(raiz->esq);
    }
    printf("%f, %f| |", raiz->x, raiz->y);
    if(raiz->dir!=NULL){
        simetrica(raiz->dir);
    }
}
NodeSmut insertAux(StSmutreap* t, double x, double y, StNode* r, Info i, DescritorTipoInfo d){
     if(r==NULL){
          StSmutreap* treap=t;
          StNode* n=criaNo(x, y, i, d, t->maxPrio);
          return n;
     }
     
     StNode* nr=r;
     if(igual(x, y, r, t->epsilon)){
          return r;
     }else if(menor(x, y, r, t->epsilon)){
          nr = insertAux(t, x, y, r->esq, i, d);
          r->esq=nr;
     }else{
          nr = insertAux(t, x, y, r->dir, i, d);
          r->dir=nr;
     }
     
     nr=rebalanceie(r);
     if(nr->dir){
          uniaobb(nr->bbsa, nr->dir->bbsa, NULL);
     }
     if (nr->esq) {
          uniaobb(nr->bbsa, NULL, nr->esq->bbsa);
     
     }
     return nr;
}

NodeSmut insertSmuT(SmuTreap t, double x, double y, Info i, DescritorTipoInfo d, FCalculaBoundingBox fCalcBb){
     StSmutreap* treap=t;
     StNode* r=treap->raiz;
     treap->raiz=insertAux(treap, x, y, r, i, d);
     return getNodeSmuT(t, x, y);
}


StNode* getNodeaux(StNode* n, double x, double y, double epsilon){
     if(n==NULL){
          return NULL;
     }

     if(igual(x, y, n, epsilon)){
          return n;
     }else if(menor(x, y, n, epsilon)){
          return getNodeaux(n->esq, x, y, epsilon);
     }else{
          return getNodeaux(n->dir, x, y, epsilon);
     }
}
NodeSmut getNodeSmuT(SmuTreap t, double x, double y){
     StSmutreap* st = (StSmutreap*)t;
     return getNodeaux(st->raiz, x, y, st->epsilon);
}

DescritorTipoInfo getTypeInfoSrbT(SmuTreap t, NodeSmut n){
     StNode* noaux= (StNode*)n;
     return noaux->descritor;
}

void promoteNodeSmuT(SmuTreap t, NodeSmut n, double promotionRate){
     StNode* node= (StNode*)n;
     node->prioridade*=promotionRate;
     //TODO: rebalancear de acordo com nova prioridade.
}

StNode* removeaux(StNode* raiz, StNode* n, double epsilon){
     if(raiz==NULL){
          return raiz;
     }

     //printf("raiz(%x)->prio %f\n", raiz, raiz->prioridade);
     StNode* nr=raiz;
     if(raiz==n){
          if(raiz->esq==NULL){
               if(raiz==n){
                    StNode* dir=raiz->dir;
                    free(raiz);
                    return dir;
               }
               if(raiz->dir==n){
                    free(raiz->dir);
                    raiz->dir=NULL;
                    return raiz;
               }
               return raiz;
          }
          if(raiz->dir==NULL){
               if(raiz==n){
                    StNode* esq=raiz->esq;
                    free(raiz);
                    return esq;
               }
               if(raiz->esq==n){
                    free(raiz->esq);
                    raiz->esq=NULL;
                    return raiz;
               }
               return raiz;
          }
          double prioD=getPrioridade(raiz->dir);
          double prioE=getPrioridade(raiz->esq);
          if(prioD>prioE){
               nr=rotaEsquerda(raiz);
               nr->esq=removeaux(nr->esq, n, epsilon);
          }else{
               nr=rotaDireita(raiz);
               nr->dir=removeaux(nr->dir, n, epsilon);
          }
     }else{
          if(menor(n->x, n->y, raiz, epsilon)){
               nr->esq=removeaux(raiz->esq, n, epsilon);
          }else{
               nr->dir=removeaux(raiz->dir, n, epsilon);
          }
     }

     return nr;
}
void removeNoSmuT(SmuTreap t, NodeSmut n){
     StSmutreap* st=(StSmutreap*)t;
     st->raiz=removeaux(st->raiz, n, st->epsilon);
}

Info getInfoSmuT(SmuTreap t, NodeSmut n){
     StNode* node=(StNode*)n;
     return node->info;
}

Info getBoundingBoxSmuT(SmuTreap t, NodeSmut n, double *x, double *y, double *w, double *h){
     StNode* node=(StNode*)n;
     return node->bbinfo;     
}

void getInfoAtingidoaux(StSmutreap* t, StNode* n, double x, double y, FpontoInternoAInfo f, Lista l){
     if(n==NULL){
          return;
     }
     if(f(t, n, n->info, x, y)){
          insertList(l, n, 0);
     }
     getInfoAtingidoaux(t, n->dir, x, y, f, l);
     getInfoAtingidoaux(t, n->esq, x, y, f, l);
}
bool getInfosAtingidoPontoSmuT(SmuTreap t, double x, double y, FpontoInternoAInfo f, Lista L){
     StSmutreap* smut=t;
     getInfoAtingidoaux(t, smut->raiz, x, y, f, L);
     if(getValor(L, 0)){
          return true;
     }
     return false;
}
/* Insere na lista L  os nos para os quais o ponto (x,y) possa ser considerado
  interno 'as  informacoes associadas ao no'. A funcao f e' invocada para determinar
  se o ponto (x,y) e' interno a uma informacao especifica.
  Retorna falso caso nao existam informacoes internas; verdadeiro, caso contrario.
 */

void profundidadeaux(SmuTreap t, StNode* n, FvisitaNo f, void* aux){
     if(n==NULL){
          return;
     }
     f(t, n, n->info, n->x, n->y, aux);
     profundidadeaux(t, n->esq, f, aux);
     profundidadeaux(t, n->dir, f, aux);
}
void visitaProfundidadeSmuT(SmuTreap t, FvisitaNo f, void *aux){
     StSmutreap* st=(StSmutreap*)t;
     profundidadeaux(t, st->raiz, f, aux);
}


void visitaLarguraSmuT(SmuTreap t, FvisitaNo f, void *aux){
     //TODO
}
/* Similar a visitaProfundidadeSmuT, porem, faz o percurso em largura.
 */


bool ancoraDentroRegiao(StNode* n, double xmax, double xmin, double ymax, double ymin){
     if(n->x >= xmin && n->x <= xmax && n->y >= ymin && n->y <= ymax){
          return true;
     }
     return false;
}
void getNodesDentroaux(StNode* n, double xmax, double xmin, double ymax, double ymin, Lista l){
     if(n==NULL){
          return;
     }
     if(!ancoraDentroRegiao(n, getbbx(n->bbsa), getbbWidth(n->bbsa), getbby(n->bbsa), getbbHeight(n->bbsa))){
         return; 
     }
     if(ancoraDentroRegiao(n, xmax, xmin, ymax, ymin)){
          insertList(l, n, 0);
          getNodesDentroaux(n->dir, xmax, xmin, ymax, ymin, l);
          getNodesDentroaux(n->esq, xmax, xmin, ymax, ymin, l);
     }
}
bool getNodesDentroRegiaoSmuT(SmuTreap t, double x1, double y1, double x2, double y2, Lista L){
     StSmutreap* smut=t;
     StNode* n=smut->raiz;
     getNodesDentroaux(n, x2, x1, y2, y1, L);
     if(getValor(L, 0)){
          return true;
     }
     return false;
}

void getInfosDentroaux(StSmutreap* t, StNode* n, double x1, double y1, double x2, double y2, FdentroDeRegiao f, Lista L){
     if(n==NULL){
          return;
     }
    // if(bbDentro(t, n, n->bbsa, x1, y1, x2, y2)){
    //      return;
    // }
     if(f(t, n, n->bbinfo, x1, y1, x2, y2)){
          printf("entro para inserir %i\n", getTypeInfoSrbT(t, n));
          insertList(L, n, 0);
     }
     getInfosDentroaux(t, n->dir, x1, y1, x2, y2, f, L);
     getInfosDentroaux(t, n->esq, x1, y1, x2, y2, f, L);
}
bool getInfosDentroRegiaoSmuT(SmuTreap t, double x1, double y1, double x2, double y2,
				 FdentroDeRegiao f, Lista L){
     StSmutreap* smut=t;
     StNode* n=smut->raiz;
     getInfosDentroaux(smut, n, x1, y1, x2, y2, f, L);

     if(getValor(L, 0)){
          return true;
     }
     return false;
}

NodeSmut procuraaux(SmuTreap t, StNode* n, FsearchNo f, void* aux){
     if(n==NULL){
          return NULL;
     }
     if(f(t, n, n->info, n->x, n->y, aux)){
          return n;
     }
     NodeSmut nr=NULL;
     if(nr=procuraaux(t, n->esq, f, aux)){
          return nr;
     }
     return procuraaux(t, n->dir, f, aux);
}
NodeSmut procuraNoSmuT(SmuTreap t, FsearchNo f, void *aux){
     StSmutreap* smut=t;
     return procuraaux(t, smut->raiz, f, aux);
}

int printSmuAux(StNode* n, FILE* f, int* index){
     if(n==NULL){
          return 0;
     }
     *index=(*index)+1;
     int nIndex=*index;
     fprintf(f, "\tn%d[label=\"%f\nx=%f, y=%f\"];\n", nIndex, n->prioridade, n->x, n->y);
     int i;
     if(i=printSmuAux(n->esq, f, index)){
          fprintf(f, "\tn%d->n%d;\n", nIndex, i);
     }
     if(i=printSmuAux(n->dir, f, index)){
          fprintf(f, "\tn%d->n%d;\n", nIndex, i);
     }

     return nIndex;
}
bool printDotSmuTreap(SmuTreap t, char *fn){
     FILE* f = fopen(fn, "w");
     if(f==NULL){
          return false;
     }

     StSmutreap* treap=(StSmutreap*)t;
     fprintf(f, "digraph \"\"\n{\n");
     int i=0;
     printSmuAux(treap->raiz, f, &i);
     fprintf(f, "}");

     fclose(f);
     return true;
}


double getEpsilon(SmuTreap t){
     StSmutreap* smut=t;
     return smut->epsilon;
}
