#ifndef FILACOMPRIORIDADE_H
#define FILACOMPRIORIDADE_H

#include "Fila.h"

class FilaComPrioridade : public Fila {
    public:
        FilaComPrioridade(int tamanho);
        virtual ~FilaComPrioridade();

        virtual void enqueue(Datagrama* d, bool prioritario);
        using Fila::enqueue;
        virtual Datagrama* dequeue();

    protected:

    private:
        int fimPrioritario;
};

#endif // FILACOMPRIORIDADE_H
