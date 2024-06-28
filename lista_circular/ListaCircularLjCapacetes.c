#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 20

/* Definição da estrutura Lista e do elemento da lista */
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct listaNo {
    int id;
    char nome[TAM_NOME];
    ListaNo *prox;
};

struct lista {
    ListaNo *prim;
    ListaNo *ult;
};

/* Funções auxiliares */
Lista* criarLista() {
    Lista *nova = (Lista*) malloc(sizeof(Lista));
    if (nova == NULL) {
        printf("Sem espaço\n");
        return NULL;
    }
    nova->prim = NULL;
    nova->ult = NULL;
    return nova;
}

int inserirElemento(Lista *lista, int id, char nome[TAM_NOME]) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }
    nova->id = id;
    strncpy(nova->nome, nome, TAM_NOME);
    nova->prox = NULL;

    if (lista->prim == NULL) {
        lista->prim = nova;
        lista->ult = nova;
        nova->prox = nova;  // Apontando para si mesmo na lista circular
    } else {
        lista->ult->prox = nova;
        lista->ult = nova;
        nova->prox = lista->prim;  // Tornando a lista circular
    }
    return 1;
}

int inserirElementoID(Lista *lista, int id, char nome[TAM_NOME], int pos) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }
    nova->id = id;
    strncpy(nova->nome, nome, TAM_NOME);

    if (pos == 0) {
        if (lista->prim == NULL) {
            lista->prim = nova;
            lista->ult = nova;
            nova->prox = nova;  // Apontando para si mesmo na lista circular
        } else {
            nova->prox = lista->prim;
            lista->ult->prox = nova;
            lista->prim = nova;
        }
        return 1;
    }

    ListaNo *atual = lista->prim;
    int i;
    for (i = 0; i < pos - 1 && atual->prox != lista->prim; i++) {
        atual = atual->prox;
    }

    if (i == pos - 1) {
        nova->prox = atual->prox;
        atual->prox = nova;
        if (atual == lista->ult) {
            lista->ult = nova;
        }
        return 1;
    }

    free(nova);
    printf("Posicao invalida\n");
    return 0;
}

int inserirElementoInicio(Lista *lista, int id, char nome[TAM_NOME]) {
    return inserirElementoID(lista, id, nome, 0);
}

void listarElementos(Lista *lista) {
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return;
    }
    ListaNo *atual = lista->prim;
    do {
        printf("ID: %d, Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    } while (atual != lista->prim);
}

void listarElementosOrdemInversa(Lista *lista) {
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return;
    }

    // Contando o número de elementos
    int n = 0;
    ListaNo *atual = lista->prim;
    do {
        n++;
        atual = atual->prox;
    } while (atual != lista->prim);

    // Array para armazenar os elementos
    ListaNo **array = (ListaNo**) malloc(n * sizeof(ListaNo*));
    if (array == NULL) {
        printf("Sem espaco\n");
        return;
    }

    // Armazenando os elementos no array
	atual = lista->prim;
	int i;
	for (i = 0; i < n; i++) {
    array[i] = atual;
    atual = atual->prox;
	}

	// Imprimindo os elementos em ordem inversa
	for (i = n - 1; i >= 0; i--) {
    printf("ID: %d, Nome: %s\n", array[i]->id, array[i]->nome);
	}

	free(array);

}

int removerElemento(Lista *lista, int pos) {
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }

    ListaNo *atual = lista->prim;
    ListaNo *anterior = lista->ult;
    if (pos == 0) {
        if (lista->prim == lista->ult) {
            lista->prim = NULL;
            lista->ult = NULL;
        } else {
            lista->prim = atual->prox;
            lista->ult->prox = lista->prim;
        }
        free(atual);
        return 1;
    }
	int i;
    for (i = 0; i < pos && atual->prox != lista->prim; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == lista->prim) {
        printf("Posicao invalida\n");
        return 0;
    }

    anterior->prox = atual->prox;
    if (atual == lista->ult) {
        lista->ult = anterior;
    }
    free(atual);
    return 1;
}

int removerElementoNome(Lista *lista, char nome[TAM_NOME]) {
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }

    ListaNo *atual = lista->prim;
    ListaNo *anterior = lista->ult;
    do {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual == lista->prim) {
                lista->prim = atual->prox;
                lista->ult->prox = lista->prim;
                if (atual == lista->ult) {
                    lista->prim = NULL;
                    lista->ult = NULL;
                }
            } else {
                anterior->prox = atual->prox;
                if (atual == lista->ult) {
                    lista->ult = anterior;
                }
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != lista->prim);

    printf("Elemento com nome %s nao encontrado\n", nome);
    return 0;
}

int atualizarElemento(Lista *lista, int id, int novoId, char novoNome[TAM_NOME]) {
    ListaNo *atual = lista->prim;
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }

    do {
        if (atual->id == id) {
            atual->id = novoId;
            strncpy(atual->nome, novoNome, TAM_NOME);
            return 1;
        }
        atual = atual->prox;
    } while (atual != lista->prim);

    printf("Elemento com ID %d nao encontrado\n", id);
    return 0;
}

ListaNo* buscarElemento(Lista *lista, int id) {
    ListaNo *atual = lista->prim;
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return NULL;
    }

    do {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    } while (atual != lista->prim);

    printf("Elemento com ID %d nao encontrado\n", id);
    return NULL;
}

int tamanhoLista(Lista *lista) {
    if (lista->prim == NULL) {
        return 0;
    }

    int n = 0;
    ListaNo *atual = lista->prim;
    do {
        n++;
        atual = atual->prox;
    } while (atual != lista->prim);

    return n;
}

void excluirLista(Lista *lista) {
    if (lista->prim == NULL) {
        free(lista);
        return;
    }

    ListaNo *atual = lista->prim;
    ListaNo *prox;
    do {
        prox = atual->prox;
        free(atual);
        atual = prox;
    } while (atual != lista->prim);

    free(lista);
}

int main() {
    Lista *lista = criarLista();

    // Inserindo elementos
    inserirElemento(lista, 1, "Elemento 1");
    inserirElemento(lista, 2, "Elemento 2");
    inserirElemento(lista, 3, "Elemento 3");
    inserirElementoInicio(lista, 0, "Elemento Inicio");
    inserirElementoID(lista, 4, "Elemento 4", 2);

    printf("Elementos da lista:\n");
    listarElementos(lista);

    printf("\nElementos da lista em ordem inversa:\n");
    listarElementosOrdemInversa(lista);

    // Atualizando elemento
    atualizarElemento(lista, 2, 5, "Elemento Atualizado");

    printf("\nElementos da lista apos atualizacao:\n");
    listarElementos(lista);

    // Buscando elemento
    ListaNo *encontrado = buscarElemento(lista, 5);
    if (encontrado != NULL) {
        printf("\nElemento encontrado: ID: %d, Nome: %s\n", encontrado->id, encontrado->nome);
    }

    // Removendo elementos
    removerElemento(lista, 2);
    removerElementoNome(lista, "Elemento 1");

    printf("\nElementos da lista apos remocoes:\n");
    listarElementos(lista);

    // Tamanho da lista
    printf("\nTamanho da lista: %d\n", tamanhoLista(lista));

    // Excluindo lista
    excluirLista(lista);

    return 0;
}
