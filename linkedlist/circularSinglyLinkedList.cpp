#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* next;
        Node(int value) : data(value), next(NULL), prev(NULL) {};
};

class circularSinglyLinkedList {
    private:
        int length;
        Node* head; 
    
    public:
        // default constructor
        circularSinglyLinkedList() : head(NULL) {}; 

        void setLength(){
            if (!head) { // if there isn't any existing list
                cout << "There is no list yet, therefore list's length = 0" << endl;
                length = 0; // declare list's length = 0
                return;
            }
            
            Node* temp = head;
            length = 1;
            // if there is any existing list
            while (temp->next != head) { // traverse to the end of list
                temp = temp->next;
                length++; // increment length each interation
            }            
            return;
        }

        int getLength(){
            return length;
        }

        void printList() {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to print" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node
            // traverse to the end of list using current Node
            while (current->next != head) { // if next pointer isn't NULL
                cout << current->data << " -> "; // print current's data
                current = current->next; // traverse 
            }
            
            cout << current->data << endl; // print last node's data
            return;
        }

        void insertFirst(int value) {
            Node* newNode = new Node(value); 
            if (!head) { // if there isn't any existing list
                head = newNode; // set head to newNode
                head->next = head; // set next pointer to point to itself
                return;
            }
            
            Node* current = head; // make new Node to track current Node
            while (current->next != head) { // traverse to the end of list using current Node
                current = current->next; // traverse 
            }
            
            current->next = newNode; // set last node's next pointer to newNode
            newNode->next = head; // set newNode's next pointer to head
            head = newNode; // set head to newNode
            return;
        }

        void insertLast(int value) {
            Node* newNode = new Node(value); 
            if (!head) { // if there isn't any existing list
                head = newNode; // set head to newNode
                head->next = head; // set next pointer to point to itself
                return;
            }
            
            Node* current = head; // make new Node to track current Node
            while (current->next != head) { // traverse to the end of list using current Node
                current = current->next; // traverse 
            }
            
            current->next = newNode; // set last node's next pointer to newNode
            newNode->next = head; // set newNode's next pointer to head
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
            
            while (current->next != head && curPos < (pos - 1)) { // traverse to the (pos - 1) using current Node
                current = current->next; // traverse 
                curPos++; // increment position 
            }

            if (current->next == head && curPos == (pos - 1)) { // if Node at pos = NULL
                cout << "Position exceed the list's length" << endl
                     << "Therefore, nothing to be inserted" << endl;
                return;
            }

            // if Node at pos isn't NULL
            newNode->next = current->next; // point newNode's next to current's next
            current->next = newNode; // point current's next to newNode
            return;
        }

        void deleteFirst(){
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            if (head->next == head) { // if there is only one node in the list
                delete head; // delete head node
                head = NULL; // set head to NULL
                return;
            }

            Node* current = head; // make new Node to track current Node
            while (current->next != head) { // traverse to the end of list using current Node
                current = current->next; // traverse 
            }
            
            current->next = head->next; // set last node's next pointer to point to second node
            delete head; // delete head node
            head = current->next; // set head to second node
            return;
        }

        void deleteLast() {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to delete" << endl; 
                return;
            }

            if (head->next == head) { // if there is only one node in the list
                delete head; // delete head node
                head = NULL; // set head to NULL
                return;
            }

            Node* current = head; // make new Node to track current Node
            while (current->next->next != head) { // traverse to the end of list using current Node
                current = current->next; // traverse 
            }
            
            delete current->next; // delete last node
            current->next = head; // set last node's next pointer to point to head
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
            
            while (current->next != head && curPos < (pos - 1)) { // traverse to the (pos - 1) using current Node
                current = current->next; // traverse 
                curPos++; // increment position 
            }

            if (current->next == head && curPos == (pos - 1)) { // if Node at pos = NULL
                cout << "Position exceed the list's length" << endl
                     << "Therefore, nothing to be deleted" << endl;
                return;
            }

            // if Node at pos isn't NULL
            Node* toDelete = current->next; // declare toDelete Node 
            current->next = current->next->next; // change current's next to point 
            delete toDelete; 
            return;
        }

        void searchData(int value) {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to search" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node
            int curPos = 1; // current position to track position
             
            do {
                if (current->data == value) {
                    cout << "Found \"" << value << "\" at position " << curPos << endl;
                    return;
                }
                current = current->next;
                curPos++;
            } while (current != head);
            
            cout << "Value not found in the list" << endl; // if value not found in the list
            return;
        }

        void sortData(int asOrDes) {
            if (!head) { // if there isn't any existing list
                cout << "There isn't any existing list, nothing to sort" << endl; 
                return;
            }

            Node* current = head; // make new Node to track current Node

            bool swapped; 

            do {
                swapped = false; // set swapped to false
                current = head; // set current to head
                
                while (current->next != head) { // traverse to the end of list using current Node
                    if (current->data > current->next->data && asOrDes == 1) { // if current's data > next's data and asOrDes = 1 (ascending)
                        int temp = current->data; // swap data
                        current->data = current->next->data;
                        current->next->data = temp;
                        swapped = true; // set swapped to true
                    } else if (current->data < current->next->data && asOrDes == 2) { // if current's data < next's data and asOrDes = 2 (descending)
                        int temp = current->data; // swap data
                        current->data = current->next->data;
                        current->next->data = temp;
                        swapped = true; // set swapped to true
                    }
                    current = current->next; // traverse 
                }
            } while (swapped); // repeat until no swaps are made

            /* Node* last = head;
            do {
                Node* current = head;
                do {
                    // Compare and swap
                    current = current->next;
                } while (current->next != last);
                last = last->next;
            } while (last != head); */
            return;
        }
};