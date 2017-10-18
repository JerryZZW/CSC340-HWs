#pragma once

#include "DictionaryInterface.h"
#include "HashedEntry.h"
#include <exception>
#include <unordered_map>
#include <vector>


#define DEFAULT_SIZE 101

/**
 *
 * This Hash table is of fixed max size 101 - which is a prime number (why?)
 */
template<class KeyType, class ItemType>
class HashedDictionary : public DictionaryInterface<KeyType, ItemType> {
private:
    HashedEntry<KeyType, ItemType> **hashTable;  // Array of pointers to entries
    int itemCount;
    int hashTableSize; //Default value should be assigned to 101

    int getHashIndex(const KeyType &itemKey) const;

    void destroyDictionary();

public:


    virtual ~HashedDictionary();

    HashedDictionary();

    bool isEmpty() const override;

    int getNumberOfItems() const override;

    bool add(const KeyType &searchKey, const ItemType &newItem) override;

    bool remove(const KeyType &searchKey) override;

    void clear() override;

    ItemType getItem(const KeyType &searchKey) const override;

    bool contains(const KeyType &searchKey) const override;

    void traverse(void (*visit)(ItemType &)) const override;

    std::vector<ItemType> toVector() const override;

    HashedEntry<KeyType, ItemType>& operator[](KeyType key);


};

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType &key) const {
    //DO NOT MODIFY
    return static_cast<int>(key % hashTableSize);
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
        : itemCount(0), hashTableSize(DEFAULT_SIZE) {
    //DO NOT MODIFY
    hashTable = new HashedEntry<KeyType, ItemType> *[DEFAULT_SIZE];
    for (int i = 0; i < DEFAULT_SIZE; i++)
        hashTable[i] = nullptr;
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::destroyDictionary() {
    //TODO
  for (int index = 0; index < hashTableSize && hashTable[index] != nullptr; index++) {
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
    remove(chainPtr->getKey());
  }
  itemCount = 0;
}

template<class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::~HashedDictionary() {
    //DO NOT MODIFY
    destroyDictionary();
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear() {
    //DO NOT MODIFY
    destroyDictionary();
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty() const {
    //TODO
    return itemCount == 0;
}

template<class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getNumberOfItems() const {
    //TODO
    return itemCount;
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::add(const KeyType &searchKey, const ItemType &newItem) {
    //TODO
  if(itemCount == 101) {//If the hash table is full, return false
    return false;
  }
  else {//When the hash table is not full
    HashedEntry<KeyType, ItemType>* newHashEntry = new HashedEntry<KeyType, ItemType>(searchKey, newItem);
    newHashEntry->setNext(nullptr);
    if(isEmpty()) {//When the hash table is empty
      hashTable[0] = newHashEntry;
      newHashEntry->setNext(nullptr);
      itemCount++;
      return true;
    }
    else {//When the hash table is not empty, but not full
      for(int index = 0; index < hashTableSize; index++) {//Add the item to the hash table
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        if(hashTable[index] == nullptr) {
          chainPtr = newHashEntry;
          chainPtr->setNext(nullptr);
          hashTable[index] = chainPtr;
          itemCount++;
          break;
        }
      }
      //Sort the hash table
      for(int i = 0; i < itemCount; i++) {
        for(int index = 0; index < itemCount; index++) {
          if(hashTable[index] == nullptr || hashTable[index+1] == nullptr) {
            break;
          }
          else if(hashTable[index]->getKey() % hashTableSize > hashTable[index+1]->getKey() % hashTableSize) {
            std::swap(hashTable[index], hashTable[index+1]);
          }
          else if(hashTable[index]->getKey() % hashTableSize == hashTable[index+1]->getKey() % hashTableSize) {
            std::swap(hashTable[index], hashTable[index+1]);
          }
        }
      }
      return true;
    }
  }
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType &searchKey) {
    //TODO
    if(isEmpty()) {//If the hash table is empty, return false
      return false;
    }
    else {//Loop the hash table until the item is found
      for (int index = 0; index < hashTableSize && hashTable[index] != nullptr; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        if(chainPtr->getKey() == searchKey) {
          hashTable[index] = chainPtr->getNext();
          itemCount--;
          return true;
        }
      }
      return false;
    }
}

template<class KeyType, class ItemType>
ItemType HashedDictionary<KeyType, ItemType>::getItem(const KeyType &searchKey) const {
    //TODO
  if(contains(searchKey) == false) {//Throw default exception, if the item is not found
    throw std::exception();
  }//Loop the hash table until the item is found
  for (int index = 0; index < hashTableSize; index++) {
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
    if(chainPtr->getKey() == searchKey) {
      return chainPtr->getItem();
    }
  }
}

template<class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::contains(const KeyType &searchKey) const {
    //TODO
  for (int index = 0; index < hashTableSize && hashTable[index] != nullptr; index++) {
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
    if(chainPtr->getKey() == searchKey) {
      return true;
    }
  }
  return false;
}

template<class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(void (*visit)(ItemType &)) const {
    //DO NOT MODIFY
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            visit(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
}

template<class KeyType, class ItemType>
std::vector<ItemType> HashedDictionary<KeyType, ItemType>::toVector() const {
    //DO NOT MODIFY
    std::vector<ItemType> returnVector;
    for (int index = 0; index < hashTableSize; index++) {
        HashedEntry<KeyType, ItemType> *chainPtr = hashTable[index];
        while (chainPtr != nullptr) {
            ItemType currentItem = chainPtr->getItem();
            returnVector.push_back(currentItem);
            chainPtr = chainPtr->getNext();
        }
    }
    return returnVector;
};

template<class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>& HashedDictionary<KeyType, ItemType>::operator[](KeyType searchKey){
    //DO NOT MODIFY
    int itemHashIndex = getHashIndex(searchKey);
    HashedEntry<KeyType, ItemType> *chainPtr = hashTable[itemHashIndex];

    // Short circuit evaluation is important here
    while ((chainPtr != nullptr) && (searchKey != chainPtr->getKey())) {
        chainPtr = chainPtr->getNext();
    } // end while

    if (chainPtr == nullptr)
        throw std::exception();

    return *chainPtr;
}
