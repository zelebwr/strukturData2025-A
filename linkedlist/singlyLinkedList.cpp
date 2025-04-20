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
        int length;
        Node* head; 
    
    public:
        // default constructor
        singlyLinkedList() : head(NULL) {}; 

        void setLength(){
            if (!head) { // if there isn't any existing list
                cout << "There is no list yet, therefore list's length = 0" << endl;
                length = 0; // declare list's length = 0
                return;
            }
            
            Node* temp = head;
            length = 1;
            // if there is any existing list
            while (temp->next) { // traverse to the end of list
                temp = temp->next;
                length++; // increment length each interation
            }            
            return;
        }

        int getLength(){
            return length;
        }

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
                cout << "Therefore newNode is to be put at first" << endl; 
                head = newNode; 
                return;
            }

            // if there is any existing list
            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position

            // traverse to the position in list using current Node
            while (current->next && curPos <=\ (pos - 1)) { // if current->next isn't NULL and position less equal position
                current = current-> next;
                curPos++;
            }
            
            // check if Node at pos = NULL, then insertLast
            if (!current->next && curPos == (pos - 1)) {
                cout << "Since position has exceeded list's length, then it will be inserted at last position" << endl;
                insertLast(value);
                return;
            }

            // if (pos - 1) isn't NULL
            newNode->next = current->next; // newNode->next points to current->next
            current->next = newNode; // current->next points newNode
            // resulted into newNode inserted after current and before current->next
            return;
        }

        void deleteFirst(){
            if (!head) { // if there is any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            Node* toDelete = head;
            head = head->next; // move head to the next pointer
            free(toDelete); // delete toDelete node, which was the first Node in list
        }

        void deleteLast() {
            if (!head) { // if there is any existing list
                cout << "There isn't any existing list, nothing to delete" << endl;
                return; 
            }

            Node* current = head; 
            while (current->next->next) current = current->next; // traverse to the end of list

            Node* toDelete = current->next; // declare toDelete Node
            current->next = NULL;  // change pointer to NULL 
            free(toDelete);  // delete toDelete
            return;
        }

        void deletePosition(int pos) {
            if (!head) { //if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            if (pos == 1) { // if position = 1
                deleteFirst(); // call deleteFirst function
                return;
            }

            // if there is any existing list
            Node* current = head;
            int curPos = 1;
            //  traverse to the (pos - 1) using current Node
            while (current->next && curPos < (pos - 1)) {
                current = current->next;
                curPos++;
            }

            // if Node at pos = NULL
            if (!current->next && curPos == (pos - 1)) { 
                cout << "Position exceed the list's length" << endl
                     << "Therefore, nothing to be deleted" << endl;
                return;
            }

            // if Node at pos isn't NULL
            Node* toDelete = current->next; // declare toDelete Node 
            current->next = current->next->next; // change current->next to point 
            free(toDelete); 
            return;
        }

        
};