//
// Created by Rui on 29/05/2022.
//

#include "Cenario.h"

Cenario::Cenario(string number){
    db = Database(number);
    dataset = db.getDataset();
}

void Cenario::Cenario_1_1() {
    dataset = db.getDataset();
    cout << endl<< endl<<"1.1"<<endl <<endl;
    cout<<"Path: Max Flow"<<endl;
    auto start = chrono::steady_clock::now();
    list<int> path = dataset.dijkstra_path(1, dataset.n);
    for(auto iter=path.begin();iter!=path.end();iter++){
        cout << "Node " << *iter<< endl;
    }
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_1_2() {
    dataset = db.getDataset();
    cout << endl<< endl<<"1.2"<<endl <<endl;

    cout<<"Path: Max Flow"<<endl;
    list<int> path = dataset.dijkstra_path(1, dataset.n);
    for(auto iter=path.begin();iter!=path.end();iter++){
        cout << "Node " << *iter<< endl;
    }
    cout<<endl;
    cout<<"Path: Menos Transbordos"<<endl;
    auto start = chrono::steady_clock::now();
    list<int> stops_changes = dataset.unweighted_path(1,dataset.n);
    for(auto iter=stops_changes.begin();iter!=stops_changes.end();iter++)
        cout << "Node " << *iter<< endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;

}

void Cenario::Cenario_2_1() {
    dataset = db.getDataset();
    int dimension;
    cout<<"Qual a dimensao do grupo desejada: "; cin>>dimension;
    cout << endl<< endl<<"2.1"<<endl <<endl;
    dataset.addEdge(0,1,dimension,0);
    auto start = chrono::steady_clock::now();
    cout <<dataset.edmonds_karp(0,dataset.n) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;

}

void Cenario::Cenario_2_2() {
    dataset = db.getDataset();
}

void Cenario::Cenario_2_3() {
    dataset = db.getDataset();
    cout<<endl<<endl<<"2.3"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    cout <<dataset.edmonds_karp(1,dataset.n) << endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_4() {
    dataset = db.getDataset();
    dataset.edmonds_karp(1,dataset.n);
    cout<<endl<<endl<<"2.4"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    int durMin = dataset.criticalPath();
    cout << durMin << endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_5() {
    dataset = db.getDataset();
    dataset.edmonds_karp(1,dataset.n);
    auto start = chrono::steady_clock::now();
    int durMin = dataset.criticalPath();
    cout<< endl<<endl<<"2.5"<<endl <<endl;
    dataset.getLF(durMin);
    dataset.putInfoOnEdges();
    pair<int,list<int>> waiting_nodes = dataset.getMaxWaitingTime();
    cout << "People waited " << waiting_nodes.first << " hours in the following nodes" << endl;
    for(auto iter=waiting_nodes.second.begin();iter!=waiting_nodes.second.end();iter++){
        cout << "Node " << *iter << endl;

    }
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}
