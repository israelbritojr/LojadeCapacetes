#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COR 20
#define TAM_MARCA 20
#define TAM_TAMANHOCAPACETE 5
#define TAM_VALOR 3
#define TAM_MAX_CAPACETES 400

typedef struct {
    int codproduto; // Número de capacetes na lista
    int *tamanho;    // Array dinâmico para tamanhos dos capacetes
    float *valor;    // ** ** para valores dos capacetes
    char (*cor)[TAM_COR]; // ** ** de strings para cores dos capacetes
    char (*marca)[TAM_MARCA]; // ** ** de strings para marcas dos capacetes
} Lista;

// FUNÇÕES IMPLEMENTADAS
Lista* criarLista();
int inserirCapacete(Lista *lista, int tamanho, float valor, const char *cor, const char *marca);
int inserirCapaceteID(Lista *lista, int tamanho, float valor, const char *cor, const char *marca, int posicao);
int inserirCapaceteInicio(Lista *lista, int tamanho, float valor, const char *cor, const char *marca);
void imprimirCapacetes(Lista *lista);
int removerCapacete(Lista *lista, int codprodutoremover);
int atualizarCapacete(Lista *lista, int busca, int novoTamanho, float novoValor, const char *novaCor, const char *novaMarca);
Lista* excluirLista(Lista *lista);
int buscarCapacete(Lista *lista, int codproduto);
int qtdCapacetes(Lista *lista);

