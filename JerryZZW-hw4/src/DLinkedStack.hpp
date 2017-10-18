#pragma once

#include "StackInterface.hpp"
#include "Node.hpp"
#include <vector>
#include <cassert>

using namespace std;

template<class T>
class DLinkedStack : public StackInterface<T> {
private:
    Node<T> *headPtr;    // Pointer to first node in the chain;
    Node<T> *topPtr;    // Pointer to (last) node in the chain that contains the stack's top
public:

    DLinkedStack();

    DLinkedStack(const DLinkedStack<T> &aStack);    // Copy constructor

    virtual ~ DLinkedStack();    // Destructor

    Node<T> *getPointerTo(const T &target) const;

    bool isEmpty() const;

    bool push(const T &newItem);

    bool pop();

    T peek() const;

    vector<T> toVector() const;

    Node<T> *getHeadPTR() const;

    Node<T> *getTopPTR() const;
};

template<class T>
DLinkedStack<T>::DLinkedStack() : headPtr(nullptr), topPtr(nullptr) {
}

template<class T>
DLinkedStack<T>::DLinkedStack(const DLinkedStack<T> &aStack) {
    //TODO - Implement the copy constructor
    //pointers point to head and top
    Node<T> *origNode_headPtr = aStack.getHeadPTR();
    Node<T> *origNode_topPtr = aStack.getTopPTR();
    Node<T> *newNode = new Node<T>();

    if (aStack.isEmpty()) {
      topPtr = nullptr;  // original stack is empty
      headPtr = nullptr;
    }
    else {// original stack is not empty
      topPtr = new Node<T>();
      headPtr = new Node<T>();
      // original stack has only one node
      if (origNode_topPtr == origNode_headPtr) {
        newNode->setItem(origNode_topPtr->getItem());
        newNode->setNext(nullptr);
        newNode->setPrev(nullptr);
        topPtr = newNode;
        headPtr = topPtr;
      }
      else {//original stack has more than one node
        newNode->setItem(origNode_topPtr->getItem());
        newNode->setNext(nullptr);
        newNode->setPrev(origNode_topPtr->getPrev());
        topPtr = newNode;
        while (origNode_topPtr->getPrev()) {
          origNode_topPtr = origNode_topPtr->getPrev();
          newNode = newNode->getPrev();
          Node<T> *newNode_topPtr = topPtr;

          newNode->setItem(origNode_topPtr->getItem());
          newNode->setNext(newNode_topPtr);
          newNode->setPrev(nullptr);

          newNode_topPtr = newNode_topPtr->getPrev();
        }
        headPtr = newNode;
      }
    }
}//end copy constructor

template<class T>
DLinkedStack<T>::~DLinkedStack() {
    //TODO - Implement the destructor
    while (!isEmpty()) {
      pop();
    }
}//end deconstructor

template<class T>
Node<T> *DLinkedStack<T>::getPointerTo(const T &target) const {
    //TODO - Return the Node pointer that contains the target(return nullptr if not found)
    //when there is more than one target exists, return the first target from top.
    if (isEmpty()) {
      return nullptr;//return false when empty
    }
    else {//when it is not empty
      Node<T> *cur = topPtr;
      while (cur != nullptr) {
        if (cur->getItem() == target) {
          return cur;//return the target
        }
        cur = cur->getPrev();
      }
      return nullptr;//return null when not found
    }
}//end getPointerTo

template<class T>
bool DLinkedStack<T>::isEmpty() const {
    //TODO - Return True if the list is empty
    if (topPtr == nullptr) {
      return true;
    }
    else {
      return false;
    }
}//end isEmpty

template<class T>
bool DLinkedStack<T>::push(const T &newItem) {
    //TODO - Push an item on the Doubly Linked Stack
    Node<T> *newNode = new Node<T>();
    if (isEmpty()) {//when the stack is empty
      newNode->setItem(newItem);
      headPtr = newNode;
      topPtr = headPtr;
      headPtr->setPrev(nullptr);
      topPtr->setNext(nullptr);
    }
    else {//when it is not empty
      newNode->setItem(newItem);
      newNode->setPrev(topPtr);
      newNode->setNext(nullptr);
      topPtr->setNext(newNode);
      topPtr = newNode;
    }
    return true;
}//end push

template<class T>
bool DLinkedStack<T>::pop() {
    //TODO - Pop an item from the stack - Return true if successful
    if (isEmpty()) {
      return false;//return false when empty
    }
    else {
      if(headPtr == topPtr) {//when there is only one node
        headPtr = nullptr;
        topPtr = nullptr;
      }
      else {//when there is more than one node
        Node<T> *nodeToDel = topPtr;
        topPtr = topPtr->getPrev();
        delete nodeToDel;
        nodeToDel = nullptr;
      }
      return true;
    }
}//end pop


template<class T>
T DLinkedStack<T>::peek() const {
    //Assume this never fails.
    //TODO - return the element stored at the top of the stack (topPtr)
    return topPtr->getItem();
}//end peek

template<class T>
vector<T> DLinkedStack<T>::toVector() const {
    // DO NOT MODIFY THIS FUNCTION
    vector<T> returnVector;
    // Put stack items into a vector in top to bottom order
    Node<T> *curPtr = topPtr;
    while (curPtr != nullptr) {
        returnVector.push_back(curPtr->getItem());
        curPtr = curPtr->getPrev();
    }
    return returnVector;
}

template<class T>
Node<T> *DLinkedStack<T>::getHeadPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return headPtr;
}

template<class T>
Node<T> *DLinkedStack<T>::getTopPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return topPtr;
}