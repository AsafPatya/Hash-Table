#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "list.h"

const int STARTING_SIZE_HASH = 101;

template <class T>
class HashTable {
      private:
         class HashTableCell {
            public:
               int key;
               T value;
               HashTableCell(int key, T value):key(key),value(value){}
               HashTableCell():key(0),value(){}
        };

        class CompareCell{
        public:
	    bool operator()(HashTableCell c1,HashTableCell c2){
            return c1.key==c2.key;
        }
        bool operator()(int key,HashTableCell c){
            return key==c.key;
        }
        bool operator()(HashTableCell c,int key){
            return c.key==key;
        }
      };

        LinkedList<HashTableCell>* table;
        int size;
        int n;
   public:
      //Constructor for hash-table
      HashTable():table(new LinkedList<HashTableCell>[STARTING_SIZE_HASH]),size(STARTING_SIZE_HASH),n(0) {}

      //Returns the hash function on the key
      int hashFunc(int key) {
         return key % size;
      }

      //Inserts a new element into the hash-table, if exists returns false
      bool insert(int key, T value) {
         int index = hashFunc(key);
         if(table[index].findNode(key,CompareCell())!=NULL)
            return false;
         table[index].insertNext(HashTableCell (key,value));
         n++;
         reSize();
         return true;
      }

      //Finds an element in hash-table, returns an empty new one if doesnt exist
      T findKey(int key) {
         int index = hashFunc(key);
         if(table[index].findNode(key,CompareCell())==NULL)
            return T();
         return table[index].findNode(key,CompareCell())->info.value;
      }

      //Finds an element and returns the list node of it
      typename LinkedList<HashTableCell>::Node* findNodeKey(int key){
         int index = hashFunc(key);
         if(table[index].findNode(key,CompareCell())==NULL)
            return NULL;
         return table[index].findNode(key,CompareCell());
      }

      //Removes an element from the hash-table, if the element isn't found returns false
      bool remove(int key) {
         int index = hashFunc(key);
         if(table[index].findNode(key,CompareCell())==NULL)
            return false;
         table[index].deleteNode(key,CompareCell());
         n--;
         reSize();
         return true;
      }

      //Checking if the hash-table needs to be resized and resizes accordingly
      void reSize(){
         if(size>STARTING_SIZE_HASH||n>=size){
            if(size<=n||size>=n*4){
               int newSize;
               if(size<=n)
                  newSize = size*2;
               else
                  newSize = size/2;
               LinkedList<HashTableCell>* newTable =new LinkedList<HashTableCell>[newSize];
               for (int i = 0; i< size; i++) {
                  for(typename LinkedList<HashTableCell>::Node* it = table[i].first;it!=NULL;it=it->right){
                     int index = it->info.key % newSize;
                     //table[index].insertNext(HashTableCell());
                     newTable[index].insertNext(it->info);
                  }
               }             
               delete[] table;
               size = newSize;
               table = newTable;
            }
         }
      }

      //Destructor for the hash-table
      ~HashTable() {
         delete[] table;
      }
};

#endif