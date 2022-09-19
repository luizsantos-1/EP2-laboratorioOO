#include "Evento.h"
#include <string>
#include <iostream>

using namespace std;

Evento::Evento(int instante, No* destino, Datagrama* d) :
instante(instante), noDestino(destino), d(d) {}

Evento::~Evento() {}

int Evento::getInstante() {
    return instante;
}

No* Evento::getDestino() {
    return noDestino;
}

Datagrama* Evento::getDatagrama() {
    return d;
}

void Evento::imprimir() {
    cout << "Instante: " << instante << endl;
    cout << "No destino: " << noDestino->getEndereco() << endl;
    cout <<  d->getSegmento()->getDado() << endl;
}
