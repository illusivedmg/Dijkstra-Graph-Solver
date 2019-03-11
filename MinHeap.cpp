#include "MinHeap.h"


MinHeap::MinHeap() { 
  mHeap.push_back(NULL);
  mPositions.push_back(NULL);
}


MinHeap::~MinHeap() {
  for (int i = 0; i < mHeap.size(); i++)
    delete mHeap[i];
  for (int i = 0; i < mPositions.size(); i++)
    delete mPositions[i];
}


int MinHeap::getPositionIndexOfLabel(int labelToFind) {
  for (int i = 1; i < mPositions.size(); i++) {
    if (mPositions[i]->mLabel == labelToFind)
      return i;
  }
  return -1;
}


void MinHeap::displayHeap() {
  std::cout << "Displaying Heap" << std::endl;
  for (int i = 1; i < mHeap.size(); i++)
    std::cout << i << ": " << mHeap[i]->mLabel << " " << mHeap[i]->mKey << std::endl;
  std::cout << std::endl;
}


void MinHeap::displayPositions() {
  std::cout << "Displaying Positions" << std::endl;
  for (int i = 1; i < mPositions.size(); i++)
    std::cout << i << ": " << mPositions[i]->mLabel << " " << mPositions[i]->mKey << std::endl;
  std::cout << std::endl;
}


void MinHeap::swapPositions(int goldenChild, int scapeGoat) {
  int gcPos = getPositionIndexOfLabel(mHeap[goldenChild]->mLabel);
  int sgPos = getPositionIndexOfLabel(mHeap[scapeGoat]->mLabel);

  std::swap(mHeap[goldenChild], mHeap[scapeGoat]);

  mPositions[gcPos]->mKey = scapeGoat;
  mPositions[sgPos]->mKey = goldenChild;
}


void MinHeap::bubbleUp(int child) {
  int parent = Parent(child);
  if (child > 1 && mHeap[parent]->mKey > mHeap[child]->mKey) {
    swapPositions(child, parent);
    bubbleUp(parent);
  }
}


void MinHeap::siftDown(int parent) {
  int lChild = Left(parent);
  int rChild = Right(parent);
  int toddler = parent;

  if (lChild <= numElements() && mHeap[lChild]->mKey < mHeap[parent]->mKey)
    toddler = lChild;

  if (rChild <= numElements() && mHeap[rChild]->mKey < mHeap[toddler]->mKey)
    toddler = rChild;

  if (toddler != parent) {
    swapPositions(parent, toddler);
    siftDown(toddler);
  }
}


void MinHeap::decreaseKey(int label, int key) {
  int i = mPositions[getPositionIndexOfLabel(label)]->mKey;
  mHeap[i]->mKey = key;
  bubbleUp(i);
}


void MinHeap::insert(Node* x) {
  mHeap.push_back(x);
  Node *posNode = new Node(x->mLabel, numElements());
  mPositions.push_back(posNode);
  bubbleUp(numElements());
}


void MinHeap::makeHeap(const std::vector<Node*> &S) {
  for (int i = 0; i < S.size(); i++ ) {
    mHeap.push_back(S[i]);

    Node *posNode = new Node(S[i]->mLabel, i+1);
    mPositions.push_back(posNode);
  }
  for (int j = numElements(); j > 0; j--)
    siftDown(j);
}


int MinHeap::deleteMin() {
  if (isEmpty()) {
    std::cerr << "Trying to delete top element of empty heap. Exiting." << std::endl;
    exit(1);
  }

  int minLabel = mHeap[1]->mLabel;
  mPositions[getPositionIndexOfLabel(minLabel)]->mKey = -1;

  swapPositions(1, numElements());
  mHeap.pop_back();

  siftDown(1);
  return minLabel;
}
