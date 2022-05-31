//
// Created by Rui on 29/05/2022.
//

#ifndef DA_TP2_CENARIO_H
#define DA_TP2_CENARIO_H

#include "Database.h"
#include <chrono>

class Cenario {
private:
    Database db;
    Graph dataset = Graph(1, true);
public:
    Cenario()= default;
    Cenario(string number);
    void Cenario_1_1();
    void Cenario_1_2();
    void Cenario_2_1();
    void Cenario_2_2();
    void Cenario_2_3();
    void Cenario_2_4();
    void Cenario_2_5();
};


#endif //DA_TP2_CENARIO_H
