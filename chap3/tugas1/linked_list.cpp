#include <iostream>
using namespace std;

// node class
class Node {
    public:
        int data;
        Node* next;
        Node* prev;
    
        Node(int data) {
            this->data = data;
            this->next = NULL;
            this->prev = NULL;
        }
};

// linked list class
class LinkedList {
    private:
        Node* head;
    
    public:
    // Default constructor
    LinkedList() {
        head = NULL;
    }

    // Function to insert a node at the start of the
    // linked list
    void insertAtHead(int data) {

        // Create the new Node
        Node *newNode = new Node(data);

        // Assign to head of the list is empty
        if (head == NULL) {
            head = newNode;
            return;
        }

        // Insert the newly created linked list at the head
        newNode->next = this->head;
        this->head = newNode;
    }

    // Function to print the linked list.
    void print() {
        Node *temp = head;

        // Check for empty list
        if (head == NULL) {
            cout << "List empty" << endl;
            return;
        }

        // Traverse the list
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
};


