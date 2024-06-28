/****************************************************************** 
 * Nome: Lista encadeada                                          *
 * Descricao: Implementacao de lista encadeada. Esse codigo possui*
 *            as principais operacoes da lista, como:             *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Israel Brito Jr.                                        *
 * Ultima alteracao: 17/06/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COR 20
#define TAM_MARCA 20

/*Definicao da estrutura Lista e do elemento da lista*/ 

typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *prim;
};

struct listaNo{
	int codproduto;
	int tamanho;
    float valor;
    char cor[TAM_COR];
    char marca[TAM_MARCA];
    ListaNo *prox;
};


/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo prim
 */
Lista* criarLista(){
    /*solicitando espaco para a lista*/
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    
    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return NULL;
    }
    /*Preparando os dados iniciais da lista*/
    nova->prim = NULL;

    /*Retonando o espaco reservado*/
    return nova;
}

/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Lista* excluirLista(Lista* lista){
    ListaNo *aux;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Liberando o espaco que foi reservado para os elementos*/
    while(lista->prim != NULL){
        aux = lista->prim; // Armazena o ponteiro para o nó atual
        lista->prim = lista->prim->prox; // Avança para o próximo nó
        free(aux); // Libera o nó atual
    }
    
    /*Liberando o espaco que foi reservado para a lista*/
    free(lista);
    
    return NULL;
}

/* Nome: atualizarCapacete
 * Parametros: lista - ponteiro que possui o endereco lista
 *             busca - elemento que sera buscado na lista (codproduto)
 *             novoTamanho - novo tamanho do capacete que sera alterado 
 *             novoValor - novo valor do capacete que sera alterado 
 *             novaCor - nova cor do capacete que sera alterado 
 *             novaMarca - nova marca do capacete que sera alterado 
 * Retorno: 1 - quando o valor e atualizado e 0 - caso contrario
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int atualizarCapacete(Lista *lista, int busca, int novoTamanho, float novoValor, char novaCor[TAM_COR], char novaMarca[TAM_MARCA]){
    ListaNo *p;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /* Verificando se a lista possui capacetes */
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /* Percorrendo todos os capacetes presentes na lista */
    for(p = lista->prim; p != NULL; p = p->prox){
        /* Verificando se o elemento da lista é igual à busca (codproduto) */
        if(p->codproduto == busca){
            /* Atualizando o elemento */
            p->tamanho = novoTamanho;
            p->valor = novoValor;
            strncpy(p->cor, novaCor, TAM_COR);
            strncpy(p->marca, novaMarca, TAM_MARCA);
            return 1;
        }
    }
    /* Elemento não encontrado */
    printf("Capacete com codigo %d nao encontrado\n", busca);
    return 0;
}

/* Nome: buscarCapacete
 * Parametro: lista - ponteiro que possui o endereco lista
 *            buscacodproduto - id do capacete que sera buscado na lista
 * Retorno: ponteiro com endereco do elemento encontrado, NULL caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
ListaNo* buscarCapacete(Lista *lista, int buscacodproduto){
    ListaNo *p;
    
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return NULL;
    }

    /*Percorrendo todos os elementos presentes na lista*/
    for(p = lista->prim; p != NULL; p = p->prox){
        /*Verificando se o elemento atual e igual ao valor buscado*/
        if(p->codproduto == buscacodproduto){
            return p;
        }
    }
    /* Elemento não encontrado */
    printf("Capacete com codigo %d nao encontrado\n", buscacodproduto);
    return NULL;
}

/* Nome: inserirCapacete
 * Parametros: lista - ponteiro que possui o endereco lista
 *             codproduto - código do produto a ser inserido
 *             tamanho - tamanho do capacete a ser inserido
 *             valor - valor do capacete a ser inserido
 *             cor - cor do capacete a ser inserido
 *             marca - marca do capacete a ser inserido
 * Retorno: 1 se o elemento foi inserido com sucesso, 0 caso contrario
 * Descricao: Funcao para inserir um novo capacete no final da lista encadeada
 */
