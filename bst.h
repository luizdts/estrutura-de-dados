#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* noBST = (struct noBst*)malloc(sizeof(struct noBst));
    if (noBST) {
        noBST->val = val;
        noBST->esq = noBST->dir = NULL;
        return noBST;
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    if ((*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        *tamanho += 1;
    }
    else if (val < (*raiz)->val) {
        inserir(&(*raiz)->esq, val, tamanho);
    }
    else {
        inserir(&(*raiz)->dir, val, tamanho);
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/
bool buscar(struct noBst* raiz, int val) {
    if (raiz == NULL) {
        return false;
    }
    else if (raiz->val == raiz){
        return true;
    }
    else if (val < raiz->val) {
        buscar(raiz->esq, val);
    }
    else {
        buscar(raiz->dir, val);
    }
}

/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    return raiz->val;
}

/**
 * Funcao que retorna o menor valor de uma BST.
 **/
int min(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    return raiz->val;
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }
    else {
        int esquerda = altura(raiz->esq);
        int direita = altura(raiz->dir);

        if (esquerda > direita) {
            return (esquerda + 1);
        }
        else {
            return (direita + 1);
        }
    }
}

/**
 * Funcao que navega em-ordem na BST e
 * imprime seus elementos.
 **/
void emOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("%d", raiz->val);
        emOrdem(raiz->dir);
    }
}

/**
 * Funcao que navega pre-ordem na BST e
 * imprime seus elementos.
 **/
void preOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        printf("%d", raiz->val);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

/**
 * Funcao que navega pos-ordem na BST e
 * imprime seus elementos.
 **/
void posOrdem(struct noBst* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d", raiz->val);
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * remove o no que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    if (raiz == NULL) {
        return raiz;
    }
    if (val < raiz->val) {
        raiz->esq = remover(raiz->dir, val, tamanho - 1);
    }
    else if (val > raiz->val){
        raiz->dir = remover(raiz->dir, val, tamanho - 1);
    }
    else {
        if (raiz->esq == NULL) {
            struct noBst* aux = raiz->dir;
            free(raiz);
            return aux;
        }
        else if (raiz->dir == NULL) {
            struct noBst* aux = raiz->esq;
            free(raiz);
            return aux;
        }

        struct noBst* aux = raiz->dir;

        while (aux && aux->esq != NULL) {
            aux = aux->esq;
        }

        raiz->val = aux->val;
        raiz->dir = remover(raiz->dir, aux->dir, tamanho - 1);
    }
    return raiz;
}