// Discente: Luiz Henrique Araújo Dantas - 20180109005

#include <stdlib.h>
#include <stdio.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    // condicoes iniciais para a linkedlist
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    // Gerando condicoes iniciais pro no
    if (novoNo != NULL) {
        novoNo->prox = NULL;
        novoNo->val = valor;
    }
    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    // criacao de um no para alocar o elemento final e um no auxiliar
    struct no* elemFinal = alocarNovoNo(valor);
    struct no* aux = lista->cabeca;
    if (lista->cabeca == NULL) {
        // verificacao se a lista eh nula, se for, aloque o no elemFinal
        lista->cabeca = elemFinal;
    }
    else {
        while (aux->prox != NULL) {
            // avançando para descobrir qual o prox no null
            aux = aux->prox;
        }
        // quando encontrar o valor null, aloca o elemFinal no final
        aux->prox = elemFinal;
    }
    // incrementa a quantidade da lista
    lista->qtdade++;
}

void inserirElementoNoInicio(struct linkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    // definindo a alocacao de um novo no
    if (lista->cabeca == NULL) {
        // o inicio da lista vai ser o novoNo se for nula
        lista->cabeca = novoNo;
    }
    else {
        struct no* aux = lista->cabeca;
        // caso nao seja nula, cria-se um no auxiliar (apontando e armazenando a cabeca da lista) para alterar a cabeca da lista recebendo o novoNo
        lista->cabeca = novoNo;
        novoNo->prox = aux;
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao) {
    // Percorremos toda a lista para adicionar um elemento em uma posicao da lista
    if (posicao >= 0 && posicao <= lista->qtdade) {
        struct no* elemAdicionado = alocarNovoNo(valor);
        struct no* aux = lista->cabeca;

        if (posicao == 0) {
            // se a posicao for a inicial,  a cabeca adiciona o elemento e o no auxiliar vai ser adicionado no prox no do elemento adicionado.
            lista->cabeca = elemAdicionado;
            elemAdicionado->prox = aux;
        }
        else {
            for (int i = 0; i < posicao - 1; i++) {
                aux = aux->prox;
            }
            // criamos um no aux2 para receber aux
            struct no* aux2 = aux->prox;
            // aux recebe o elemento adicionado
            aux->prox = elemAdicionado;
            // e o prox no do elemento adicionado recebe aux2
            elemAdicionado->prox = aux2;
        }
        lista->qtdade++;
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    int contador = 0;
    // percorremos toda a lista até encontrarmos a posicao desejada
    if (posicao >= 0 && posicao < lista->qtdade) {
        while (aux->prox != NULL) {
            // finaliza o while quando a posicao for igual a do contador
            if (contador == posicao) {
                break;
            }
            aux = aux->prox;
            contador++;
        }
    }
    // retorna o valor na posicao em que o contador eh igual a posicao
    return aux->val;
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao) {
    // considerando toda a lista, vamos percorrer e analisar duas situações
    if (posicao >= 0 && posicao < lista->qtdade) {
        struct no* aux = lista->cabeca;
        if (posicao == 0) {
            // se for a posicao inicial, o auxiliar recebe a cabeca da lista e a cabeca recebe o prox no do auxiliar.
            aux = lista->cabeca;
            lista->cabeca = aux->prox;
            free(aux);
            // libera o no auxiliar
        }
        else {
            // para as demais posicoes, criamos um no aux2 para ajudar nas trocas.
            struct no* aux2;
            for (int i = 0; i < posicao - 1; i++) {
                aux = aux->prox;
            }
            aux2 = aux->prox;
            aux->prox = aux2->prox;
            free(aux2);
            // liberamos aux2
        }
        lista->qtdade--;
        // removemos o elemento e decrementamos a quantidade de elementos da lista
    }
}

void imprimirLista(struct linkedlist* lista) {
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL) {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça ate chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista esta vazia!");
    }
}
