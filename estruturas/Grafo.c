#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <float.h>

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

typedef struct vetores
{
    float *d;
    int *p;
    int *aberto;
} VETORES;


void inicializaD(int Ncidades, VETORES *vetores, int inicial)
{
    int i;

    vetores->d = (float *) malloc(Ncidades * sizeof(float));
    vetores->p = (int *) malloc(Ncidades * sizeof(int));
    vetores->aberto = (bool *) malloc(Ncidades *sizeof(bool));

    for (i = 0;i < Ncidades; i++)
    {
        vetores->d[i] = FLT_MAX / 2;
        vetores->p[i] = -1;
        vetores->aberto[i] = true;
    }
    vetores->d[inicial] = 0;
}

void relaxa(GRAFO *g, VETORES *vetores, int origem)
{
    int i;

    for(i = 0; i < g->Ncidades; i++)
    {
        if (g->caminhos[origem][i])
        {
            if (vetores->d[i] > vetores->d[origem] + g->caminhos[origem][i])
            {
                vetores->d[i] = vetores->d[origem] + g->caminhos[origem][i];
                vetores->p[i] = origem;

            }
        }
    }

}

bool existeAberto(int Ncidades, VETORES *vetores)
{
    int i;
    for (i = 0; i < Ncidades; i++)
        if (vetores->aberto[i]) return true;
    return false;

}

int menorDist(GRAFO *g, VETORES *vetores)
{
    int i;
    for (i = 0; i < g->Ncidades; i++)
        if (vetores->aberto[i]) break;
    if (i == g->Ncidades) return -1;
    int menor = i;
    for (i = menor + 1; i < g->Ncidades; i++)
        if (vetores->aberto[i] && (vetores->d[menor] > vetores->d[i]))
            menor = i;
    return menor;
}



float *dijkstra(GRAFO *g, int inicial, VETORES *vetores)
{
    inicializaD(g->Ncidades, vetores, inicial);

    int i;

    while (existeAberto(g->Ncidades, vetores))
    {
        int u = menorDist(g, vetores);
        if (u == -1) break;
        vetores->aberto[u] = false;
        relaxa(g, vetores, u);
    }


    return vetores->d;

}


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
    int porcentagem, op, i;
    char cidade1 [30],cidade2 [30];

    VETORES *vetores = (VETORES *) malloc(sizeof(VETORES));

    criarCidades(&grafo);
    porcentagem = lerPorcentagem();
    gerarCaminhos(grafo, porcentagem);

    do
    {
        printf("Selecione a opcao desejada: \n");
        printf("1 - Caminho minimo entre cidades\n");
        printf("0 - Sair\n");
        op = getchar();
        if (op)
        {
            printf("Digite a cidade origem: \n");
            lbuffer();
            scanf("%s", &cidade1);
            for (i = 0; i < grafo->Ncidades; i++)
            {

            }
            printf("Digite a cidade destino: \n");
            lbuffer();
            scanf("%s", &cidade2);
            printf("1 - Caminho minimo entre cidades\n");


        }

    } while (op);

    imprimirMatriz(grafo);

    float *r = dijkstra(grafo,0,vetores);

    int i;

    for (i = 0; i < grafo->Ncidades; i++)
    {
        printf("D %f\n",r[i]);
    }

    printf("\n");

    for (i = 0; i < grafo->Ncidades; i++)
    {
        printf("P %d\n",vetores->p[i]);
    }
    //170141173319264430000000000000000000000.000000

    return 0;
}
