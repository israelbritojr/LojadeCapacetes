/****************************************************************** 
 * Nome: Lista Duplamente encadeada                               *
 * Descricao: Implementacao de lista duplamente encadeada. Esse   *
 *            codigo possui*                                      *
 *            as principais operacoes da lista, como:             *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos em ordem inversa,                 *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Israel Brito Jr.                                        *
 * Ultima alteracao: 17/06/2024                                   *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COR 20
#define TAM_MARCA 20

/* Definicao da estrutura Lista e do elemento da lista */
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista {
    ListaNo *prim;
    ListaNo *ult;
};

struct listaNo {
    int codproduto;
    int tamanho;
    float valor;
    char cor[TAM_COR];
    char marca[TAM_MARCA];
    ListaNo *prox;
    ListaNo *ant;
};

/* Funções */
Lista* criarLista() {
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    if(nova == NULL) {
        printf("Sem espaco\n");
        return NULL;
    }
    nova->prim = NULL;
    nova->ult = NULL;
    return nova;
}

Lista* excluirLista(Lista *lista) {
    ListaNo *aux;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return NULL;
    }
    while(lista->prim != NULL) {
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux);
    }
    free(lista);
    return NULL;
}

int atualizarCapacete(Lista *lista, int busca, int novoTamanho, float novoValor, char novaCor[TAM_COR], char novaMarca[TAM_MARCA]) {
    ListaNo *p;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if(lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }
    for(p = lista->prim; p != NULL; p = p->prox) {
        if(p->codproduto == busca) {
            p->tamanho = novoTamanho;
            p->valor = novoValor;
            strncpy(p->cor, novaCor, TAM_COR);
            strncpy(p->marca, novaMarca, TAM_MARCA);
            return 1;
        }
    }
    printf("Capacete com codigo %d nao encontrado\n", busca);
    return 0;
}

ListaNo* buscarCapacete(Lista *lista, int buscacodproduto) {
    ListaNo *p;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return NULL;
    }
    if(lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return NULL;
    }
    for(p = lista->prim; p != NULL; p = p->prox) {
        if(p->codproduto == buscacodproduto) {
            return p;
        }
    }
    printf("Capacete com codigo %d nao encontrado\n", buscacodproduto);
    return NULL;
}

int inserirCapacete(Lista *lista, int codproduto, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA]) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    if(nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }
    nova->codproduto = codproduto;
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = NULL;
    nova->ant = NULL;
    if(lista->prim == NULL) {
        lista->prim = nova;
        lista->ult = nova;
    } else {
        lista->ult->prox = nova;
        nova->ant = lista->ult;
        lista->ult = nova;
    }
    return 1;
}

int inserirCapaceteCodProduto(Lista *lista, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA], int codprodutoIndicado) {
    ListaNo *p, *nova;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    nova = (ListaNo*) malloc(sizeof(ListaNo));
    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }

    // Inicializa o novo nó com os dados fornecidos
    nova->codproduto = codprodutoIndicado;
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = NULL;
    nova->ant = NULL;

    // Caso a lista esteja vazia ou se codprodutoIndicado for zero, insere no início da lista
    if (lista->prim == NULL || codprodutoIndicado == 0) {
        nova->prox = lista->prim;
        if (lista->prim != NULL) {
            lista->prim->ant = nova;
        }
        lista->prim = nova;
        if (lista->ult == NULL) {
            lista->ult = nova;
        }
        return 1;
    }

    // Verifica se o código do produto já existe ou encontra a posição correta para inserção
    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->codproduto == codprodutoIndicado) {
            printf("Cod.Produto %d ja existe na lista. Insercao nao realizada.\n", codprodutoIndicado);
            free(nova);
            return 0;
        }
        if (p->prox == NULL || p->prox->codproduto > codprodutoIndicado) {
            nova->prox = p->prox;
            nova->ant = p;
            if (p->prox != NULL) {
                p->prox->ant = nova;
            } else {
                lista->ult = nova;
            }
            p->prox = nova;
            return 1;
        }
    }

    free(nova);
    return 0;
}

