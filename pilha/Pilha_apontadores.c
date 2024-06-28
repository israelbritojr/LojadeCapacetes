/****************************************************************** 
 * Nome: Pilha com apontadores                                    *
 * Descricao: Implementacao de pilha apontadores. Esse codigo     *
 *            possui as principais operacoes da pilha como:              *
 *                                                                *
 *      criarPilha                                                *
 *      push (insere no topo da pilha)                            *
 *      pop (remove do topo da pilha)                             *
 *      ehVazia (informa se a pilha está vazia)                   *   
 *      verTopo (informa o conteúdo do elemento do topo da pilha) *
 *      excluirPilha (apaga todos os elementos e a pilha)         *
 *                                                                *
 * Autor: Israel Brito Jr.                                        *
 * Ultima alteracao: 27/06/2024                                   *
 ******************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COR 20
#define TAM_MARCA 20

/* Definicao da estrutura Pilha e do elemento da pilha */ 
typedef struct pilha Pilha;
typedef struct pilhaNo PilhaNo;

struct pilha {
    PilhaNo *topo;
};

struct pilhaNo {
    int tamanho;
    float valor;
    char *cor;
    char *marca;
    PilhaNo *prox;
};

Pilha* criarPilha() {
    Pilha *nova = (Pilha*)malloc(sizeof(Pilha));
    if (nova == NULL) {
        printf("Sem espaco!\n");
        return NULL;
    }
    nova->topo = NULL;
    return nova;
}

int push(Pilha *pilha, int nTamanho, float nValor, const char *cor, const char *marca) {
    PilhaNo *nova = (PilhaNo*)malloc(sizeof(PilhaNo));
    if (nova == NULL) {
        printf("Sem espaco!\n");
        return 0;
    }

    nova->tamanho = nTamanho;
    nova->valor = nValor;
    nova->cor = (char*)malloc(strlen(cor) + 1);
    nova->marca = (char*)malloc(strlen(marca) + 1);
    if (nova->cor == NULL || nova->marca == NULL) {
        printf("Sem espaco para strings!\n");
        free(nova->cor);
        free(nova->marca);
        free(nova);
        return 0;
    }
    strcpy(nova->cor, cor);
    strcpy(nova->marca, marca);
    nova->prox = pilha->topo;
    pilha->topo = nova;
    return 1;
}

PilhaNo* pop(Pilha *pilha) {
    if (pilha == NULL) {
        printf("A pilha nao foi criada!\n");
        return NULL;
    }
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia!\n");
        return NULL;
    }

    PilhaNo *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    printf("O capacete foi removido com sucesso.\n");
    return aux;
}

int verTopo(Pilha *pilha) {
    if (pilha == NULL) {
        printf("A pilha nao foi criada!\n");
        return -1;
    }
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia!\n");
        return -1;
    }

    PilhaNo *aux = pilha->topo;
    printf("Tamanho: %d\n", aux->tamanho);
    printf("Valor: %.2f\n", aux->valor);
    printf("Cor: %s\n", aux->cor);
    printf("Marca: %s\n", aux->marca);
    return 0;
}

int ehVazia(Pilha* pilha) {
    if (pilha == NULL) {
        printf("A pilha nao foi criada!\n");
        return 1;
    }
    if (pilha->topo == NULL) {
        printf("A pilha esta vazia!\n");
        return 1;
    }
    printf("A pilha contem dados.\n");
    return 0;
}

Pilha* excluirPilha(Pilha* pilha) {
    PilhaNo *aux;
    while (pilha->topo != NULL) {
        aux = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(aux->cor);
        free(aux->marca);
        free(aux);
    }

    free(pilha);
    printf("A pilha foi excluida com sucesso!\n");
    return NULL;
}

int main() {
    Pilha *pilha = criarPilha();
    if (pilha == NULL) {
        printf("Erro ao criar a pilha.\n");
        return 1;
    }

    printf("Seja bem-vindo à pilha de capacetes!\n");

    int opcao;
    do {
        printf("\n===== Menu de Opcoes =====\n");
        printf("1. Inserir capacete no topo da pilha\n");
        printf("2. Remover capacete (remove o ultimo inserido)\n");
        printf("3. Ver se a pilha esta vazia\n");
        printf("4. Ver ultimo capacete inserido\n");
        printf("5. Apagar toda pilha\n");
        printf("0. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int tam;
                float val;
                char cor[TAM_COR], marca[TAM_MARCA];
                printf("Digite o tamanho do capacete: ");
                scanf("%d", &tam);
                printf("Digite o valor do capacete: ");
                scanf("%f", &val);
                printf("Digite a cor do capacete: ");
                scanf(" %[^\n]", cor);
                printf("Digite a marca do capacete: ");
                scanf(" %[^\n]", marca);
                if (push(pilha, tam, val, cor, marca)) {
                    printf("Capacete inserido com sucesso.\n");
                } else {
                    printf("Erro ao inserir capacete.\n");
                }
                break;
            }
            case 2: {
                PilhaNo *removido = pop(pilha);
                if (removido != NULL) {
                    free(removido->cor);
                    free(removido->marca);
                    free(removido); // Libera o nó removido
                }
                break;
            }
            case 3: {
                ehVazia(pilha);
                break;
            }
            case 4: {
                printf("O ultimo capacete inserido foi:\n");
                verTopo(pilha);
                break;
            }
            case 5: {
                pilha = excluirPilha(pilha);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Por favor, digite novamente.\n");
                break;
        }
    } while (opcao != 0);

    if (pilha != NULL) {
        pilha = excluirPilha(pilha);
    }

    return 0;
}
