#include <iostream>
#include "Cenario.h"

void menu(Cenario c){
    int opcao2,src,trg;
    do {
        cout << endl;
        cout << "Escolha o cenario (1 a 7) ou pressione 8 para sair: " << endl;
        cout << "1: 1.1 - Maximizar dimensao do grupo que nao se separa e mostrar caminhos" << endl;
        cout << "2: 1.2 - Comparar caminho maximizado com o caminho com menos transbordos" << endl;
        cout << "3: 2.1 - Caminho para um grupo dada a sua dimensao" << endl;
        cout << "4: 2.2 - Corrigir encaminhamento, para um grupo aumentar n unidades" << endl;
        cout << "5: 2.3 - Maximizar dimensao do grupo que se pode separar e mostrar caminhos" << endl;
        cout << "6: 2.4 - Tempo que o grupo inicial demora a se encontrarem todos no fim." << endl;
        cout << "7: 2.5 - Maximo tempo de espera de um grupo num ou mais locais" << endl;
        cout << "8: Sair" << endl;
        cin >> opcao2;
        cout << "Indique o nó source: "; cin>>src;
        cout << "Indique o nó sink: "; cin>>trg;
        switch (opcao2) {

            case 1:
                c.Cenario_1_1(src,trg);
                break;
            case 2:
                c.Cenario_1_2(src,trg);
                break;
            case 3:
                c.Cenario_2_1(src,trg);
                break;
            case 4:
                c.Cenario_2_2(src,trg);
                break;
            case 5:
                c.Cenario_2_3(src,trg);
                break;
            case 6:
                c.Cenario_2_4(src,trg);
                break;
            case 7:
                c.Cenario_2_5(src,trg);
                break;
            case 8:
                break;
            default:
                cout << "Opcao Invalida, tente de novo" << endl;
                break;
        }
        cout << endl;
    }while(!cin.fail() && opcao2!=8 && !cin.eof());
}

int main() {
    string opcao= "";
    Cenario c;
    do {
        cout << endl;
        cout << "Escolha o grafo (01 to 10) ou insira z para sair: ";
        cin >> opcao;
        if(opcao=="z" || cin.eof()) return 0;
        c = Cenario(opcao);
        menu(c);
    }while(!cin.fail() && !cin.eof());
    return 0;
}
