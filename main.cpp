#include <iostream>
#include "Database.h"
int main() {
   Database d = Database("11");
   Graph dataset = d.getDataset();
   cout << dataset.edmonds_karp(1,dataset.n) << endl;
   list<int> path = dataset.dijkstra_path(1, dataset.n);
   cout<<"Path:"<<endl;
   for(auto iter=path.begin();iter!=path.end();iter++){
      cout << "Node " << *iter<< endl;
   }
   return 0;
}