int inserirCapaceteInicio(Lista *lista, int codproduto, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA]) {
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    if (nova == NULL) {
        printf("Sem espaco\n");
        return 0;
    }

    nova->codproduto = codproduto;
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = lista->prim;
    nova->ant = NULL;

    if (lista->prim != NULL) {
        lista->prim->ant = nova;
    } else {
        lista->ult = nova;
    }
    lista->prim = nova;

    return 1;
}

int removerCapacetemarca(Lista *lista, char marca[TAM_MARCA]) {
    ListaNo *p;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if (lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (strcmp(p->marca, marca) == 0) {
            if (p->ant != NULL) {
                p->ant->prox = p->prox;
            } else {
                lista->prim = p->prox;
            }
            if (p->prox != NULL) {
                p->prox->ant = p->ant;
            } else {
                lista->ult = p->ant;
            }
            free(p);
            return 1;
        }
    }

    printf("Capacete com marca '%s' nao encontrado\n", marca);
    return 0;
}

void imprimirCapacetes(Lista *lista) {
    ListaNo *p;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return;
    }
    if(lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return;
    }
    for(p = lista->prim; p != NULL; p = p->prox) {
        printf("Código do Produto: %d\n", p->codproduto);
        printf("Tamanho: %d\n", p->tamanho);
        printf("Valor: %.2f\n", p->valor);
        printf("Cor: %s\n", p->cor);
        printf("Marca: %s\n", p->marca);
        printf("\n");
    }
    printf("\n");
}

void imprimirCapacetesOrdemInversa(Lista *lista) {
    ListaNo *p;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return;
    }
    if(lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return;
    }
    for(p = lista->ult; p != NULL; p = p->ant) {
        printf("Código do Produto: %d\n", p->codproduto);
        printf("Tamanho: %d\n", p->tamanho);
        printf("Valor: %.2f\n", p->valor);
        printf("Cor: %s\n", p->cor);
        printf("Marca: %s\n", p->marca);
        printf("\n");
    }
    printf("\n");
}

int removerCapacete(Lista *lista, int deletecodproduto) {
    ListaNo *p;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if(lista->prim == NULL) {
        printf("A lista esta vazia\n");
        return 0;
    }
    if(lista->prim->codproduto == deletecodproduto) {
        p = lista->prim;
        lista->prim = lista->prim->prox;
        if (lista->prim != NULL) {
            lista->prim->ant = NULL;
        } else {
            lista->ult = NULL;
        }
        free(p);
        return 1;
    }
    for(p = lista->prim; p != NULL; p = p->prox) {
        if(p->codproduto == deletecodproduto) {
            if (p->ant != NULL) {
                p->ant->prox = p->prox;
            }
            if (p->prox != NULL) {
                p->prox->ant = p->ant;
            }
            if (p == lista->ult) {
                lista->ult = p->ant;
            }
            free(p);
            return 1;
        }
    }
    printf("Capacete com codigo %d nao encontrado\n", deletecodproduto);
    return 0;
}

