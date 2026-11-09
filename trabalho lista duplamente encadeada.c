#include <stdio.h>
#include <stdlib.h>


// Definição da estrutura do Nó
typedef struct No {
    int dado;
    struct No *anterior;
    struct No *proximo;
} No;


// Definição da estrutura da Lista Duplamente Encadeada
typedef struct Lista {
    No *inicio;
    No *fim;
} Lista;


// Declaração das funções
void inicializar(Lista *lista);
void inserirInicio(Lista *lista, int valor);
void inserirFinal(Lista *lista, int valor);
void inserirPosicao(Lista *lista, int valor, int posicao);
void removerInicio(Lista *lista);
void removerFinal(Lista *lista);
void removerValor(Lista *lista, int valor);
No* buscar(Lista *lista, int valor);
void imprimirDireto(Lista *lista);
void imprimirInverso(Lista *lista);
int contarElementos(Lista *lista);
void liberarLista(Lista *lista);


int main() {
    Lista lista;
    inicializar(&lista);
    int opcao, valor, posicao;


    do {
        printf("\n========================================\n");
        printf("    SISTEMA DE LISTA DUPLAMENTE ENCADEADA\n");
        printf("========================================\n");
        printf(" 1. Inicializar/Reinicializar lista\n");
        printf(" 2. Inserir no inicio\n");
        printf(" 3. Inserir no final\n");
        printf(" 4. Inserir em posicao especifica\n");
        printf(" 5. Remover do inicio\n");
        printf(" 6. Remover do final\n");
        printf(" 7. Remover um valor\n");
        printf(" 8. Buscar um valor\n");
        printf(" 9. Imprimir do inicio ao final\n");
        printf("10. Imprimir do final ao inicio\n");
        printf("11. Contar elementos\n");
        printf("12. Liberar memoria e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch (opcao) {
            case 1:
                liberarLista(&lista);
                inicializar(&lista);
                printf("Lista inicializada com sucesso (vazia).\n");
                break;
            case 2:
                printf("Digite o valor a inserir no inicio: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                break;
            case 3:
                printf("Digite o valor a inserir no final: ");
                scanf("%d", &valor);
                inserirFinal(&lista, valor);
                break;
            case 4:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                printf("Digite a posicao desejada (1 para a primeira): ");
                scanf("%d", &posicao);
                inserirPosicao(&lista, valor, posicao);
                break;
            case 5:
                removerInicio(&lista);
                break;
            case 6:
                removerFinal(&lista);
                break;
            case 7:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removerValor(&lista, valor);
                break;
            case 8:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                buscar(&lista, valor);
                break;
            case 9:
                printf("Lista (Inicio -> Fim): ");
                imprimirDireto(&lista);
                break;
            case 10:
                printf("Lista (Fim -> Inicio): ");
                imprimirInverso(&lista);
                break;
            case 11:
                printf("Quantidade de elementos na lista: %d\n", contarElementos(&lista));
                break;
            case 12:
                liberarLista(&lista);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 12);


    return 0;
}


// 1. Inicializar lista
void inicializar(Lista *lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}


// 2. Inserir elemento no início
void inserirInicio(Lista *lista, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novo->dado = valor;
    novo->anterior = NULL;
    novo->proximo = lista->inicio;


    if (lista->inicio == NULL) {
        lista->fim = novo;
    } else {
        lista->inicio->anterior = novo;
    }
    lista->inicio = novo;
    printf("Elemento %d inserido no inicio com sucesso.\n", valor);
}


// 3. Inserir elemento no final
void inserirFinal(Lista *lista, int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novo->dado = valor;
    novo->proximo = NULL;
    novo->anterior = lista->fim;


    if (lista->fim == NULL) {
        lista->inicio = novo;
    } else {
        lista->fim->proximo = novo;
    }
    lista->fim = novo;
    printf("Elemento %d inserido no final com sucesso.\n", valor);
}


// 4. Inserir em uma posição específica (1-indexed)
void inserirPosicao(Lista *lista, int valor, int posicao) {
    if (posicao <= 1) {
        inserirInicio(lista, valor);
        return;
    }


    int total = contarElementos(lista);
    if (posicao > total + 1) {
        printf("Posicao invalida! A lista possui atualmente %d elementos.\n", total);
        return;
    }
    if (posicao == total + 1) {
        inserirFinal(lista, valor);
        return;
    }


    No *atual = lista->inicio;
    for (int i = 1; i < posicao; i++) {
        atual = atual->proximo;
    }


    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    novo->dado = valor;
    novo->proximo = atual;
    novo->anterior = atual->anterior;


    if (atual->anterior != NULL) {
        atual->anterior->proximo = novo;
    }
    atual->anterior = novo;


    printf("Elemento %d inserido na posicao %d com sucesso.\n", valor, posicao);
}


// 5. Remover do início
void removerInicio(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }
    No *temp = lista->inicio;
    int valorRemovido = temp->dado;


    lista->inicio = temp->proximo;


    if (lista->inicio == NULL) {
        lista->fim = NULL;
    } else {
        lista->inicio->anterior = NULL;
    }


    free(temp);
    printf("Elemento %d removido do inicio com sucesso.\n", valorRemovido);
}


// 6. Remover do final
void removerFinal(Lista *lista) {
    if (lista->fim == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }
    No *temp = lista->fim;
    int valorRemovido = temp->dado;


    lista->fim = temp->anterior;


    if (lista->fim == NULL) {
        lista->inicio = NULL;
    } else {
        lista->fim->proximo = NULL;
    }


    free(temp);
    printf("Elemento %d removido do final com sucesso.\n", valorRemovido);
}


// 7. Remover um valor específico
void removerValor(Lista *lista, int valor) {
    if (lista->inicio == NULL) {
        printf("A lista esta vazia!\n");
        return;
    }


    No *atual = lista->inicio;
    while (atual != NULL && atual->dado != valor) {
        atual = atual->proximo;
    }


    if (atual == NULL) {
        printf("Valor %d nao encontrado na lista.\n", valor);
        return;
    }


    if (atual == lista->inicio) {
        removerInicio(lista);
        return;
    }
    if (atual == lista->fim) {
        removerFinal(lista);
        return;
    }


    atual->anterior->proximo = atual->proximo;
    atual->proximo->anterior = atual->anterior;
    free(atual);
    printf("Primeira ocorrencia do valor %d removida com sucesso.\n", valor);
}


// 8. Buscar um valor
No* buscar(Lista *lista, int valor) {
    No *atual = lista->inicio;
    int pos = 1;
    while (atual != NULL) {
        if (atual->dado == valor) {
            printf("Valor %d encontrado na posicao %d.\n", valor, pos);
            return atual;
        }
        atual = atual->proximo;
        pos++;
    }
    printf("Valor %d nao encontrado na lista.\n", valor);
    return NULL;
}


// 9. Imprimir do início ao final
void imprimirDireto(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("NULL\n");
        return;
    }
    No *atual = lista->inicio;
    printf("NULL <-> ");
    while (atual != NULL) {
        printf("%d <-> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}


// Imprimir do final ao início
void imprimirInverso(Lista *lista) {
    if (lista->fim == NULL) {
        printf("NULL\n");
        return;
    }
    No *atual = lista->fim;
    printf("NULL <-> ");
    while (atual != NULL) {
        printf("%d <-> ", atual->dado);
        atual = atual->anterior;
    }
    printf("NULL\n");
}


// 10. Contar elementos
int contarElementos(Lista *lista) {
    int contador = 0;
    No *atual = lista->inicio;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}


// 11. Liberar memória
void liberarLista(Lista *lista) {
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}