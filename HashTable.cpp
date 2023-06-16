#include <iostream>
#include "HashTable.hpp"


/** Initialises the values of a, c and m and allocates memory space (to store m integer values) 
  * to the hash table 'buckets'
*/
HashTable::HashTable(long _a, long _c, long _m) {
  std::cout << "Creating hash table from coefficient 'a':  " << _a << " coefficient 'c': " << _c <<  " nr buckets 'm' :" << _m << std::endl;
  a = _a;
  c = _c;
  m = _m;

  /** NB:
   * The 'new' keyword returns a pointer to the object (array) created and can be 
   * used to initialize the array storing 'm' integers.
   * The pointer returned points to the element at index 0 in the array.
   * Here the pointer called 'buckets' is used to store the pointer returned from using the 'new' keyword.
   * "buckets" now stores a pointer to the **first element** in the array of m-integers.
   * Ref: https://www.programiz.com/cpp-programming/pointers-arrays
   *  The new keyword allocates memory on the heap for the specified data_type and size
   * Ref: https://www.educative.io/answers/how-to-dynamically-allocate-initialize-and-delete-arrays-in-cpp
  */
  buckets = new int[m];

  // IMPORTANT SYNTAX:
  // *buckets is equivalent to array[0], *(buckets + 1) is equivalent to array[1], and so on...
  for (int i = 0; i < m; ++i)
  {
    std::cout << "Value of *(buckets + " << i << ") is equivalent to array[" << i << "] : " << *(buckets + i) << std::endl;
    
    // Without the '*' dereferencer, (buckets + i) stores the address of the i'th location in the hash table
    std::cout << "Address in memory of bucket #" << i << ": " << (buckets + i) << std::endl;

    std::cout << std::endl;
  }

  // Initialize the values in every 'bucket' to -1,
  // This is because currently some buckets store 0 and some store nonsense-values..
  // It could be confusing when sometimes you want a genuine 0 from the input array stored 
  // in the hash table, but some cells were just set to 0 by default with the 'new' keyword.
  for (int i = 0; i < m; ++i)
  { 
    // (buckets + i) just stores the memory address of the desired element
    // Therefore, * to dereference (buckets + i) grants access to the element
    *(buckets + i) = -1;
  }

  // Print again to check that values are all -1 now
  // Values in the memory cells have all been changed to -1, but the addresses in memory are the same
  for (int i = 0; i < m; ++i)
  {
    std::cout << "Value of *(buckets + " << i << ") is equivalent to array[" << i << "] : " << *(buckets + i) << std::endl;
    std::cout << "Address in memory of bucket #" << i << ": " << (buckets + i) << std::endl;
    std::cout << std::endl;
  }
  
}

HashTable::~HashTable() {
}

void HashTable::insert(int key) {

  /**************PSEUDOCODE****************/

  // Check the key is a strictly positive number (exclude 0: https://proofwiki.org/wiki/Definition:Strictly_Positive/Number#:~:text=The%20strictly%20positive%20real%20numbers,are%20strictly%20greater%20than%20zero.)
  // Print error, throw exception and crash out if not
  if (key < 1)
  {
    std::cout << "HashTable::insert - BAD KEY: key must be a strictly positive integer, and " << key << " is 0 or lower." << std::endl;
    throw;
  }

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "CURRENT KEY: " << key << std::endl;

  // Get the load factor using the loadFactor function
  double loadFactor = HashTable::loadFactor();

  if (loadFactor >= 1)
  {
    std::cout << "LOAD FACTOR IS 1 OR GREATER!" << std::endl;

    // Extend the table so we can rehash everything
    HashTable::extend();
  }

  // Calculate the function f(key) = (a*k + c) mod m, store this in a variable called 'index'
  int hash = (a * key + c) % m;

  std::cout << "Output of (ak + c) mod m = " << hash << std::endl;

  // Check the value at the 'index' of the hash table
  int index = hash;

  // If the value is not equal to -1, then we have to go to the next index:
  // Iterate over the next indices (looping around to position 0 if the current index is [m-1])
  // If the index-value is full (i.e. not -1), continue looping until you find a value which is -1
  // Once you find index which is set to -1 as the value, insert the key
  while (*(buckets + index) != -1)
  { 
    
    std::cout << "Current index in hash table: " << index << std::endl;
    std::cout << "Current value in the hash table at " << index << " : " << *(buckets + index) << std::endl;

    if (index == (m-1))
    { 
      std::cout << "Last index in the hash table: loop around!" << std::endl;
      index = 0;
    }
    else
    { 
      std::cout << "Value at " << index << " in the hash table is not -1, so we will increment the index by 1" << std::endl;
      ++index;
    }
  }

  // If the value is -1, insert the key into that slot by using *(buckets + index)
  std::cout << "INSERTING THE KEY " << key << " AT INDEX " << index << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  *(buckets + index) = key;
}


