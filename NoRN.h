#ifndef NORN_H_INCLUDED
#define NORN_H_INCLUDED

struct rating{
    int userId;
    int movieId;
    float rate;
    std::string timestamp;
};


struct NoRN{
	rating* chave; // chave do nó
	NoRN* filhoEsq; // ponteiro para o filho esquerdo
	NoRN* filhoDir; //ponteiro para o filho direito
	int cor; // 1 -> Vermelho, 0 -> Preto

	NoRN( rating* elemento, NoRN *lt = nullptr, NoRN *rt = nullptr, int c = 1){
        chave = elemento;
        filhoEsq = lt ;
        filhoDir = rt;
        cor = 1;
	}

};



#endif // NORN_H_INCLUDED
