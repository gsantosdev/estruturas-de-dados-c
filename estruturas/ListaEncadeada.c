#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sPessoa{
    char nome[50];
    int matricula;
}PESSOA;

PESSOA criarPessoa(char *nome, int matricula){
    PESSOA pessoa;
    strcpy(pessoa.nome,nome);
    pessoa.matricula = matricula;
    return pessoa;
}

typedef struct sCell{
    PESSOA info;
    struct sCell *next;
}CELULA;

CELULA* criarCelula(){
    CELULA *nova = (CELULA *) malloc(sizeof(CELULA));
    return nova;

}
void inicializarLista(CELULA **lista){
    (*lista) = NULL;
}

int listaVazia(CELULA **lista){
    if((*lista) == NULL){
        return 1;
    }
    return 0;
}

PESSOA removerInicio(CELULA **lista){

    //Ponteiro p/ armazenar o end. da célula a ser excluída.
    CELULA *removida;

    //Elemento vazio
    PESSOA removido = criarPessoa(" ", -1);

    //Se a lista vazia, então não remove.
    if(listaVazia(lista)){
        printf("\n ERRO: Lista vazia");
        return removido;
    }

    removida = (*lista);
    removido = (removida->info);

    (*lista) = (*lista)->next;
    free(removida);
    return removido;
}


CELULA *pesquisarMatr(CELULA **lista, int mat){
    CELULA *auxiliar;
    if(listaVazia(lista)){
        printf("\n Erro: Lista Vazia");
        return NULL;
    }

    auxiliar = (*lista); //Recebe a cabeça da lista
    while(auxiliar != NULL){
        if(auxiliar->info.matricula == mat)
            return auxiliar;

        //Se nao encontrou continua
        auxiliar = auxiliar->next;
    }
    return NULL;

}



PESSOA removerFinal(CELULA **lista){
    //Armazena o end. do nó a ser removido
    CELULA *removida;
    //Marca a celula que sera a nova ultima
    CELULA *anterior;
    //Para facilitar o preenchimento de 1 elemento
    //do tipo pessoa, criamos uma funcao criar pessoa
    PESSOA removido = criarPessoa(" ", -1);

    if(listaVazia(lista)){
        printf("\n Erro: Lista Vazia");
        return removerInicio(lista);
    }

    if((*lista)->next == NULL){
        return removerInicio(lista);
    }

    removida = (*lista);

    while(removida-> next != NULL){
        anterior = removida;
        removida = removida->next;
    }

    removido = removida->info;
    anterior->next = NULL;
    free(removida);
    return removido;

}



PESSOA removeMatr(CELULA **lista, int mat){
    CELULA *removida;
    CELULA *anterior;
    PESSOA pRemover = criarPessoa(" ",-1);


    if(listaVazia(lista)){
        printf("\n Erro: Lista Vazia");
        return removerInicio(lista);
    }

    //pesquisa pela matricula
    removida = pesquisarMatr(lista, mat);
    if(removida == NULL){
        printf("ERRO: Matricula nao encontrada");
        return pRemover;
    }

    //Caso seja o primeiro elemento
    if(removida == (*lista)){
        return removerInicio(lista);
    }
    pRemover = removida->info;

    anterior = (*lista);

    while (anterior->next != removida){
        anterior = anterior->next;
    }

    anterior->next = removida->next;
    free(removida);

    return pRemover;
}



void imprimirElemento(PESSOA elemento){
    printf("\n Matricula: %d \tNome: %s",elemento.matricula, elemento.nome);
}

int inserirFim(CELULA **lista, PESSOA elemento){
    CELULA *novaCelula;
    CELULA *auxiliar;

    novaCelula = criarCelula();
    if(novaCelula == NULL){
        printf("ERRO: Memoria Cheia");
        return 0;
    }

    novaCelula->info = elemento;
    novaCelula->next = NULL;

    if(listaVazia(lista)){
        (*lista) = novaCelula;
        return 1;
    }
    auxiliar = (*lista);

    while(auxiliar->next != NULL){
        auxiliar = auxiliar->next;
    }
    auxiliar->next = novaCelula;
    return 1;

}

int inserirInicio(CELULA **lista, PESSOA elemento){
    CELULA *novaCelula = criarCelula();
    if(novaCelula == NULL){
        printf("ERRO: Memoria Cheia");
        return 0;
    }
    if(listaVazia(lista)){
        //Ja que está vazia é equivalente inserir no fim
        return inserirFim(lista, elemento);
    }
    //Preenche a nova celula com o elemento
    novaCelula->info = elemento;
    novaCelula->next = (*lista);
    (*lista) = novaCelula;
    return 1;
}

void imprimirLista(CELULA **lista){
    CELULA *auxiliar = (*lista);
    if(listaVazia(lista)){
        printf("\nLista Vazia.");
    }else{
        printf("\nLista: ");
        while(auxiliar != NULL){
            imprimirElemento(auxiliar->info);
            auxiliar = auxiliar->next;
        }
        printf("\n");
    }
}


int main(void)
{


    PESSOA temp;
    CELULA *ptrLista, *tempCel;
    inicializarLista(&ptrLista);

    strcpy(temp.nome, "Jose");
    temp.matricula = 1;
    inserirInicio(&ptrLista, temp);
    imprimirLista(&ptrLista);

    tempCel = pesquisarMatr(&ptrLista, 2);
    (tempCel != NULL)?printf("\nEncontrada"):printf("\nNao encontrada");

    strcpy(temp.nome, "Maria");
    temp.matricula = 2;

    inserirFim(&ptrLista, temp);
    imprimirLista(&ptrLista);

    strcpy(temp.nome, "Joao");
    temp.matricula = 4;

    inserirInicio(&ptrLista, temp);
    imprimirLista(&ptrLista);

    tempCel = pesquisarMatr(&ptrLista, 2);
    (tempCel != NULL)?printf("\nEncontrada"):printf("\nNao encontrada");

    temp = removeMatr(&ptrLista, 4);
    imprimirLista(&ptrLista);



    return 0;
}
