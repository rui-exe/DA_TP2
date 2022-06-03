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
    /**
     * Constructor of the Database class, reads the file number of the argument and creates a graph using its values
     * @param number number of the text file we want to read.
     */
    Database(const string &number);
    /**
     * Just a simple default constructor of the class Database
     */
    Database()=default;
    /**
     * Simple getter of the dataset, which is the graph created by this class's constructor
     * @return returns a graph containing the information stored in the file that was read by this class's constructor
     */
    Graph getDataset() const;
};


#endif //DA_TP2_DATABASE_H
