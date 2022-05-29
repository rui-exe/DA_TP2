//
// Created by pedro on 22-05-2022.
//

#ifndef DA_TP2_DATABASE_H
#define DA_TP2_DATABASE_H

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Database {
private:
    Graph dataset=Graph(0,true);
public:
    Database(const string &number);
    Database()=default;
    Graph getDataset() const;
};


#endif //DA_TP2_DATABASE_H
