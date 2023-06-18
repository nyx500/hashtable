#pragma once

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

class HashTable {

public: 
  // Set to 0 just for now --> will be initialized to store a pointer to the Hash Table (array in C++ ) later.
  int *buckets = 0;

public:

  /** Initialize the values of a, c and m and allocates memory space (to store m integer values) 
   * to the Hash Table pointed to by the int pointer 'buckets' (which points to first int in the Hash Table)
  */
  HashTable(long, long, long);

  ~HashTable();
  
  /** Hashes and inserts a number into the hash table pointed to by 'buckets' */
  void insert(int);

  /** Extends and rehashes the existing hash table by a factor of 2 */
  void extend();

  /** Searches for the inputted integer in the hash table, returns 'true' if found and 'false' if not*/
  bool find(int);

  /** Searches for the inputted integer in the hash table and returns its index in the table, returns -1 if not found */
  int findAndReturnIndex(int);

  /** Removes the inputted integer from the hash table */
  void remove(int);
  
  /** Calculates the load factor: (numbers already in hash table)/(total size of hash table) */
  double loadFactor();

  // For testing purposes
  void printFinalHashTable();

private:
  /** Constant by which key is multiplied by*/
  long a;
  /** Constant added to a * key */
  long c;
  /** Hashing function is (a*k + c) % m --> m is the number of buckets/hash slots */
  long m;
};

#endif
