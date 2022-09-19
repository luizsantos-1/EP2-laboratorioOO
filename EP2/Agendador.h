#ifndef AGENDADOR_H
#define AGENDADOR_H
#include "Rede.h"
#include "Datagrama.h"
#include "Evento.h"
#include "No.h"

class Agendador
{
    public:
        Agendador(int instanteInicial, Rede* rede, int tamanho);
        virtual ~Agendador();

        virtual bool agendar(int instante, No* n, Datagrama* d);
        virtual void processar();
        virtual int getInstante();
    private:
        Rede* rede;
        int tamanho;
        Evento** eventosAgendados;
        int quantidade;
        int instanteAtual;
};

#endif // AGENDADOR_H
