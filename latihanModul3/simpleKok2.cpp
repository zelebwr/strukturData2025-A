#include <iostream>
using namespace std;

class LinkedListNode {
public:
    int key;
    int value;
    LinkedListNode* next;
    LinkedListNode(int k, int v) : key(k), value(v), next(nullptr) {}
};

class LinkedList {
private:
    LinkedListNode* head;
public:
    LinkedList() : head(nullptr) {}
    
    ~LinkedList() {
        LinkedListNode* current = head;
        while (current != nullptr) {
            LinkedListNode* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void append(int key, int value) {
        LinkedListNode* current = head;
        // Update existing key if found
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }
        // Add new node at the front
        LinkedListNode* newNode = new LinkedListNode(key, value);
        newNode->next = head;
        head = newNode;
    }
    
    int search(int key) {
        LinkedListNode* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return -1;
    }
};

class HashTable {
private:
    static const int TABLE_SIZE = 100003;
    LinkedList* table;
    
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        table = new LinkedList[TABLE_SIZE];
    }
    
    ~HashTable() {
        delete[] table;
    }
    
    void insert(int key, int value) {
        int index = hash(key);
        table[index].append(key, value);
    }
    
    int find(int key) {
        int index = hash(key);
        return table[index].search(key);
    }
};

int main() {
    int n, x;
    cin >> n >> x;
    int* arr = new int[n];
    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    HashTable ht;
    
    for (int i = 0; i < n; ++i) {
        int current = arr[i];
        int complement = x - current;
        int foundIndex = ht.find(complement);
        
        if (foundIndex != -1) {
            cout << foundIndex << " " << (i + 1) << endl;
            delete[] arr;
            return 0;
        }
        ht.insert(current, i + 1);
    }
    
    cout << "IMPOSSIBLE" << endl;
    delete[] arr;
    return 0;
}