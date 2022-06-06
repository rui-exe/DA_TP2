//
// Created by Rui on 29/05/2022.
//

#include "Cenario.h"

Cenario::Cenario(string number){
    db = Database(number);
    dataset = db.getDataset();
}

void Cenario::Cenario_1_1(int src, int trg) {
    dataset = db.getDataset();
    cout << endl<< endl<<"1.1"<<endl <<endl;
    cout<<"Encaminhamento: Fluxo maximo"<<endl;
    auto start = chrono::steady_clock::now();
    list<int> path = dataset.dijkstra_path(src, trg);
    auto end = chrono::steady_clock::now();
    for(auto iter=path.begin();iter!=path.end();iter++){
        cout << "No " << *iter<< endl;
    }
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_1_2(int src, int trg) {
    cout << endl<< endl<<"1.2"<<endl <<endl;

    dataset = db.getDataset();


    auto start = chrono::steady_clock::now();

    dataset.showParetoOptimalPaths(src, trg);

    auto end = chrono::steady_clock::now();

    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_1(int src, int trg) {
    dataset = db.getDataset();
    int dimension;
    cout<<"Qual a dimensao do grupo desejada: "; cin>>dimension;
    cout << endl<< endl<<"2.1"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    dataset.addEdge(0,src,dimension,0);
    int max_flow = dataset.edmonds_karp(0,trg);
    cout << max_flow << endl;
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(0);
    group.first=path;
    group.second=max_flow;
    dataset.print_path(group,trg);
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_2(int src, int trg) {
    dataset = db.getDataset();
    int dimension,extra;
    cout<<"Qual a dimensao do grupo desejada: "; cin>>dimension;
    cout<<"Quantas pessoas quer adicionar ao grupo?: "; cin>>extra;
    dataset.addEdge(0,src,dimension,0);
    int max_flow = dataset.edmonds_karp(0,trg);
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(0);
    group.first=path;
    group.second=max_flow;
    cout << "Encaminhamento original: " << endl;
    dataset.print_path(group,trg);
    auto start = chrono::steady_clock::now();
    cout << endl;
    int added_people = dataset.correctRoute(src,trg,extra);
    auto end = chrono::steady_clock::now();
    if(added_people==0){
        cout << "Nao e possivel adicionar pessoas ao encaminhamento dado." << endl;
    }
    else{
        cout << added_people << " pessoas foram adicionadas ao encaminhamento." << endl << endl;
        cout << "Novo encaminhamento: " << endl;
        group.first=path;
        group.second=max_flow+added_people;
        dataset.print_path(group,trg);
    }
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}


void Cenario::Cenario_2_3(int src, int trg) {
    dataset = db.getDataset();
    cout<<endl<<endl<<"2.3"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    int max_flow = dataset.edmonds_karp(src,trg);
    cout << max_flow << endl;
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(1);
    group.first=path;
    group.second=max_flow;
    dataset.print_path(group,trg);
    auto end = chrono::steady_clock::now();
    cout <<endl<<"Fluxo Maximo = " <<max_flow << endl;
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_4(int src, int trg) {
    dataset = db.getDataset();
    auto start = chrono::steady_clock::now();
    dataset.edmonds_karp(src,trg);
    cout<<endl<<endl<<"2.4"<<endl <<endl;
    int durMin = dataset.criticalPath();
    cout <<"Tempo total de demora: "<< durMin <<" horas." <<endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_5(int src, int trg) {
    dataset = db.getDataset();
    auto start = chrono::steady_clock::now();
    dataset.edmonds_karp(src,trg);
    dataset.criticalPath();
    cout<< endl<<endl<<"2.5"<<endl <<endl;
    dataset.putInfoOnEdges(trg);
    pair<int,list<int>> waiting_nodes = dataset.getMaxWaitingTime();
    auto end = chrono::steady_clock::now();
    cout << "Pessoas esperaram " << waiting_nodes.first << " horas nos seguintes nos" << endl;
    for(auto iter=waiting_nodes.second.begin();iter!=waiting_nodes.second.end();iter++){
        cout << "No " << *iter << endl;
    }
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}
