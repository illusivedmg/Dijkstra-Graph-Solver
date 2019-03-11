#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>


struct Node {
  Node(int lab, int k)
  : mLabel(lab), mKey(k) {}

  int mLabel, mKey;
};


class MinHeap {
public:
  // init vectors as 1-indexed
  MinHeap();

  // delete Nodes in both lists
  ~MinHeap();

  // |i|
  int numElements() { return mHeap.size()-1; };

  int top() { return mHeap[1]->mLabel; };

  bool isEmpty() { return numElements() == 0; };

  // i^-1(x) => get index in position vector of label
  int getPositionIndexOfLabel(int labeltofind); 

  // swap and update in Pos vector
  void swapPositions(int indexL, int indexR);

  // prints contents of vectors
  void displayHeap();
  void displayPositions();

  // compare parent with child, swap if parent bigger
  void bubbleUp(int i);

  // same label as existing Node, new value for key
  void decreaseKey(int label, int key);

  // compare parent with children, swap with smaller
  void siftDown(int i);

  void insert(Node* x);

  void makeHeap(const std::vector<Node*> &S);

  // swaps and pops first/last in heap, swap/nullify in pos vector
  int deleteMin();

private:
  int Parent(int i) { return floor(i/2); };

  int Left(int i) { return (2*i); };

  int Right(int i) { return (2*i+1); };

  // key = value to minimize
  std::vector<Node*> mHeap;

  // key = tree index/position
  std::vector<Node*> mPositions;
};