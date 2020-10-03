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

//EX 1
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
    NO *aux;
    aux = *raiz;
    while (aux->dir)
    {
        aux = aux->dir;
    }
    NO *aux1 = aux;
    if(aux->esq)
    {
        aux = aux->esq;
        printf("sim");
    }
    else
        aux = NULL;
    return aux1;
}


NO *anteriorMaiorEl(NO **raiz)
{
    NO *aux;
    NO *aux2;
    aux = *raiz;
    aux2 = aux;
    while (aux->dir)
    {
        aux2 = aux;
        aux = aux->dir;
    }
    return aux2;

}

//EX 2
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
            NO *aux2;
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
                        aux2 = anteriorMaiorEl(&aux->esq);
                        aux1 = maiorEl(&aux->esq);
                        printf("%d ",aux2->info);
                        if (anterior == NULL)
                        {
                           aux->info = aux1->info;
                           aux2->dir = aux1->esq;
                           free(aux1);

                        }
                        else if (anterior->dir->info == aux->info)
                        {
                            if (aux1 != aux2)
                            {
                                aux1->dir = aux->dir;
                                aux2->dir = NULL;
                            }
                            aux1->esq = aux->esq;
                            anterior->dir = aux1;
                            free(aux);

                        }
                        else if (anterior->esq->info == aux->info)
                        {
                            if (aux1 != aux2)
                            {
                                aux1->esq = aux->esq;
                                aux2->dir = NULL;
                            }
                            aux1->dir = aux->dir;
                            anterior->esq = aux1;
                            free(aux);
                        }
                    }
                }
            }
            break;
        }
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
    inserir(&ptrRaiz,2);
    imprimirArvore(ptrRaiz);
    printf("\n");
    remover(&ptrRaiz,14);
    printf("\n");
    imprimirArvore(ptrRaiz);

    limparArvore(ptrRaiz);
    return 0;
}
