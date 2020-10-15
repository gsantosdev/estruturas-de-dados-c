#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define lbuffer() while(getchar() != '\n')

#define bool int
#define true 1
#define false 0





typedef struct cidade
{
    char nome[50];
    float x;
    float y;
} CIDADE;

typedef struct grafo
{
    int Ncidades;
    int Ncaminhos;
    float **caminhos;
    CIDADE *cidades;
} GRAFO;






GRAFO *criaGrafo(int Ncidades)
{
    int i, j;

    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO));
    if (!g) return NULL;

    g->Ncidades = Ncidades;
    g->Ncaminhos = 0;

    g->caminhos = (float **) malloc( sizeof(float *) * Ncidades);

    for(i = 0; i < Ncidades ; i++)
        g->caminhos[i] = (float *) malloc( sizeof(float) * Ncidades);

    for(i = 0; i < Ncidades; i++)
        for (j = 0; j < Ncidades; j++)
            g->caminhos[i][j] = 0;

    g->cidades = (CIDADE *) malloc(sizeof(CIDADE) * Ncidades);
    for (i = 0; i < Ncidades; i++)
    {
        strcpy(g->cidades[i].nome, "");
        g->cidades[i].x = 0;
        g->cidades[i].y = 0;
    }

    return g;
}

void criarCidades(GRAFO **g)
{
    int Ncidades;
    int i;

    printf("Insira o numero de cidades: ");
    scanf("%d", &Ncidades);
    printf("\n");

    *g = criaGrafo(Ncidades);

    for (i = 0; i < Ncidades; i++)
    {
        lbuffer();
        printf("Insira o nome da %da. cidade: ", i + 1);
        scanf("%s", (*g)->cidades[i].nome);
        printf("Insira a posicao x da %da. cidade: ", i + 1);
        scanf("%f", &(*g)->cidades[i].x);
        printf("Insira a posicao y da %da. cidade: ", i + 1);
        scanf("%f", &(*g)->cidades[i].y);
        printf("\n");
    }

}

int lerPorcentagem()
{
    int porcentagem;
    do
    {
        printf("\nInsira a porcentagem de caminhos existentes entre as cidades: ");
        scanf("%d", &porcentagem);

    } while (porcentagem < 1 || porcentagem > 100);

    return porcentagem;
}



bool haCaminho(GRAFO *g, int origem, int destino)
{
    return g->caminhos[origem][destino];


}

void criarCaminho(GRAFO *g, int origem, int destino)
{
    float dist;
    int x1, x2, y1, y2;


    x1 = g->cidades[origem].x;
    y1 = g->cidades[origem].y;
    x2 = g->cidades[destino].x;
    y2 = g->cidades[destino].y;

    dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    g->caminhos[origem][destino] = dist;
    g->Ncaminhos++;

}

void gerarCaminhos(GRAFO *g, int porcentagem)
{
    int Ntotal = (g->Ncidades - 1) * g->Ncidades;

    int Ncaminhos = (porcentagem / 100.0) * Ntotal;

    srand(time(0));
    int a, b;

    while(g->Ncaminhos < Ncaminhos)
    {
        a = rand() % g->Ncidades;
        b = rand() % g->Ncidades;
        if (a!= b && !haCaminho(g,a,b))
        {
            criarCaminho(g,a,b);
        }
    }
}

void imprimirMatriz(GRAFO *g)
{
    int i, j;
    printf("\n");
    for (i = 0; i < g->Ncidades; i++)
    {
        for (j = 0; j < g->Ncidades; j++)
        {
            printf("%10.3f ", g->caminhos[i][j]);
        }
        printf("\n");
    }
}











int main(void)
{
    GRAFO *grafo;
    int porcentagem;

    criarCidades(&grafo);
    porcentagem = lerPorcentagem();
    gerarCaminhos(grafo, porcentagem);

    imprimirMatriz(grafo);





    return 0;
}
