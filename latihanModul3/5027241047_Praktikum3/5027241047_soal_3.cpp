#include <iostream>
using namespace std;

class Dictionary {
private:
    struct Node {
        int key;
        int value;
        // Feel free to add more variable if needed
    };
    Node dict[100];
    int size;

public:
    Dictionary() {
        size = 0;
    }
    
    void insert(int key, int value) {
        dict[size++] = {key, value};
    }

    void update(int pos, int key, int newValue) {
        dict[pos].key = key;
        dict[pos].value = newValue;
    }

    int search(int key, int value) {
        int cur;
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (dict[i].key == key && dict[i].value == value) {
                cur = i; 
                count++;
                continue;
            }
        }
        if (count > 0) return cur; 
        else return -1;
    }

    int position(int key, int value) {
        int pos = search(key, value);
        int compare = search(key, 0); 
        if (pos < compare && compare != -1) {
            update(pos, key, 1); 
            return pos; 
        } 
        return -1;
    }
};

int main() {
    int N;
    cin >> N;

    Dictionary dict;
    
    int key;
    for (int i = 0; i < N; i++) {
        cin >> key;
        dict.insert(key, 0);
        cout << dict.position(key,1) << " ";
    }
}