int qtdCapacetes(Lista *lista) {
    ListaNo *p;
    int tamanho = 0;
    if(lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    for(p = lista->prim; p != NULL; p = p->prox) {
        tamanho++;
    }
    return tamanho;
}

int main() {
    Lista *lista = criarLista();
    if (lista == NULL) {
        printf("Erro ao criar a lista.\n");
        return 1;
    }

    printf("Seja Bem-vindo ao seu estoque de Capacetes!\n");

    int opcao;
    do {
        printf("\n===== Menu de Opcoes =====\n");
        printf("1. Inserir capacete\n");
        printf("2. Atualizar capacete\n");
        printf("3. Buscar capacete\n");
        printf("4. Remover capacete\n");
        printf("5. Exibir capacetes\n");
        printf("6. Exibir capacetes em ordem inversa\n");
        printf("7. Quantidade de capacetes\n");
        printf("8. Inserir capacete no inicio da lista\n");
        printf("9. Inserir capacete pelo codigo do produto\n");
        printf("10. Remover capacete por marca\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        int codproduto, tamanho, busca, deletecodproduto, codprodutoIndicado;
        float valor;
        char cor[TAM_COR], marca[TAM_MARCA];

        switch (opcao) {
            case 1:
                printf("\nDigite o codigo do produto: ");
                scanf("%d", &codproduto);
                printf("Digite o tamanho: ");
                scanf("%d", &tamanho);
                printf("Digite o valor: ");
                scanf("%f", &valor);
                printf("Digite a cor: ");
                scanf("%s", cor);
                printf("Digite a marca: ");
                scanf("%s", marca);
                if (inserirCapacete(lista, codproduto, tamanho, valor, cor, marca)) {
                    printf("Capacete inserido com sucesso!\n");
                } else {
                    printf("Falha ao inserir capacete.\n");
                }
                break;
            case 2:
                printf("\nDigite o codigo do produto a ser atualizado: ");
                scanf("%d", &busca);
                printf("Digite o novo tamanho: ");
                scanf("%d", &tamanho);
                printf("Digite o novo valor: ");
                scanf("%f", &valor);
                printf("Digite a nova cor: ");
                scanf("%s", cor);
                printf("Digite a nova marca: ");
                scanf("%s", marca);
                if (atualizarCapacete(lista, busca, tamanho, valor, cor, marca)) {
                    printf("Capacete atualizado com sucesso!\n");
                } else {
                    printf("Falha ao atualizar capacete.\n");
                }
                break;
            case 3:
                printf("\nDigite o codigo do produto a ser buscado: ");
                scanf("%d", &busca);
                ListaNo *capaceteBuscado = buscarCapacete(lista, busca);
                if (capaceteBuscado != NULL) {
                    printf("Capacete encontrado:\n");
                    printf("Codigo do Produto: %d\n", capaceteBuscado->codproduto);
                    printf("Tamanho: %d\n", capaceteBuscado->tamanho);
                    printf("Valor: %.2f\n", capaceteBuscado->valor);
                    printf("Cor: %s\n", capaceteBuscado->cor);
                    printf("Marca: %s\n", capaceteBuscado->marca);
                }
                break;
            case 4:
                printf("\nDigite o codigo do produto a ser removido: ");
                scanf("%d", &deletecodproduto);
                if (removerCapacete(lista, deletecodproduto)) {
                    printf("Capacete removido com sucesso!\n");
                } else {
                    printf("Falha ao remover capacete.\n");
                }
                break;
            case 5:
                printf("\nCapacetes cadastrados:\n");
                imprimirCapacetes(lista);
                break;
            case 6:
                printf("\nCapacetes cadastrados em ordem inversa:\n");
                imprimirCapacetesOrdemInversa(lista);
                break;
            case 7:
                printf("\nA quantidade de Capacetes total é:\n");
                qtdCapacetes(lista);
                break;
            case 8:
                printf("\nDigite o codigo do produto a ser inserido no inicio: ");
                scanf("%d", &codproduto);
                printf("Digite o tamanho: ");
                scanf("%d", &tamanho);
                printf("Digite o valor: ");
                scanf("%f", &valor);
                printf("Digite a cor: ");
                scanf("%s", cor);
                printf("Digite a marca: ");
                scanf("%s", marca);
                if (inserirCapaceteInicio(lista, codproduto, tamanho, valor, cor, marca)) {
                    printf("Capacete inserido no inicio com sucesso!\n");
                } else {
                    printf("Falha ao inserir capacete no inicio.\n");
                }
                break;
            case 9:
                printf("\nDigite o codigo do produto indicado: ");
                scanf("%d", &codprodutoIndicado);
                printf("Digite o tamanho: ");
                scanf("%d", &tamanho);
                printf("Digite o valor: ");
                scanf("%f", &valor);
                printf("Digite a cor: ");
                scanf("%s", cor);
                printf("Digite a marca: ");
                scanf("%s", marca);
                if (inserirCapaceteCodProduto(lista, tamanho, valor, cor, marca, codprodutoIndicado)) {
                    printf("Capacete inserido com sucesso!\n");
                } else {
                    printf("Falha ao inserir capacete.\n");
                }
                break;
            case 10:
                printf("\nDigite a marca do capacete a ser removido: ");
                scanf("%s", marca);
                if (removerCapacetemarca(lista, marca)) {
                    printf("Capacete(s) da marca '%s' removido(s) com sucesso!\n", marca);
                } else {
                    printf("Falha ao remover capacete(s) da marca '%s'.\n", marca);
                }
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    lista = excluirLista(lista);
    return 0;
}