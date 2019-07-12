#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "RNTree.h"

extern int numElementos;
extern std::string raiz_dir;

void leArq(rating** elements); //Le o arquivo ratings.csv

RNTree* criaRNTree(rating** elements, int numIter); ///Cria arvore com os elementos passados por parametro
void fazBuscasRNTree(RNTree* rntree, rating** elements, int numInter); ///Faz as buscas de todos os elementos

