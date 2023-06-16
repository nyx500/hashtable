#include <iostream>
#include "HashTable.hpp"

int main()
{   
    // Initialize and define test array
    int practice_array[5] = {9, 4, 8, 2, 5};

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
    ht.printFinalHashTable();

    return 0;
 }