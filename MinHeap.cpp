#include "MinHeap.h"


MinHeap::MinHeap() { 
  mHeap.push_back(NULL);
  mPositions.push_back(NULL);
}


MinHeap::~MinHeap() {
  for (int i = 0; i < mHeap.size(); i++)
    delete mHeap[i];
  for (int j = 0; j < mPositions.size(); j++)
    delete mPositions[j];
}


int MinHeap::numElements() {
  return mHeap.size() - 1;
}


int MinHeap::getPosIndex(int labeltofind) {
  for (int i = 1; i < mPositions.size(); i++) {
    if (mPositions[i]->mLabel == labeltofind) {
      return i;
    }
  }
  std::cerr << "Label not found in pos vector: " << labeltofind << std::endl;
  return -1;
}



bool MinHeap::exists(int labeltofind) {
  for (int i = 1; i < mHeap.size(); i++) {
    if (mHeap[i]->mLabel == labeltofind)
      return true;
  }
  return false;
}


void MinHeap::displayHeap() {
  std::cout << "Displaying mHeap" << std::endl;
  for (int i = 1; i < mHeap.size(); i++) {
    std::cout << i << ": " << mHeap[i]->mLabel << " " << mHeap[i]->mKey << std::endl;
  }
  std::cout << std::endl;
}


void MinHeap::displayPositions() {
  std::cout << "Displaying mPositions" << std::endl;
  for (int i = 1; i < mPositions.size(); i++) {
    std::cout << i << ": " << mPositions[i]->mLabel << " " << mPositions[i]->mKey << std::endl;
  }
  std::cout << std::endl;
}


int MinHeap::top() {
  return mHeap[1]->mLabel;
}


bool MinHeap::isEmpty() {
  return numElements() == 0;
}


int MinHeap::Parent(int i) {
  return floor(i / 2);
}


int MinHeap::Left(int i) {
  return (2*i);
}


int MinHeap::Right(int i) {
  return (2*i + 1);
}


// CORE FXNS


void MinHeap::bubbleUp(int i) {
  int parentindex = Parent(i);
  if (i > 1 && mHeap[parentindex]->mKey > mHeap[i]->mKey) {
    int parentlabel = mHeap[parentindex]->mLabel;
    int childlabel = mHeap[i]->mLabel;
    
    std::swap(mHeap[i], mHeap[parentindex]);
    
    mPositions[getPosIndex(parentlabel)]->mKey = i;
    mPositions[getPosIndex(childlabel)]->mKey = parentindex;
    bubbleUp(parentindex);
  }
}


void MinHeap::decreaseKey(int label, int key) {
  int i = mPositions[getPosIndex(label)]->mKey; // get mHeap position of current node w/ old value
  mHeap[i]->mKey = key; // update key to new value
  bubbleUp(i);
}


void MinHeap::siftDown(int i) {
  int left = Left(i);
  int right = Right(i);
  int smallest = i;
  if (left <= numElements() && mHeap[left]->mKey < mHeap[i]->mKey)
    smallest = left;
  if (right <= numElements() && mHeap[right]->mKey < mHeap[smallest]->mKey)
    smallest = right;
  if (smallest != i) { // if there's a change to be made
    std::swap(mHeap[i], mHeap[smallest]);
    siftDown(smallest);
  }
}

 
void MinHeap::insert(Node* x) {
  mHeap.push_back(x);
  Node *posNode = new Node(x->mLabel, numElements()); // default position vec entry to last position in mHeap
  mPositions.push_back(posNode);
  bubbleUp(numElements());
}


void MinHeap::makeHeap(const std::vector<Node*> &S) {
  for (int i = 0; i < S.size(); i++ ) {
    mHeap.push_back(S[i]);

    Node *posNode = new Node(S[i]->mLabel, i+1); // default to last position
    mPositions.push_back(posNode);
  }
  for (int j = numElements(); j > 0; j--) {
    siftDown(j);
  }
}


int MinHeap::deleteMin() {
  if (isEmpty()) {
    std::cerr << "Trying to delete top element of empty heap. Exiting." << std::endl;
    exit(1);
  }
  
  // update pos vec before swapping
  int firstlabel = mHeap[1]->mLabel;
  int lastlabel = mHeap[numElements()]->mLabel;
  mPositions[getPosIndex(lastlabel)]->mKey = 1;
  mPositions[getPosIndex(firstlabel)]->mKey = -1;

  std::swap(mHeap[1], mHeap[numElements()]);
  mHeap.pop_back();

  siftDown(1);
  return firstlabel;
}
