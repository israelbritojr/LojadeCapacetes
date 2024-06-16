#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_COR 20
#define TAM_MARCA 20
#define TAM_TAMANHOCAPACETE 5
#define  TAM_VALOR 3
#define TAM_MAX_CAPACETES 400

/* Definição da estrutura */
typedef struct {
    int codproduto; // Código do Capacete
    int *tamanho;    // Tamanho do Capacete 
    char *cor;      // Cor do capacete
    char *marca;    // Marca do Capacete
    float *valor;    // Valor do Capacete
} Lista;

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
    nova->tamanho = (int*)malloc(TAM_TAMANHOCAPACETE * sizeof(int));
    nova->valor = (float*)malloc(TAM_VALOR * sizeof(float));
    nova->cor = (char*)malloc(TAM_COR * sizeof(char));
    nova->marca = (char*)malloc(TAM_MARCA * sizeof(char));

    /* Verificando se a alocação de memória foi bem-sucedida */
    if(nova->cor == NULL || 
	nova->marca == NULL || 
	nova ->valor ==NULL || 
	nova ->tamanho == NULL){
        printf("Não há espaço suficiente para alocar memória.\n");
        free(nova); // Liberando a estrutura Lista já alocada
        return NULL;
    }

    /* Inicializando as strings */
    nova->cor[0] = '\0';   // Inicializando a string cor como vazia
    nova->marca[0] = '\0'; // Inicializando a string marca como vazia

    /* Retornando o espaço reservado */
    return nova;
}

int inserirCapacete(Lista *lista, int tamanho,
	  	  	  	  	   	          float valor,
			                      char cor,
								  char marca){
    
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }
    
    /*Verificando se existe espaco para inserir mais um elemento na lista*/
    if(lista->codproduto < TAM_MAX_CAPACETES){
        /*Inserindo os dados na lista*/
        lista->tamanho[lista->codproduto] = tamanho;
        lista->valor[lista->codproduto] = valor;
        lista->cor[lista->codproduto] = cor;
        lista->marca[lista->codproduto] = marca;
        /*Atualizando a quantidade de capacetes da lista*/
        ++(lista->id);
    }else{
        printf("Espaco esgotado\n");
        return 0;
    }

    return 1;
}

int inserirCapaceteID(Lista *lista, int tamanho, 
									float valor, 
									const char *cor, 
									const char *marca, 
									int posicao) {
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }

    if (lista->codproduto < TAM_MAX_CAPACETES) {
        if (posicao <= lista->codproduto) {
            for (int i = lista->codproduto; i > posicao; --i) {
                lista->tamanho[i] = lista->tamanho[i - 1];
                lista->valor[i] = lista->valor[i - 1];
                strncpy(lista->cor[i], lista->cor[i - 1], TAM_COR);
                strncpy(lista->marca[i], lista->marca[i - 1], TAM_MARCA);
            }
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

int inserirCapaceteInicio(Lista *lista, int tamanho,
 			 	  	   		 	        float valor,
                                        const char *cor,
                                        const char *marca) {
    /* utilizando função para fazer o mesmo só que 
	dessa vez na posição 0 ou seja inicio */                                   	
    return inserirCapaceteID(lista, tamanho, valor, cor, marca, 0);
}


void imprimirCapacetes(Lista *lista) {
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return;
    }

    if (lista->codproduto == 0) {
        printf("Lista vazia\n");
        return;
    }

    for (int i = 0; i < lista->codproduto; ++i) {
        printf("Capacete %d:\n", i + 1);
        printf("Tamanho: %d\n", lista->tamanho[i]);
        printf("Valor: %.2f\n", lista->valor[i]);
        printf("Cor: %s\n", lista->cor[i]);
        printf("Marca: %s\n", lista->marca[i]);
    }
    printf("\n");
}

int removerCapacete(Lista *lista, int tamanho, 
						          float valor, 
                                  const char *cor, 
								  const char *marca) {
								  	
    if (lista == NULL) {
        printf("A lista não foi criada\n");
        return 0;
    }

    for (int i = 0; i < lista->codproduto; ++i) {
        if (lista->tamanho[i] == tamanho &&
            lista->valor[i] == valor &&
            strcmp(lista->cor[i], cor) == 0 &&
            strcmp(lista->marca[i], marca) == 0) {
            	
            for (int j = i; j < lista->codproduto - 1; ++j) {
                lista->tamanho[j] = lista->tamanho[j + 1];
                lista->valor[j] = lista->valor[j + 1];
                strncpy(lista->cor[j], lista->cor[j + 1], TAM_COR);
                strncpy(lista->marca[j], lista->marca[j + 1], TAM_MARCA);
            }
            lista->codproduto--;
            return 1;
        }
    }

    return 0;
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
    for (int i = 0; i < lista->codproduto; ++i) {
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
