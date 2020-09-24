#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sPessoa{
    char nome[50];
    int matricula;
}PESSOA;

typedef struct sCell{
    PESSOA info;
    struct sCell *next;
}CELULA;

void inicializarLista(CELULA **lista){
    (*lista) = NULL;

}
int listaVazia(CELULA **lista){
    if((*lista) == NULL){
        return 1;
    }
    return 0;
}

CELULA* criarCelula(){
    CELULA *nova = (CELULA *) malloc(sizeof(CELULA));
    return nova;

}

PESSOA criarPessoa(char *nome, int matricula){
    PESSOA pessoa;
    strcpy(pessoa.nome,nome);
    pessoa.matricula = matricula;
    return pessoa;
}

int inserirFinal(CELULA **lista, PESSOA elemento){
    CELULA *nova;
    nova = criarCelula();

    if(nova == NULL){
        printf("\nERRO! Memoria cheia.");
        return 0;
    }

    nova->info = elemento;

    if(listaVazia(lista)){
        nova->next = nova;
        (*lista) = nova;
        return 1;
    }

    nova->next = (*lista)->next;
    (*lista)->next = nova;
    (*lista) = nova;
    return 1;

}


PESSOA removerInicio(CELULA **lista){
    CELULA *removida;
    PESSOA rem = criarPessoa(" ", -1);
    if(listaVazia(lista)){
        printf("\n ERRO! Lista Vazia.");
        return rem;
    }
    removida = (*lista)->next;
    rem = removida->info;

    if((*lista)->next == (*lista)){
        inicializarLista(lista);
    }else{
        (*lista)->next = removida->next;
    }
    free(removida);
    return rem;

}
void imprimirElemento(PESSOA elemento){
    printf("\n Matricula: %d \tNome: %s",elemento.matricula, elemento.nome);
}

void imprimirLista(CELULA **lista){
    CELULA *auxiliar;
    if(listaVazia(lista)){
        printf("Lista Vazia.");

    }else{
        auxiliar = (*lista)->next;
        printf("Lista: ");

    }
    do{
        imprimirElemento(auxiliar->info);
        auxiliar = auxiliar->next;
    }while(auxiliar != (*lista)->next);
    printf("\n");

}

int main(void)
{
    CELULA *ptrlista;
    PESSOA temp;

    inicializarLista(&ptrlista);

    strcpy(temp.nome, "Maria");
    temp.matricula  = 2;
    inserirFinal(&ptrlista, temp);
    imprimirLista(&ptrlista);

    strcpy(temp.nome, "Jose");
    temp.matricula = 4;
    inserirFinal(&ptrlista, temp);
    imprimirLista(&ptrlista);

    removerInicio(&ptrlista);
    imprimirLista(&ptrlista);

    removerInicio(&ptrlista);
    imprimirLista(&ptrlista);



    return 0;
}
