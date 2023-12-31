#include <iostream>
#include "HashTable.hpp"


/** Initialises the values of a, c and m and allocates memory space (to store m integer values) 
  * to the hash table 'buckets'
*/
HashTable::HashTable(long _a, long _c, long _m) {
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
  
}

HashTable::~HashTable() {
}

/** Hashes and inserts a number into the hash table pointed to by 'buckets' */
void HashTable::insert(int key) {

  /**************PSEUDOCODE****************/

  // Check the key is a strictly positive number (exclude 0: https://proofwiki.org/wiki/Definition:Strictly_Positive/Number#:~:text=The%20strictly%20positive%20real%20numbers,are%20strictly%20greater%20than%20zero.)
  // Print error, throw exception and crash out if not
  if (key < 1)
  {
    std::cout << "HashTable::insert - BAD KEY: key must be a strictly positive integer, and " << key << " is 0 or lower." << std::endl;
    throw;
  }

  // Get the load factor using the loadFactor function
  double loadFactor = HashTable::loadFactor();

  if (loadFactor >= 1)
  {
    // Extend the table so we can rehash everything
    HashTable::extend();
  }

  // Calculate the function f(key) = (a*k + c) mod m, store this in a variable called 'index'
  int hash = (a * key + c) % m;

  // Check the value at the 'index' of the hash table
  int index = hash;

  // If the value is not equal to -1, then we have to go to the next index:
  // Iterate over the next indices (looping around to position 0 if the current index is [m-1])
  // If the index-value is full (i.e. not -1), continue looping until you find a value which is -1
  // Once you find index which is set to -1 as the value, insert the key
  while (*(buckets + index) != -1)
  { 

    if (index == (m-1))
    { 
      index = 0;
    }
    else
    { 
      ++index;
    }
  }

  // If the value is -1, insert the key into that slot by using *(buckets + index)
  *(buckets + index) = key;
}



/** Extends and rehashes the existing hash table by a factor of 2 */
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
    HashTable::insert(*(tempHashTable + index));
    ++index;
  }
}



/** Searches for the inputted integer in the hash table, returns 'true' if found and 'false' if not*/
bool HashTable::find(int key) {

  // Apply hash function to the key
  int indexToSearch = ((a * key) + c) % m;

  // Once 'm' comparisons are made looping around the hash table (to account for the linear probing), this means the key is not in the table
  int numberAttempts = 0;

  // Do not check more than m elements, or there would be an infinite loop
  while (numberAttempts < m)
  { 
    // Return 'true' if the index to search by in the hash table stores the desired key
    if (*(buckets + indexToSearch) == key)
    {
      return true;
    }
    else
    { 
      // Loop around the hash table if index is the last element of the hash table
      if (indexToSearch == m - 1)
      {
        indexToSearch = 0;
      }
      // If not at the last index, just increment the index to search the next element in the hash table
      else
      {
        ++indexToSearch;
      }
    }

    ++numberAttempts;
  }

  return false;
}


/** Searches for the inputted integer in the hash table and returns its index in the table, returns -1 if not found */
int HashTable::findAndReturnIndex(int key){

   // Apply hash function to the key
  int indexToSearch = ((a * key) + c) % m;

  // Once 'm' comparisons are made looping around the hash table (to account for the linear probing), this means the key is not in the table
  int numberAttempts = 0;

  // Do not check more than m elements, or there would be an infinite loop
  while (numberAttempts < m)
  { 
    // Return 'true' if the index to search by in the hash table stores the desired key
    if (*(buckets + indexToSearch) == key)
    {
      return indexToSearch;
    }
    else
    { 
      // Loop around the hash table if index is the last element of the hash table
      if (indexToSearch == m - 1)
      {
        indexToSearch = 0;
      }
      // If not at the last index, just increment the index to search the next element in the hash table
      else
      {
        ++indexToSearch;
      }
    }

    ++numberAttempts;
  }

  // Return -1 if index not found
  return -1;
}


/** Removes the inputted integer from the hash table */
void HashTable::remove(int key){

  // Run findAndReturnIndex to find the index in hash table where you would like to delete the key
  int indexWhereToDelete = findAndReturnIndex(key); // Returns -1 if key not found

  if (indexWhereToDelete != -1)
  {
    *(buckets + indexWhereToDelete) = -1;
  }
}


/** Calculates the load factor: (numbers already in hash table)/(total size of hash table) */
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

  // To divide number of used-up slots by total number of slots/indices in the hash table, we need to convert them to doubles.
  double loadFactor = double(numbersStored) / double(m);

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



