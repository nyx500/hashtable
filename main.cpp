#include <iostream>
#include "HashTable.hpp"

int main()
{   
    // Initialize and define test array
    int practice_array[6] = {9, 4, 8, 2, 5, 6};

    // Creates the hash table
    HashTable ht(2, 4, 5);

    // Test insert function
    for (const int& i : practice_array)
    {
        ht.insert(i);
    }
    
    // Print out final array
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "FINAL HASH TABLE: ";
    ht.printFinalHashTable();

    // Should return false
    bool resultOfTest1 = ht.find(7);
    if (resultOfTest1)
    {
        std::cout << "Test 1: " << "7 is in the hash table." << std::endl;
    }
    else
    {
        std::cout << "Test 1: " << "7 is not in the hash table." << std::endl;
    }
  

    // Should return true
    bool resultOfTest2 = ht.find(8);
    if (resultOfTest2)
    {
        std::cout << "Test 2: " << "8 is in the hash table." << std::endl;
    }
    else
    {
        std::cout << "Test 2: " << "8 is not in the hash table." << std::endl;
    }

     // Should return true
    bool resultOfTest3 = ht.find(6);
    if (resultOfTest3)
    {
        std::cout << "Test 3: " << "6 is in the hash table." << std::endl;
    }
    else
    {
        std::cout << "Test 3: " << "6 is not in the hash table." << std::endl;
    }
    
    // Test removing 8
    ht.remove(8);

    std::cout << "Hash table with 8 deleted: " << std::endl;
    ht.printFinalHashTable();

     // Test removing 7 (not in the hash table)
    ht.remove(7);

    std::cout << "Hash table with 7 deleted: " << std::endl;
    ht.printFinalHashTable();


    // Test adding 8 back into hash table
    std::cout << "Adding 8 back in: " << std::endl;
    ht.insert(8);
    ht.printFinalHashTable();

    return 0;
 }