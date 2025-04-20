#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* next;
        Node* prev; // pointer to the previous node
        Node(int value) : data(value), next(NULL), prev(NULL) {};
};

class doublyLinkedList {
    private:
        int length;
        Node* head;
        Node* tail; // pointer to the last node

    public:
        // default constructor
        doublyLinkedList() : head(NULL), tail(NULL) {};

        void setLength() {
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

        int getLength() {
            return length;
        }

        void printList() {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to print" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node
            // traverse to the end of list using current Node
            while (current->next) { // if next pointer isn't NULL
                cout << current->data << " <-> "; // print current's data
                current = current->next; // traverse 
            }
            
            cout << current->data << endl; // print last node's data
            return;
        }

        void insertFirst(int value) {
            if (!head) { // if there isn't any existing list
                Node* newNode = new Node(value); 
                head = newNode; // declare newNode as head
                tail = newNode; // declare newNode as tail
                return;
            }

            Node* newNode = new Node(value); // create new node
            newNode->next = head; // point newNode's next to head
            head->prev = newNode; // point head's prev to newNode
            head = newNode; // set newNode as head
            return; 
        }

        void insertLast(int value) {
            if (!head) { // if there isn't any existing list
                Node* newNode = new Node(value); 
                head = newNode; // declare newNode as head
                tail = newNode; // declare newNode as tail
                return;
            }

            Node* newNode = new Node(value); // create new node
            tail->next = newNode; // point tail's next to newNode
            newNode->prev = tail; // point newNode's prev to tail
            tail = newNode; // set newNode as tail
            return;
        }
        
        void insertPosition(int value, int pos) {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to insert" << endl; 
                return;
            }

            /* if (pos < 1 || pos > length + 1) { // if position < 1 or position > length + 1
                cout << "Position out of range" << endl; 
                return;
            } */

            if (pos < 1) { // if position < 1
                cout << "Position out of range" << endl; 
                return;
            }

            if (pos == 1) { // if position = 1
                insertFirst(value); // call insertFirst function
                return;
            }

            /* if (pos == length + 1) { // if position = length + 1
                insertLast(value); // call insertLast function
                return;
            } */

            Node* newNode = new Node(value); // create new node
            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position
            
            while (current->next && curPos < (pos - 1)) { // traverse to the (pos - 1) using current Node
                current = current->next; // traverse
                curPos++; // increment position 
            }

            newNode->next = current->next; // point newNode's next to current's next
            newNode->prev = current; // point newNode's prev to current
            current->next = newNode; // point current's next to newNode
            current->next->prev = newNode; // point current's next's prev to newNode
            return;
        }

        void deleteFirst() {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            Node* toDelete = head; // declare toDelete Node 
            head = head->next; // change head to point to the next node
            delete toDelete; // delete the old head node
            return;
        }

        void deleteLast() {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            Node* toDelete = tail; // declare toDelete Node 
            tail = tail->prev; // change tail to point to the previous node
            tail->next = NULL; // set new tail's next pointer to NULL
            delete toDelete; // delete the old tail node
            return;
        }

        void deletePosition(int pos) {
            if (!head) { //if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            /* if (pos < 1 || pos > length) { // if position < 1 or position > length
                cout << "Position out of range" << endl; 
                return;
            } */

            if (pos < 1) { // if position < 1
                cout << "Position out of range" << endl; 
                return;
            }

            if (pos == 1) { // if position = 1
                deleteFirst(); // call deleteFirst function
                return;
            }

            /* if (pos == length) { // if position = length
                deleteLast(); // call deleteLast function
                return;
            } */

            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position
            
            while (current->next && curPos < (pos - 1)) { // traverse to the (pos - 1) using current Node
                current = current->next; // traverse
                curPos++; // increment position 
            }

            Node* toDelete = current->next; // declare toDelete Node 
            current->next = current->next->next; // change current's next to point 
            delete toDelete; 
            return;
        }

        void searchData (int value) {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to search" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position
            
            while (current) { // traverse to the end of list
                if (current->data == value) { // if current's data = value
                    cout << "Found \"" << value << "\" in the list in node " << curPos << endl; 
                    return;
                }
                current = current->next; // traverse
                curPos++; // increment position 
            }

            cout << "There isn't any \"" << value << "\" in the list" << endl;
            return;
        }

        void sortData (int asOrDes) {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to sort" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node
            Node* index = NULL; // make new Node to track index Node
            int temp; // temporary variable to swap data

            while (current) { // traverse to the end of list
                index = current->next; // set index to the next node
                while (index) { // traverse to the end of list using index Node
                    if (asOrDes == 1) { // if ascending order
                        if (current->data > index->data) { // if current's data > index's data
                            temp = current->data; // swap data between current and index
                            current->data = index->data;
                            index->data = temp;
                        }
                    } else { // if descending order
                        if (current->data < index->data) { // if current's data < index's data
                            temp = current->data; // swap data between current and index
                            current->data = index->data;
                            index->data = temp;
                        }
                    }
                    index = index->next; // traverse 
                }
                current = current->next; // traverse 
            }
            return;
        }
};