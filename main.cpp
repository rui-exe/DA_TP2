#include <iostream>
#include "Database.h"
int main() {
   Database d = Database("01");
   Graph dataset = d.getDataset();
   dataset.edmonds_karp(1,dataset.n);
   return 0;
}
