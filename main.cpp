#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "FuncoesGerais.h"
using namespace std;

int numElementos;
std::string raiz_dir =  "C:\\projetos\\TrabalhoARN\\ARN"; ///Diretorio raiz do projeto

using namespace std;

int main(int argc, char const *argv[])
{
  srand(time(NULL));

    ///Bloco que roda 5 vezes para cada entrada de tamanho no arquivo "entradaTamanhos"
    for(int numIter = 0; numIter < 5; numIter++){

        std::ifstream file;
        file.open(raiz_dir + "\\arquivosEntrada\\entradaTamanhos.txt");

        std::string buffer;

        if(file.is_open()){

            while(!file.eof()){

                ///Le o tamanho
                getline(file, buffer);
                numElementos = stoi(buffer);

                ///Vetor que armazena todas as avaliacoes
                rating** elementos = new rating*[numElementos];

                ///Le do arquivo ratings, o tamanho correspondente
                std::cout << "LENDO O ARQUIVO RATINGS... " << std::endl;
                leArq(elementos);

                ///Monta a arvore B, inserindo os elementos
                std::cout << "MONTANDO ARVORES PARA " << numElementos << " ELEMENTOS..."  << std::endl;
                RNTree* rntree = criaRNTree(elementos, numIter+1);

                std::cout << "ELEMENTOS " << std::endl;
                for(int i = 0; i < numElementos;i++)
                    std::cout << elementos[i]->userId << " " << elementos[i]->movieId << std::endl;

                 ///Faz as buscas na arvore, uma por uma
                std::cout << "FAZENDO AS BUSCAS NA ARVORE..." << std::endl;
                fazBuscasRNTree(rntree, elementos, numIter+1);

                std::cout << "TERMINADO COM SUCESSO! RESULTADOS COLOCADOS NOS ARQUIVOS DE SAIDA :) " << std::endl;

                delete [] elementos;
                delete rntree;

            }

        }else
            std::cout << "Erro ao abrir o arquivo !" << std::endl;
    }

    return 0;
}
