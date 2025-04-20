#include <iostream>
#include <algorithm> // For std::swap

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int length;

public:
    // Constructor
    CircularDoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    // Destructor
    ~CircularDoublyLinkedList() {
        clear();
    }

    // Insertion methods
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        
        if (!head) {
            head = tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
        length++;
    }

    void insertAtTail(int val) {
        Node* newNode = new Node(val);
        
        if (!tail) {
            head = tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
        length++;
    }

    void insertAtPosition(int val, int pos) {
        if (pos <= 1) {
            insertAtHead(val);
            return;
        }
        if (pos > length) {
            insertAtTail(val);
            return;
        }

        Node* current = head;
        for (int i = 1; i < pos - 1; ++i) {
            current = current->next;
        }

        Node* newNode = new Node(val);
        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        length++;
    }

    // Deletion methods
    void deleteAtHead() {
        if (!head) return;

        if (length == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = head;
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        length--;
    }

    void deleteAtTail() {
        if (!tail) return;

        if (length == 1) {
            delete tail;
            head = tail = nullptr;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }
        length--;
    }

    void deleteByValue(int val) {
        if (!head) return;

        Node* current = head;
        for (int i = 0; i < length; ++i) {
            if (current->data == val) {
                if (current == head) {
                    deleteAtHead();
                } else if (current == tail) {
                    deleteAtTail();
                } else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    delete current;
                    length--;
                }
                return;
            }
            current = current->next;
        }
    }

    void deleteAtPosition(int pos) {
        if (pos < 1 || pos > length) return;
        if (pos == 1) {
            deleteAtHead();
            return;
        }
        if (pos == length) {
            deleteAtTail();
            return;
        }

        Node* current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        length--;
    }

    // Search method
    bool search(int val) const {
        if (!head) return false;

        Node* current = head;
        for (int i = 0; i < length; ++i) {
            if (current->data == val) return true;
            current = current->next;
        }
        return false;
    }

    // Sort method (Bubble Sort)
    void sort(bool ascending = true) {
        if (!head || length == 1) return;

        bool swapped;
        Node* current;
        Node* last = nullptr;

        for (int i = 0; i < length - 1; ++i) {
            current = head;
            swapped = false;

            for (int j = 0; j < length - i - 1; ++j) {
                bool condition = ascending ? 
                    (current->data > current->next->data) : 
                    (current->data < current->next->data);

                if (condition) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }

            if (!swapped) break;
        }
    }

    // Utility methods
    void clear() {
        while (head) {
            deleteAtHead();
        }
    }

    void display() const {
        if (!head) {
            std::cout << "Empty List" << std::endl;
            return;
        }

        Node* current = head;
        for (int i = 0; i < length; ++i) {
            std::cout << current->data;
            if (i < length - 1) std::cout << " <-> ";
            current = current->next;
        }
        std::cout << " -> HEAD" << std::endl;
    }

    int getLength() const {
        return length;
    }
};