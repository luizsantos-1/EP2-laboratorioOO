#include "Hospedeiro.h"
#include <stdexcept>


Hospedeiro::Hospedeiro(int endereco, Roteador* gateway, int atraso)
    : No(endereco, fila = new Fila(TAMANHO_FILA)), gateway(gateway), atraso(atraso) {
    chats = new vector<Chat*>;
}

Hospedeiro::~Hospedeiro() {
    for (unsigned int i = 0; i < chats->size(); i++)
        delete (*chats)[i];
    delete chats;
}

void Hospedeiro::adicionarChat(int porta, int enderecoDestino, int portaDestino) {
    for (unsigned int i = 0; i < chats->size(); i++) {
        if (porta == (*chats)[i]->getPorta())
            throw new logic_error("Porta ocupada");
    }
    Chat* chat = new Chat(this, porta, enderecoDestino, portaDestino);
    chats->push_back(chat);
}

vector<Chat*>* Hospedeiro::getChats() {
    return chats;
}

Chat* Hospedeiro::getChat(int porta) {
    for (unsigned int i = 0; i < chats->size(); i++) {
        if (porta == (*chats)[i]->getPorta())
            return (*chats)[i];
    }
    return NULL;
}

Evento* Hospedeiro::processar(int instante) {
    if (fila->isEmpty())
        return NULL;
    Datagrama* dt = fila->dequeue();
    cout << "Hospedeiro " << endereco << endl;

    if (dt->getDestino() == endereco) {
        int portaDeDestino = dt->getSegmento()->getPortaDeDestino();
        bool temChat = false;
        for (unsigned int i = 0; i < chats->size() && !temChat; i++) {
            if (portaDeDestino == (*chats)[i]->getPorta()) {
                (*chats)[i]->receber(dt);
                cout << "\tMensagem recebida" << endl;
                cout << (*chats)[i]->getTextoCompleto();
                temChat = true;
            }
        }
        if (!temChat) {
            cout << "\tSem chat: ";
            dt->imprimir();
            delete dt;
        }
        return NULL;
    }

    else {
        Evento* evento = new Evento(instante + atraso, gateway, dt);
        cout << "\tMensagem enviada" << endl;
        return evento;
    }
}

void Hospedeiro::imprimir(){
    cout << "\tHospedeiro de endereco " << endereco << ", de Gateway " << gateway->getEndereco() << " e atraso " << atraso << ";" << " Com os Chats: " << endl;
    for (int i = 0; i < chats->size(); i++)
        (*chats)[i]->imprimir();
    cout << endl;
}
