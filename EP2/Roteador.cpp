#include "Roteador.h"

Roteador::Roteador(int endereco)
        : No(endereco) {
        tabelaDoRoteador = new TabelaDeRepasse(TAMANHO_TABELA);
}

Roteador::Roteador(int endereco, Fila* fila)
        : No(endereco, fila) {
        tabelaDoRoteador = new TabelaDeRepasse(TAMANHO_TABELA);
}

Roteador::~Roteador() {
    delete tabelaDoRoteador;
}

void Roteador::mapear(int endereco, No* adjacente, int atraso) {
    tabelaDoRoteador->mapear(endereco, adjacente, atraso);
}

void Roteador::setPadrao(No* padrao, int atraso) {
    tabelaDoRoteador->setPadrao(padrao, atraso);
}


Evento* Roteador::processar(int instante) {
    Datagrama* dtRetirado;

    if (filaDeDatagramas->isEmpty() == true)
        return NULL;
    else {
        cout << "Roteador " << endereco << endl;

        dtRetirado = filaDeDatagramas->dequeue();
        if (dtRetirado->getDestino() == endereco) {
            cout << "\tRecebido: " << dtRetirado->getSegmento() << endl;
            delete dtRetirado;
            return NULL;
        }

        else {
            int atraso;
            No* proximoNo = tabelaDoRoteador->getProximoSalto(dtRetirado->getDestino(), atraso);
            if (proximoNo == NULL) {
                cout << "\tSem chat: ";
                dtRetirado->imprimir();
                delete dtRetirado;
                return NULL;
            }
            else {
                cout << "\tRepassado para " << proximoNo->getEndereco() << " (instante " << instante + atraso << "): ";
                dtRetirado->imprimir();
                Evento* evento = new Evento(instante + atraso, proximoNo, dtRetirado);
                return evento;
            }
        }
    }
}

void Roteador::imprimir(){
    cout << "\tRoteador de endereco " << endereco << endl;
}
