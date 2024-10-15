#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int count;
    float loadFactor;
    
    // Helper function to find the next prime number for resizing
    int nextPrime(int n) {
        while (true) {
            if (isPrime(n)) return n;
            n++;
        }
    }

    // Check if a number is prime
    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Hash function: key mod table size
    int hash(int key) {
        return key % size;
    }

    // Function to rehash the table when resizing
    void rehash() {
        int oldSize = size;
        std::vector<int> oldTable = table;
        size = nextPrime(size * 2);
        table.assign(size, -1); // Reset the table to new size filled with -1
        count = 0;
        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor to initialize the table
    HashTable(int initialSize = 5) {
        size = nextPrime(initialSize);
        table.resize(size, -1);  // Initialize table with -1 (representing empty slots)
        count = 0;
        loadFactor = 0.8;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (count >= size * loadFactor) {
            rehash();
        }
        
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                std::cout << "Duplicate key insertion is not allowed" << std::endl;
                return;
            }
            i++;
            if (i > (size + 1) / 2) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
        }
        
        table[(index + i * i) % size] = key;
        count++;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                table[(index + i * i) % size] = -1;
                count--;
                return;
            }
            i++;
            if (i > (size + 1) / 2) {
                std::cout << "Element not found" << std::endl;
                return;
            }
        }
        std::cout << "Element not found" << std::endl;
    }

    // Search for a key in the hash table
    int search(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i * i) % size] != -1) {
            if (table[(index + i * i) % size] == key) {
                return (index + i * i) % size;
            }
            i++;
            if (i > (size + 1) / 2) {
                return -1; // Key not found
            }
        }
        return -1; // Key not found
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    HashTable ht(5);
    ht.insert(1);
    ht.insert(4);
    ht.insert(7);
    ht.printTable();
    ht.remove(4);
    ht.printTable();
    ht.insert(12);
    ht.printTable();
    return 0;
}
