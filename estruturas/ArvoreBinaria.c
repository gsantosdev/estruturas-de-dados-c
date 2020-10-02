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

int vazia(NO **raiz)
{
    return !(*raiz);
}

int inserir(NO **raiz, int elem)
{
    NO *novo;
    novo = novoNo(elem);
    if(!novo) return 0;

    if(vazia(raiz))
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

int inserirRec(NO **raiz, int elem)
{
    if(!(*raiz))
        (*raiz) = novoNo(elem);
    else if(elem >= (*raiz)->info)
        inserirRec(&(*raiz)->dir, elem);
    else
        inserirRec(&(*raiz)->esq, elem);
    return 1;
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

NO *maiorEl(NO **raiz)
{
    while ((*raiz)->dir)
        (*raiz) = (*raiz)->dir;

    return (*raiz);
}

void remover(NO **raiz, int elem)
{
    NO *aux;
    NO *anterior = NULL;

    if(vazia(raiz))
    {
        printf(" Arvore vazia!!!\n");
        return;
    }

    aux = (*raiz);

    while(aux != NULL)
    {
        if (elem > aux->info){
            anterior = aux;
            aux = aux->dir;
        }
        else if (elem < aux->info){
            anterior = aux;
            aux = aux->esq;
        }
        else
        {
            NO *aux1;
            aux1 = aux;
            if(aux->esq == NULL && aux->dir == NULL)
            {
                if (aux->info < anterior->info)
                    anterior->esq = NULL;
                else
                    anterior->dir = NULL;
                free(aux);
            }
            else
            {
                if (!aux->dir)
                {
                    anterior->esq = aux->esq;
                    free(aux);
                }
                else
                {
                    if (!aux->esq)
                    {
                        anterior->dir = aux->dir;
                        free(aux);
                    }
                    else
                    {
                        aux1 = maiorElemento(&aux->esq);
                        //printf("%d", aux1->info);
                        aux->info = aux1->info;
                    }
                }
            }
            break;

        }
    }
    //printf("\n%d ", anterior->info);
    //printf("\n%p ", aux->dir);
    //printf("\n%p \n", aux->esq);
    //free(aux);
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

void imprimirFolhinha(NO *raiz)
{
    if(raiz == NULL)
        return;
    if(raiz->dir == NULL && raiz->esq == NULL)
    {
        printf("%d ", raiz->info);
        return;
    }
    imprimirFolhinha(raiz->esq);
    imprimirFolhinha(raiz->dir);
}

void imprimirArvore(NO *raiz)
{
    if(raiz == NULL)
        return;
    imprimirArvore(raiz->dir);
    printf("%d ", raiz->info);
    imprimirArvore(raiz->esq);
}
void limparArvore(NO *raiz)
{
    if(raiz == NULL)
        return;
    limparArvore(raiz->esq);
    limparArvore(raiz->dir);
    free(raiz);
}


int main(void)
{
    NO *ptrRaiz;
    inicializar(&ptrRaiz);
    inserir(&ptrRaiz,14);
    inserir(&ptrRaiz,4);
    inserir(&ptrRaiz,18);
    inserir(&ptrRaiz,20);
    inserir(&ptrRaiz,16);
    inserir(&ptrRaiz,9);
    inserir(&ptrRaiz,3);
    inserir(&ptrRaiz,7);
    inserir(&ptrRaiz,15);
    inserir(&ptrRaiz,17);
    inserir(&ptrRaiz,5);
    inserir(&ptrRaiz,21);
    imprimirArvore(ptrRaiz);
    printf("\n");
    remover(&ptrRaiz,18);
    printf("\n");
    imprimirArvore(ptrRaiz);

    limparArvore(ptrRaiz);
    return 0;
}
