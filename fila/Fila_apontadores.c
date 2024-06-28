/******************************************************************
 * Nome: Fila com ponteiros                                       *
 * Descricao: Implementacao de fila com ponteiros. Esse codigo    *
 *            possui as principais operacoes da fila como:        *
 *                                                                *
 *      criarFila                                                 *
 *      enqueue (insere o elemento na fila)                       *
 *      dequeue (remove o elemento da fila)                       *
 *      excluirFila (apaga todos os elementos e a fila)           *
 *                                                                *
 * Autor: Israel Brito Jr.                                        *
 * Ultima alteracao: 27/06/2024                                   *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 50

typedef struct No {
    int tamanho;
    float valor;
    char cor[MAX_STR_LEN];
    char marca[MAX_STR_LEN];
    struct No* proximo;
} No;

typedef struct {
    No* inicio;
    No* fim;
} Fila;

Fila* criarFila() {
    Fila* nova = (Fila*)malloc(sizeof(Fila));
    if (nova == NULL) {
        printf("Nao tem espaco\n");
        return NULL;
    }
    nova->inicio = NULL;
    nova->fim = NULL;
    return nova;
}

int enqueue(Fila* fila, int nTamanho, float nValor, const char* cor, const char* marca) {
    if (fila == NULL) {
        printf("A fila nao foi criada\n");
        return 0;
    }

    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Nao tem espaco\n");
        return 0;
    }

    novoNo->tamanho = nTamanho;
    novoNo->valor = nValor;
    strncpy(novoNo->cor, cor, MAX_STR_LEN);
    strncpy(novoNo->marca, marca, MAX_STR_LEN);
    novoNo->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novoNo;
    } else {
        fila->fim->proximo = novoNo;
    }
    fila->fim = novoNo;
    return 1;
}

int dequeue(Fila* fila, int* nTamanho, float* nValor, char* cor, char* marca) {
    if (fila == NULL) {
        printf("A fila nao foi criada\n");
        return 0;
    }

    if (fila->inicio == NULL) {
        printf("Fila vazia\n");
        return 0;
    }

    No* temp = fila->inicio;
    *nTamanho = temp->tamanho;
    *nValor = temp->valor;
    strncpy(cor, temp->cor, MAX_STR_LEN);
    strncpy(marca, temp->marca, MAX_STR_LEN);

    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return 1;
}

int excluirFila(Fila* fila) {
    if (fila == NULL) {
        return 0;
    }

    No* atual = fila->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    free(fila);
    return 1;
}

int main() {
    Fila* fila = criarFila();
    if (fila == NULL) {
        return 1;
    }

    if (enqueue(fila, 10, 100.5, "vermelho", "Toyota")) {
        printf("Elemento inserido com sucesso\n");
    }

    int tamanho;
    float valor;
    char cor[MAX_STR_LEN];
    char marca[MAX_STR_LEN];

    if (dequeue(fila, &tamanho, &valor, cor, marca)) {
        printf("Elemento removido com sucesso\n");
        printf("Tamanho: %d, Valor: %.2f, Cor: %s, Marca: %s\n", tamanho, valor, cor, marca);
    }

    if (excluirFila(fila)) {
        printf("Fila excluida com sucesso!. Ate a proxima...\n");
    } else {
        printf("Erro ao excluir a fila.\n");
    }

    return 0;
}
