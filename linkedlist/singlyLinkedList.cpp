#include <iostream> 
#include <string> 
using namespace std; 

class Node {
    public:
    string data;
    Node* next;
};

class singlyLinkedList {
    Node* head;

    public: 
    singlyLinkedList() : head(NULL) {}

    void insertBeginning(string data) {
        // make new Node, assign data to it, and make it head
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = head; // assign current head to "next" of newNode
        head = newNode;
    }

    void insertEnd(string data) {
        // make new Node, assign data to it
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = NULL; // assign NULL to "next" of newNode

        // if list is empty, make newNode head
        if (!head) {
            head = newNode;
            return;
        }

        // traverse to the end of the list
        Node* temp = head; 
        while (temp->next) {
            temp = temp->next; 
        }

        // assign newNode to next of last Node
        temp->next = newNode; 
    }
};