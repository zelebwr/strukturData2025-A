// singly linked list c++

#include <iostream> 
using namespace std; 

class Node {
    public: 
        int data; 
        Node* next; 
        Node(int value) : data(value), next(NULL) {}; 
};

class singlyLinkedList {
    private: 
        Node* head; 
    
    public:
        // default constructor
        singlyLinkedList() : head(NULL) {}; 

        void insertFirst(int value) {
            Node* newNode = new Node(value); 
            if (!head) { // if there isn't any existing list
                head = newNode; // declare newNode as head
                return; 
            }

            // if there is any existing list 
            newNode->next = head; // change next pointer to head
            head = newNode; // declare newNode as head
            return;
        }

        void insertLast(int value) {
            Node* newNode = new Node(value); 
            if (!head) { // if there isn't any existing list
                head = newNode; // declare newNode as head
                return;
            }
            
            // if there is any existing list 
            Node* current = head; // make new Node to track current Node 
            
            // traverse to the end of list using current Node
            while (current->next) { // if next pointer isn't NULL
                current = current->next; // traverse 
            }
            
            // set current's next pointer to point to newNode
            current->next = newNode;
            return;
        }
        
        void insertPosition(int value, int pos) {
            Node* newNode = new Node(value);
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list yet, position in list isn't available" << endl; // error message
                return;
            }

            // if there is any existing list
            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position

            // traverse to the position in list using current Node
            while (current->next && curPos <= (pos - 1)) { // if current->next isn't NULL and position less equal position
                current = current-> next;
                curPos++;
            }
            
            // check if (pos - 1) = NULL, then insertLast
            if (!current->next && curPos == (pos - 1)) {
                insertLast(value);
                return;
            }

            // if (pos - 1) isn't NULL
            newNode->next = current->next; // newNode->next points to current->next
            current->next = newNode; // current->next points newNode
            // resulted into newNode inserted after current and before current->next
            return;
        }
};