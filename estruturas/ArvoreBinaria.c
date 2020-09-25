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

    if(raiz->info == elem)
        return raiz;
    else if(raiz->info > elem)
        return pesquisar(raiz->esq, elem);
    else
        return pesquisar(raiz->dir,elem);
}

NO *maiorElemento(NO **no)
{
    if((*no)->dir)
        return maiorElemento(&(*no)->dir);
    else
    {
        NO *aux = *no;
        if((*no)->esq)
            *no = (*no)->esq;
        else
            *no = NULL;
        return aux;
    }
}



void removerRec(NO **raiz, int elem)
{
    NO *aux;

    if(vazia(raiz))
    {
        printf(" Arvore vazia!!!\n");
        return;
    }
    if(elem < (*raiz)->info)
    {
        removerRec(&(*raiz)->esq, elem);
    }
    else if(elem > (*raiz)->info)
    {
        removerRec(&(*raiz)->dir, elem);
    }
    else
    {
        aux = *raiz;
        //caso 1 - o nó é folha
        if((*raiz)->esq == NULL && ((*raiz)->dir == NULL))
        {
            free(aux);
            (*raiz) = NULL;
        }
        else //caso 2 dir
        {
            if((*raiz)->esq == NULL)
            {
                (*raiz) = (*raiz)->dir;
                aux->dir = NULL;
                free(aux);
            }
            else //caso 2 esq
            {
                if((*raiz)->dir == NULL)
                {
                    (*raiz) = (*raiz)->esq;
                    aux->esq = NULL;
                    free(aux);
                }
                else
                {
                    aux = maiorElemento(&(*raiz)->esq);
                    aux->esq = (*raiz)->esq;
                    aux->dir = (*raiz)->dir;
                    free((*raiz));
                    *raiz = aux;
                }
            }
        }


    }
}



int main(void)
{
    NO *ptrRaiz;
    inicializar(&ptrRaiz);
    inserir(&ptrRaiz,2);




    return 0;
}
