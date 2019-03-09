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
  int numElements();

  // i^-1(x) => get index in position vector of label
  int getPosIndex(int labeltofind);

  bool exists(int labeltofind);
  
  // prints contents of vectors
  void displayHeap();
  void displayPositions();

  // returns top label
  int top();
  
  bool isEmpty();

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
  int Parent(int i);
  int Left(int i);
  int Right(int i);

  // key = value to minimize
  std::vector<Node*> mHeap;

  // key = tree index/position
  std::vector<Node*> mPositions; 
};