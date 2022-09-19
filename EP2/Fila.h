#ifndef FILA_H
#define FILA_H

#include "Datagrama.h"


class Fila {
    public:
        Fila(int tamanho);
        virtual ~Fila();

        virtual void enqueue(Datagrama* d);
        virtual Datagrama* dequeue();
        virtual bool isEmpty();
        virtual int getSize();

        virtual void imprimir();

    protected:
        int tamanho; //tamanho do vetor de datagramas
        int inicio; //indica de qual posicao sera retirado o proximo datagrama
        int fim; //indica em q posicao o proximo datagrama sera adicionado
        int contador; //tamanho da fila
        Datagrama **vetorDatagramas; //vetor
};

#endif // FILA_H
