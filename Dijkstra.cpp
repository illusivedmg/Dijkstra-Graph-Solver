#include "Dijkstra.h"


Edge::Edge(int dest, int weight) 
 : mDestination(dest), mWeight(weight) {
    mNext = NULL;
}


EdgeList::EdgeList() { 
  mHead = NULL; 
}


EdgeList::~EdgeList() {
  Edge* curr = mHead;
  Edge* next = NULL;
  while (curr) {
    next = curr->getNext();
    delete curr;
    curr = next;
  }
}


Graph::Graph(int numV, bool dir)
 : mNumVertices(numV), mDirected(dir) {
  EdgeList* newEL;
  for (int i = 0; i < mNumVertices; i++) {
    newEL = new EdgeList();
    mEdgeLists.push_back(newEL);
  }
}


Graph::~Graph() {
  for (int i = 0; i < mNumVertices; i++)
    delete mEdgeLists[i];
}


void Graph::addEdge(int source, int dest, int weight) {
  Edge* newE = new Edge(dest, weight);
  newE->setNext(mEdgeLists[source]->getHead());
  mEdgeLists[source]->setHead(newE);

  if (!mDirected) {
    newE = new Edge(source, weight);
    newE->setNext(mEdgeLists[dest]->getHead());
    mEdgeLists[dest]->setHead(newE);
  }
}


Dijkstra::Dijkstra(Graph* G)
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


Dijkstra::~Dijkstra() {
  delete mGraph;
  delete mQ;
  for (i = 0; i < mNodeList.size(); i++)
    delete mNodeList[i];
}


void Dijkstra::solve(int start) {
  mDist[start] = 0;
  mQ->decreaseKey(start, mDist[start]);

  while (!mQ->isEmpty()) {
    u = mQ->deleteMin();

    mEdgeTraveler = mGraph->getStartingEdge(u);
    while (mEdgeTraveler) {
      v = mEdgeTraveler->getDestination();
      if (mQ->getPositionIndexOfLabel(v) > 0 && mDist[u] != INT_MAX && mEdgeTraveler->getWeight() + mDist[u] < mDist[v]) {
        mDist[v] = mDist[u] + mEdgeTraveler->getWeight();
        mQ->decreaseKey(v, mDist[v]);
      }
      mEdgeTraveler = mEdgeTraveler->getNext();
    }
  }
  printSolution(start);
}


void Dijkstra::printSolution(int start) {
  std::cout << "Solution found." << std::endl;
  std::cout << "Starting from: " << start << std::endl;
  std::cout << "Vertex: Distance" << std::endl;
  for (i = 0; i < mDist.size(); i++) {
    std::cout << i << ": " << mDist[i] << std::endl;
  }
}