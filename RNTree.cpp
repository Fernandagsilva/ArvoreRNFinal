#include "RNTree.h"
#include <iostream>
#include <cstring>
#include "../NoRN.h"
using namespace std;


RNTree::RNTree()
{
    rating* aux = new rating;
    rating* aux2 = new rating;
    aux->userId = -10;
    aux->movieId = -10;
    aux2->userId = -1000000000000;
    aux2->movieId = -1000000000000;

    PNULL = new NoRN(aux);
    PNULL->filhoEsq = PNULL->filhoDir = PNULL;

    raiz = new NoRN(aux2);
    raiz->cor = 0;
    raiz->filhoDir = raiz->filhoEsq = PNULL;

}

RNTree::~RNTree()
{
    delete aux;
    delete raiz;
    delete PNULL;
}

// item é o item em reorientaRaiz.
// pai é o pai da raiz da subárvore rotacionada.
// Retorne a raiz da subárvore girada.
NoRN *RNTree::rotate(rating* item, NoRN *noPai, int &numComparacoes, int &numCopias)
{
    numComparacoes++;
    if(item->userId < noPai->chave->userId )
    {
        numComparacoes++;
        item->userId < noPai->filhoEsq->chave->userId ?
        rotacionaEsquerda( noPai->filhoEsq, numCopias) : // esquerda-esquerda
        rotacionaDireita( noPai->filhoEsq, numCopias) ; // esquerda-direita
        return noPai->filhoEsq;
    }
    else
    {
        numComparacoes++;
        item->userId < noPai->filhoDir->chave->userId ?
        rotacionaEsquerda( noPai->filhoDir, numCopias ) : // direita-esquerda
        rotacionaDireita( noPai->filhoDir, numCopias ); // direita-direita
        return noPai->filhoDir;
    }
}

// Rotina interna que é chamada durante uma inserção se um nó tiver dois vermelhos
// crianças. Executa flip e rotações. item é o item que está sendo inserido.

void RNTree::reorientaARN(rating* item, int &numComparacoes, int &numCopias)
{
    noAtual->cor = 1;
    noAtual->filhoEsq->cor = 0;
    noAtual->filhoDir->cor = 0;

    numComparacoes++;
    if( pai->cor == 1 ) //precisa rotacionar
    {
        avo->cor = 1;
        numComparacoes++;
        if( item ->userId < avo->chave->userId != item->userId < pai->chave->userId )
            pai = rotate(item, avo, numComparacoes, numCopias);

        noAtual = rotate(item, aux, numComparacoes, numCopias);
        noAtual->cor = 0;
    }
    raiz->filhoDir->cor = 0;

}
/**
2 * Rotate binary tree node with left child.
3 * For AVL trees, this is a single rotation for case 1.
4 * Update heights, then set new root.
5 */
void RNTree::rotacionaEsquerda(NoRN* no, int &numCopias)
{
    NoRN *noAux = no->filhoEsq;
    no->filhoEsq = noAux->filhoDir;
    noAux->filhoDir = no;
    no = noAux;
    numCopias+= 3;
}

//rotaciona para a direita
void RNTree::rotacionaDireita(NoRN* no, int &numCopias)
{
    NoRN *noAux = no->filhoDir;
    no->filhoDir = noAux->filhoEsq;
    noAux->filhoEsq = no;
    no = noAux;
    numCopias+= 3;

}

//insere a chave na arvore
void RNTree::insercao(rating* chave, int &numComparacoes, int &numCopias)
{
    noAtual = pai = avo = raiz;
    PNULL->chave = chave;

    numComparacoes++;
    while( noAtual->chave != chave )
    {
        numComparacoes++;
        aux = avo;
        avo = pai;
        pai = noAtual;

        numComparacoes++;
        noAtual = chave->userId < noAtual->chave->userId ? noAtual->filhoEsq : noAtual->filhoDir;

        // verifica se tem dois nós vermelhos e conserta
        numComparacoes++;
        if( noAtual->filhoEsq->cor ==1 && noAtual->filhoDir->cor == 1 )
        {
            reorientaARN(chave, numComparacoes, numCopias);
        }
    }

    // Inserção falha se já tem o no
    numComparacoes++;
    if( noAtual != PNULL )
    {
        return;
    }
    noAtual = new NoRN(chave, PNULL, PNULL, 1);

    // anexa ao pai
    numComparacoes++;
    if( chave->userId < pai->chave->userId )
    {
        pai->filhoEsq = noAtual;
    }
    else
    {
        pai->filhoDir = noAtual;
    }

    reorientaARN(chave, numComparacoes, numCopias);

}

//busca uma chave na arvore
bool RNTree::busca(NoRN *no, rating* chave, int &numComparacoes)
{
    numComparacoes++;
    if (no == PNULL)
    {
        return 0;
    };
    numComparacoes++;
    if (chave->userId == no->chave->userId || chave->movieId == no->chave->movieId)
    {
        return 1;
    };
    numComparacoes++;
    if (chave->userId <= no->chave->userId)
    {
        return busca(no->filhoEsq, chave, numComparacoes);
    };
    return busca(no->filhoDir, chave, numComparacoes);

}

//busca uma chave e retorna o nó em que ela se encontra
bool RNTree::buscaPelaChave(rating* chave, int &numComparacoes)
{
    return busca(raiz, chave, numComparacoes);
}
