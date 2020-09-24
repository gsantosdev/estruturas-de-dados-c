#include <stdio.h>
#include <stdlib.h>
#define MAX_TAM 10

void menu(){
    printf("\n");
    printf("Inserir no fim da lista ----------------------------------> <1>\n");
    printf("Modificar elemento da lista ------------------------------> <2>\n");
    printf("Remover elemento da lista --------------------------------> <3>\n");
    printf("Acessar elemento da lista --------------------------------> <4>\n");
    printf("Tamanho da lista -----------------------------------------> <5>\n");
    printf("Listar elementos da lista --------------------------------> <6>\n");
    printf("Inserir em posição da lista ------------------------------> <7>\n");
    printf("Inverter lista -------------------------------------------> <8>\n");
    printf("Ordenar lista --------------------------------------------> <9>\n");
    printf("Sair -----------------------------------------------------> <0>\n");
    return;
}

void lbuffer(void)
{
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {}
    return;
}

typedef struct sLista{
        char elem[MAX_TAM];
        int ultimo;
    }Lista;

void inicializarLista(Lista *lista){
    lista->ultimo = -1;
}

int listaCheia(Lista *lista){
    if(lista->ultimo == (MAX_TAM -1)){
        return 1;
    }

    return 0;
}

int listaVazia(Lista *lista){
    if(lista->ultimo == -1){
        return 1;
    }
    return 0;
}

int inserirFim(Lista *lista, char elemento){

    if(listaCheia(lista)){
        printf("\nERRO: lista cheia!\n");
        return 0;
    }
    lista->elem[lista->ultimo + 1] = elemento;
    lista->ultimo++;

    printf("\nElemento inserido com sucesso!\n");
    return 1;
}

int modificarElemento(Lista *lista, int posicao, char elem){
    if(!listaVazia(lista)){

        if(posicao >= 0 && posicao < lista->ultimo + 1){

            lista ->elem[posicao] = elem;

            return 1;
        }
    }
    return 0;
}

int removerElemento(Lista *lista, int posicao){
    int i;

    if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!\n");
        return 0;
    }

    if(posicao < 0 || posicao > lista->ultimo){
        printf("\nERRO:Posicao Invalida!\n");
        return 0;
    }

    for (i = posicao; i< lista->ultimo; i++){
        lista->elem[i] = lista->elem[i+1];
    }

    lista->ultimo--;
    printf("\nElemento removido com sucesso!\n");
    return 1;
}

char acessarElemento(Lista *lista, int posicao){
    if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!");
        return ' ';
    }
    if(posicao < 0 || posicao >lista->ultimo){
        printf("\nERRO: Posicao Invalida!\n");
        return ' ';
    }
    return lista->elem[posicao];
}

int pesquisarElemento(Lista *lista, char elem){
    int i;
    if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!\n");
        return -1;
    }

    for(i = 0; i<= lista->ultimo; i++){
        if(lista->elem[i] == elem){
            return i;
        }
    }

    return -1;
}

int tamanhoLista(Lista *lista){
    return lista->ultimo+1;
}


void todosElementos (Lista *lista){
    int i;
    if(lista->ultimo == -1){
        printf("\nERRO: Lista Vazia!\n");
        return 0;
    }
    printf("\n\nLista -> [");
    for (i = 0; i <= lista->ultimo; i++){
        if(i == lista->ultimo)
            printf("%c",lista->elem[i]);
        else
            printf("%c, ",lista->elem[i]);
    }
    printf("]\n");

}

int inserirPosicao(Lista *lista, char elemento,int posicao){


     char temp;
     if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!\n");
        return ' ';
    }
    if(posicao < 0 || posicao >lista->ultimo){
        printf("\nERRO: Posicao Invalida!\n");
        return ' ';
    }


    for(int i = lista->ultimo; i >= posicao; i--){

        lista->elem[i+1] = lista->elem[i];
        if(i == posicao){
            lista->elem[posicao] = elemento;
        }
    }
    lista->ultimo++;


    printf("\nElemento inserido com sucesso!\n");
    return 1;
}

int inverteLista(Lista *lista){
    int i;
    char aux;
     if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!");
        return ' ';
    }
    for (int i = 0; i <= lista->ultimo / 2; i++){
        aux = lista->elem[i];
        lista->elem[i] = lista->elem[lista->ultimo - i];
        lista->elem[lista->ultimo - i] = aux;
    }
    printf("\nLista Invertida com sucesso!\n");
    return 1;

}

int ordernarLista(Lista *lista){
    int i,j;
    char aux;
     if(listaVazia(lista)){
        printf("\nERRO: Lista Vazia!");
        return ' ';
    }
    for (i = 0; i<= lista->ultimo - 1;i++){
        for(j = i + 1; j <= lista->ultimo; j++)
        {
            if ( lista->elem[j] < lista->elem[i]){
                aux = lista->elem[i];
                lista->elem[i] = lista->elem[j];
                lista->elem[j]= aux;
            }
        }
    }
    printf("\nLista ordenada com sucesso!\n");
    return 1;

}
//EX5
//Crie um procedimento na main que permite o usuário ter acesso a todas
//as funcionalidades descritas até então. Permita também que uma vez
//que o programa estiver funcionando, o usuário possa fazer quantas
//operações quiser.
int main()
{
    Lista *lista = (Lista *) malloc (sizeof(Lista));
    inicializarLista(lista);
    char *elem;
    int op,posicao;

    do {
        menu();
        scanf("%d", &op);
        lbuffer();
        switch (op) {
            case 1:
                printf("\nDigite o elemento que deseja inserir no fim da lista: ");
                elem = getchar();
                lbuffer();
                printf("\n");
                inserirFim(lista,elem);
                break;
            case 2:
                printf("\nDigite a posicao em que deseja alterar o elemento: ");
                scanf("%d", &posicao);
                lbuffer();
                printf("\nDigite um novo elemento: ");
                elem = getchar();
                printf("\n");
                modificarElemento(lista,posicao,elem);
                break;
            case 3:
                printf("\nDigite a posicao em que deseja remover o elemento: ");
                scanf("%d", &posicao);
                lbuffer();
                removerElemento(lista,posicao);
                break;
            case 4:
                printf("\nDigite a posicao em que deseja acessar o elemento: ");
                scanf("%d", &posicao);
                lbuffer();
                printf("\nElemento acessado: %c",acessarElemento(lista,posicao));
                break;
            case 5:
                printf("\n Tamanho Atual da Lista: %d\n",tamanhoLista(lista));
                break;
            case 6:
                todosElementos(lista);
                break;
            case 7:
                printf("\nDigite um novo elemento: ");
                elem = getchar();
                printf("\n");
                printf("\nDigite a posicao em que deseja inserir o elemento: ");
                scanf("%d", &posicao);
                lbuffer();
                inserirPosicao(lista,elem,posicao);
                break;
            case 8:
                inverteLista(lista);
                break;
            case 9:
                ordernarLista(lista);
                break;
            }
}
while (op > 0 && op < 10);
free(lista); //LIBERA O ESPAÇO ALOCADO DA MEMÓRIA
return 0;


    return 0;
}
