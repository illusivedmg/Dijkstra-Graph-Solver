#include "MinHeap.h"
#include "Dijkstra.h"
#include <ctime>
#include <sstream>


int codeTest() {
  int numV = 10;
  Graph* G = new Graph(numV, false);

  G->addEdge(0, 1, 4);
  G->addEdge(0, 7, 8);
  G->addEdge(1, 2, 8);
  G->addEdge(1, 7, 11);
  G->addEdge(2, 3, 7);
  G->addEdge(2, 8, 2);
  G->addEdge(2, 5, 4);
  G->addEdge(3, 4, 9);
  G->addEdge(3, 5, 14);
  G->addEdge(4, 5, 10);
  G->addEdge(5, 6, 2);
  G->addEdge(6, 7, 1);
  G->addEdge(6, 8, 6);
  G->addEdge(7, 8, 7);
  G->addEdge(8, 9, 4);
  G->addEdge(6, 9, 14);

  Dijkstra* D = new Dijkstra(G);

  D->solve(0);

  delete D;

  return 0;
}


int main(int argc, char **argv) {
  std::srand(time(NULL)); 

  if (argc == 1)
    return codeTest();

  std::string arg(argv[1]);
  std::stringstream ss(arg);
  int probSizeExp;
  ss >> probSizeExp;

  int numV = pow(2, probSizeExp);

  Graph* G = new Graph(numV, false);

  for (int i = 0; i < numV; i++) {
    if (i != numV-1)
      G->addEdge(i, i+1, rand() % 50 + 1);
    else
      G->addEdge(i, 0, rand() % 50 + 1);

    int numEdges = rand() % 5; // 0-4 more edges
    for (int j = 0; j < numEdges; j++) {
      G->addEdge(i, rand() % numV, rand() % 50 + 1);
    }
  }

  Dijkstra* D = new Dijkstra(G);

  D->solve(0);

  delete D;

  return 0;
}