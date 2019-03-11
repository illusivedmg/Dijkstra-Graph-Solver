#pragma once

#include <climits>
#include "MinHeap.h"


struct Edge {
  Edge(int dest, int weight);

  Edge* getNext() { return mNext; }

  void setNext(Edge* nn) { mNext = nn; }

  int getDestination() { return mDestination; }

  int getWeight() { return mWeight; }

private:
  int mDestination, mWeight;
  Edge* mNext;
};


struct EdgeList {
  EdgeList();

  ~EdgeList();

  Edge* getHead() { return mHead; }

  void setHead(Edge* nh) { mHead = nh; }

private:
  Edge* mHead;
};


// num vertices, directed or not, vec of linked list of edges per vertex
struct Graph {
  Graph(int numV, bool dir);

  ~Graph();

  void addEdge(int source, int dest, int weight);

  int getNumVertices() { return mNumVertices; }

  Edge* getStartingEdge(int i) { return mEdgeLists[i]->getHead(); }

private:
  std::vector<EdgeList*> mEdgeLists;
  int mNumVertices;
  bool mDirected;
};


struct Dijkstra {
  Dijkstra(Graph* G);

  ~Dijkstra();

  void solve(int start);

  void printSolution(int start);

private:
  Graph* mGraph;
  Node* mNewNode;
  MinHeap* mQ;
  Edge* mEdgeTraveler;
  int mNumVertices, i, u, v;
  std::vector<Node*> mNodeList;
  std::vector<int> mDist;
};