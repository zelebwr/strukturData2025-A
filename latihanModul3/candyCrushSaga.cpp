#include <iostream>
using namespace std; 

class Stack {
    private:
        // Node structure
        struct StackNode {
            int data;
            StackNode *next;
            StackNode(int value) : data(value), next(nullptr) {}
        };

        StackNode *_top;
        unsigned _size;

    public:
        // Constructor
        Stack() {
            _top = nullptr;
            _size = 0;
        }

        // Destructor
        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }
    
    bool isEmpty() {
        return (_top == nullptr);
    }

    void push(int value) {
        StackNode *newNode = new StackNode(value);
        if (newNode) {
            _size++;
            if (isEmpty()) newNode->next = nullptr;
            else newNode->next = _top;
            _top = newNode;
        }
    }

    void pop() {
        if (!isEmpty()) {
            StackNode *temp = _top;
            _top = _top->next;
            delete temp;
            _size--;
        }
    }

    int top() {
        if (!isEmpty())
            return _top->data;
        else {
            // cout << "kosong" << endl;
            return -100;
        }
    }

    unsigned size() {
        return _size;
    }
};

int main () {
    Stack s; 

    int n; 
    cin >> n; 
    
    int value, high, compare;
    bool check = true;
    for (int i = 1 ; i <= n; i++) {
        cin >> value; 
        s.push(value);
        if (i != 1) {
            check = true;
            // cout << "masuk" << endl;
            while (check) {
                // cout << "masuk check" << endl;
                high = s.top();
                // cout << "top1" << endl;
                s.pop();
                // cout << "pop1" << endl;
                for (int i = 1; i < high; i++) {
                    if (!(s.top())) {
                        // cout << "top kosong" << endl; 
                        for (int j = 0; j < i; j++) {
                            s.push(high); 
                            // cout << "push" << i << endl; 
                        }
                        check = false;
                        // cout << "keluar check" << endl;
                        break;
                    }
                    compare = s.top();
                    // cout << "top2" << endl;
                    if (compare == high) {
                        s.pop();
                        // cout << "pop2" << endl;
                    } else {
                        for (int j = 0; j < i; j++) {
                            s.push(high); 
                            // cout << "push" << i << endl; 
                        }
                        check = false;
                        // cout << "keluar check" << endl;
                        break;
                    }
                }
                check = false;
                // cout << "keluar check" << endl;
            }
            // cout << "keluar" << endl;
        }
        cout << s.size() << endl;
    }
    return 0;
}