int inserirCapacete(Lista *lista, int codproduto, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA]){
    ListaNo *p; 

    /* Solicitando espaco para criar um novo no da lista */
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    
    /* Verificando se o espaco foi reservado corretamente */
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /* Preparando os dados iniciais do capacete a ser inserido */
    nova->codproduto = codproduto;
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = NULL;

    /* Tratamento para inserir um capacete quando a lista esta vazia */
    if(lista->prim == NULL){
        lista->prim = nova;
        return 1;
    }

    /* Procurando o ultimo ponteiro da lista para receber o novo capacete */
    for(p = lista->prim; p->prox != NULL; p = p->prox);

    /* Inserindo o capacete na ultima posicao da lista */
    p->prox = nova;

    return 1;
}

/* Nome: inserirCapaceteCodProduto
 * Parametros: lista - ponteiro que possui o endereco lista
 *             tamanho - tamanho do capacete a ser inserido
 *             valor - valor do capacete a ser inserido
 *             cor - cor do capacete a ser inserido
 *             marca - marca do capacete a ser inserido
 *             codprodutoIndicado - codproduto que também é a posição na lista onde o capacete será inserido
 * Retorno: 1 se o elemento foi inserido com sucesso, 0 caso contrário
 * Descricao: Funcao para inserir um novo capacete na lista encadeada na posição (Cód.Produto) especificada pelo usuário
 */
int inserirCapaceteCodProduto(Lista *lista, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA], int codprodutoIndicado){
    ListaNo *p, *nova;
    int contador = 0;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /* Solicitando espaco para criar um novo no da lista */
    nova = (ListaNo*) malloc(sizeof(ListaNo));
    
    /* Verificando se o espaco foi reservado corretamente */
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /* Preparando os dados iniciais do capacete a ser inserido */
    nova->codproduto = codprodutoIndicado;
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = NULL;

    /* Caso especial: inserir no inicio da lista */
    if(codprodutoIndicado == 0){
        nova->prox = lista->prim;
        lista->prim = nova;
        return 1;
    }

    /* Percorrendo a lista para encontrar a posicao desejada */
    for(p = lista->prim; p != NULL; p = p->prox){
        if(p->codproduto == codprodutoIndicado){
            printf("Cod.Produto %d ja existe na lista. Insercao nao realizada.\n", codprodutoIndicado);
            free(nova); // Liberando o espaco alocado para o novo capacete
            return 0;
        }
        if(p->prox == NULL || p->prox->codproduto > codprodutoIndicado){
            nova->prox = p->prox;
            p->prox = nova;
            return 1;
        }
        contador++;
    }

    /* Caso a posicao(Cod.Produto) indicada pelo usuario seja maior que o tamanho da lista, insere no final */
    if(p == NULL && contador == codprodutoIndicado){
        for(p = lista->prim; p->prox != NULL; p = p->prox);
        p->prox = nova;
        return 1;
    }

    /* Caso a posicao indicada seja invalida */
    printf("Cod.Produto %d invalido para insercao\n", codprodutoIndicado);
    free(nova); // Liberando o espaco alocado para o novo capacete
    return 0;
}

/* Nome: inserirCapaceteInicio
 * Parametros: lista - ponteiro que possui o endereco lista
 *             codproduto - código do produto a ser inserido
 *             tamanho - tamanho do capacete a ser inserido
 *             valor - valor do capacete a ser inserido
 *             cor - cor do capacete a ser inserido
 *             marca - marca do capacete a ser inserido
 * Retorno: 1 se o elemento foi inserido com sucesso, 0 caso contrário
 * Descricao: Funcao para inserir um novo capacete no inicio da lista encadeada
 */
