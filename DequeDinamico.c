#include <stdio.h>
#include <stdlib.h>


typedef struct sCell{
    int info;
    struct sCell *prev, *next;
}CELULA;

typedef struct sDeque{
    CELULA *inicio, *fim;
}DEQUE;

void inicializarDeque(DEQUE **deque){
    *deque = (DEQUE *) malloc(sizeof(DEQUE));
    (*deque)->inicio = (*deque)->fim = NULL;
}

CELULA *novoElemento(int elem){
    CELULA *novo = (CELULA*) malloc(sizeof(CELULA));
    if (novo)
    {
        novo->info = elem;
        novo->next = NULL;
        novo->prev = NULL;
    }
    else
        printf("\nERRO: MEMORIA CHEIA\n");
    return novo;

}

int dequeVazio(DEQUE *deque)
{
    if (!deque->inicio)
        return 1;

    return 0;

}

int inserirInicio(DEQUE *deque, int elem)
{

    CELULA *novo = novoElemento(elem);
    if (!novo)
        return 0;

    if (dequeVazio(deque))
        deque->fim = deque->inicio = novo;

    else
    {
        deque->inicio->prev = novo;
        novo->next = deque->inicio;
        deque->inicio = novo;
    }
    return 1;
}

int inserirFim(DEQUE *deque, int elem)
{

    CELULA *novo = novoElemento(elem);
    if (!novo)
        return 0;

    if (dequeVazio(deque))
        return inserirInicio(deque, elem);
    else
    {
        deque->fim->next = novo;
        novo->prev = deque->fim;
        deque->fim = novo;
    }
    return 1;
}

int removerFim(DEQUE *deque)
{
    CELULA *removida;
    int removido;

    if (dequeVazio(deque))
    {
        printf("\nERRO: Deque Vazio !");
        return 0;
    }

    removida = deque->fim;
    removido = removida->info;

    deque->fim = deque->fim->prev;

    dequeVazio(deque) ? deque->inicio = NULL : 0;

    free(removida);
    return removido;

}

int removerInicio(DEQUE *deque)
{
    CELULA *removida;
    int removido;


    if (dequeVazio(deque))
    {
        printf("\nERRO: Deque Vazio !");
        return 0;
    }

    removida = deque->inicio;
    removido = removida->info;

    deque->inicio = deque->inicio->next;

    dequeVazio(deque) ? deque->fim = NULL : 0;

    free(removida);
    return removido;

}

void imprimirDeque(DEQUE *deque, int sentido)
{
    if (dequeVazio(deque))
    {
        printf("\nERRO: Deque Vazio !");
        return;
    }
    while (deque->inicio && deque->fim)
    {
        if(!sentido)
            printf("%d ",removerInicio(deque));
        else
            printf("%d ",removerFim(deque));
    }

    return;

}

void limparDeque(DEQUE *deque)
{
    while (deque->inicio && deque->fim)
        removerInicio(deque);
}

int main(void)
{
    DEQUE *deque;
    inicializarDeque(&deque);
    inserirInicio(deque,1);
    inserirInicio(deque,2);
    inserirInicio(deque,3);
    inserirFim(deque,4);
    inserirFim(deque,5);
    inserirFim(deque,6);
    imprimirDeque(deque,1);

    return 0;
}
