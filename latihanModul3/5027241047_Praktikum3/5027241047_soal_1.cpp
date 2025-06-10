#include <iostream>
#include <string>
using namespace std;

class Stack {
    private:
        // Node structure
        struct StackNode {
            char data;
            StackNode *next;
            StackNode(char value) : data(value), next(nullptr) {}
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

    void push(char value) {
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

    char top() {
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

Stack s, temp; 

int isBalanced(string expr, int count){
        // cout << "masuk" << endl;
        int counting = count;

        for (char ch : expr) {
            s.push(ch);
        }

        while (!s.isEmpty()) {
            char compare = s.top();
            char compare2;
            s.pop();
            if (compare == ')'){
                // cout << "masuk ()" << endl;
                while(!s.isEmpty()){
                    compare2 = s.top();
                    s.pop();
                    if(compare2 == '(') {
                        // cout << "masuk count" << endl;
                        counting++;
                    } else {
                        temp.push(compare2);
                    }
                }
                while (!temp.isEmpty()) {
                    compare2=temp.top(); 
                    temp.pop();
                    s.push(compare2);
                }
            } else
            if (compare == '}'){
                // cout << "masuk {}" << endl;
                while(!s.isEmpty()){
                    compare2 = s.top();
                    s.pop();
                    if(compare2 == '{') {
                        // cout << "masuk count" << endl;
                        counting++;
                    } else {
                        temp.push(compare2);
                    }
                }
                while (!temp.isEmpty()) {
                    compare2=temp.top(); 
                    temp.pop();
                    s.push(compare2);
                }
            } else 
            if (compare == ']'){
                // cout << "masuk []" << endl;
                while(!s.isEmpty()){
                    compare2 = s.top();
                    s.pop();
                    if(compare2 == '[') {
                        // cout << "masuk count" << endl;
                        counting++;
                    } else {
                        temp.push(compare2);
                    }
                }
                while (!temp.isEmpty()) {
                    compare2=temp.top(); 
                    temp.pop();
                    s.push(compare2);
                }
            }
            if (compare == '(' || compare == '[' || compare == '{' ) return false;
        }
        if (s.isEmpty()) return counting;
        else return -1;
    }

int main () {

    string str;
    cin >> str;

    int count = 0;
    count = isBalanced(str, count); 

    if (count > 0)
        cout << count << endl;
    else
        cout << "LUPA NUTUP" << endl;

    return 0;
}