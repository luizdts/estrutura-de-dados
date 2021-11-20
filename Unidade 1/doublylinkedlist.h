#include <stdlib.h>
#include <stdio.h>

struct no {
    struct no* ant;
    int val;
    struct no* prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    novoNo->val = valor;
    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor) {
    if (lista->qtdade == 0) {
        lista->cabeca = alocarNovoNo(valor);
        lista->cauda = lista->cabeca;
    }
    else {
        struct no* aux = lista->cabeca;
        lista->cabeca = alocarNovoNo(valor);
        lista->cabeca->prox = aux;
        aux->ant = lista->cabeca;
        if (lista->qtdade == 1) {
            lista->cauda = aux;
        }
    }
    lista->qtdade++;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    if (lista->qtdade == 0) {
        lista->cabeca = alocarNovoNo(valor);
        lista->cauda = lista->cabeca;
    }
    else {
        struct no* aux = lista->cauda;
        lista->cauda = alocarNovoNo(valor);
        aux->prox = lista->cauda;
        lista->cauda->ant = aux;
        if (lista->qtdade == 1) {
            lista->cabeca = aux;
        }
    }
    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {
    if (posicao >= 0 && posicao <= lista->qtdade) {
        if (posicao == 0) {
            inserirElementoNoInicio(lista, valor);
        }
        else if (posicao == lista->qtdade) {
            inserirElementoNoFim(lista, valor);
        }
        else {
            if (posicao <= lista->qtdade / 2) {
                struct no* aux = lista->cabeca;
                struct no* aux2 = alocarNovoNo(valor);
                for (int i = 0; i < posicao - 1; i++) {
                    aux = aux->prox;
                }
                aux2->prox = aux->prox;
                aux2->ant = aux;
                aux->prox = aux2;
                aux = aux2->prox;
                aux->ant = aux2;
            }
            else {
                struct no* aux = lista->cauda;
                struct no* aux2 = alocarNovoNo(valor);
                for (int i = lista->qtdade; i > posicao + 1; i--) {
                    aux = aux->ant;
                }
                aux2->ant = aux->ant;
                aux2->prox = aux;
                aux->ant = aux2;
                aux = aux2->ant;
                aux->prox = aux2;
            }
            lista->qtdade++;
        }
    }
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao <= lista->qtdade / 2) {
        struct no* aux = lista->cabeca;
        for (int i = 0; i < posicao; i++) {
            aux = aux->prox;
        }
        return aux->val;
    }
    else {
        struct no* aux = lista->cauda;
        for (int i = lista->qtdade; i > posicao + 1; i--) {
            aux = aux->ant;
        }
        return aux->val;
    }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        if (posicao <= lista->qtdade / 2) {
            struct no* aux1, * aux2, * aux3;
            if (posicao == 0) {
                if (posicao != lista->qtdade - 1) {
                    aux1 = lista->cabeca;
                    lista->cabeca = lista->cabeca->prox;
                    lista->cabeca->ant = NULL;
                    free(aux1);
                }
                else {
                    lista->cabeca->prox = NULL;
                    lista->cabeca->val = NULL;
                    lista->cabeca = NULL;
                    lista->cauda = lista->cabeca;
                }
            }
            else if (posicao == 1) {
                if (posicao != lista->qtdade - 1) {
                    aux1 = lista->cabeca->prox;
                    aux2 = aux1->prox;
                    lista->cabeca->prox = aux2;
                    aux2->ant = lista->cabeca;
                    free(aux1);
                }
                else {
                    aux1 = lista->cauda;
                    lista->cauda = lista->cabeca;
                    lista->cabeca->prox = NULL;
                    free(aux1);
                }
            }
            else {
                aux1 = lista->cabeca;
                for (int i = 1; i < posicao; i++) {
                    aux1 = aux1->prox;
                }
                aux2 = aux1->prox;
                aux2 = aux2->prox;
                aux3 = aux1->prox;
                aux1->prox = aux2;
                aux2->ant = aux1;
                free(aux3);
            }
        }
        else {
            struct no* aux1, * aux2, * aux3;
            if (posicao == lista->qtdade - 1) {
                aux1 = lista->cauda;
                lista->cauda = lista->cauda->ant;
                lista->cauda->prox = NULL;
                free(aux1);
            }
            else if (posicao == lista->qtdade - 2) {
                aux1 = lista->cauda->ant;
                aux2 = aux1->ant;
                lista->cauda->ant = aux2;
                aux2->prox = lista->cauda;
                free(aux1);
            }
            else {
                aux1 = lista->cauda;
                for (int i = lista->qtdade; i > posicao; i--) {
                    aux1 = aux1->ant;
                }
                aux2 = aux1->ant;
                aux3 = aux2;
                aux2 = aux2->ant;
                aux1->ant = aux2;
                aux2->prox = aux1;
                free(aux3);
            }
        }
        lista->qtdade--;
    }
}

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
        //navega partindo da cabeça até chegar NULL
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
        printf("A lista está vazia!");
    }
}
