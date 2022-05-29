#include <iostream>
#include "Database.h"
int main() {
   Database d = Database("11");
   Graph dataset = d.getDataset();
   /*
   cout<<"2.3"<<endl <<endl;

   cout <<dataset.edmonds_karp(1,dataset.n) << endl;
   int durMin = dataset.criticalPath();
   cout<< endl<<endl<<"2.5"<<endl <<endl;
   cout << durMin << endl;
   dataset.getLF(durMin);
   dataset.putInfoOnEdges();
   pair<int,list<int>> waiting_nodes = dataset.getMaxWaitingTime();
   cout << "People waited " << waiting_nodes.first << " hours in the following nodes" << endl;
   for(auto iter=waiting_nodes.second.begin();iter!=waiting_nodes.second.end();iter++){
       cout << "Node " << *iter << endl;

   }
    */
   cout << endl<< endl<<"1.1"<<endl <<endl;

   cout<<"Path: Max Flow"<<endl;
    list<int> path = dataset.dijkstra_path(1, dataset.n);
   for(auto iter=path.begin();iter!=path.end();iter++){
      cout << "Node " << *iter<< endl;
   }
  cout << endl<< endl<<"1.2"<<endl <<endl;

  cout<<"Path: Menos Transbordos"<<endl;
  list<int> stops_changes = dataset.unweighted_path(1,dataset.n);
  for(auto iter=stops_changes.begin();iter!=stops_changes.end();iter++)
    cout << "Node " << *iter<< endl;

  /*
  cout << endl<< endl<<"2.1"<<endl <<endl;
  dataset=d.getDataset();
    int n = 8; //user imput
    dataset.addEdge(0,1,n,0);

    cout <<dataset.edmonds_karp(0,dataset.n) << endl;
   return 0;
    */
}
