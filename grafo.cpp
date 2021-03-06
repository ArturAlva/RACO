#include <vcl.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <conio>
#include <queue>
#include <stdio.h>
#include <fstream>
using namespace std;


typedef struct queue *QUEUE;
typedef struct node *link;
typedef struct gnode *bins;
typedef struct Glist *glist;
typedef struct graph *Graph;
typedef struct resp *Resp;
typedef struct req *Req;
typedef struct lreq *Lreq;
typedef struct ordem *Ordem;
typedef struct lord *Lord;
Graph GRAPHinit(int V);
void GRAPHinsertArc(Graph G);
/*estruturas*/
struct gnode{
        Graph g;
        bins next;
};

struct Glist{
        bins ini;
        bins fim;
        int q;
};

struct node{
        int w;
        link next;
};

/*ordem requisi�ao*/
struct ordem{
        int I;
        int O;
        Ordem prox;
        };

struct lord{
        Ordem ini;
        };

struct graph{
        int V;
        int A;
        link *adj;
};

struct resp{
        int V;
        bool c;
        link next;
};

struct queue { /* aqui esta especificado o que e' */
  link inicio; /* uma fila: dois apontadores para QUEUEnode */
  link fim;
};
/*lista de resposta*/
struct req{
        int o;
        int f;
        Resp r;
        Req next;
};

struct lreq{
        Req ini;
        };

/*fun�oes para lista*/
int glist_vazia(glist l){
        if(l->ini == NULL ){
                if(l->fim == NULL)
                         return 1;
         }
        else
                return 0;}

glist crialista(){
        glist l = new struct Glist;
        l->ini =NULL;
        l-> fim =NULL;
        l->q=0;
        return l;
}



static link NEWnode( int w, link next){
        link a= new struct node ;
        a->w=w;
        a->next=next;
        return a;
}
/*fun�ao de criar um novo grafo*/
static glist NEWgnode(glist x,int v){
        bins novo = new struct gnode;
        novo->next = NULL;
        novo->g = GRAPHinit(v);
        if(glist_vazia(x)){
                x->ini = novo;
                x->fim = novo;
                x->q++;
                GRAPHinsertArc(novo->g);
                return x;
        }
        else
                x->fim->next = novo;
                x->fim = novo;
                x->q++;
                GRAPHinsertArc(novo->g);
                return x;



}


/*iniciar um grafo*/
Graph GRAPHinit(int V){
Graph G = new struct graph;
G->V=V;
G->A=0;
G->adj=new link[V];
for (int v=0; v<V; ++v){
        G->adj[v]=NULL;
        }
return G;}

 void GRAPHinsertArc(Graph G){
 int i,j;
 int ad[14][14];
 link aux;
 std::ifstream file ("adj.txt");
printf("\n");
if(!file){
        printf("\n Erro de leitura.");
        return ;
}
 for(i=0;i<14;i++){
   for(j=0;j<14;j++){
        file>>ad[i][j];
        printf(" %d ",ad[i][j]) ;
   }
      printf("\n");
}
 for(i=0;i<14;i++){
 for(j=0;j<14;j++){
        if(ad[i][j]==1){
                if(G->adj[i]==NULL){
                        G->adj[i]=NEWnode(j+1 ,G->adj[i]);
                                G->A++;}
                else{
                for(aux=G->adj[i];aux!=NULL;aux=aux->next){
                if(aux->w != j+1){
                        G->adj[i]=NEWnode(j+1 ,G->adj[i]);
                        G->A++;
                        break;}
                }}

        }

   }
 }

return;
}


static int num[1000];

/*fun�oes da fila
QUEUE QUEUEinit()
{
  QUEUE q = new struct queue;
  q->inicio = NULL;
  q->fim = NULL;
  return q;
}*/

