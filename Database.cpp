//
// Created by pedro on 22-05-2022.
//

#include "Database.h"

Database::Database(const string &number){
    ifstream input_file;
    string line;
    int num_nodes,num_edges;
    input_file.open("Tests_B/in"+number+"_b.txt");
    if(!input_file.is_open()){
        cout << "Error opening file " << "Tests_B/in"+number+"_b.txt" << endl;
    }
    else {
        getline(input_file, line);
        stringstream ss(line);
        ss >> num_nodes >> num_edges;
        dataset = Graph(num_nodes, true);
        for (int i = 1; i <= num_edges && getline(input_file, line); i++) {
            int src, dest, capacity, duration;
            stringstream edge(line);
            edge >> src >> dest >> capacity >> duration;
            dataset.addEdge(src, dest,  capacity, duration);
        }
    }
}

Graph Database::getDataset() const{
    return dataset;
}