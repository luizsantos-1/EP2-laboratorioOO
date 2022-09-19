#include "Chat.h"
#include <stdexcept>


Chat::Chat(Hospedeiro* h, int porta, int enderecoDestino, int portaDestino)
    : h(h), porta(porta), enderecoDestino(enderecoDestino), portaDestino(portaDestino) {
    if (h == NULL)
        throw new invalid_argument("Hospedeiro invalido");
    textoCompleto= "";
}
Chat::~Chat() {}

int Chat::getPorta() {
    return porta;
}

void Chat::enviar(string texto) {
    h->receber(new Datagrama(h->getEndereco(), enderecoDestino, new Segmento(porta, portaDestino, texto)));
    textoCompleto = textoCompleto + "\t\tEnviado: " + texto + "\n";
}

void Chat::receber(Datagrama* d) {
    string texto = d->getSegmento()->getDado();
    textoCompleto = textoCompleto + "\t\tRecebido: " + texto + "\n";
    delete d;
}

string Chat::getTextoCompleto() {
    return textoCompleto;
}

void Chat::imprimir() {
    cout << "\tChat: " << porta << endl;
}

