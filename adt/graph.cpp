#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <fstream> // Untuk ekspor ke file
#include "doublelinkedlist.cpp" // Include the DoubleLinkedList class
using namespace std;

struct Simpul {
    int info;
    Simpul *left, *right;
};

class Graf {
private:
    Simpul *first, *last;
    DoubleLinkedList adjacencyLists[5]; // Replace adjacency matrix with DoubleLinkedList

public:
    Graf(int matrix[5][5], int nodes[5]) {
        // Inisialisasi simpul
        InisialisasiSimpul(nodes);
        // Buat hubungan antar simpul
        BuatHubungan(matrix);
    }

    void InisialisasiSimpul(int nodes[5]) {
        Simpul *P;
        first = last = nullptr;

        // Buat simpul pertama
        P = new Simpul;
        P->info = nodes[0];
        first = last = P;
        P->left = P->right = nullptr;

        // Buat simpul berikutnya
        for (int i = 1; i < 5; i++) {
            P = new Simpul;
            P->info = nodes[i];
            last->left = P;
            last = P;
            P->left = P->right = nullptr;
        }
    }

    void BuatHubungan(int matrix[5][5]) {
        Simpul *Q = first;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (matrix[i][j] != 0) {
                    adjacencyLists[i].insertAtEnd(to_string(j + 1) + ":" + to_string(matrix[i][j]));
                }
            }
            Q = Q->left;
        }
    }

    void TampilkanGraf() {
        Simpul *Q = first;

        for (int i = 0; i < 5; i++) {
            cout << "Vertex " << Q->info << endl;
            cout << "  Berhubungan dengan: ";
            adjacencyLists[i].displayList();
            Q = Q->left;
        }
    }

    // Fungsi Dijkstra untuk mencari jarak terpendek
    void Dijkstra(int start) {
        // Array untuk menyimpan jarak minimum dari simpul awal
        vector<int> dist(5, INT_MAX);
        dist[start - 1] = 0;

        // Priority queue untuk memilih simpul dengan jarak minimum
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start - 1}); // {jarak, simpul}

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            // Jika jarak saat ini lebih besar dari jarak yang sudah diketahui, lewati
            if (currentDist > dist[currentNode]) continue;

            // Iterasi melalui tetangga simpul saat ini
            auto node = adjacencyLists[currentNode].getHead()->next; // Pastikan mulai dari node pertama
            while (node != nullptr) {
                const string &neighbor = node->data;

                // Validasi format data "simpul:bobot"
                size_t colonPos = neighbor.find(':');
                if (colonPos == string::npos) {
                    cerr << "Format data tidak valid: " << neighbor << endl;
                    node = node->next;
                    continue;
                }

                // Pisahkan data "simpul:bobot"
                int neighborNode = stoi(neighbor.substr(0, colonPos)) - 1;
                int weight = stoi(neighbor.substr(colonPos + 1));

                // Relaksasi jarak
                if (dist[currentNode] + weight < dist[neighborNode]) {
                    dist[neighborNode] = dist[currentNode] + weight;
                    pq.push({dist[neighborNode], neighborNode});
                }
                node = node->next;
            }
        }

        // Tampilkan hasil
        cout << "Jarak terpendek dari simpul " << start << ":\n";
        for (int i = 0; i < 5; i++) {
            cout << "Ke simpul " << (i + 1) << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
        }

        // Ekspor hasil ke file
        EksporHasil(dist, start);
    }

    void EksporHasil(const vector<int>& dist, int start) {
        ofstream file("hasil_dijkstra.csv");
        if (!file.is_open()) {
            cerr << "Gagal membuka file untuk ekspor!" << endl;
            return;
        }

        file << "Simpul Awal,Jarak Ke,Simpul Tujuan\n";
        for (int i = 0; i < dist.size(); i++) {
            file << start << "," << (dist[i] == INT_MAX ? -1 : dist[i]) << "," << (i + 1) << "\n";
        }

        file.close();
        cout << "Hasil diekspor ke 'hasil_dijkstra.csv'" << endl;
    }

    ~Graf() {
        // Hapus semua simpul
        Simpul *current = first, *next;
        while (current != nullptr) {
            next = current->left;
            delete current;
            current = next;
        }
    }
};

int main() {
    try {
        system("cls");

        // Adjacency matrix dan nomor simpul
        int A[5][5] = {
            {0, 5, 0, 2, 0},
            {6, 0, 3, 0, 0},
            {0, 0, 0, 0, 9},
            {0, 0, 12, 0, 7},
            {0, 14, 0, 0, 0}};
        int NoSimpul[5] = {1, 2, 3, 4, 5};

        // Buat dan tampilkan graf
        Graf graf(A, NoSimpul);
        graf.TampilkanGraf();

        // Panggil fungsi Dijkstra
        int startSimpul;
        cout << "Masukkan simpul awal untuk mencari jarak terpendek (1-5): ";
        cin >> startSimpul;
        if (startSimpul < 1 || startSimpul > 5) {
            throw runtime_error("Simpul awal harus antara 1 sampai 5.");
        }
        graf.Dijkstra(startSimpul);

        system("pause");
    } catch (const exception& e) {
        cerr << "Terjadi kesalahan: " << e.what() << endl;
        system("pause");
        return 1;
    }
    return 0;
}