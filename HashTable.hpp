#pragma once

#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

class HashTable {

public: 
  // Will store a ptr to the hash-table/array storing 'm' buckets, initialised in the ctor.
  int *buckets = 0;

public:

  /** Initialises the values of a, c and m and allocates memory space (to store m integer values) 
   * to the hash table buckets
  */
  HashTable(long, long, long);

  ~HashTable();
  
  void insert(int);
  void extend();
  bool find(int);
  void remove(int);
  
  /** Calculates the load factor: (numbers already in hash table)/(total size of hash table) */
  double loadFactor();

  // For testing purposes
  void printFinalHashTable();

private:
  long a;
  long c;
  long m;
};

#endif
