#include "PersistenciaDeRede.h"
#include <fstream>
#include <algorithm>
#include <list>
#include <stdexcept>

#include "No.h"
#include "Roteador.h"
#include "RoteadorComQoS.h"
#include "Hospedeiro.h"

PersistenciaDeRede::PersistenciaDeRede(string arquivo)
    : arquivo(arquivo){
    //ctor
}

PersistenciaDeRede::~PersistenciaDeRede(){
    //dtor
}
Rede* PersistenciaDeRede::carregar() {
    Rede* rede = new Rede();
    ifstream input;

    input.open("exemplo.txt");
    if (input.fail())
        throw new logic_error ("Erro na abertura do arquivo");


    int quantidadeDeRoteadores;
    input >> quantidadeDeRoteadores;

    for (int i = 0; i < quantidadeDeRoteadores; i++){
        string tipo;
        int endereco;
        input >> tipo;
        input >> endereco;

        if (tipo == "r")
            rede->adicionar(new Roteador(endereco));

        else {
            int quantidadeDePrioritarios;
            input >> quantidadeDePrioritarios;

            RoteadorComQoS* roteador = new RoteadorComQoS (endereco);

            for (int u = 0; u < quantidadeDePrioritarios; u++){
                int destino;
                input >> destino;
                roteador->priorizar(destino);
            }
            rede->adicionar(roteador);
        }
    }

    int quantidadeDeHospedeiros;
    input >> quantidadeDeHospedeiros;

    for (int i = 0; i < quantidadeDeHospedeiros; i++){
        int endereco;
        int gateway;
        int atraso;
        int quantidadeDeChats;

        input >> endereco;
        input >> gateway;
        input >> atraso;
        input >> quantidadeDeChats;

        list <No*>::iterator noGateway = rede->getNos()->begin();
        for (int u = 0; u < gateway - 1; u++)
            noGateway++;

        Hospedeiro* hospedeiro = new Hospedeiro(endereco, static_cast<Roteador*>(*noGateway), atraso);

        for (int u = 0; u < quantidadeDeChats; u++){
            int porta;
            int enderecoDeDestino;
            int portaDeDestino;

            input >> porta;
            input >> enderecoDeDestino;
            input >> portaDeDestino;

            hospedeiro->adicionarChat(porta, enderecoDeDestino, portaDeDestino);
        }
        rede->adicionar(hospedeiro);
    }

    for (int i = 0; i < quantidadeDeRoteadores; i++){
        list <No*>::iterator no = rede->getNos()->begin();
        list <No*>::iterator noPadrao = rede->getNos()->begin();

        int roteador;
        int roteadorPadrao;
        int atrasoPadrao;
        int quantidadeDeMapeamentos;

        input >> roteador;
        input >> roteadorPadrao;
        input >> atrasoPadrao;
        input >> quantidadeDeMapeamentos;

        for (int u = 0; u < roteador - 1; u++)
            no++;
        for (int u = 0; u < roteadorPadrao - 1; u++)
            noPadrao++;

        Roteador* noRoteador = static_cast<Roteador*>(*no);
        noRoteador->setPadrao((*noPadrao), atrasoPadrao);

        for (int u = 0; u < quantidadeDeMapeamentos; u++){
            int enderecoDoDestino;
            int enderecoAdjacente;
            int atraso;

            input >> enderecoDoDestino;
            input >> enderecoAdjacente;
            input >> atraso;

            list <No*>::iterator noAdjacente = rede->getNos()->begin();
            while (enderecoAdjacente != (*noAdjacente)->getEndereco())
                noAdjacente++;

            noRoteador->mapear(enderecoDoDestino, (*noAdjacente), atraso);
        }
    }
    input.close();
    return rede;
}

