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
    void correctRoute(Graph routeGraph,int previous_flow,int n,int trg);
    void Cenario_1_1(int src, int trg);
    void Cenario_1_2(int src, int trg);
    void Cenario_2_1(int src, int trg);
    void Cenario_2_2(int src, int trg);
    void Cenario_2_3(int src, int trg);
    void Cenario_2_4(int src, int trg);
    void Cenario_2_5(int src, int trg);
};


#endif //DA_TP2_CENARIO_H
