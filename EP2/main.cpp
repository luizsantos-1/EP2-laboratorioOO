#include <iostream>
#include <string>
#include <stdexcept>
#include "Segmento.h"
#include "FilaComPrioridade.h"
#include "PersistenciaDeRede.h"
#include "Rede.h"
#include "Chat.h"
#include "Agendador.h"

using namespace std;

int main() {
    try {
        int comando = 4;

        string nomeArquivo;
        cout << "Nome do arquivo: ";
        cin >> nomeArquivo;
        int instanteInicial;
        cout << "Instante inicial: ";
        cin >> instanteInicial;

        Rede* rede = new Rede();
        try {
            PersistenciaDeRede* persistencia = new PersistenciaDeRede(nomeArquivo);
            rede = persistencia->carregar();
        } catch (logic_error *e) {
            cout << e->what() << endl;
            delete e;
        }

        Agendador* agendador = new Agendador(instanteInicial, rede, 10);

        while (comando != 0) {

            cout << endl;
            cout<< "Simulador de Rede" << endl;
            cout<< "1) Enviar uma mensgaem" << endl;
            cout<< "2) Passar tempo" << endl;
            cout<< "0) Sair" << endl;
            cout<< "Escolha uma opcao: ";

            cin >> comando;
            cout << endl;

            if (comando == 1) {

                list<Hospedeiro*>* hospedeiros = rede->getHospedeiros();
                list<Hospedeiro*>::iterator h = hospedeiros->begin();
                while (h != hospedeiros->end()) {
                    cout << "Hospedeiro: " << (*h)->getEndereco() << endl;
                    vector<Chat*>* chats = (*h)->getChats();
                    for (unsigned int i = 0; i < chats->size(); i++)
                        (*chats)[i]->imprimir();
                    h++;
                }
                int enderecoHospedeiro;
                int portaChat;
                cout << "Endereco do hospedeiro: ";
                cin >> enderecoHospedeiro;
                cout << "Porta do chat: ";
                cin >> portaChat;

                Hospedeiro* hospedeiro = dynamic_cast<Hospedeiro*>(rede->getNo(enderecoHospedeiro));

                if (hospedeiro == NULL)
                    cout << "Erro: origem desconhecida" << endl;
                else {
                    Chat* chat = hospedeiro->getChat(portaChat);
                    if (chat == NULL)
                        cout << "Erro: origem desconhecida" << endl;
                    else {
                        cout << "Conteudo: " << endl;
                        cout << chat->getTextoCompleto() << endl;
                        string msg;
                        cout << "Mensagem: ";
                        cin >> msg;
                        chat->enviar(msg);
                    }
                }
            }

            if (comando == 2) {
                int qtdDeTempo;
                cout << "Quantidade de tempo: ";
                cin >> qtdDeTempo;
                cout << endl;

                for (int tempo = 1; tempo <= qtdDeTempo; tempo++){
                    cout << "Instante " << agendador->getInstante() << endl;
                    cout  << "---"<< endl;
                    agendador->processar();
                    if (tempo != qtdDeTempo)
                        cout << endl;
                }
            }
        }

        delete rede;
        delete agendador;
    } catch (invalid_argument *e) {
        cout << e->what() << endl;
        delete e;
    } catch (logic_error *e) {
        cout << e->what() << endl;
        delete e;
    } catch (overflow_error *e) {
        cout << e->what() << endl;
        delete e;
    } catch (underflow_error *e) {
        cout << e->what() << endl;
        delete e;
    }
    return 0;
}
