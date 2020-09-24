#include <stdio.h>

#define TAM 10


typedef struct fila{
    int elem[TAM];
    int cabecalho, ultimo;
}FILA;

void inicializarFila(FILA *fila){
    fila->ultimo = 0;
    fila->cabecalho = fila->ultimo;
}

int filaVazia(FILA *fila){
    return (fila->ultimo == fila->cabecalho);
}

int filaCheia(FILA *fila){
    int proxi = (fila->ultimo + 1) % TAM;
    return (proxi == fila->cabecalho);
}

int enfileirar(FILA *fila, int elemento){
    int proxi;
    if(filaCheia(fila)){
        printf("\nFila Cheia!");
        return 0;
    }
    proxi = (fila->ultimo + 1) % TAM;
    fila->elem[proxi] = elemento;
    fila->ultimo = proxi;
    return 1;
}

int desenfileirar(FILA* fila){
    int removido = -1;

    if(filaVazia(fila)){
        printf("\nFila Vazia!");
        return removido;
    }
    fila->cabecalho = (fila->cabecalho + 1) % TAM;
    removido = fila->elem[fila->cabecalho];
    return removido;
}

void imprimirFila(FILA *fila){
    FILA *auxiliar;

    auxiliar = fila;
    while(auxiliar->ultimo != auxiliar->cabecalho){
        printf("%d ",desenfileirar(auxiliar));
    }
}

int main(void)
{
    FILA *fila;
    inicializarFila(&fila);
    enfileirar(&fila,1);
    enfileirar(&fila,2);
    enfileirar(&fila,3);
    imprimirFila(&fila);



    return 0;
}
