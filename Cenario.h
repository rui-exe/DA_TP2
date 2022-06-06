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
    /**
     * Simple default constructor of the Cenario Class
     */
    Cenario()= default;
    /**
     * Constructor of the Cenario Class. Initializes the db field with the number of the file we want to read.
     * Initializes the dataset by using the get_dataset method from the Database Class
     * @param number number of the file we want to read.
     */
    Cenario(string number);
    /**
     * Calls all the functions needed for cenario 1.1 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_1_1(int src, int trg);
    /**
     * Calls all the functions needed for cenario 1.2 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_1_2(int src, int trg);
    /**
     * Calls all the functions needed for cenario 2.1 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_2_1(int src, int trg);
    /**
     * Calls all the functions needed for cenario 2.2 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_2_2(int src, int trg);
    /**
     * Calls all the functions needed for cenario 2.3 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_2_3(int src, int trg);
    /**
     * Calls all the functions needed for cenario 2.4 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_2_4(int src, int trg);
    /**
     * Calls all the functions needed for cenario 2.5 and prints its execute time
     * @param src source node
     * @param trg sink node (target)
     */
    void Cenario_2_5(int src, int trg);
};


#endif //DA_TP2_CENARIO_H