int main() {
    Lista *lista = NULL;
    int opcao;
    int posicao;
    int codBusca;
    int tamanho;
    float valor;
    char cor[TAM_COR];
    char marca[TAM_MARCA];

    do {
        printf("\n### Menu ###\n");
        printf("1 - Criar lista de capacetes\n");
        printf("2 - Inserir capacete no final da lista\n");
        printf("3 - Inserir capacete em posicao especifica\n");
        printf("4 - Inserir capacete no inicio da lista\n");
        printf("5 - Remover capacete\n");
        printf("6 - Atualizar capacete\n");
        printf("7 - Buscar capacete\n");
        printf("8 - Imprimir todos os capacetes\n");
        printf("9 - Quantidade total de capacetes\n");
        printf("10 - Excluir lista de capacetes\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (lista == NULL) {
                    lista = criarLista();
                    if (lista != NULL) {
                        printf("Lista de capacetes criada com sucesso!\n");
                    }
                } else {
                    printf("A lista de capacetes já foi criada.\n");
                }
                break;
            case 2:
                if (lista != NULL) {
                    printf("Digite o tamanho do capacete: ");
                    scanf("%d", &tamanho);
                    printf("Digite o valor do capacete: ");
                    scanf("%f", &valor);
                    printf("Digite a cor do capacete: ");
                    scanf("%s", cor);
                    printf("Digite a marca do capacete: ");
                    scanf("%s", marca);
                    if (inserirCapacete(lista, tamanho, valor, cor, marca)) {
                        printf("Capacete inserido com sucesso!\n");
                    } else {
                        printf("Erro ao inserir capacete.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 3:
                if (lista != NULL) {
                    printf("Digite o tamanho do capacete: ");
                    scanf("%d", &tamanho);
                    printf("Digite o valor do capacete: ");
                    scanf("%f", &valor);
                    printf("Digite a cor do capacete: ");
                    scanf("%s", cor);
                    printf("Digite a marca do capacete: ");
                    scanf("%s", marca);
                    printf("Digite a posição para inserção (de 0 a %d): ", lista->codproduto);
                    scanf("%d", &posicao);
                    if (inserirCapaceteID(lista, tamanho, valor, cor, marca, posicao)) {
                        printf("Capacete inserido na posição %d com sucesso!\n", posicao);
                    } else {
                        printf("Erro ao inserir capacete na posição %d.\n", posicao);
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 4:
                if (lista != NULL) {
                    printf("Digite o tamanho do capacete: ");
                    scanf("%d", &tamanho);
                    printf("Digite o valor do capacete: ");
                    scanf("%f", &valor);
                    printf("Digite a cor do capacete: ");
                    scanf("%s", cor);
                    printf("Digite a marca do capacete: ");
                    scanf("%s", marca);
                    if (inserirCapaceteInicio(lista, tamanho, valor, cor, marca)) {
                        printf("Capacete inserido no início da lista com sucesso!\n");
                    } else {
                        printf("Erro ao inserir capacete no início da lista.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 5:
                if (lista != NULL) {
                    printf("Digite o código do capacete a ser removido: ");
                    scanf("%d", &codBusca);
                    if (removerCapacete(lista, codBusca)) {
                        printf("Capacete removido com sucesso.\n");
                    } else {
                        printf("Erro ao remover capacete.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 6:
                if (lista != NULL) {
                    printf("Digite o código do capacete a ser atualizado: ");
                    scanf("%d", &codBusca);
                    printf("Digite o novo tamanho do capacete: ");
                    scanf("%d", &tamanho);
                    printf("Digite o novo valor do capacete: ");
                    scanf("%f", &valor);
                    printf("Digite a nova cor do capacete: ");
                    scanf("%s", cor);
                    printf("Digite a nova marca do capacete: ");
                    scanf("%s", marca);
                    if (atualizarCapacete(lista, codBusca, tamanho, valor, cor, marca)) {
                        printf("Capacete atualizado com sucesso.\n");
                    } else {
                        printf("Erro ao atualizar capacete.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 7:
                if (lista != NULL) {
                    printf("Digite o código do capacete a ser buscado: ");
                    scanf("%d", &codBusca);
                    int indice = buscarCapacete(lista, codBusca);
                    if (indice != -1) {
                        printf("Capacete encontrado na posição %d.\n", indice);
                    } else {
                        printf("Capacete não encontrado.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 8:
                if (lista != NULL) {
                    imprimirCapacetes(lista);
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 9:
                if (lista != NULL) {
                    printf("Quantidade total de capacetes na lista: %d\n", qtdCapacetes(lista));
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 10:
                if (lista != NULL) {
                    lista = excluirLista(lista);
                    if (lista == NULL) {
                        printf("Lista de capacetes excluída com sucesso.\n");
                    }
                } else {
                    printf("Crie a lista primeiro.\n");
                }
                break;
            case 0:
                printf("Encerrando programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}


/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo id e alocacao do vetor de elementos
 */
Lista* criarLista(){
    /* Solicitando espaço para a lista */
    Lista *nova = (Lista*)malloc(sizeof(Lista));

    /* Verificando se o espaço foi reservado */
    if(nova == NULL){
        printf("Não há espaço suficiente.\n");
        return NULL;
    }

    /* Inicializando os dados iniciais da lista */
    nova->codproduto = 0;
    nova->tamanho = (int*)malloc(TAM_MAX_CAPACETES * sizeof(int));
    nova->valor = (float*)malloc(TAM_MAX_CAPACETES * sizeof(float));
    nova->cor = (char(*)[TAM_COR])malloc(TAM_MAX_CAPACETES * sizeof(*nova->cor));
    nova->marca = (char(*)[TAM_MARCA])malloc(TAM_MAX_CAPACETES * sizeof(*nova->marca));

    /* Verificando se a alocação de memória foi bem-sucedida */
    if(nova->cor == NULL || 
	nova->marca == NULL || 
	nova ->valor ==NULL || 
	nova ->tamanho == NULL){
        printf("Não há espaço suficiente para alocar memória.\n");
        free(nova); // Liberando a estrutura Lista já alocada
        free(nova->tamanho);
        free(nova->valor);
        free(nova->cor);
        free(nova->marca);
        return NULL;
    }
    /* Retornando o espaço reservado */
    return nova;
}

/* Nome: inserirCapacete
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */

int inserirCapacete(Lista *lista, int tamanho,
                                  float valor,
                                  const char *cor,
                                  const char *marca) {
    /* Verificando se a lista existe */                              	
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }

	/* Verficando se a há espaço e inserindo novo capacete */
	
    if (lista->codproduto < TAM_MAX_CAPACETES) {
        lista->tamanho[lista->codproduto] = tamanho;
        lista->valor[lista->codproduto] = valor;
        strncpy(lista->cor[lista->codproduto], cor, TAM_COR);
        strncpy(lista->marca[lista->codproduto], marca, TAM_MARCA);
        lista->codproduto++;
    } else {
        printf("Espaço esgotado\n");
        return 0;
    }

    return 1;
}

/* Nome: inserirCapaceteID
 * Parametros: lista - ponteiro que possui o endereco lista
 *             posicao - posicao que o elemento sera adicionado na lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento na posicao indicada na lista
 */
int inserirCapaceteID(Lista *lista, int tamanho, 
									float valor, 
									const char *cor, 
									const char *marca, 
									int posicao) {
	/* Verificando se a lista existe */									
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }
	
	/* Verificando se a espaço na lista e se a posição
	 está correta através dos if's */
    if (lista->codproduto < TAM_MAX_CAPACETES) {
        if (posicao <= lista->codproduto) {
        	/* Deslocando os dados */
        	int i;
            for (i = lista->codproduto; i > posicao; --i) {
                lista->tamanho[i] = lista->tamanho[i - 1];
                lista->valor[i] = lista->valor[i - 1];
                strncpy(lista->cor[i], lista->cor[i - 1], TAM_COR);
                strncpy(lista->marca[i], lista->marca[i - 1], TAM_MARCA);
            }
            /* Inserindo os novos dados*/
            lista->tamanho[posicao] = tamanho;
            lista->valor[posicao] = valor;
            strncpy(lista->cor[posicao], cor, TAM_COR);
            strncpy(lista->marca[posicao], marca, TAM_MARCA);
            lista->codproduto++;
        } else {
            printf("Posição fora do intervalo permitido\n");
            return 0;
        }
    } else {
        printf("Espaço esgotado\n");
        return 0;
    }

    return 1;
}

/* Nome: inserirCapaceteInicio
 * Parametros: lista - ponteiro que possui o endereco lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no inicio da lista 
 utilizando a funcao inserirCapaceteID
 */
int inserirCapaceteInicio(Lista *lista, int tamanho,
 			 	  	   		 	        float valor,
                                        const char *cor,
                                        const char *marca) {
    /* utilizando função para fazer o mesmo só que 
	dessa vez na posição 0 ou seja inicio */                                   	
    return inserirCapaceteID(lista, tamanho, valor, cor, marca, 0);
}

/* Nome: imprimirCapacetes
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos elementos presentes na lista
 */
void imprimirCapacetes(Lista *lista) {
     /*Verificando se a lista foi criada*/
	if (lista == NULL) {
        printf("A lista não foi criada\n");
        return;
    }
	/* Verificando se a lista é vazia */
    if (lista->codproduto == 0) {
        printf("Lista vazia\n");
        return;
    }
	/*Mostrando cada elemento presente na lista*/
	int i;
    for (i = 0; i < lista->codproduto; ++i) {
        printf("Capacete %d:\n", i + 1);
        printf("Tamanho: %d\n", lista->tamanho[i]);
        printf("Valor: %.2f\n", lista->valor[i]);
        printf("Cor: %s\n", lista->cor[i]);
        printf("Marca: %s\n", lista->marca[i]);
    }
    printf("\n");
}

/* Nome: removerCapacete
 * Parametro: lista - ponteiro que possui o endereco lista
 *            codprodutoremover - codproduto do Capacete que sera removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrario
 * Descricao: Funcao criada para remover um elemento da lista
 */
int removerCapacete(Lista *lista, int codprodutoremover) {
    /* Verificando se a lista foi criada */
	if (lista == NULL) {
        printf("A lista não foi criada.\n");
        return 0;
    }

	/* Verificando se o codproduto realmente existe */
    if (codprodutoremover < 0 || codprodutoremover >= lista->codproduto) {
        printf("Codigo do Produto não existente.\n");
        return 0;
    }
	int i;
    for (i = codprodutoremover; i < lista->codproduto - 1; ++i) {
        lista->tamanho[i] = lista->tamanho[i + 1];
        lista->valor[i] = lista->valor[i + 1];
        strncpy(lista->cor[i], lista->cor[i + 1], TAM_COR);
        strncpy(lista->marca[i], lista->marca[i + 1], TAM_MARCA);
    }
    lista->codproduto--;

    return 1;
}
/* Nome: atualizarCapacete
 * Parametros: lista - ponteiro que possui o endereco lista
 *             busca - elemento que sera buscado na lista
 *             novo **** - novo valor do elemento que sera alterado 
 * Retorno: 1 - quando o valor e atualizado e 0 - caso contrario
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int atualizarCapacete(Lista *lista, int busca, 
									int novoTamanho, 
									float novoValor, 
									const char *novaCor, 
									const char *novaMarca) {
    /*Verificando se a lista foi criada*/								
	if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }
    /*percorrendo todos os elementos presentes na lista*/
    int i;
    for (i = 0; i < lista->codproduto; ++i) {
    	/*condicao que verifica se o elemento da lista e igual a busca*/
        if (lista->tamanho[i] == busca) {
        	/*atualizando os elementos*/
            lista->tamanho[i] = novoTamanho;
            lista->valor[i] = novoValor;
            strncpy(lista->cor[i], novaCor, TAM_COR);
            strncpy(lista->marca[i], novaMarca, TAM_MARCA);
            return 1;
        }
    }

    return 0;
}

/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Lista* excluirLista(Lista *lista) {
    /* Verificando se a lista foi criada */
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return NULL;
    }

    /* Liberando o espaço que foi reservado para os vetores */
    free(lista->tamanho);
    free(lista->valor);
    free(lista->cor);
    free(lista->marca);

    /* Liberando o espaço que foi reservado para a lista */
    free(lista);
    
    return NULL;
}

/* Nome: buscarCapacete
 * Parametro: lista - ponteiro que possui o endereco lista
 *            codproduto - Capacete que sera buscado na lista
 * Retorno: o indice do Capacete encontrado, -1 caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
int buscarCapacete(Lista *lista, int codproduto) {
    /* Verificando se a lista foi criada */
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return -1;
    }

    /* Percorrendo todos os elementos da lista */
    int i;
    for (i = 0; i < lista->codproduto; ++i) {
        /* Verificando se o código do produto corresponde ao procurado */
        if (lista->codproduto == codproduto) {
            /* Imprimindo os detalhes do capacete */
            printf("Capacete encontrado na posição %d:\n", i);
            printf("Código do Produto: %d\n", codproduto);
            printf("Tamanho: %d\n", lista->tamanho[i]);
            printf("Valor: %.2f\n", lista->valor[i]);
            printf("Cor: %s\n", lista->cor[i]);
            printf("Marca: %s\n", lista->marca[i]);
            return i; // Retorna o índice do capacete encontrado
        }
    }

    printf("Capacete não encontrado\n");
    return -1; // Retorna -1 se o capacete não for encontrado
}

/* Nome: qtdCapacetes
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: a quantidade total de capacetes na lista
 * Descricao: Funcao criada para mostrar total de capacetes dentro da lista
 */
int qtdCapacetes(Lista *lista) {
	/*Verificando se a lista existe*/
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }
    /* o codproduto no caso ultimo codproduto tem o 
	quantitativo total de capacetes cadastrados*/
    return lista->codproduto;
}

