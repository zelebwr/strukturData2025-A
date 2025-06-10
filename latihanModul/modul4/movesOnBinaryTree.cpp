#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Diperlukan untuk reverse
using namespace std;

// Struktur Node untuk merepresentasikan setiap vertex dalam pohon secara eksplisit
struct Node {
    long long value; // Nomor vertex
    Node* parent;    // Pointer ke parent
    Node* left;      // Pointer ke anak kiri
    Node* right;     // Pointer ke anak kanan

    // Constructor untuk inisialisasi node
    Node(long long val) : value(val), parent(nullptr), left(nullptr), right(nullptr) {}
};

// Fungsi rekursif untuk menghapus semua node yang telah dibuat (mencegah memory leak)
void deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    // Optimasi I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    long long x;
    string s;

    cin >> n >> x;
    cin >> s;

    // --- TAHAP 1: MEMBANGUN JALUR AWAL DARI ROOT KE NODE X ---

    if (x == 0) { // Kasus aneh, tapi untuk keamanan
        cout << "Invalid starting position." << endl;
        return 1;
    }
    
    // 1a. Cari jalur matematis dari X ke root (1)
    vector<long long> pathToRoot;
    long long tempX = x;
    while (tempX > 0) {
        pathToRoot.push_back(tempX);
        tempX /= 2;
    }
    reverse(pathToRoot.begin(), pathToRoot.end()); // Dibalik agar menjadi: [1, 3, 6, 12] (contoh)

    // 1b. Bangun node-node di sepanjang jalur tersebut
    Node* root = new Node(pathToRoot[0]); // Buat root (selalu node 1)
    Node* currentNode = root;

    for (size_t i = 1; i < pathToRoot.size(); ++i) {
        long long nextValue = pathToRoot[i];
        if (nextValue == currentNode->value * 2) { // Jika anak kiri
            Node* newNode = new Node(nextValue);
            currentNode->left = newNode;
            newNode->parent = currentNode;
            currentNode = newNode; // Pindah ke node yang baru dibuat
        } else { // Jika anak kanan
            Node* newNode = new Node(nextValue);
            currentNode->right = newNode;
            newNode->parent = currentNode;
            currentNode = newNode; // Pindah ke node yang baru dibuat
        }
    }
    // `currentNode` sekarang sudah berada di Node dengan nilai X

    // --- TAHAP 2: SIMULASI GERAKAN DAN MEMBANGUN POHON SECARA DINAMIS ---
    
    for (char move : s) {
        if (move == 'U') {
            if (currentNode->parent != nullptr) {
                currentNode = currentNode->parent;
            }
        } else if (move == 'L') {
            // Jika anak kiri belum pernah dikunjungi, buat sekarang
            if (currentNode->left == nullptr) {
                long long leftValue = currentNode->value * 2;
                Node* newNode = new Node(leftValue);
                currentNode->left = newNode;
                newNode->parent = currentNode;
            }
            currentNode = currentNode->left;
        } else if (move == 'R') {
            // Jika anak kanan belum pernah dikunjungi, buat sekarang
            if (currentNode->right == nullptr) {
                long long rightValue = currentNode->value * 2 + 1;
                Node* newNode = new Node(rightValue);
                currentNode->right = newNode;
                newNode->parent = currentNode;
            }
            currentNode = currentNode->right;
        }
    }

    // --- TAHAP 3: CETAK HASIL AKHIR DAN BERSIHKAN MEMORI ---
    
    cout << currentNode->value << endl;

    // Menghapus semua node yang dialokasikan dari root untuk mencegah memory leak
    deleteTree(root);

    return 0;
}