int inserirCapaceteInicio(Lista *lista, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA]){
    ListaNo *nova;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /* Solicitando espaco para criar um novo no da lista */
    nova = (ListaNo*) malloc(sizeof(ListaNo));
    
    /* Verificando se o espaco foi reservado corretamente */
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /* Preparando os dados iniciais do capacete a ser inserido */
    nova->codproduto = 0; // Inserção no início, codproduto 0
    nova->tamanho = tamanho;
    nova->valor = valor;
    strncpy(nova->cor, cor, TAM_COR);
    strncpy(nova->marca, marca, TAM_MARCA);
    nova->prox = lista->prim; // O próximo nó será o atual primeiro da lista

    /* Atualizando o ponteiro prim para apontar para o novo nó */
    lista->prim = nova;

    return 1;
}




/* Nome: imprimirCapacetes
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos os capacetes presentes na lista
 */
void imprimirCapacetes(Lista *lista){
    ListaNo *p;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return;
    }

    /* Verificando se a lista possui capacetes */
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return;
    }

    /* Mostrando cada elemento presente na lista */
    for(p = lista->prim; p != NULL; p = p->prox){
        printf("Código do Produto: %d\n", p->codproduto);
        printf("Tamanho: %d\n", p->tamanho);
        printf("Valor: %.2f\n", p->valor);
        printf("Cor: %s\n", p->cor);
        printf("Marca: %s\n", p->marca);
        printf("\n");
    }
}

/* Nome: removerCapacete
 * Parametro: lista - ponteiro que possui o endereco lista
 *            deletecodproduto - cod. produto do capacete que sera removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrario
 * Descricao: Funcao criada para remover um capacete da lista
 */
int removerCapacete(Lista *lista, int deletecodproduto){
    ListaNo *p, *aux;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /* Verificando se a lista esta vazia */
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /* Removendo o capacete caso ele esteja na primeira posicao da lista */
    if(lista->prim->codproduto == deletecodproduto){
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux);
        return 1;
    }

    /* Passando por todos os capacetes em busca do elemento que sera removido */
    for(p = lista->prim; p->prox != NULL; p = p->prox){
        /* Verificando se encontrou o capacete a ser removido */
        if(p->prox->codproduto == deletecodproduto){
            aux = p->prox;
            p->prox = p->prox->prox;
            free(aux);
            return 1;
        }
    }

    /* Caso o capacete nao tenha sido encontrado na lista */
    printf("Capacete com codigo %d nao encontrado\n", deletecodproduto);
    return 0;
}

/* Nome: qtdCapacetes
 * Parametros: lista - ponteiro que possui o endereco lista
 * Retorno: tamanho da lista (quantidade de capacetes)
 * Descricao: Funcao para calcular e retornar o tamanho da lista encadeada de capacetes
 */
int qtdCapacetes(Lista *lista){
    ListaNo *p;
    int tamanho = 0;

    /* Verificando se a lista foi criada */
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /* Percorrendo todos os elementos presentes na lista */
    for(p = lista->prim; p != NULL; p = p->prox){
        tamanho++;
    }

    return tamanho;
}


/* Protótipos das funções */
Lista* criarLista();
Lista* excluirLista(Lista *lista);
int inserirCapacete(Lista *lista, int codproduto, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA]);
int inserirCapaceteCodProduto(Lista *lista, int tamanho, float valor, char cor[TAM_COR], char marca[TAM_MARCA], int codprodutoIndicado);
int atualizarCapacete(Lista *lista, int codproduto, int novoTamanho, float novoValor, char novaCor[TAM_COR], char novaMarca[TAM_MARCA]);
int removerCapacete(Lista *lista, int deletecodproduto);
ListaNo* buscarCapacete(Lista *lista, int buscacodproduto);
void imprimirCapacetes(Lista *lista);
int qtdCapacetes(Lista *lista);

