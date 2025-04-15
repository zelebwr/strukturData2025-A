#include <iostream>
using namespace std;

// Kelas Node merepresentasikan satu elemen dalam Circular Doubly Linked List
class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int val);
};

// Kelas CircularDoublyLinkedList mengelola operasi pada Circular Doubly Linked List
class CircularDoublyLinkedList {
private:
    Node* head;
public:
    CircularDoublyLinkedList();

    void insert(int val);

    void deleteFirst(Node* &head){ 
        if (head == NULL) {
            cout << "There is no list to be deleted" << endl;
        }

        Node* temp = head->prev;
        Node* toDelete = head; 
        temp->next = NULL; 
        head = head->next;
        head->prev = NULL; 
        free(toDelete);
        return;
    }

    void deleteEnd(Node* &head){
        if (head == NULL) {
            cout << "There is no list to be deleted" << endl; 
        }

        Node* temp = head->prev->prev;
        Node* toDelete = temp->next; 
        temp->next = NULL; 
        head->prev = NULL; 
        free(toDelete);
        temp->next = head; 
        head->prev = temp;
        return;
    }

    void deleteNode(int k){
        if (head == NULL) {
            cout << "There is no list to be deleted" << endl;
        }

        if ((k == 0 || k == 1)) {
            deleteFirst();
        }

        Node* temp = head; 
        Node* start = head->prev;
        int i = 0;
        while(i < (k-1) && temp) {
            temp = temp->next; 
            i++;
        }

        if (!temp) deleteEnd();
    };


    void display();
};

// Fungsi utama
int main() {
    CircularDoublyLinkedList list;
    // peserta tinggal melanjutkan implementasi insert, deleteNode, dan display
}