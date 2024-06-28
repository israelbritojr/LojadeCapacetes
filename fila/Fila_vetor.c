/******************************************************************
 * Nome: Fila com vetores                                         *
 * Descricao: Implementacao de fila vetores. Esse codigo          *
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

#define TAM 25
#define MAX_STR_LEN 50

typedef struct {
    int inicio, fim;
    int *tamanho;
    float *valor;
    char (*cor)[MAX_STR_LEN];
    char (*marca)[MAX_STR_LEN];
} Fila;

Fila* criarFila() {
    Fila *nova = (Fila*)malloc(sizeof(Fila));
    if(nova == NULL) {
        printf("Nao tem espaco\n");
        return NULL;
    }

    nova->inicio = 0;
    nova->fim = 0;
    nova->tamanho = (int*)malloc(TAM * sizeof(int));
    nova->valor = (float*)malloc(TAM * sizeof(float));
    nova->cor = (char(*)[MAX_STR_LEN])malloc(TAM * MAX_STR_LEN * sizeof(char));
    nova->marca = (char(*)[MAX_STR_LEN])malloc(TAM * MAX_STR_LEN * sizeof(char));

    if (nova->valor == NULL || nova->tamanho == NULL || nova->cor == NULL || nova->marca == NULL) {
        printf("Sem espaco\n");
        free(nova->tamanho);
        free(nova->valor);
        free(nova->cor);
        free(nova->marca);
        free(nova);
        return NULL;
    }

    return nova;
}

int enqueue(Fila *fila, int nTamanho, float nValor, const char *cor, const char *marca) {
    if(fila == NULL) {
        printf("A fila nao foi criada\n");
        return 0;
    }

    if((fila->fim + 1) % TAM != fila->inicio) {
        fila->tamanho[fila->fim] = nTamanho;
        fila->valor[fila->fim] = nValor;
        strncpy(fila->cor[fila->fim], cor, MAX_STR_LEN);
        strncpy(fila->marca[fila->fim], marca, MAX_STR_LEN);
        fila->fim = (fila->fim + 1) % TAM;
    } else {
        printf("Espaco esgotado\n");
        return 0;
    }
    return 1;
}

int dequeue(Fila *fila, int *nTamanho, float *nValor, char *cor, char *marca) {
    if (fila == NULL) {
        printf("A fila nao foi criada\n");
        return 0;
    }

    if (fila->inicio == fila->fim) {
        printf("Fila vazia\n");
        return 0;
    }

    *nTamanho = fila->tamanho[fila->inicio];
    *nValor = fila->valor[fila->inicio];
    strncpy(cor, fila->cor[fila->inicio], MAX_STR_LEN);
    strncpy(marca, fila->marca[fila->inicio], MAX_STR_LEN);

    fila->inicio = (fila->inicio + 1) % TAM;

    return 1;
}

void excluirFila(Fila *fila) {
    if (fila != NULL) {
        free(fila->tamanho);
        free(fila->valor);
        free(fila->cor);
        free(fila->marca);
        free(fila);
    }
}

int main() {
    Fila *fila = criarFila();
    if (fila == NULL) {
        return 1;
    }

    if (enqueue(fila, 60, 350.49, "Verde", "FW3")) {
        printf("Elemento inserido com sucesso\n");
    }
    
   if (enqueue(fila, 58, 150.49, "vermelho", "Honda")) {
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

    excluirFila(fila);

    return 0;
}
