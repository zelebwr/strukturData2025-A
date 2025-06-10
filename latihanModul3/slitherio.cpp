#include <iostream>
using namespace std;

class queue {
private:
    long long* prefix;
    int maxSize;
    int currentIdx; // Jumlah ular yang telah ditambahkan
    int m; // Indeks awal ular yang aktif (1-based)

public:
    queue(int Q) {
        maxSize = Q + 2; // Alokasi memori untuk Q+2 elemen
        prefix = new long long[maxSize];
        prefix[0] = 0; // Inisialisasi prefix sum awal
        currentIdx = 0;
        m = 1; // Mulai dari ular pertama
    }

    ~queue() {
        delete[] prefix;
    }

    void add(int l) {
        currentIdx++;
        prefix[currentIdx] = prefix[currentIdx - 1] + l;
    }

    void removeFront() {
        m++; // Geser indeks awal ke kanan
    }

    long long getHeadPosition(int k) {
        int pos = m + k - 2; // Hitung posisi dalam prefix sum
        return prefix[pos] - prefix[m - 1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int Q;
    cin >> Q;

    queue q(Q);

    while (Q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l;
            cin >> l;
            q.add(l);
        } else if (type == 2) {
            q.removeFront();
        } else {
            int k;
            cin >> k;
            cout << q.getHeadPosition(k) << '\n';
        }
    }

    return 0;
}