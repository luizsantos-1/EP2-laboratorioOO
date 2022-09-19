#include "Rede.h"
#include <algorithm>

Rede::Rede(){
    nos = new list<No*>();
}

Rede::~Rede(){
    while (!nos->empty())
       nos->pop_back();
    delete nos;
}

void Rede::adicionar(No* n) {
    list<No*>::iterator no = nos->begin();
    while(nos->end()!= no) {
        if (n->getEndereco() == (*no)->getEndereco())
            throw new logic_error("Um no ja adicionado a rede tem esse endereco");
        no++;
    }
    nos->push_back(n);
}

No* Rede::getNo(int endereco) {
    list<No*>::iterator no = nos->begin();
    while(nos->end()!= no) {
        if (endereco == (*no)->getEndereco())
            return (*no);
        no++;
    }
    return NULL;
}

list<No*>* Rede::getNos() {
    return nos;
}

list<Hospedeiro*>* Rede::getHospedeiros() {
    list<Hospedeiro*>* hospedeiros = new list<Hospedeiro*>();
    list<No*>::iterator no = nos->begin();
    while(nos->end()!= no) {
        Hospedeiro* hospedeiro = dynamic_cast<Hospedeiro*>(*no);
        if (NULL != hospedeiro)
            hospedeiros->push_back(hospedeiro);
        no++;
    }
    return hospedeiros;
}

void Rede::imprimir() {
    list<No*>::iterator no = nos->begin();
    cout << "Rede de nos: " << endl;
    while(nos->end()!= no) {
        (*no)->imprimir();
        no++;
    }
    /*
    no = nos->begin();
    while(nos->end()!= no) {
        Roteador* r = dynamic_cast<Roteador*>(*no);
        if (r != NULL) {
            r->getTabelaDeRepasse();
        }
        no++;
    }
    */
}
