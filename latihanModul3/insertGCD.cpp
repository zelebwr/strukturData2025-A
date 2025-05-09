#include <iostream>
using namespace std;

class Node {
    public: 
        int data;
        bool didGCD;
        Node* next;
        Node(int data, bool inserted = 0) :  next(nullptr), data(data), didGCD(inserted) {};
};

class singlyLinkedList {
    Node* head; 
    size_t size;

    public: 
        singlyLinkedList() : head(NULL) {};

        int gcdEuclidean(int a, int b){
            if (a == 0) return b; 
            if (b == 0) return a;
        }

        void insertFirst(int data, bool inserted = 0){
            Node* newNode = new Node(data, inserted);
            if(!head) head = newNode; 
            else {
                newNode->next = head; 
                head = newNode;
            }
            size++;
        }

        void insertLast(int data, bool inserted = 0){
            Node* newNode = new Node(data, inserted);
            if(!head) head;
            else {
                Node* temp = head; 
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            size++;
        }

        void insertPosition(size_t index, int data, bool inserted) {
            Node* newNode = new Node(data, inserted);
            if (!head) {
                cout << "There\'s no list yet, please insert list first" << endl;
                return;
            }
            if(index >= size) insertLast(data); 
            else if (index <= size) insertFirst(data);
            else {
                Node* temp = head; 
                size_t pos;
                while (temp->next && pos < (index-1)) temp = temp->next;
                if (!temp) cout << "Loop has exceeded list" << endl; 
                size_t value 
            }
        }
};

int main() {
    
}