/** Extend and rehash the existing hash table */
void HashTable::extend() {

  /** Create a new **bigger** array, which should temporarily store all the contents of the current hash-table pointed to by "buckets" */
  // 1. Initalize a new array with m * 2 elements (thus doubling the size of the current hash table)
  // 2. 'tempHashTable' points to this temporary array/hashTable, which is twice the size of the original hash table
  int* tempHashTable = new int[m * 2];  // This temporary array will be destroyed afetr exiting the function, so there is no memory leak.

  // Transfer the contents of 'buckets' to bigger temp array
  for (int i = 0; i < m; ++i)
  {
    *(tempHashTable + i) = *(buckets + i);
  }
  // Fill the remaining slots in the temp array with -1s
  for (int i = m; i < m * 2; ++i)
  {
    *(tempHashTable + i) = -1;
  }
  std::cout << "Contents of temp hash table: " << std::endl;
  for (int i = 0; i < m * 2; ++i)
  {
    std::cout << *(tempHashTable + i) << std::endl;
  }

  // Delete the current hash table, so deallocate memory from the heap which was used for the old hash table
  // Ref: https://www.educative.io/answers/how-to-dynamically-allocate-initialize-and-delete-arrays-in-cpp
  delete[] buckets;

  // Make 'buckets' point to a new, expanded hash table
  buckets = new int[m * 2];
  
  // Update 'm' to be m*2 (number of buckets)
  m = m*2;

  // Initialize buckets elems to - 1 again
  for (int i = 0; i < m; ++i)
  { 
    *(buckets + i) = -1;
  }

  // Rehash the contents of the temporary array into the new larger 'buckets' array
  int index = 0;

  while (*(tempHashTable + index) != -1)
  { 
    std::cout << "Current Index: " << index << std::endl;
    std::cout << "Inserting key : " << *(tempHashTable + index) << std::endl;

    HashTable::insert(*(tempHashTable + index));
    ++index;
  }

  std::cout << "First table rehashed: " << std::endl;
  for (int i = 0; i < m; i++)
  {
    std::cout << *(buckets + i) << ", " << std::endl;
  }

}

bool HashTable::find(int key) {
  return false;
}

void HashTable::remove(int key){
}

// Calculates the load factor: (numbers already in hash table)/(total size of hash table)
double HashTable::loadFactor() {
  
  // Calculate number of numbers already stored in the hash table
  int numbersStored = 0;

  for (int i = 0; i < m ; ++i)
  {
    if (*(buckets + i) != -1)
    {
      ++numbersStored;
    }
  }

  std:: cout << "NUMBER OF NUMBERS STORED: " << numbersStored << ", m: " << m << std::endl;

  // To divide number of used-up slots by total number of slots/indices in the hash table, we need to convert them to doubles.
  double loadFactor = double(numbersStored) / double(m);

  std::cout << "Load factor is: " << loadFactor << std::endl;

  return loadFactor;

}


// For testing purposes
void HashTable::printFinalHashTable()
{
  for (int i = 0; i < m; ++i)
  { 
    if (i != (m-1))
    {
      std::cout << *(buckets + i) << ", ";
    }
    else
    {
      std::cout << *(buckets + i) << std::endl;
    }
    
  }
}



