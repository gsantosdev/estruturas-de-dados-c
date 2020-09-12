#include <stdio.h>
#include <stdlib.h>

typedef struct sCell{
    int info;
    struct sCell *next;
}CELULA;

CELULA* criarCelula(int elemento){
    CELULA *nova = (CELULA *) malloc(sizeof(CELULA));
    if (nova){
        nova->info = elemento;
        nova->next = NULL;
    }
    return nova;
}


typedef struct fila{
    CELULA *inicio;
    CELULA *fim;
}FILA;


void inicializarFila(FILA **fila){
    *fila = (FILA *) malloc(sizeof(FILA));
    (*fila)->inicio = NULL;
    (*fila)->fim = NULL;
}

int filaVazia(FILA **fila){
    if((*fila)->inicio == NULL){
        return 1;
    }
    return 0;
}


int enfileirar(FILA **fila, int elemento){

    CELULA *novaCelula = criarCelula(elemento);
    if(novaCelula == NULL){
        printf("ERRO: Memoria Cheia");
        return 0;
    }
    if(filaVazia(fila)){
        (*fila)->inicio = novaCelula;
        (*fila)->fim = novaCelula;
    }
    else{
        (*fila)->fim->next = novaCelula;
        (*fila)->fim = novaCelula;
    }
    return 1;
}

int desenfileirar(FILA **fila){
    CELULA *removida;
    int removido;

    if(filaVazia(fila)){
        printf("ERRO: Fila Vazia.");
        return 0;
    }
    removida = (*fila)->inicio;
    (*fila)->inicio = (*fila)->inicio->next;
    removido = removida->info;

    free(removida);
    return removido;
}


void imprimir(FILA **fila){
    while(!filaVazia(fila))
        printf("%d ",desenfileirar(fila));

}



int main(void)
{
    FILA *ptrfila;
    inicializarFila(&ptrfila);
    enfileirar(&ptrfila, 1);
    enfileirar(&ptrfila, 2);
    enfileirar(&ptrfila, 3);
    enfileirar(&ptrfila, 4);
    enfileirar(&ptrfila, 5);
    imprimir(&ptrfila);


    return 0;
}