int main(){
    Lista *lista = criarLista();
    if (lista == NULL) {
        printf("Erro ao criar a lista.\n");
        return 1;
    }
	
	printf("Seja Bem-vindo ao seu estoque de Capacetes!\n\a");
	
    int opcao;
    do {
        printf("\n===== Menu de Opcoes =====\n");
        printf("1. Inserir capacete\n");
        printf("2. Inserir capacete em posição especifica (Cod. Produto)\n");
        printf("3. Atualizar capacete\n");
        printf("4. Remover capacete\n");
        printf("5. Buscar capacete por Cod. Produto\n");
        printf("6. Imprimir lista de capacetes\n");
        printf("7. Imprimir total de capacetes (tamanho da lista)\n");
        printf("0. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int cod, tam;
                float val;
                char cor[TAM_COR], marca[TAM_MARCA];
                printf("Digite o codigo do produto: ");
                scanf("%d", &cod);
                printf("Digite o tamanho do capacete: ");
                scanf("%d", &tam);
                printf("Digite o valor do capacete: ");
                scanf("%f", &val);
                printf("Digite a cor do capacete: ");
                scanf(" %[^\n]", cor);
                printf("Digite a marca do capacete: ");
                scanf(" %[^\n]", marca);
                if (inserirCapacete(lista, cod, tam, val, cor, marca)) {
                    printf("Capacete inserido com sucesso.\n");
                } else {
                    printf("Erro ao inserir capacete.\n");
                }
                break;
            }
            case 2: {
                int tam, cod;
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
                printf("Digite o codigo do produto (posicao na lista): ");
                scanf("%d", &cod);
                if (inserirCapaceteCodProduto(lista, tam, val, cor, marca, cod)) {
                    printf("Capacete inserido na posicao especificada com sucesso.\n");
                } else {
                    printf("Erro ao inserir capacete na posicao especificada.\n");
                }
                break;
            }
            case 3: {
                int cod, tam;
                float val;
                char cor[TAM_COR], marca[TAM_MARCA];
                printf("Digite o codigo do produto a ser atualizado: ");
                scanf("%d", &cod);
                printf("Digite o novo tamanho do capacete: ");
                scanf("%d", &tam);
                printf("Digite o novo valor do capacete: ");
                scanf("%f", &val);
                printf("Digite a nova cor do capacete: ");
                scanf(" %[^\n]", cor);
                printf("Digite a nova marca do capacete: ");
                scanf(" %[^\n]", marca);
                if (atualizarCapacete(lista, cod, tam, val, cor, marca)) {
                    printf("Capacete atualizado com sucesso.\n");
                } else {
                    printf("Capacete com codigo %d nao encontrado para atualizacao.\n", cod);
                }
                break;
            }
            case 4: {
                int cod;
                printf("Digite o codigo do produto a ser removido: ");
                scanf("%d", &cod);
                if (removerCapacete(lista, cod)) {
                    printf("Capacete removido com sucesso.\n");
                } else {
                    printf("Capacete com codigo %d nao encontrado para remocao.\n", cod);
                }
                break;
            }
            case 5: {
                int cod;
                printf("Digite o codigo do produto a ser buscado: ");
                scanf("%d", &cod);
                ListaNo *capaceteBuscado = buscarCapacete(lista, cod);
                if (capaceteBuscado != NULL) {
                    printf("Capacete encontrado - Cod.: %d, Tamanho: %d, Valor: %.2f, Cor: %s, Marca: %s\n",
                           capaceteBuscado->codproduto, capaceteBuscado->tamanho, capaceteBuscado->valor,
                           capaceteBuscado->cor, capaceteBuscado->marca);
                } else {
                    printf("Capacete com codigo %d nao encontrado.\n", cod);
                }
                break;
            }
            case 6: {
                printf("\nLista de capacetes:\n");
                imprimirCapacetes(lista);
                break;
            }
            case 7: {
                printf("\nA quantidade de capacetes no seu estoque e: %d\n", qtdCapacetes(lista));
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

    // Liberando a memória alocada para a lista de capacetes
    lista = excluirLista(lista);

    return 0;
}