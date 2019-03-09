#include "MinHeap.h"
#include <climits>
#include <ctime>
#include <sstream>


struct Edge {
  Edge(int dest, int weight) 
   : mDestination(dest), mWeight(weight) {
     mNext = NULL;
   }

  Edge* getNext() { return mNext; }

  void setNext(Edge* nn) { mNext = nn; }

  int getDestination() { return mDestination; }

  int getWeight() { return mWeight; }

private:
  int mDestination, mWeight;
  Edge* mNext;
};


struct EdgeList {
  EdgeList() { mHead = NULL; };

  ~EdgeList() {
    Edge* curr = mHead;
    Edge* next = NULL;
    while (curr) {
      next = curr->getNext();
      delete curr;
      curr = next;
    }
  }

  Edge* getHead() { return mHead; }

  void setHead(Edge* nh) { mHead = nh; }

private:
  Edge* mHead;
};


// num vertices, directed or not, vec of linked list of edges per vertex
struct Graph {
  Graph(int numV, bool dir)
   : mNumVertices(numV), mDirected(dir) {
    EdgeList* newEL;
    for (int i = 0; i < mNumVertices; i++) {
      newEL = new EdgeList();
      mEdgeLists.push_back(newEL);
    }
  }

  ~Graph() {
    for (int i = 0; i < mNumVertices; i++)
      delete mEdgeLists[i];
  }

  void addEdge(int source, int dest, int weight) {
    Edge* newE = new Edge(dest, weight);
    newE->setNext(mEdgeLists[source]->getHead());
    mEdgeLists[source]->setHead(newE);

    if (!mDirected) {
      newE = new Edge(source, weight);
      newE->setNext(mEdgeLists[dest]->getHead());
      mEdgeLists[dest]->setHead(newE);
    }
  }

  int getNumVertices() { return mNumVertices; }

  Edge* getStartingEdge(int i) { return mEdgeLists[i]->getHead(); }

private:
  std::vector<EdgeList*> mEdgeLists;
  int mNumVertices;
  bool mDirected;
};


struct dijkstra {
  dijkstra(Graph* G)
   : mGraph(G) {
    mNumVertices = mGraph->getNumVertices();

    for (i = 0; i < mNumVertices; i++) {
      mDist.push_back(INT_MAX);
      mNewNode = new Node(i, mDist[i]);
      mNodeList.push_back(mNewNode);
    }

    mQ = new MinHeap();
    mQ->makeHeap(mNodeList);
  }

  ~dijkstra() {
    delete mGraph;
    delete mQ;
    for (i = 0; i < mNodeList.size(); i++)
      delete mNodeList[i];
  }

  void solve(int start) {
    mDist[start] = 0;
    mQ->decreaseKey(start, mDist[start]);

    while (!mQ->isEmpty()) {
      u = mQ->deleteMin();
      
      mEdgeTraveler = mGraph->getStartingEdge(u);
      while (mEdgeTraveler) {
        v = mEdgeTraveler->getDestination();
        if (mQ->exists(v) && mDist[u] != INT_MAX && mEdgeTraveler->getWeight() + mDist[u] < mDist[v]) {
          mDist[v] = mDist[u] + mEdgeTraveler->getWeight();
          mQ->decreaseKey(v, mDist[v]);
        }
        mEdgeTraveler = mEdgeTraveler->getNext();
      }
    }
    printSolution(start);
  }

  void printSolution(int start) {
    std::cout << "Solution found." << std::endl;
    std::cout << "Starting from: " << start << std::endl;
    std::cout << "Vertex: Distance" << std::endl;
    for (i = 0; i < mDist.size(); i++) {
      std::cout << i << ": " << mDist[i] << std::endl;
    }
  }

private:
  Graph* mGraph;
  Node* mNewNode;
  MinHeap* mQ;
  Edge* mEdgeTraveler;
  int mNumVertices, i, u, v;
  std::vector<Node*> mNodeList;
  std::vector<int> mDist;
};


int codeTest() {
  int numV = 9;
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

  dijkstra* D = new dijkstra(G);

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

  dijkstra* D = new dijkstra(G);

  D->solve(0);

  delete D;

  return 0;
}