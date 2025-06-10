#include <iostream>
#include <string>
using namespace std;

struct Node {
    int key;
    int height;
    int size;   // subtree size
    Node* left;
    Node* right;

    Node(int val) {
        key = val;
        height = 1;
        size = 1;
        left = right = nullptr;
    }
};

class WBAVL {
public:
    Node* root = nullptr;

    int height(Node* n) { return n ? n->height : 0; }
    int size(Node* n) { return n ? n->size : 0; }

    void update(Node* n) {
        if (!n) return;
        n->height = 1 + max(height(n->left), height(n->right));
        n->size = 1 + size(n->left) + size(n->right);
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        update(y);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        update(x);
        update(y);
        return y;
    }

    Node* rebalance(Node* node) {
        update(node);
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        } else if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return rebalance(node);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    int rank(Node* node, int x) {
        if (!node) return 0;
        if (x <= node->key)
            return rank(node->left, x);
        else
            return size(node->left) + 1 + rank(node->right, x);
    }

    int rank(int x) {
        return rank(root, x+1);
    }

    int select(Node* node, int k) {
        if (!node) throw runtime_error("k out of range");
        int lsize = size(node->left);
        if (k < lsize)
            return select(node->left, k);
        else if (k == lsize)
            return node->key;
        else
            return select(node->right, k - lsize - 1);
    }

    int select(int k) {
        return select(root, k-1);
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << "(" << node->size << ") ";
        inorder(node->right);
    }

    void print() {
        inorder(root);
        cout << "\n";
    }
};

int main() {
    WBAVL tree;
    for (int x : {30, 20, 40, 10, 25, 35, 50, 5, 15, 22, 27, 33, 37, 45, 55})
        tree.insert(x);

    tree.print();

    string command;
    while (true) {
        cout << "Enter command (rank <val>, select <k>, exit): ";
        getline(cin, command);
        if (command == "exit") break;
        if (command.substr(0, 4) == "rank") {
            int val = stoi(command.substr(5));
            cout << "Rank of " << val << ": " << tree.rank(val) << "\n";
        } else if (command.substr(0, 6) == "select") {
            int k = stoi(command.substr(7));
            try {
                cout << k << "-th smallest: " << tree.select(k) << "\n";
            } catch (exception& e) {
                cout << e.what() << "\n";
            }
        } else {
            cout << "Invalid command. Try 'rank <val>', 'select <k>', or 'exit'.\n";
        }
    }

    return 0;
}
