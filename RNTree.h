#ifndef RNTREE_H
#define RNTREE_H
#include <string>
#include <stdlib.h>
#include <iostream>
#include "../NoRN.h"
using namespace std;

class RNTree
{
    public:
        RNTree(); //inicializa a arvore
        virtual ~RNTree();
        bool buscaPelaChave(rating* chave, int &numComparacoes); //busca uma chave e retorna o nó em que ela se encontra
        void insercao(rating* chave, int &numComparacoes, int &numCopias); //insere a chave

        void rotacionaEsquerda(NoRN* no,  int &numCopias); //rotaciona para a esquerda
        void rotacionaDireita(NoRN* no, int &numCopias); //rotaciona para a direita
        void reorientaARN( rating* item, int &numComparacoes, int &numCopias );
        NoRN *rotate( rating* current, NoRN *pai, int &numComparacoes, int &numCopias );

        void printRNTree();

    private:
        NoRN *raiz; //No da raiz
        NoRN *PNULL; //ponteiro null
        NoRN *noAtual; //No atual
        NoRN *pai; //No pai
        NoRN *avo; //No avo
        NoRN *aux;

        bool busca(NoRN *no, rating* chave, int &numComparacoes);
        void printARN(NoRN *no);
};

#endif // RNTREE_H
