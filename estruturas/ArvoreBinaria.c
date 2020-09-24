#include <stdio.h>
#include <stdlib.h>


typedef struct sNode{
    int info;
    struct sNode *esq;
    struct sNode *dir;
} NO;


int inicializar(NO **raiz)
{
    (*raiz) = NULL;
}

NO *novoNo(int elem){
    NO *novo = (NO*) malloc(sizeof(NO));
    if (novo)
    {
        novo->info = elem;
        novo->dir = NULL;
        novo->esq = NULL;
    }
    else
        printf("\nERRO: MEMORIA CHEIA\n");
    return novo;

}

int vazia(NO *raiz)
{
    return !raiz;
}

int inserir(NO **raiz, int elem)
{
    NO *novo;
    novo = novoNo(elem);
    if(!novo) return 0;

    if(vazia(*raiz))
    {
        (*raiz) = novo;
        return 1;
    }

    NO *aux = (*raiz);
    NO *anterior = NULL;

    while(aux != NULL)
    {
        anterior = aux;
        if(elem >= aux->info)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    if(elem >= anterior->info)
        anterior->dir = novo;
    else
        anterior->esq = novo;

}

NO *pesquisar (NO *raiz, int elem)
{
    if(!raiz) return NULL;

    if(raiz->info == elemento)
        return raiz;
    else if(raiz->info > elemento)
        return pesquisar(raiz->esq, elemento);
    else
        return pesquisar(raiz->dir,elemento);
}

void removerRec(NO **raiz, int elem)
{
    NO *aux;

    if(vazia(raiz))
    {
        printf(" Arvore vazia!!!\n");
        return;
    }
    if(elemento < (*raiz)->info)
    {
        removerRec(&(*raiz)->esq, elemento);
    }
    else if(elemento > (*raiz)->info)
    {
        removerRec(&(*raiz)->dir, elemento);
    }
    else
    {

    }
}



int main(void)
{
    NO *ptrRaiz;
    inicializar(&ptrRaiz);
    inserir(&ptrRaiz,2);




    return 0;
}
