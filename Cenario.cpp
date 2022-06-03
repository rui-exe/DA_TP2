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
    auto end = chrono::steady_clock::now();
    for(auto iter=path.begin();iter!=path.end();iter++){
        cout << "Node " << *iter<< endl;
    }
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_1_2() {
    cout << endl<< endl<<"1.2"<<endl <<endl;

    dataset = db.getDataset();


    auto start = chrono::steady_clock::now();

    dataset.showParetoOptimalPaths();

    auto end = chrono::steady_clock::now();


    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_1() {
    dataset = db.getDataset();
    int dimension;
    cout<<"Qual a dimensao do grupo desejada: "; cin>>dimension;
    cout << endl<< endl<<"2.1"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    dataset.addEdge(0,1,dimension,0);
    int max_flow = dataset.edmonds_karp(0,dataset.n);
    cout << max_flow << endl;
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(0);
    group.first=path;
    group.second=max_flow;
    dataset.print_path(group);
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_2() {
    dataset = db.getDataset();
    int dimension,added_people;
    cout<<"Qual a dimensao do grupo desejada: "; cin>>dimension;
    cout<<"Quantas pessoas quer adicionar ao grupo?: "; cin>>added_people;

    dataset.addEdge(0,1,dimension,0);
    int max_flow = dataset.edmonds_karp(0,dataset.n);
    cout << max_flow << endl;
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(0);
    group.first=path;
    group.second=max_flow;
    cout << "Original route: " << endl;
    dataset.print_path(group);
    cout << endl;
    Graph routeGraph = dataset.createRouteGraph();
    correctRoute(routeGraph,max_flow,added_people);

}

void Cenario::correctRoute(Graph routeGraph,int previous_flow,int n){
    routeGraph.nodes[1].adj.front().capacity+=n;
    int max_flow = routeGraph.edmonds_karp(1,routeGraph.n);
    if(max_flow==previous_flow){
        cout << "Impossible to correct given route!" << endl;
    }
    else{
        cout << "Added " << max_flow-previous_flow << " people to the given route" << endl;
        cout << "New route:" << endl;
        pair<list<int>,int> group;
        list<int>path;
        path.push_back(1);
        group.first=path;
        group.second=max_flow;
        routeGraph.print_path2(group);
    }
}

void Cenario::Cenario_2_3() {
    dataset = db.getDataset();
    cout<<endl<<endl<<"2.3"<<endl <<endl;
    auto start = chrono::steady_clock::now();
    int max_flow = dataset.edmonds_karp(1,dataset.n);
    cout << max_flow << endl;
    pair<list<int>,int> group;
    list<int>path;
    path.push_back(1);
    group.first=path;
    group.second=max_flow;
    dataset.print_path(group);
    auto end = chrono::steady_clock::now();
    cout <<endl<<"Max Flow = " <<max_flow << endl;
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_4() {
    dataset = db.getDataset();
    auto start = chrono::steady_clock::now();
    dataset.edmonds_karp(1,dataset.n);
    cout<<endl<<endl<<"2.4"<<endl <<endl;
    int durMin = dataset.criticalPath();
    cout <<"Tempo total de demora: "<< durMin <<" horas." <<endl;
    auto end = chrono::steady_clock::now();
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}

void Cenario::Cenario_2_5() {
    dataset = db.getDataset();
    auto start = chrono::steady_clock::now();
    dataset.edmonds_karp(1,dataset.n);
    dataset.criticalPath();
    cout<< endl<<endl<<"2.5"<<endl <<endl;
    dataset.putInfoOnEdges();
    pair<int,list<int>> waiting_nodes = dataset.getMaxWaitingTime();
    auto end = chrono::steady_clock::now();
    cout << "People waited " << waiting_nodes.first << " hours in the following nodes" << endl;
    for(auto iter=waiting_nodes.second.begin();iter!=waiting_nodes.second.end();iter++){
        cout << "Node " << *iter << endl;
    }
    cout << "Tempo de execucao: "<<chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms"<< endl;
}
