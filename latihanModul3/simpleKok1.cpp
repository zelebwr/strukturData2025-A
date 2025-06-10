#include <iostream>
using namespace std; 

// Struktur Single Linked List
class SListNode {
public:
    long long data;
    SListNode* next;
    
    SListNode(long long value) {
        data = value;
        next = nullptr;
    }
};


class SinglyList {
private:
    SListNode* head;
    unsigned size;

public:
    SinglyList() {
        head = nullptr;
        size = 0;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void pushFront(long long value) {
        SListNode* newNode = new SListNode(value);
        if (isEmpty()) newNode->next = nullptr;
        else newNode->next = head;
        head = newNode;
        size++;
    }

    void pushBack(long long value) {
        SListNode* newNode = new SListNode(value);
        if (isEmpty()) {
            head = newNode;
        } else {
            SListNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    void popFront() {
        if (!isEmpty()) {
            SListNode* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    void popBack() {
        if (!isEmpty()) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
            } else {
                SListNode* temp = head;
                while (temp->next->next != nullptr) {
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
            }
            size--;
        }
    }

    void insertAt(long long index, long long value) {
        if (isEmpty() || index >= size) {
            pushBack(value);
            return;
        } else if (index == 0) {
            pushFront(value);
            return;
        }

        SListNode* newNode = new SListNode(value);
        SListNode* temp = head;
        for (long long i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    void removeAt(long long index) {
        if (!isEmpty()) {
            /* Kasus apabila posisinya melebihi batas */
            if (index >= size) {
                popBack();
                return;
            } else if (index == 0) {
                popFront();
                return;
            }

            SListNode* temp = head;
            for (long long i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            SListNode* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            size--;
        }
    }

    void remove(long long value) {
        if (!isEmpty()) {
            if (head->data == value) {
                popFront();
                return;
            }
            SListNode* temp = head;
            SListNode* prev = nullptr;
            while (temp != nullptr && temp->data != value) {
                prev = temp;
                temp = temp->next;
            }
            if (temp == nullptr) return;
            prev->next = temp->next;
            delete temp;
            size--;
        }
    }

    long long front() {
        return isEmpty() ? exit(-1), 0 : head->data;
    }

    long long back() {
        if (isEmpty()) exit(-1);
        SListNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    long long getAt(long long index) {
        if (isEmpty() || index >= size) exit(-1);
        SListNode* temp = head;
        for (long long i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    unsigned getSize() {
        return size;
    }

    SListNode* getHead(){
        if (head) return head;
            else {
                cout << "there's no head";
                return 0;
            }
    }
    
};

int main() {
    SinglyList sl;

    long long n, x, value; 
    cin >> n >> x; 

    for (long long i = 0 ; i < n; i ++) {
        cin >> value; 
        sl.pushBack(value);    
    }

    long long pos1 = 1; 
    long long pos2 = 1;

    SListNode* temp1 = sl.getHead();
    SListNode* temp2;
    
    while(temp1) {
        pos2 = 1;
        temp2 = sl.getHead(); 
        while(temp2) {
            if ((temp1->data + temp2->data) == x) {
                cout << pos1 << " " << pos2;
                return 0;
            }
            else {
                temp2 = temp2->next;
                pos2++;
            }
        }
        temp1 = temp1->next; 
        pos1++;
    }

    cout << "IMPOSSIBLE";

    return 0;
}