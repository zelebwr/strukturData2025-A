#include <iostream>
#include <string>
#include <fstream>
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
        for (int i = 0; i < bucketCount; i++) {
            Node* current = buckets[i];
            // Traverse the linked list and delete each node
            while (current) {
                Node* toDelete = current; // putting current Node in another temporary variable
                current = current->next; // move current Node to the next node
                delete toDelete; // Free the node memory
            }
        }
        delete[] buckets; // Free the memory allocated for buckets
    }

    unsigned int hashFunction(const string& value) {
        unsigned int hash = 0;
        for (char c : value) {
            hash = (hash + c) % bucketCount; // Simple hash function
        }
        return hash;
    }

    bool contains(const string& value) {
        unsigned int index = hashFunction(value);
        Node* current = buckets[index];
        // traverse the linked list at the index
        while (current) {
            if (current->data == value) {
                return true; // Found
            }
            current = current->next;
        }
        return false; // Not found
    }

    // Function to add a value in the beginning of the bucket of the hash set
    void add(const string& value) {
        // check if the value already exists to avoid duplicates
        if (contains(value)) {
            cout << "Value '" << value << "' already exists." << endl;
            return; // Value already exists, do not add again
        }

        // calculate the index for the hash table
        unsigned int index = hashFunction(value);

        // Create a new node and add it to the front of the list
        Node* newNode = new Node();
        newNode->data = value; // Assign the value to the new node
        newNode->next = buckets[index]; // Point to the current head of the list
        buckets[index] = newNode; // Update the head of the list to the new node
    }

    void remove(const string& value) {
        // check if the value exists before trying to remove it
        if (!contains(value)) {
            cout << "Value '" << value << "' not found." << endl;
            return; // Value not found, do not remove
        }

        unsigned int index = hashFunction(value);
        Node** current = &buckets[index];
        
        while (*current) {
            if ((*current)->data == value) {
                Node* toDelete = *current;
                *current = (*current)->next;
                delete toDelete; // Free the node memory
                return; // Value removed
            }
            current = &((*current)->next);
        }
    }

    void print() {
        for (size_t i = 0; i < bucketCount; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = buckets[i];
            while (current) {
                cout << current->data << " -> ";
                current = current->next;
            }
            cout << "NULL" << endl;
        }
    }
};

int main() {
    // local variables
    class skylineSet; 
    ifstream iFile("./ind_500_2_product.csv");
        // check if the file opened successfully
        if (!iFile) { 
            cout << "Error opening file" << endl;
            return 1;
        }
    string line = "";

    getline(iFile, line);
    getline(iFile, line);
    cout << line << endl;
}