#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct Fila {
    No *inicio;
    No *fim;
} Fila;

void inicializar(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

int estaVazia(Fila *fila) {
    return fila->inicio == NULL;
}

int enqueue(Fila *fila, int valor) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }

    novo->dado = valor;
    novo->proximo = NULL;

    if (estaVazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    return 1;
}

int dequeue(Fila *fila, int *valor) {
    if (estaVazia(fila)) {
        return 0;
    }

    No *temporario = fila->inicio;
    *valor = temporario->dado;
    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temporario);
    return 1;
}

int front(Fila *fila, int *valor) {
    if (estaVazia(fila)) {
        return 0;
    }

    *valor = fila->inicio->dado;
    return 1;
}

int back(Fila *fila, int *valor) {
    if (estaVazia(fila)) {
        return 0;
    }

    *valor = fila->fim->dado;
    return 1;
}

void imprimirFila(Fila *fila) {
    No *atual = fila->inicio;

    if (estaVazia(fila)) {
        printf("A fila esta vazia.\n");
        return;
    }

    printf("Inicio -> ");

    while (atual != NULL) {
        printf("%d", atual->dado);

        if (atual->proximo != NULL) {
            printf(" -> ");
        }

        atual = atual->proximo;
    }

    printf(" -> NULL <- Fim\n");
}

int contarElementos(Fila *fila) {
    int quantidade = 0;
    No *atual = fila->inicio;

    while (atual != NULL) {
        quantidade++;
        atual = atual->proximo;
    }

    return quantidade;
}

void liberarFila(Fila *fila) {
    No *atual = fila->inicio;

    while (atual != NULL) {
        No *temporario = atual;
        atual = atual->proximo;
        free(temporario);
    }

    fila->inicio = NULL;
    fila->fim = NULL;
}

int main() {
    Fila fila;
    int opcao, senha;

    inicializar(&fila);

    do {
        printf("\n===== SISTEMA DE ATENDIMENTO =====\n");
        printf("1 - Adicionar pessoa\n");
        printf("2 - Chamar proxima pessoa\n");
        printf("3 - Consultar proxima pessoa\n");
        printf("4 - Consultar ultima senha\n");
        printf("5 - Verificar se a fila esta vazia\n");
        printf("6 - Exibir todas as pessoas\n");
        printf("7 - Consultar quantidade de pessoas\n");
        printf("8 - Liberar memoria\n");
        printf("0 - Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o numero da senha: ");
                scanf("%d", &senha);

                if (enqueue(&fila, senha))
                    printf("Senha adicionada com sucesso!\n");
                else
                    printf("Erro ao alocar memoria.\n");
                break;

            case 2:
                if (dequeue(&fila, &senha))
                    printf("Senha %d chamada para atendimento.\n", senha);
                else
                    printf("A fila esta vazia.\n");
                break;

            case 3:
                if (front(&fila, &senha))
                    printf("Proxima senha: %d\n", senha);
                else
                    printf("A fila esta vazia.\n");
                break;

            case 4:
                if (back(&fila, &senha))
                    printf("Ultima senha: %d\n", senha);
                else
                    printf("A fila esta vazia.\n");
                break;

            case 5:
                if (estaVazia(&fila))
                    printf("A fila esta vazia.\n");
                else
                    printf("Existem pessoas aguardando.\n");
                break;

            case 6:
                imprimirFila(&fila);
                break;

            case 7:
                printf("Quantidade: %d\n",
                       contarElementos(&fila));
                break;

            case 8:
                liberarFila(&fila);
                printf("Memoria liberada!\n");
                break;

            case 0:
                liberarFila(&fila);
                printf("Programa encerrado!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}