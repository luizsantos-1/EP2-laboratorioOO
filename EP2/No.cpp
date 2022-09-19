#include "No.h"
#include <iostream>
#include <stdexcept>

using namespace std;

No::No(int endereco)
    : endereco(endereco) {
    filaDeDatagramas = new Fila(TAMANHO_FILA);
    }

No::No(int endereco, Fila* fila)
    : endereco(endereco), filaDeDatagramas(fila) {}

No::~No() {
   delete filaDeDatagramas;
}


int No::getEndereco() {
    return endereco;
}

void No::receber(Datagrama* d) {
    try {
        filaDeDatagramas->enqueue(d);
    } catch(overflow_error *e) {
        cout << "\tFila em " << endereco << " estourou" << endl;
    delete e;
    }
}
