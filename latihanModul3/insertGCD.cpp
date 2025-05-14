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
        singlyLinkedList() : head(nullptr), size(0) {};

        int gcd(int a, int b) {
            // Find Minimum of a and b
            int res = min(a, b);

            // Testing divisiblity with all numbers starting from
            // min(a, b) to 1

            while (res > 1) {
                // If any number divide both a and b, so we
                // got the answer
                if (a % res == 0 && b % res == 0)
                    break;
                res--;
            }
            return res;
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
            if(!head) head = newNode;
            else {
                Node* temp = head; 
                while (temp->next) temp = temp->next;
                temp->next = newNode;
            }
            size++;
        }

        void insertPosition(int index, int data, bool inserted) {
            Node* newNode = new Node(data, inserted);
            if (!head) {
                cout << "There\'s no list yet, please insert list first" << endl;
                return;
            }
            // if(index >= size) insertLast(data); 
            // else if (index <= size) insertFirst(data);
            // else {
                Node* temp = head; 
                int pos = 1;
                while (temp->next && pos < (index-1)) {
                    temp = temp->next;
                    pos++;
                }
                if (!temp) cout << "Loop has exceeded list" << endl;
                
                // cout << temp->data << endl;
                // cout << temp->next->data << endl;

                newNode->data = gcd(temp->data, temp->next->data);

                // cout << "try this " << newNode->data << endl;

                newNode->next = temp->next; 
                temp->next = newNode;
            // }
            size++;
        }

        void printList() {
            Node* temp = head;
            while (temp){
                cout << temp->data << " "; 
                temp = temp->next;
            }
        }
};

int main() {
    singlyLinkedList ll;

    int amount; 
    cin >> amount; 

    int value;
    for (int i = 1 ; i <= amount; i++) {
        cin >> value; 
        ll.insertLast(value);
    }

    // ll.printList();
    // cout << endl;

    for (int i = 1 ; i <= ((amount*2)-1); i++){
        // cout << "i = " << i << endl; 
        if (i % 2 == 0) ll.insertPosition(i,100,1);
    }

    // cout << "Test" << endl;
    ll.printList();
    // cout << endl;
    
    return 0;
}