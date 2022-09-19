#include "FilaComPrioridade.h"
#include <stdexcept>

FilaComPrioridade::FilaComPrioridade(int tamanho)
    : Fila(tamanho) {
    fimPrioritario = 0;
}

FilaComPrioridade::~FilaComPrioridade() {

}

void FilaComPrioridade::enqueue(Datagrama* d, bool prioritario) {
    if (tamanho == contador)
        throw new overflow_error("Nao se pode adicionar: Fila cheia");
    else {
        if (!prioritario) {
            vetorDatagramas[fim] = d;
        } else {
            if (fim >= inicio) {
                for (int i = fim; i > fimPrioritario; i--)
                    vetorDatagramas[i] = vetorDatagramas[i-1];
            } else {
                for (int i = fim; i > 0; i--)
                    vetorDatagramas[i] = vetorDatagramas[i-1];
                vetorDatagramas[0] = vetorDatagramas[tamanho-1];
                for (int i = tamanho-1; i > fimPrioritario; i--)
                    vetorDatagramas[i] = vetorDatagramas[i-1];
            }

            vetorDatagramas[fimPrioritario] = d;
            if (fimPrioritario  == tamanho - 1)
                fimPrioritario = 0;
            else
                fimPrioritario++;
        }
        contador++;
        if (fim  == tamanho - 1)
            fim = 0;
        else
            fim++;
    }
}

Datagrama* FilaComPrioridade::dequeue() {
    if (isEmpty() == true)
        throw new underflow_error("Nao se pode retirar: fila vazia");

    else {
        int aux = inicio;
        contador--;
        if (inicio == tamanho - 1)
            inicio = 0;
        else
            inicio++;

        if (aux == fimPrioritario)
            fimPrioritario = inicio;

        return vetorDatagramas[aux];
    }
}
