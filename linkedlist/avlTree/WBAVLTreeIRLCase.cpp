#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

struct Player {
    int id;
    int score;
    Player(int i, int s) : id(i), score(s) {}
    
    bool operator<(const Player& other) const {
        if (score != other.score)
            return score > other.score; // higher score = better
        return id < other.id; // tie-breaker: smaller ID wins
    }
};

struct Node {
    Player key;
    int height;
    int size;
    Node* left;
    Node* right;

    Node(Player val) : key(val), height(1), size(1), left(nullptr), right(nullptr) {}
};

class Leaderboard {
    Node* root = nullptr;
    map<int, int> idToScore; // track scores for quick update

    int height(Node* n) { return n ? n->height : 0; }
    int size(Node* n) { return n ? n->size : 0; }

    void update(Node* n) {
        if (!n) return;
        n->height = 1 + max(height(n->left), height(n->right));
        n->size = 1 + size(n->left) + size(n->right);
    }

    int balanceFactor(Node* n) {
        return height(n->left) - height(n->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        update(y);
        update(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
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
        }
        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, Player key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return rebalance(node);
    }

    Node* erase(Node* node, Player key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = erase(node->left, key);
        else if (node->key < key)
            node->right = erase(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* succ = node->right;
            while (succ->left) succ = succ->left;
            node->key = succ->key;
            node->right = erase(node->right, succ->key);
        }
        return rebalance(node);
    }

    int rank(Node* node, Player x) {
        if (!node) return 0;
        if (x < node->key)
            return rank(node->left, x);
        else if (node->key < x)
            return size(node->left) + 1 + rank(node->right, x);
        else
            return size(node->left);
    }

    Player select(Node* node, int k) {
        if (!node) throw runtime_error("k out of range");
        int lsize = size(node->left);
        if (k < lsize)
            return select(node->left, k);
        else if (k == lsize)
            return node->key;
        else
            return select(node->right, k - lsize - 1);
    }

    void print(Node* node) {
        if (!node) return;
        print(node->left);
        cout << "Player " << node->key.id << " - Score: " << node->key.score << endl;
        print(node->right);
    }

public:
    void addOrUpdatePlayer(int id, int score) {
        Player newP(id, score);
        if (idToScore.count(id)) {
            Player oldP(id, idToScore[id]);
            root = erase(root, oldP);
        }
        idToScore[id] = score;
        root = insert(root, newP);
    }

    int getRank(int id) {
        if (!idToScore.count(id)) return -1;
        Player p(id, idToScore[id]);
        return rank(root, p) + 1; // 1-based rank
    }

    void getPlayerByRank(int rank1) {
        try {
            Player p = select(root, rank1 - 1);
            cout << rank1 << "-th place: Player " << p.id << " (Score: " << p.score << ")\n";
        } catch (...) {
            cout << "Rank out of range\n";
        }
    }

    void showLeaderboard() {
        print(root);
    }
};

int main() {
    Leaderboard lb;
    lb.addOrUpdatePlayer(101, 300);
    lb.addOrUpdatePlayer(102, 600);
    lb.addOrUpdatePlayer(103, 250);
    lb.addOrUpdatePlayer(104, 500);
    lb.addOrUpdatePlayer(105, 450);

    cout << "Leaderboard:\n";
    lb.showLeaderboard();

    cout << "\n Rank of Player 105: " << lb.getRank(105) << endl;
    cout << " Rank of Player 103: " << lb.getRank(103) << endl;

    cout << "\n Player at Rank 1: ";
    lb.getPlayerByRank(1);

    cout << " Player at Rank 3: ";
    lb.getPlayerByRank(3);
}
