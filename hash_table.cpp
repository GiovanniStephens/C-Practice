/* This is meant to be a simple hash table
 * example to practice C++. 
 *
 * Author:  Giovanni Stephens
 * Date:    07/07/2022
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

#define CAPACITY 5

class Hash {
    int BUCKETS;
    int size;
    vector<string> *table;
    int hash(string key);
    int hash2(string key);

    public:
        Hash();
        ~Hash();
        void insert(string key);
        bool search(string key);
        void remove(string key);
        void print();
};

int Hash::hash(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    return hash % BUCKETS;
}

int Hash::hash2(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += key[i] * pow(i, 2);
    }
    return hash % BUCKETS;
}

Hash::Hash() {
    BUCKETS = CAPACITY;
    size = 0;
    table = new vector<string>[BUCKETS];
}

Hash::~Hash() {
    delete[] table;
}

void Hash::insert(string key) {
    int index = hash(key);
    if (table[index].size() == 0) {
        table[index].push_back(key);
        size++;
    } else {
        int index2 = hash2(key);
        if (table[index2].size() == 0) {
            table[index2].push_back(key);
            size++;
        } else {
            cout << "Hash table is full" << endl;
        }
    }
}

void Hash::remove(string key) {
    int index = hash(key);
    if (table[index].size() == 0) {
        cout << "Error: Key not found" << endl;
    } else {
        int index2 = hash2(key);
        if (table[index2].size() == 0) {
            cout << "Error: Key not found" << endl;
        } else {
            table[index].erase(table[index].begin());
            table[index2].erase(table[index2].begin());
            size--;
        }
    }
}

bool Hash::search(string key) {
    int index = hash(key);
    if (table[index].size() == 0) {
        return false;
    } else {
        int index2 = hash2(key);
        if (table[index2].size() == 0) {
            return false;
        } else {
            return true;
        }
    }
}

void Hash::print() {
    for (int i = 0; i < BUCKETS; i++) {
        cout << "Bucket " << i << ": ";
        for (int j = 0; j < table[i].size(); j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Add something to the hash table
    Hash hash;
    hash.insert("Hello");
    hash.insert("World");
    hash.insert("!");

    // Print the hash table
    hash.print();

    // Search for something in the hash table
    cout << "Searching for \"Hello\": " << hash.search("Hello") << endl;
    cout << "Searching for \"World\": " << hash.search("World") << endl;

    // Remove something from the hash table
    hash.remove("Hello");
    hash.remove("World");

    // Search for something in the hash table
    cout << "Searching for \"Hello\": " << hash.search("Hello") << endl;

    // Print the hash table
    hash.print();
}