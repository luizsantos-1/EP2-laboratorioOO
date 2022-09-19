#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

#include "Fila.h"
#include "Datagrama.h"


Fila::Fila(int tamanho) : tamanho(tamanho) {
    inicio = 0;
    fim = 0;
    contador = 0;
    if (tamanho <= 0)
        throw new invalid_argument("Tamanho invalido");
    vetorDatagramas = new Datagrama*[tamanho];
}

Fila::~Fila() {
    if (inicio < fim) {
        for (int i = inicio; i < fim; i++)
            delete vetorDatagramas[i];//varre do incio ao fim da fila
    }
    else {
        for (int i = inicio; i < tamanho; i++)
            delete vetorDatagramas[i]; //varre do inicio da fila ao fim do vetor
        for (int i = 0; i < fim; i++)
            delete vetorDatagramas[i];
    }
    delete[] vetorDatagramas;

}

void Fila::enqueue(Datagrama* d) {
    if (tamanho == contador)
        throw new overflow_error("Nao se pode adicionar: Fila cheia");
    else {
        vetorDatagramas[fim] = d;
        contador += 1;

        if (fim  == tamanho - 1)
            fim = 0; //garante que a fila eh circular
        else
            fim += 1;
    }
}

Datagrama* Fila::dequeue() {
    if (isEmpty() == true)
        throw new underflow_error("Nao se pode retirar: fila vazia");

    else {
        int aux = inicio;
        contador--;
        if (inicio == tamanho - 1)
            inicio = 0;
        else
            inicio++;

        return vetorDatagramas[aux];
    }
}

bool Fila::isEmpty() {
    return contador == 0;
}

int Fila::getSize() {
    return contador;
}

void Fila::imprimir() {
    if (isEmpty() == true)
        cout << "Fila vazia" << endl;
    else {
        if (inicio < fim) {
                for (int i = inicio; i % tamanho < fim; i++)
                    vetorDatagramas[i]->imprimir();//varre do incio ao fim da fila
        }
        else {
            for (int i = inicio; i < tamanho; i++)
                vetorDatagramas[i]->imprimir(); //varre do inicio da fila ao fim do vetor
            for (int i = 0; i < fim; i++)
                vetorDatagramas[i]->imprimir(); //varre do inicio do vetor ao fim da fila
        }
    }
}