/*int QUEUEempty(QUEUE q)
{
  return q->inicio == NULL;
}

void QUEUEput(QUEUE q, int item)
{
  if (q->inicio == NULL)
    {
      q->fim = NEWnode(item, NULL);
      q->inicio = q->fim;
    }
  q->fim->next = NEWnode(item, NULL);
  q->fim = q->fim->next;
}

int QUEUEget(QUEUE q)
{
  int item = q->inicio->w;
  link t = q->inicio->next;
  free(q->inicio);
  q->inicio = t;
  return item;
}

void QUEUEfree(QUEUE q)
{
  while (q->inicio != NULL)
    {
      link t = q->inicio->next;
      free(q->inicio);
      q->inicio = t;
    }
  free(q);
}*/
/*fun�ao para achar o H*/
/*int GRAPHbfs( Graph G, int s){
int cnt=0;
QUEUE q;
/*q=QUEUEinit();*/
/*for(int v=0;v<G->V;v++){
num[v]=-1;
/*QUEUEput(q,v);
}
/*QUEUEput(q,s-1);
num[s-1]=cnt++;
num[cnt]=cnt++;
while(!QUEUEempty(q)){
        int v=QUEUEget(q);
        for(link a=G->adj[v];a!=NULL;a=a->next){
                if(num[a->w]==-1){
                num[a->w]=cnt++;
                QUEUEput(q,a->w);
                }
 }
 QUEUEfree(q);
 }
 return cnt;
 }*/


 typedef struct link2 Link2;
struct link2
  {
    int dist;
    int visitado;
    int anterior;
  };
Resp dijkstra(int o, int f, Graph g)
  {
    Link2 *Q;
    int inf,menor, menor_id,tamQ;

    inf = g->V +1;
    Q = new Link2[g->V];
    tamQ = g->V;
    for (int i=0; i<g->V; i++)
      {
        /*Q[i]->id = i;*/
        if(i==o-1) Q[i].dist = 0;
        else Q[i].dist = inf;
        Q[i].visitado = 0;
        Q[i].anterior = -1;

      }
    menor_id = o;
    menor = 0;
    while((tamQ>0)&&(menor<inf))
      {
        for(link j = g->adj[menor_id-1]; j !=NULL; j = j->next)
          {
            if(!Q[j->w-1].visitado)
              {
                int dist_aux = Q[menor_id-1].dist + 1;
                if (dist_aux<Q[j->w-1].dist)
                  {
                    Q[j->w-1].dist = dist_aux;
                    Q[j->w-1].anterior = menor_id;
                  }
              }
          }
        Q[menor_id-1].visitado =1;
        if (menor_id == f) break;
        tamQ = tamQ-1;
        menor= g->V +1;
        if (tamQ >0)
          {
            for(int i = 0; i < g->V; i++)
              {
                if (!Q[i].visitado)
                  {
                    if (Q[i].dist < menor)
                      {
                        menor_id = i+1;
                        menor = Q[i].dist;
                      }
                  }
              }
          }
      }
      Resp r = new struct resp;
      if (Q[f-1].visitado)
        {
          r->V = Q[f-1].dist;
          r->c =1;
          r->next = NULL;

          int id = f;
          r->next = NEWnode(id,r->next);
          while(id !=o)
            {
              id = Q[id-1].anterior;
              r->next = NEWnode(id,r->next);
            }
        }
      else
        {
          r->V = g->V+1;
          r->c = 0;
          r->next = NULL;
        }
      return r;
    }

/*fun�ao para excluir o caminho ja usado*/
void exclui_aresta(Graph g , Resp r){
printf("\n exclui aresta");
        link i,j,k;
        int m;
        for(i=r->next, j= r->next->next; j!=NULL;i=j,j=j->next){
                m=i->w;
                for(k=g->adj[m-1]; k!=NULL; k=k->next){
                        if(k->w== j->w){
                                link aux = k;
                                g->adj[m-1]= k ->next;
                                free (aux);
                                break;
                                }
                }
        }

}

