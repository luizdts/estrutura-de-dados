#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;

void atualizar(struct noBst* no);
struct noBst* balancear(struct noBst* no);
struct noBst* rebalancearEsqEsq(struct noBst* no);
struct noBst* rebalancearEsqDir(struct noBst* no);
struct noBst* rebalancearDirDir(struct noBst* no);
struct noBst* rebalancearDirEsq(struct noBst* no);
int altura(struct noBst* raiz);

/**
 * Embora durante a aula eu disse que precisar�amos
 * das vari�veis alturaEsq e alturaDir, na verdade n�o
 * � necess�rio. Depois de implementar que percebi algo
 * �bvio: para pegar a altura de uma sub-�rvore basta
 * obter o valor da vari�vel altura na sub-�rvore. (:
 **/
struct noBst {
    int val;
    int altura;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL,
 * e vari�veis altura e balanco para 0.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBst* rotacaoDireita(struct noBst* arvore) {
    struct noBst* esq = arvore->esq;
    arvore->esq = esq->dir;
    esq->dir = arvore;
    atualizar(arvore);
    atualizar(esq);
    return esq;
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBst* rotacaoEsquerda(struct noBst* arvore) {
    struct noBst* dir = arvore->dir;
    arvore->dir = dir->esq;
    dir->esq = arvore;
    atualizar(arvore);
    atualizar(dir);
    return dir;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz s�o passados por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� inserido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de inserir de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    if ((*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        *tamanho += 1;
        return;
    }
    else if (val < (*raiz)->val) {
        inserir(&(*raiz)->esq, val, tamanho);
        (*raiz) = balancear(*raiz);
        atualizar(*raiz);
    }
    else {
        inserir(&(*raiz)->dir, val, tamanho);
        (*raiz) = balancear(*raiz);
        atualizar(*raiz);
    }
    (*raiz) = balancear(*raiz);
    atualizar(*raiz);
}

/**
 * Funcao que recebe a raiz de uma BST e atualiza sua altura
 * e fator de balan�o.
 * Lembre que a altura das sub-�rvores direita e esquerda
 * n�o v�o mudar, por isso a implementa��o n�o � t�o complicada.
 **/
void atualizar(struct noBst* no) {
    no->altura = altura(no);
    if (no->dir != NULL && no->esq != NULL) {
        no->balanco = no->dir->altura - no->esq->altura;
    }
    else if (no->dir != NULL) {
        no->balanco = no->dir->altura;
    }
    else if (no->esq != NULL) {
        no->balanco = -no->esq->altura;
    }
    else {
        no->balanco = 0;
    }
}

/**
 * Funcao que recebe a raiz de uma BST e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Dica: usar fator de balan�o do n� e de uma de suas sub-�rvores
 * para descobrir qual � o caso.
 **/
struct noBst* balancear(struct noBst* no) {
    if (no->balanco == -2) {
        if (no->esq->balanco <= 0) {
            no = rebalancearEsqEsq(no);
        }
        else {
            no = rebalancearEsqDir(no);
        }
    }
    if (no->balanco == 2) {
        if (no->dir->balanco >= 0) {
            no = rebalancearDirDir(no);
        }
        else {
            no = rebalancearDirEsq(no);
        }
    }
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqEsq(struct noBst* no) {
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqDir(struct noBst* no) {
    no->esq = rotacaoEsquerda(no->esq);
    no = rotacaoDireita(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirDir(struct noBst* no) {
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirEsq(struct noBst* no) {
    no->dir = rotacaoDireita(no->dir);
    no = rotacaoEsquerda(no);
    return no;
}

/**
 * Funcao que retorna o maior valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL) { // mesma implementa��o utilizada na BST
        return NULL;
    }
    else if (raiz->dir != NULL) {
        return max(raiz->dir);
    }
    return raiz->val;
}

/**
 * Funcao que retorna o menor valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int min(struct noBst* raiz) {
    if (raiz == NULL) { // mesma implementa��o utilizada na BST
        return NULL;
    }
    else if (raiz->esq != NULL) {
        return min(raiz->esq);
    }
    return raiz->val;
}

/**
 * Funcao que retorna a altura de uma �rvore.
 * A altura de uma �rvore � dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementa��o da BST.
 **/
int altura(struct noBst* raiz) {
    int maior = 0;
    if (raiz == NULL) { 
        return NULL;
    }
    else {
        int esquerda = -1;
        int direita = -1;

        if (raiz->esq != NULL) {
            esquerda = altura(raiz->esq);
        }
        if(raiz->dir != NULL) {
            direita = altura(raiz->dir);
        }
        if (esquerda > direita) {
            return esquerda + 1;
        }
        else {
            return direita + 1;
        }
    }
}
/**
 * Funcao que recebe a raiz de uma �rvore, e
 * remove o n� que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho � passado por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� removido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de remover de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    if (raiz == NULL) {
        return NULL;
    }
    if (val < raiz->val) {
        raiz->esq = remover(raiz->esq, val, tamanho);
        raiz = balancear(raiz);
        atualizar(raiz);
    }
    else if (val > raiz->val) {
        raiz->dir = remover(raiz->dir, val, tamanho);
        raiz = balancear(raiz);
        atualizar(raiz);
    }
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            *tamanho -= 1;
            return NULL;
        }
        else if (raiz->esq == NULL || raiz->dir == NULL) {
            struct noBst* aux;
            if (raiz->esq == NULL) {
                aux = raiz->dir;
            }
            else {
                aux = raiz->esq;
            }
            free(raiz);
            *tamanho -= 1;
            return aux;
        }
        else {
            int aux;
            aux = min(raiz->dir);
            raiz->val = aux;
            raiz->dir = remover(raiz->dir, aux, tamanho);
        }
    }
    raiz = balancear(raiz);
    atualizar(raiz);
    return raiz;
}

void imprimir(queue<struct noBst*> nosImpressao);

/** 
* Fun��o que imprime a �rvore.
* Pode ser �til para depura��o.
**/
void imprimir(struct noBst* raiz) {
    queue<struct noBst*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst*> nosImpressao) {

    queue<struct noBst*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBst* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}