#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    // Utility functions
    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(Node* node) {
        if(node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    Node* balance(Node* node) {
        if(!node) return node;

        updateHeight(node);
        int bf = balanceFactor(node);

        // Left heavy
        if(bf > 1) {
            if(balanceFactor(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        // Right heavy
        if(bf < -1) {
            if(balanceFactor(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    Node* insert(Node* node, int key) {
        if(!node) return new Node(key);

        if(key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);

        return balance(node);
    }

    Node* findMin(Node* node) {
        while(node && node->left)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, int key) {
        if(!node) return nullptr;

        if(key < node->key) {
            node->left = remove(node->left, key);
        } else if(key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if(!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                if(!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        if(!node) return node;

        return balance(node);
    }

    void inorder(Node* node) {
        if(node) {
            inorder(node->left);
            std::cout << node->key << " ";
            inorder(node->right);
        }
    }

    void printTree(Node* node, int space = 0, int gap = 5) {
        if(!node) return;
        
        space += gap;
        
        printTree(node->right, space);
        
        std::cout << std::endl;
        for(int i = gap; i < space; i++)
            std::cout << " ";
        std::cout << node->key << "\n";
        
        printTree(node->left, space);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    void display() {
        std::cout << "In-order traversal: ";
        inorder(root);
        std::cout << "\nTree structure:\n";
        printTree(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree avl;

    // Insert values
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    std::cout << "After insertions:\n";
    avl.display();

    // Delete a node
    avl.remove(40);
    std::cout << "\nAfter deleting 40:\n";
    avl.display();

    return 0;
}