#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * @class RoomCounter
 * @brief Kelas untuk menghitung jumlah ruangan dalam sebuah peta grid.
 */
class RoomCounter {
private:
    int height;
    int width;
    vector<string> map;
    vector<vector<bool>> visited; // Peta untuk menandai petak yang sudah dikunjungi

    /**
     * @brief Memeriksa apakah sebuah koordinat (r, c) valid untuk dijelajahi.
     * @param r Baris
     * @param c Kolom
     * @return true jika valid, false jika tidak.
     * Sebuah petak valid jika:
     * 1. Berada dalam batas peta.
     * 2. Merupakan petak lantai ('.').
     * 3. Belum pernah dikunjungi sebelumnya.
     */
    bool isValid(int r, int c) {
        return (r >= 0 && r < height && c >= 0 && c < width &&
                map[r][c] == '.' && !visited[r][c]);
    }

    /**
     * @brief Menjelajahi sebuah ruangan menggunakan Depth-First Search (DFS) secara rekursif.
     * @param r Baris awal
     * @param c Kolom awal
     * Fungsi ini akan menandai semua petak yang terhubung dalam satu ruangan.
     */
    void explore(int r, int c) {
        if (!isValid(r, c)) {
            return;
        }

        // Tandai petak saat ini sebagai sudah dikunjungi
        visited[r][c] = true;

        // Jelajahi semua tetangga (atas, bawah, kiri, kanan) secara rekursif
        explore(r - 1, c); // Atas
        explore(r + 1, c); // Bawah
        explore(r, c - 1); // Kiri
        explore(r, c + 1); // Kanan
    }

public:
    /**
     * @brief Constructor untuk inisialisasi peta.
     * @param n Tinggi peta
     * @param m Lebar peta
     */
    RoomCounter(int n, int m) : height(n), width(m) {
        map.resize(height);
        visited.resize(height, vector<bool>(width, false));
    }

    /**
     * @brief Membaca data peta dari input.
     */
    void readMap() {
        for (int i = 0; i < height; ++i) {
            cin >> map[i];
        }
    }

    /**
     * @brief Menghitung total jumlah ruangan di peta.
     * @return Jumlah ruangan.
     */
    int count() {
        int roomCount = 0;
        // Iterasi setiap petak di peta
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                // Jika menemukan petak lantai yang belum dikunjungi,
                // berarti kita menemukan ruangan baru.
                if (map[i][j] == '.' && !visited[i][j]) {
                    roomCount++; // Tambah hitungan ruangan
                    explore(i, j); // Jelajahi seluruh ruangan ini untuk menandainya
                }
            }
        }
        return roomCount;
    }
};

int main() {
    // Optimasi I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    // Buat objek dari kelas RoomCounter
    RoomCounter solver(n, m);
    
    // Baca peta
    solver.readMap();

    // Hitung dan cetak hasilnya
    cout << solver.count() << endl;

    return 0;
}