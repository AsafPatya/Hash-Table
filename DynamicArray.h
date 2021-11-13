#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

//Implementing a dynamic array specific for Course
const int STARTING_SIZE_ARRAY = 101;

class DynamicArray {
      private:
        int *arr;
        int size;
        int n;
   public:

      //Constructor for the dynamic array
      DynamicArray():arr(new int[STARTING_SIZE_ARRAY]),size(STARTING_SIZE_ARRAY),n(0) {
      }

      //Copy consturctor
      DynamicArray(const DynamicArray& dynamicArray) {
         size = dynamicArray.size;
         n = dynamicArray.n;
         arr = new int[size];
         for (int i = 0;i <n ; i ++)
            arr[i] = dynamicArray.arr[i];
      }

      //Operator =
      DynamicArray& operator=(const DynamicArray& dynamicArray) {
         if(this == &dynamicArray)
            return *this;
         delete[] arr;
         size = dynamicArray.size;
         n = dynamicArray.n;
         arr = new int[size];
         for (int i = 0;i <n ; i ++)
            arr[i] = dynamicArray.arr[i];
         return *this;
      }

      //Returns number of elements in the array
      int getN(){
         return n;
      }

      //Returns the value of an element
      int getValue(int i){
         if(n<=i)
            return false;
         return arr[i];
      }
      
      //Inserts a new element into the dynamic array
      int add() {
         arr[n] = 0;
         n+=1;
         reSize();
         return n-1;
      }

      //Changes the element's value in the dynamic array, returns False if doesn't exist
      bool addToElement(int i,int value) {
         if(n<=i)
            return false;
         arr[i]+=value;
         return true;
      }


      //Checking if the dynamic array needs to be resized and resizes accordingly
      void reSize(){
            if(size<=n){
               int newSize = size*=2;
               int* newArr = new int[newSize];
               for (int i = 0; i< size; i++) {
                  newArr[i] = arr[i];
               }             
               delete[] arr;
               size = newSize;
               arr = newArr;
            }
      }

      //Destructor for the dynamic array
      ~DynamicArray() {
         delete[] arr;
      }
};

#endif