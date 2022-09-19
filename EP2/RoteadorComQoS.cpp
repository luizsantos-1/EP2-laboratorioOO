#include "RoteadorComQoS.h"
#include <algorithm>

RoteadorComQoS::RoteadorComQoS(int endereco) : Roteador(endereco, filaQoS = new FilaComPrioridade(TAMANHO_FILA)) {
    destinosPriorizados = new vector<int>;
}

RoteadorComQoS::~RoteadorComQoS() {
    delete destinosPriorizados;
}


void RoteadorComQoS::priorizar(int destino) {
    destinosPriorizados->push_back(destino);
}

vector<int>* RoteadorComQoS::getDestinosPriorizados() {
    return destinosPriorizados;
}

void RoteadorComQoS::receber(Datagrama *d) {
    bool prioridade = false;
    int destinoDoDatagrama;
    destinoDoDatagrama = d->getDestino();
    if (find(destinosPriorizados->begin(), destinosPriorizados->end(), destinoDoDatagrama) != destinosPriorizados->end())
        prioridade = true;
    try {
        filaQoS->enqueue(d, prioridade);
    } catch(overflow_error *e) {
        cout << "\tFila em " << endereco << " estourou" << endl;
    delete e;
    }
}

void RoteadorComQoS::imprimir() {
    cout << "\tRoteadorComQoS de endereco " << endereco <<  " e destino(s) priorizado(s) ";
    for (unsigned int i = 0; i < destinosPriorizados->size(); i++)
        cout << (*destinosPriorizados)[i] << "; ";
    cout << endl;
}
