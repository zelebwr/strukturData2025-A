#include <iostream> 
#include <algorithm> 
using namespace std; 

class Node {
    public:
        int data; 
        Node* left; 
        Node* right; 
        int height; 
        int size;
        Node(int d) : data(d), left(nullptr), right(nullptr), height(1), size(1) {}
}; 

class AVLTree {
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0; 
    }

    Node* rotateLeft(Node* top) {
        Node* mid = top->right;
        Node* bot = mid->left; 

        mid->left = top;
        top->right = bot;

        update
    }
    
    public: 
    AVLTree() : root(nullptr) {};
    
}       


int main() {

}