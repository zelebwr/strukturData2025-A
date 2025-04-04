#include <iostream>
#include <string>
using namespace std;

class Node {
    public:
    string data;
    Node* next;
};

class hashSet {
    Node** buckets; // Pointer to an array of linked lists (buckets)
    int bucketCount;
    
    public: 
    hashSet(int datasetSize) : bucketCount(int(datasetSize / 0.7)) {
        // initialize the amount of buckets there is
        buckets = new Node*[bucketCount];
        
        // initialize each bucket to NULL
        for (int i = 0; i < bucketCount; i++) {
            buckets[i] = NULL;
        }
    }
    
    ~hashSet() {
        delete[] buckets; // Free the memory allocated for buckets
    }

    unsigned int hashFunction(const string& value) {
        unsigned int hash = 0;
        for (char c : value) {
            hash = (hash + c) % 10; // Simple hash function
        }
        return hash;
    }

    void add(const string& value) {
        unsigned int index = hashFunction(value);
        
        // Check if the value already exists to avoid duplicates
        Node* current = buckets[index];
        while (current != NULL) {
            if (current->data == value) {
                return; // Value already exists, do not add
            }
            current = current->next;
        }


        // Create a new node and add it to the front of the list
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = buckets[index];
        buckets[index] = newNode;
    }

    bool contains(const string& value) {
        unsigned int index = hashFunction(value);
        Node* current = buckets[index];
        while (current != NULL) {
            if (current->data == value) {
                return true; // Found
            }
            current = current->next;
        }
        return false; // Not found
    }

    void remove(const string& value) {
        unsigned int index = hashFunction(value);
        Node** current = &buckets[index];
        
        while (*current != NULL) {
            if ((*current)->data == value) {
                Node* toDelete = *current;
                *current = (*current)->next;
                delete toDelete; // Free the node memory
                return; // Value removed
            }
            current = &((*current)->next);
        }
    }
};

int main() {
    
}