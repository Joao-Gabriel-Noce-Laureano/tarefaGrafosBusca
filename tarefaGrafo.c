#include <stdio.h>
#include <stdlib.h>

// Definições de tipos
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

// Estruturas de dados para o grafo
typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
	int nroVizinhos;
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

// Função para criar um grafo
GRAFO *criaGrafo(int v) {
    int i;

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

    for (i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
        g->adj[i].nroVizinhos = 0;
    }
    return g;
}

// Função para criar uma adjacência
ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

// Função para criar uma aresta
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
    if (!gr)
        return false;
    if ((vf < 0) || (vf >= gr->vertices))
        return false;
    if ((vi < 0) || (vf >= gr->vertices))
        return false;

    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].nroVizinhos++;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

// Função para imprimir a lista de adjacência do grafo
void imprimeLista (GRAFO *gr){
	
	printf("Vertices: %d. Arestas: %d. \n", gr->vertices, gr->arestas); 
	int i;
	for (i=0; i<gr->vertices; i++){
		printf("v%d: ",i);
		ADJACENCIA *ad = gr->adj[i].cab; 
			while(ad){ 
				printf("v%d (%d) ", ad->vertice, ad->peso); 
				ad = ad->prox; 
			}
		printf("\n");
	}
}

// Função para imprimir a matriz do grafo
void imprimeMatriz(GRAFO *gr) {
    int i, j;
    printf("Matriz do Grafo:\n");

    for (i = 0; i < gr->vertices; i++) {
        for (j = 0; j < gr->vertices; j++) {
            ADJACENCIA *ad = gr->adj[i].cab;
            bool adjacente = false;

            while (ad) {
                if (ad->vertice == j) {
                    printf("%d ", ad->peso);
                    adjacente = true;
                    break;
                }
                ad = ad->prox;
            }

            if (!adjacente) {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Função para imprimir o valor total do caminho de {1, 5}
void imprimeValorCaminho(GRAFO *gr) {
	int valorTotal = 0;
	ADJACENCIA *ad = gr->adj[0].cab; 
    
    
    while(ad){ 
    	if(ad->vertice == 2)
		{
			valorTotal += ad->peso;
			ad = gr->adj[2].cab; 
			break;
		} 
		ad = ad->prox; 
	}
	
	while(ad){ 
    	if(ad->vertice == 3)
		{
			valorTotal += ad->peso;
			ad = gr->adj[3].cab; 
			break;
		} 
		ad = ad->prox; 
	}
	
	while(ad){ 
    	if(ad->vertice == 4)
		{
			valorTotal += ad->peso;
			ad = gr->adj[4].cab; 
			break;
		} 
		ad = ad->prox; 
	}
	printf("O valor total do caminho de {1, 5} eh: %d\n", valorTotal);

}



void buscaEmLargura (GRAFO *gr, int inicio) {
	int *visitado = (int *)malloc(gr->vertices * sizeof(int));
    int i;

    for (i = 0; i < gr->vertices; i++) {
        visitado[i] = false;
    }

    int *fila = (int *)malloc(gr->vertices * sizeof(int));
    int frente = 0, tras = 0;

    printf("Busca em Largura a partir do vertice %d: ", inicio);
    printf("%d ", inicio);
    visitado[inicio] = true;
    fila[tras++] = inicio;

    while (frente != tras) {
        int atual = fila[frente++];
        ADJACENCIA *ad = gr->adj[atual].cab;

        while (ad) {
            int vizinho = ad->vertice;
            if (!visitado[vizinho]) {
                printf("%d ", vizinho);
                visitado[vizinho] = true;
                fila[tras++] = vizinho;
            }
            ad = ad->prox;
        }
    }

    printf("\n");
    free(visitado);
    free(fila);

}

void buscaEmProfundidadeRec(GRAFO *gr, int inicio, int *visitado, int *ordem, int *contador) {
     printf("%d ", inicio);
    visitado[inicio] = true;
    ordem[*contador] = inicio;
    (*contador)++;

    ADJACENCIA *ad = gr->adj[inicio].cab;
    while (ad) {
        int vizinho = ad->vertice;
        if (!visitado[vizinho]) {
            buscaEmProfundidadeRec(gr, vizinho, visitado, ordem, contador);
            ordem[*contador] = inicio;
            (*contador)++;
        }
        ad = ad->prox;
    }


    
    
}


void buscaEmProfundidade(GRAFO *gr, int inicio) {
    int *visitado = (int *)malloc(gr->vertices * sizeof(int));
    int *ordem = (int *)malloc(gr->vertices * 10 * sizeof(int));
    int contador = 0;
    int i;

    printf("Busca em Profundidade a partir do vertice %d: ", inicio);

    for (i = 0; i < gr->vertices; i++) {
        visitado[i] = false;
        ordem[i] = 0;
    }

    buscaEmProfundidadeRec(gr, inicio, visitado, ordem, &contador);

    printf("\nOrdem de passagem: ");
    for (i = 0; i < contador; i++) {
        printf("%d ", ordem[i]);
    }

    printf("\n");
    free(visitado);
    free(ordem);
}



int main() {
    GRAFO *grafo = criaGrafo(15);
    criaAresta(grafo, 0, 1, 1);
	criaAresta(grafo, 0, 2, 1);
	criaAresta(grafo, 1, 3, 1);
	criaAresta(grafo, 1, 4, 1);
	criaAresta(grafo, 1, 5, 1);
	criaAresta(grafo, 3, 6, 1);
	criaAresta(grafo, 3, 7, 1);
	criaAresta(grafo, 5, 8, 1);
	criaAresta(grafo, 5, 9, 1);
	criaAresta(grafo, 7, 10, 1);
	criaAresta(grafo, 7, 11, 1);
	criaAresta(grafo, 7, 12, 1);
	criaAresta(grafo, 9, 13, 1);
	criaAresta(grafo, 9, 14, 1);
   

	imprimeLista(grafo);
   	printf("\n");
   	buscaEmLargura(grafo, 1);
	printf("\n");
	printf("---------------\nGrafo 2:\n");
	
	GRAFO *grafo2 = criaGrafo(10);
    criaAresta(grafo2, 0, 1, 1);
	criaAresta(grafo2, 1, 2, 1);
	criaAresta(grafo2, 1, 4, 1);
	criaAresta(grafo2, 2, 3, 1);
	criaAresta(grafo2, 2, 4, 1);
	criaAresta(grafo2, 2, 9, 1);
	criaAresta(grafo2, 3, 4, 1);
	criaAresta(grafo2, 4, 5, 1);
	criaAresta(grafo2, 4, 6, 1);
	criaAresta(grafo2, 4, 7, 1);
	criaAresta(grafo2, 5, 6, 1);
	criaAresta(grafo2, 7, 8, 1);
	criaAresta(grafo2, 7, 9, 1);
    
    imprimeLista(grafo2);
	printf("\n");
	buscaEmProfundidade(grafo2, 0);
    return 0;
}