Lord ordena(int V){
glist O;
O=crialista();
O=NEWgnode(O,V);
link q;
int cont=0,i,j,k=0;
Lord Vord = new struct lord;
Vord->ini=NULL;
Ordem l;
int **or=new int*[V];
for(i=0;i<V;i++){
        or[i] = new int[V];
        }
int **ror=new int*[V];
for(i=0;i<V;i++){
        ror[i] = new int[V];
        }


/*ordena�ao das requisi�oes*/
std::ifstream file1 ("ord.txt");

if(!file1){
        cout<<"\n Erro de leitura.";
        }

for(i=0;i<V;i++){
   for(j=0;j<V;j++){
        file1>>or[i][j];
   }
      printf("\n");
}

/*fechar arquivo*/
file1.close();

for(i=0;i<V;i++){
        for(j=0;j<V;j++){
        if(or[i][j]==0){
                ror[i][j]=0;}
                while(or[i][j]!=0){
                        Resp ord = new struct resp;
                        ord = NULL;
                        ord=dijkstra(i+1,j+1,O->ini->g);
                                if(ord->c==1){
                                        ror[i][j] = ord->V;
                                        or[i][j]--;
                                        cont++;

                                        }
                        }

                }
        }
for(i=0;i<V;i++){
        for(j=0;j<V;j++){
                cout<<" "<<ror[i][j];
                }
        cout<<"\n";
        }




int *ordR=new int[cont];
for(i=0;i<V;i++){
        for(j=0;j<V;j++){
                if(ror[i][j]!=0){
                        ordR[k]=ror[i][j];
                        k++;}
                }
        }
/*ordenar o vetor*/
int aux;
for(i = 0;i<cont;i++){
    for(j=i+1; j<cont;j++)
    {
      if (ordR[i] > ordR[j])
      {
         aux = ordR[i];
         ordR[i] = ordR[j];
         ordR[j] = aux;
      }
    }
  }

int C=cont-1;
cout <<"\n C:"<< cont;
while(C> 0){
cout<<"\nintera�ao C:"<<C;
for(i=0;i<V;i++){
        for(j=0;j<V;j++){
                if(ror[i][j]==ordR[C]){
                                Ordem OR= new struct ordem;
                                OR->I=i+1;
                                OR->O=j+1;
                                OR->prox=Vord->ini;
                                Vord->ini = OR;
                                C--;
                                }

                }
}
}

cout<<"\n\nCCC:"<<C;
int ba=0;
for(l=Vord->ini; l!=NULL; l=l->prox){
        ba++;
        cout << "\n\n\n Origem :"<< l->I;
        cout << "\nDestino :"<< l->O;

        }
cout<<"\n\nba:"<<ba;
cout<<"\n";


return Vord;
}


int main(){
glist B;
int v,y,i,j;
link te;
std::ifstream file2 ("tamanho.txt");

if(!file2){
        printf("\n Erro de leitura.");
        return 0;}
file2>>v;

file2.close();

int **r=new int*[v];
for(i=0;i<v;i++){
        r[i] = new int[v];
        }
B=crialista();
B=NEWgnode(B,v);
Lord Lordena= ordena(v);
Ordem l;

/* inicio da criacao da matriz de requisicao*/
std::ifstream file ("matriz.txt");

if(!file){
        printf("\n Erro de leitura.");
        return 0;
};
for(i=0;i<v;i++){
   for(j=0;j<v;j++){
        file>>r[i][j];
   }
}
file.close();

for(l=Lordena->ini;l!=NULL;l=l->prox){
        i=l->I;
        j=l->O;
        while(r[i-1][j-1]>0){
        Resp road = new struct resp;
        road = NULL;
        road=dijkstra(i,j,B->ini->g);
        printf("\n tem caminho de %d para %d: %d",l->I,l->O, road->c);
        for(te=road->next;te!=NULL;te=te->next){
        printf("\nC:%d",te->w);}
        cout<<"\nTamanho: "<<road->V;
        if(road->c==1){
                exclui_aresta(B->ini->g, road);
                r[i-1][j-1]--;
                }
        if(road->c==0){
                B=NEWgnode(B,v);
                GRAPHinsertArc(B->ini->g);
                }
        printf("\nG:%d",B->q);
        }
}







/*for(i=0;i<14;i++){
        for(j=0;j<14;j++){
                while(r[i][j]!=0){
                        Resp road = new struct resp;
                        road = NULL;
                        road=dijkstra(i+1,j+1,B->ini->g);
                        printf("\n tem caminho de %d para %d: %d",i+1,j+1, road->c);
                        for(te=road->next;te!=NULL;te=te->next){
                                printf("\nC:%d",te->w);}
                                if(road->c==1){
                                        exclui_aresta(B->ini->g, road);
                                        r[i][j]--;
                                        }
                                if(road->c==0){
                                        B=NEWgnode(B,v);
                                        GRAPHinsertArc(B->ini->g);
                                        }
                         printf("\nG:%d",B->q);
                        }

                }

        }*/
        printf("\n");
for(i=0;i<v;i++){
        for(j=0;j<v;j++){
                printf(" %d ",r[i][j]);}
                printf("\n");
                }



getch();
        return 0;
}

