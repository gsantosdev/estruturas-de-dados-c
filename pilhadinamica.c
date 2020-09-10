#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM 10


typedef struct sCell{
    int info;
    struct sCell *next;
}CELULA;

void inicializarPilha(CELULA **pilha){
    (*pilha) = NULL;
}

CELULA* criarCelula(){
    CELULA *nova = (CELULA *) malloc(sizeof(CELULA));
    return nova;
}

int pilhaVazia(CELULA **pilha){
    if((*pilha) == NULL){
        return 1;
    }
    return 0;
}

int acessarTopo(CELULA **pilha){
    if(pilhaVazia(pilha)){
        printf("\ERRO: Pilha Vazia !");
        return 0;
    }
    CELULA *auxiliar;
    auxiliar = (*pilha); //Recebe a cabeça da lista
    while(auxiliar != NULL){
        if(auxiliar->next == NULL)
            return auxiliar->info;
        //Se nao encontrou continua
        auxiliar = auxiliar->next;
    }
    return -1;

}

int push(CELULA **pilha, int elemento){
    CELULA *novaCelula;
    CELULA *auxiliar;

    novaCelula = criarCelula();
    if(novaCelula == NULL){
        printf("ERRO: Memoria Cheia");
        return 0;
    }

    novaCelula->info = elemento;
    novaCelula->next = NULL;
    if(pilhaVazia(pilha)){
        (*pilha) = novaCelula;
        return 1;
    }
    auxiliar = (*pilha);

    while(auxiliar->next != NULL){
        auxiliar = auxiliar->next;
    }
    auxiliar->next = novaCelula;
    return 1;

}

int pop(CELULA **pilha){
    //Armazena o end. do nó a ser removido
    CELULA *removida;
    //Marca a celula que sera a nova ultima
    CELULA *anterior;
    //Para facilitar o preenchimento de 1 elemento
    //do tipo pessoa, criamos uma funcao criar pessoa
    int removido = -1;

    if(pilhaVazia(pilha)){
        printf("\n Erro: Lista Vazia");
        return removido;
    }

    if((*pilha)->next == NULL){
        removida = (*pilha);
        removido = (removida->info);
        (*pilha) = (*pilha)->next;
        free(removida);
        return removido;
    }

    removida = (*pilha);

    while(removida-> next != NULL){
        anterior = removida;
        removida = removida->next;
    }

    removido = removida->info;
    anterior->next = NULL;
    free(removida);
    return removido;

}

void imprimirPilha(CELULA **pilha){
     CELULA *auxiliar = (*pilha);
    if(pilhaVazia(pilha)){
        printf("\nPilha Vazia.");
    }else{
        printf("\nPilha: ");
        while((*pilha) != NULL){
            printf("%d ",pop(pilha));
        }
        printf("\n");
    }
}


int main(void)
{
    CELULA *ptrpilha;
    inicializarPilha(&ptrpilha);
    push(&ptrpilha,0);
    push(&ptrpilha,1);
    push(&ptrpilha,2);
    printf("Elemento do topo: %d", acessarTopo(&ptrpilha));
    imprimirPilha(&ptrpilha);


    return 0;
}
