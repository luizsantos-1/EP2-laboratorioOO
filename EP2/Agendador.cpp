#include "Agendador.h"
#include <list>
#include <algorithm>

using namespace std;

Agendador::Agendador(int instanteInicial, Rede* rede, int tamanho)
    :rede(rede), tamanho(tamanho), instanteAtual(instanteInicial) {
    eventosAgendados = new Evento*[tamanho];
    quantidade = 0;
}

Agendador::~Agendador() {
    for (int i = 0; i < quantidade; i++)
        delete eventosAgendados[i];
    delete[] eventosAgendados;
}

bool Agendador::agendar(int instante, No* r, Datagrama* d) {
    if (quantidade >= tamanho)
        return false;

    else {
        eventosAgendados[quantidade] = new Evento(instante, r, d);
        quantidade++;
        return true;
    }
}

void Agendador::processar(){
    for (int i = 0; i < quantidade; i++) {
        if (instanteAtual == eventosAgendados[i]->getInstante()) { //verifica se o evento esta agendado para o instante atual
            //eventosAgendados[i]->getDatagrama()->imprimir();
            eventosAgendados[i]->getDestino()->receber(eventosAgendados[i]->getDatagrama()); //o No de destino do evento recebe o datagrama
            delete eventosAgendados[i];
            for (int u = i; u < quantidade - 1; u++) //desloca todos os eventos seguintes para eliminar o "buraco" criado ao se ler o evento
                eventosAgendados[u] = eventosAgendados[u+1];
            i--; //volta-se uma posicao para ler-se os eventos deslocados
            quantidade--;
        }
    }

    Evento *nullOuEvento = NULL;
    list<No*>* nos = rede->getNos();
    list<No*>::iterator no = nos->begin();
    while(nos->end()!= no) {
        nullOuEvento = (*no)->processar(instanteAtual); //chama o metodo processar de cada um dos Nos da rede
        if (nullOuEvento != NULL) //caso o processar retorne um evento, ele eh agendado
            agendar(nullOuEvento->getInstante(), nullOuEvento->getDestino(), nullOuEvento->getDatagrama());
        no++;
    }
    instanteAtual++;
}

int Agendador::getInstante() {
    return instanteAtual;
}

