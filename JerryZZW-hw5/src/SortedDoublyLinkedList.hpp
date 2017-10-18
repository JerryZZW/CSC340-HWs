#include <vector>
#include <memory>
#include "Node.hpp"

#pragma once


using namespace std;

template<class ItemType>
class SortedDoublyLinkedList {
    //DO NOT MODIFY THIS CLASS DECLARATION. FIND T-O-D-O-S to work on.
private:
    std::shared_ptr<Node<ItemType>> head;
    std::shared_ptr<Node<ItemType>> tail;
    int size;
public:

    SortedDoublyLinkedList();

    SortedDoublyLinkedList(std::shared_ptr<Node<ItemType>> head, std::weak_ptr<Node<ItemType>> tail, int size);

    SortedDoublyLinkedList(const SortedDoublyLinkedList<ItemType> &list);    // Copy constructor

    std::shared_ptr<Node<ItemType>> getPointerTo(const ItemType &target) const;

    virtual ~ SortedDoublyLinkedList();    // Destructor should be virtual

    int getCurrentSize() const;

    bool isEmpty() const;

    bool add(const ItemType &newEntry);

    bool remove(const ItemType &anEntry);

    bool contains(const ItemType &anEntry) const;

    int getFrequencyOf(const ItemType &anEntry) const;

    vector<ItemType> toVector() const;

};

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList() : head(nullptr), tail(),
                                                             size(0) { }

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList(std::shared_ptr<Node<ItemType>> head, std::weak_ptr<Node<ItemType>> tail, int size) :
        head(head), tail(tail), size(size) { }

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList(const SortedDoublyLinkedList<ItemType> &list) {
    //TODO - Implement the copy constructor
    auto origNode_headPtr = list.head;

    if(list.isEmpty()) {//when original list is empty
      SortedDoublyLinkedList();
    }
    else {//when original list is not empty
      head = make_shared<Node<ItemType>>();
      head.get()->setItem(list.head.get()->getItem());
      size = list.size;


      auto newNode_headPtr = head;
      weak_ptr<Node<ItemType>> cur;
      origNode_headPtr = origNode_headPtr.get()->getNext();
      while(origNode_headPtr != nullptr) {
        auto newNodePtr = make_shared<Node<ItemType>>(origNode_headPtr.get()->getItem());

        newNode_headPtr.get()->setNext(newNodePtr);
        newNode_headPtr.get()->setPrev(cur);

        newNode_headPtr = newNode_headPtr.get()->getNext();
        cur = newNode_headPtr.get()->getPrev();

        origNode_headPtr = origNode_headPtr.get()->getNext();
      }// end while

      newNode_headPtr.get()->setNext(nullptr);

      if(size == 1) {
        tail = head;
      }
      else {
        tail = newNode_headPtr;
      }

    } // end if
}// end copy constructor

template<class ItemType>
std::shared_ptr<Node<ItemType>> SortedDoublyLinkedList<ItemType>::getPointerTo(const ItemType &target) const {
    //TODO - Return the Node pointer that contains the target(return nullptr if not found)
    if (isEmpty()) {//when list is empty, return false
      return nullptr;
    }
    else {//when list is not empty
      auto cur = head;
      while(cur) {
        if(cur.get()->getItem() == target) {
          return cur;
        }
        cur = cur.get()->getNext();
      }
      return nullptr;
    }
}

template<class ItemType>
SortedDoublyLinkedList<ItemType>::~SortedDoublyLinkedList() {
    //TODO - Implement the destructor
    head = nullptr;
}

template<class ItemType>
int SortedDoublyLinkedList<ItemType>::getCurrentSize() const {
    //TODO - Return the current size
     return size;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::isEmpty() const {
    //TODO - Return True if the list is empty
    return size == 0;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::add(const ItemType &newEntry) {
    //TODO - Add an item to the sorted Doubly Linked list
    auto newNode = make_shared<Node<ItemType>>();
    if(isEmpty()) {//when list is empty
      newNode.get()->setItem(newEntry);
      head = newNode;
      tail = head;
      size++;
    }
    else {//when list is not empty
      newNode.get()->setItem(newEntry);
      newNode.get()->setPrev(tail);
      tail.get()->setNext(newNode);
      tail = newNode;
      size++;
      // sort list in ascending order
      for (int i = 0; i < size; i++) {
        auto cur = head;
        while (cur.get()->getNext()) {
          if (cur.get()->getItem() > cur.get()->getNext().get()->getItem()) {
            auto item = cur.get()->getItem();
            cur.get()->setItem(cur.get()->getNext().get()->getItem());
            cur.get()->getNext().get()->setItem(item);
          }
          cur = cur.get()->getNext();
        }
      }
    }
    return true;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::remove(const ItemType &anEntry) {
    //TODO - Remove the Item(anEntry) from the list - Return true if successful
    if(isEmpty()) {//when list is empty, return false
      return false;
    }
    else {//when list is not empty
      auto cur = head;
      while(cur) {
        if(cur.get()->getItem() == anEntry) {
          if (cur == head) {
            head = cur.get()->getNext();
            size--;
          }
          else if(cur == tail) {
            tail = cur.get()->getPrev().lock();
            tail.get()->setNext(nullptr);
            size--;
          }
          else {
            cur.get()->getPrev().lock().get()->setNext(cur.get()->getNext());
            cur.get()->getNext().get()->setPrev(cur.get()->getPrev());
            size--;
          }
          return true;
        }
        cur = cur.get()->getNext();
      }
      return false;
    }
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::contains(const ItemType &anEntry) const {
    //TODO - Check if the List contains the Item(anEntry)- Return true if successful
    auto cur = head;
    while(cur) {
      if(cur.get()->getItem() == anEntry) {
        return true;
      }
      cur = cur.get()->getNext();
    }
    return false;
}

template<class ItemType>
int SortedDoublyLinkedList<ItemType>::getFrequencyOf(const ItemType &anEntry) const {
    //TODO - Return the frequency of the Item(anEntry) in the list
    auto cur = head;
    int count = 0;
    while(cur) {
      if(cur.get()->getItem() == anEntry) {
        count++;
      }
      cur = cur.get()->getNext();
    }
    return count;
}

template<class ItemType>
vector<ItemType> SortedDoublyLinkedList<ItemType>::toVector() const {
    // DO NOT MODIFY THIS FUNCTION
    vector <ItemType> myVector;
    std::shared_ptr<Node<ItemType>> cur;
    cur = this->head;
    while (cur != nullptr) {
        myVector.push_back(cur->getItem());
        cur = cur->getNext();
    }
    return myVector;
}
