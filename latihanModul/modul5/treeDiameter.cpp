#include <iostream>
#include <vector>
#include <queue>
#include <utility> // Untuk std::pair

using namespace std;

/**
 * @class Tree
 * @brief Kelas untuk merepresentasikan sebuah pohon dan menghitung diameternya.
 */
class Tree {
private:
    int numNodes;
    vector<vector<int>> adjList; // Adjacency list untuk menyimpan graf

    /**
     * @brief Melakukan Breadth-First Search (BFS) dari sebuah simpul awal.
     * @param startNode Simpul untuk memulai BFS.
     * @return pair<int, int> - {simpul terjauh, jarak ke simpul terjauh}.
     */
    pair<int, int> bfs(int startNode) {
        // Vektor untuk menyimpan jarak dari startNode. -1 berarti belum dikunjungi.
        vector<int> distance(numNodes + 1, -1);
        queue<int> q;

        // Inisialisasi untuk simpul awal
        distance[startNode] = 0;
        q.push(startNode);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            // Kunjungi semua tetangga dari currentNode
            for (int neighbor : adjList[currentNode]) {
                if (distance[neighbor] == -1) { // Jika belum dikunjungi
                    distance[neighbor] = distance[currentNode] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Cari simpul dengan jarak terjauh dari startNode
        int farthestNode = -1;
        int maxDistance = 0;
        for (int i = 1; i <= numNodes; ++i) {
            if (distance[i] > maxDistance) {
                maxDistance = distance[i];
                farthestNode = i;
            }
        }

        return {farthestNode, maxDistance};
    }

public:
    /**
     * @brief Constructor untuk inisialisasi pohon.
     * @param n Jumlah simpul dalam pohon.
     */
    Tree(int n) : numNodes(n) {
        adjList.resize(numNodes + 1);
    }

    /**
     * @brief Menambahkan sisi (edge) tak berarah antara dua simpul.
     * @param u Simpul pertama.
     * @param v Simpul kedua.
     */
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    /**
     * @brief Menghitung diameter pohon menggunakan algoritma dua kali BFS.
     * @return Nilai integer dari diameter pohon.
     */
    int findDiameter() {
        // Langkah 1: Lakukan BFS dari simpul sembarang (misal: 1)
        // untuk menemukan salah satu ujung dari diameter.
        pair<int, int> firstBfsResult = bfs(1);
        int diameterEndpoint = firstBfsResult.first;

        // Langkah 2: Lakukan BFS dari ujung diameter yang ditemukan
        // untuk mencari panjang jalur terpanjang (diameter).
        pair<int, int> secondBfsResult = bfs(diameterEndpoint);

        return secondBfsResult.second;
    }
};

int main() {
    // Optimasi I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Menangani kasus pohon dengan satu simpul
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    // Buat objek dari kelas Tree
    Tree tree(n);

    // Baca n-1 sisi dan tambahkan ke pohon
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        tree.addEdge(a, b);
    }

    // Hitung dan cetak diameter
    cout << tree.findDiameter() << endl;

    return 0;
}