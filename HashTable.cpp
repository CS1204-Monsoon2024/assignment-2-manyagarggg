#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

class HashTable {
private:
    vector<int> table;
    vector<bool> filled; 
    int currentSize;
    int count;
    const double threshold = 0.8;

    int hash(int key) {
        return key % currentSize;
    }

    void resize() {
        int newSize = nextPrime(2 * currentSize);
        vector<int> oldTable = table;
        vector<bool> oldFilled = filled;

        table.assign(newSize, -1);
        filled.assign(newSize, false);
        currentSize = newSize;
        count = 0;

        for (int i = 0; i < oldTable.size(); i++) {
            if (oldFilled[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(int initialSize) {
        currentSize = nextPrime(initialSize);
        table.assign(currentSize, -1); // -1 represents an empty slot
        filled.assign(currentSize, false);
        count = 0;
    }
    void insert(int key) {
        if ((double)count / currentSize >= threshold) {
            resize();
        }
        int index = hash(key);
        int i = 0;
        while (i < currentSize) {
            int x = (index + i * i) % currentSize;
            if (table[x] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            if (!filled[x]) {
                table[x] = key;
                filled[x] = true;
                count++;
                return;
            }
            i++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    int search(int key) {
        int index = hash(key);
        int i = 0;
        while (i < currentSize) {
            int x = (index + i * i) % currentSize;
            if (filled[x] && table[x] == key) {
                return x;
            }
            if (!filled[x]) {
                return -1; 
            }

            i++;
        }

        return -1; 
    }

    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found" << endl;
        } else {
            table[index] = -1;
            filled[index] = false;
            count--;
        }
    }

    void printTable() {
        for (int i = 0; i < currentSize; i++) {
            if (filled[i]) {
                cout << table[i] << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
};


int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}


// done qed let's go 