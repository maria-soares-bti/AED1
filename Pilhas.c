#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Estrutura de cada no da lista
typedef struct No {
    int dado;
    struct No *proximo;
} No;


// Estrutura da pilha
typedef struct Pilha {
    No *topo;
} Pilha;


// Inicializar a pilha
void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}


// Verificar se a pilha esta vazia
int estaVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}


// Inserir elemento (PUSH)
void push(Pilha *pilha, int valor) {


    // INT_MIN e reservado para indicar erro no POP
    if (valor == INT_MIN) {
        printf("\nValor reservado! Escolha outro numero.\n");
        return;
    }


    No *novo = (No *) malloc(sizeof(No));


    if (novo == NULL) {
        printf("\nErro ao alocar memoria!\n");
        return;
    }


    novo->dado = valor;
    novo->proximo = pilha->topo;


    pilha->topo = novo;


    printf("\nElemento inserido com sucesso!\n");
}


// Remover elemento (POP)
int pop(Pilha *pilha) {


    if (estaVazia(pilha)) {
        return INT_MIN;
    }


    No *auxiliar = pilha->topo;
    int valor = auxiliar->dado;


    pilha->topo = auxiliar->proximo;


    free(auxiliar);


    return valor;
}


// Consultar elemento do topo (PEEK)
int peek(Pilha *pilha, int *valor) {


    if (estaVazia(pilha)) {
        return 0;
    }


    *valor = pilha->topo->dado;


    return 1;
}


// Exibir todos os elementos
void imprimirPilha(Pilha *pilha) {


    if (estaVazia(pilha)) {
        printf("\nA pilha esta vazia!\n");
        return;
    }


    No *auxiliar = pilha->topo;


    printf("\n====== ELEMENTOS DA PILHA ======\n");
    printf("           TOPO\n");
    printf("            |\n");
           


    while (auxiliar != NULL) {
        printf("            %d\n", auxiliar->dado);
        auxiliar = auxiliar->proximo;
    }


    printf("           NULL\n");
    printf("================================\n");
}


// Contar quantidade de elementos
int contarElementos(Pilha *pilha) {


    int quantidade = 0;
    No *auxiliar = pilha->topo;


    while (auxiliar != NULL) {
        quantidade++;
        auxiliar = auxiliar->proximo;
    }


    return quantidade;
}


// Liberar toda a memoria da pilha
void liberarPilha(Pilha *pilha) {


    No *auxiliar;


    while (pilha->topo != NULL) {


        auxiliar = pilha->topo;
        pilha->topo = auxiliar->proximo;


        free(auxiliar);
    }


    pilha->topo = NULL;
}


// Funcao principal
int main() {


    Pilha pilha;
    int opcao, valor;


    inicializar(&pilha);


    do {


        printf("\n========== MENU PILHA ==========\n");
        printf("1 - Inserir elemento (PUSH)\n");
        printf("2 - Remover elemento (POP)\n");
        printf("3 - Consultar topo (PEEK)\n");
        printf("4 - Verificar se esta vazia\n");
        printf("5 - Exibir todos os elementos\n");
        printf("6 - Contar elementos\n");
        printf("7 - Liberar pilha\n");
        printf("0 - Sair\n");
        printf("================================\n");


        printf("Escolha uma opcao: ");


        if (scanf("%d", &opcao) != 1) {
            printf("\nEntrada invalida!\n");


            while (getchar() != '\n');


            opcao = -1;
            continue;
        }


        switch (opcao) {


            case 1:
                printf("\nDigite o valor que deseja inserir: ");


                if (scanf("%d", &valor) != 1) {
                    printf("\nValor invalido!\n");


                    while (getchar() != '\n');


                    break;
                }


                push(&pilha, valor);
                break;


            case 2:
                valor = pop(&pilha);


                if (valor == INT_MIN) {
                    printf("\nNao foi possivel remover: pilha vazia!\n");
                } else {
                    printf("\nElemento removido: %d\n", valor);
                }
                break;


            case 3:
                if (peek(&pilha, &valor)) {
                    printf("\nElemento no topo: %d\n", valor);
                } else {
                    printf("\nA pilha esta vazia!\n");
                }
                break;


            case 4:
                if (estaVazia(&pilha)) {
                    printf("\nA pilha esta vazia!\n");
                } else {
                    printf("\nA pilha possui elementos.\n");
                }
                break;


            case 5:
                imprimirPilha(&pilha);
                break;


            case 6:
                printf("\nQuantidade de elementos: %d\n",
                       contarElementos(&pilha));
                break;


            case 7:
                liberarPilha(&pilha);
                printf("\nToda a memoria da pilha foi liberada!\n");
                break;


            case 0:
                liberarPilha(&pilha);
                printf("\nPrograma encerrado!\n");
                break;


            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }


    } while (opcao != 0);


    return 0;
}