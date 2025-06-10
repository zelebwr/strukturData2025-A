#include <iostream>
#include <vector>
#include <queue>
#include <utility> // Untuk std::pair
#include <climits> // Untuk LLONG_MAX

using namespace std;

// Tipe data alias untuk mempersingkat
// {biaya, node}
using State = pair<long long, int>;

/**
 * @class FlightRouter
 * @brief Kelas untuk mencari rute penerbangan termurah dengan satu kupon diskon.
 */
class FlightRouter {
private:
    int num_cities;
    vector<vector<pair<int, int>>> adj; // Adjacency list: adj[kota] -> {{tujuan, harga}, ...}

public:
    /**
     * @brief Constructor untuk inisialisasi.
     * @param n Jumlah kota.
     */
    FlightRouter(int n) : num_cities(n) {
        adj.resize(n + 1);
    }

    /**
     * @brief Menambahkan rute penerbangan searah.
     * @param from Kota asal.
     * @param to Kota tujuan.
     * @param cost Harga penerbangan.
     */
    void addFlight(int from, int to, int cost) {
        adj[from].push_back({to, cost});
    }

    /**
     * @brief Mencari rute termurah dari kota 1 ke kota n menggunakan Dijkstra.
     * @return Harga termurah.
     */
    long long findCheapestRoute() {
        // Jarak[0][kota] -> biaya termurah ke kota ini tanpa pakai kupon
        // Jarak[1][kota] -> biaya termurah ke kota ini setelah pakai kupon
        vector<vector<long long>> distance(2, vector<long long>(num_cities + 1, LLONG_MAX));

        // Min-priority queue untuk menyimpan {biaya, {kota, status_kupon}}
        // status_kupon: 0 = belum dipakai, 1 = sudah dipakai
        priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;

        // Inisialisasi: Mulai dari Surabaya (kota 1) dengan biaya 0, kupon belum dipakai
        distance[0][1] = 0;
        pq.push({0, {1, 0}}); // {biaya, {kota, status_kupon}}

        while (!pq.empty()) {
            long long current_cost = pq.top().first;
            int current_city = pq.top().second.first;
            int coupon_status = pq.top().second.second;
            pq.pop();

            // Optimisasi: Jika sudah ada rute yang lebih murah, lewati
            if (current_cost > distance[coupon_status][current_city]) {
                continue;
            }

            // Jelajahi semua penerbangan dari kota saat ini
            for (auto& flight : adj[current_city]) {
                int neighbor_city = flight.first;
                int flight_cost = flight.second;

                // --- Opsi 1: Terbang dengan harga normal ---
                long long new_cost = current_cost + flight_cost;
                if (new_cost < distance[coupon_status][neighbor_city]) {
                    distance[coupon_status][neighbor_city] = new_cost;
                    pq.push({new_cost, {neighbor_city, coupon_status}});
                }

                // --- Opsi 2: Pakai kupon (jika belum pernah dipakai) ---
                if (coupon_status == 0) {
                    long long discounted_cost = current_cost + (flight_cost / 2);
                    // Setelah ini, status kupon menjadi 1 (sudah dipakai)
                    if (discounted_cost < distance[1][neighbor_city]) {
                        distance[1][neighbor_city] = discounted_cost;
                        pq.push({discounted_cost, {neighbor_city, 1}});
                    }
                }
            }
        }
        
        // Hasil akhir adalah minimum dari tiba di Medan (kota n)
        // dengan atau tanpa menggunakan kupon.
        return min(distance[0][num_cities], distance[1][num_cities]);
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    FlightRouter router(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        router.addFlight(a, b, c);
    }

    cout << router.findCheapestRoute() << endl;

    return 0;
}