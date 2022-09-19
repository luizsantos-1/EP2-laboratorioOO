#include "TabelaDeRepasse.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

TabelaDeRepasse::TabelaDeRepasse(int tamanho) : tamanho(tamanho) {
    if (tamanho <= 0)
        throw new invalid_argument ("Tamanho invalido");
    posicaoVazia = 0;
    noPadrao = NULL;
    atrasoPadrao = 0;
    enderecosDeDestino = new int [tamanho];
    atrasos = new int [tamanho];
    nosAdjacentes = new No*[tamanho];

}

TabelaDeRepasse::~TabelaDeRepasse() {
    delete[] enderecosDeDestino;
    delete[] atrasos;
    delete[] nosAdjacentes;
}

void TabelaDeRepasse::mapear(int endereco, No* adjacente, int atraso) {
    for (int i = 0; i < posicaoVazia; i++) {
        if (enderecosDeDestino[i] == endereco)
            throw new invalid_argument("O endereco ja foi mapeado");
    }
    if (posicaoVazia < tamanho) {
        enderecosDeDestino[posicaoVazia] = endereco;
        nosAdjacentes[posicaoVazia] = adjacente;
        atrasos[posicaoVazia] = atraso;
        posicaoVazia++;
    }
    else
        throw new overflow_error("Numero maximo de enderecos ja mapeados");
}

No** TabelaDeRepasse::getAdjacentes() {
    return nosAdjacentes;
}

int TabelaDeRepasse::getQuantidadeDeAdjacentes() {
    return posicaoVazia;
}

void TabelaDeRepasse::setPadrao(No* padrao, int atraso) {
    noPadrao = padrao;
    atrasoPadrao = atraso;
}

No* TabelaDeRepasse::getProximoSalto(int endereco, int& atraso) {
    for (int i = 0; i < posicaoVazia; i++) {
        if (enderecosDeDestino[i] == endereco){
            atraso = atrasos[i];
            return nosAdjacentes[i];
        }
    }
    atraso = atrasoPadrao;
    return noPadrao;

}

void TabelaDeRepasse::imprimir() {
    cout << "\t\tNo padrao: " << noPadrao->getEndereco() << ", atraso padrao: " << atrasoPadrao <<  " e quantidade de adjacentes: " << posicaoVazia << ";" << endl;
    for (int i = 0; i < posicaoVazia; i++) {
        cout << "\t\t\tMapeamento " << i + 1 << ":";
        cout << " Endereco de destino: " << enderecosDeDestino[i];
        cout << ", endereco do adjacente: " << nosAdjacentes[i]->getEndereco();
        cout << " e atraso: " << atrasos[i] << endl;
    }
}
