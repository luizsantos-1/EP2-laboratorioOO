#ifndef ROTEADOR_H
#define ROTEADOR_H

#include "No.h"
#include "TabelaDeRepasse.h"
#include <iostream>

using namespace std;

class Roteador: public No {
    public:
        Roteador(int endereco);
        virtual ~Roteador();

        virtual void mapear(int endereco, No* adjacente, int atraso);

        virtual void setPadrao(No* padrao, int atraso);
        static const int TAMANHO_TABELA = 10;

        virtual Evento* processar(int instante);

        virtual void imprimir();
    protected:
        Roteador(int endereco, Fila* fila);
        TabelaDeRepasse* tabelaDoRoteador;
};

#endif // ROTEADOR_H
