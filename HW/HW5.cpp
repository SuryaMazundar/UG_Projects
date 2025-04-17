#include <iostream>
#include <vector>
using namespace std;

// Node structure for chaining
struct Node {
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};

// Hash Table with Separate Chaining
class HashTableChaining {
private:
    int size;
    vector<Node*> table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTableChaining(int sz = 10) : size(sz), table(sz, nullptr) {}

    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);
        newNode->next = table[index]; // Insert at head
        table[index] = newNode;
    }

    void display() {
        cout << "\nHash Table with Chaining:\n";
        for (int i = 0; i < size; i++) {
            cout << i << " : ";
            Node* current = table[i];
            while (current) {
                cout << current->key << (current->next ? ", " : "");
                current = current->next;
            }
            cout << (table[i] ? "" : "Empty") << endl;
        }
    }
};

// Hash Table with Quadratic Probing
class HashTableQuadratic {
private:
    int size;
    vector<int> table;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTableQuadratic(int sz = 23) : size(sz), table(sz, -1) {}

    void insert(int key) {
        int index = hashFunction(key);
        int i = 0;
        vector<int> probedIndices;

        while (table[(index + i * i) % size] != -1) {
            probedIndices.push_back((index + i * i) % size);
            i++;
        }

        int finalIndex = (index + i * i) % size;
        table[finalIndex] = key;
        probedIndices.push_back(finalIndex);

        // Display probing sequence
        cout << key << " : ";
        for (size_t j = 0; j < probedIndices.size(); j++) {
            cout << probedIndices[j] << (j < probedIndices.size() - 1 ? ", " : "");
        }
        cout << endl;
    }

    void display() {
        cout << "\nHash Table with Quadratic Probing:\n";
        for (int i = 0; i < size; i++) {
            cout << i << " : " << (table[i] != -1 ? to_string(table[i]) : "Empty") << endl;
        }
    }
};

int main() {
    vector<int> keys = {12, 44, 13, 67, 23, 90, 11, 25, 21, 45};

    // Problem 1: Hash Table with Chaining
    HashTableChaining hashTableChaining;
    for (int key : keys) {
        hashTableChaining.insert(key);
    }
    hashTableChaining.display();

    // Problem 2: Hash Table with Quadratic Probing
    HashTableQuadratic hashTableQuadratic;
    cout << "\nQuadratic Probing Insertion Steps:\n";
    for (int key : keys) {
        hashTableQuadratic.insert(key);
    }
    hashTableQuadratic.display();

    return 0;
}

