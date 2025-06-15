#pragma once // Cegah duplikasi include
#include <vector> // Library untuk vector STL

class DoubleLinkedList; // Forward declaration DoubleLinkedList

// Struktur simpul untuk graf
struct Simpul {
    int info; // Informasi node (label)
    Simpul *left, *right; // Pointer ke simpul lain
};

// Deklarasi kelas Graf
class Graf {
private:
    Simpul *first, *last; // Pointer ke simpul pertama dan terakhir
    static const int NODE_COUNT = 6; // Jumlah node tetap
    DoubleLinkedList* adjacencyLists; // Array pointer adjacency list

    void InisialisasiSimpul(int nodes[NODE_COUNT]); // Inisialisasi simpul
    void BuatHubungan(int matrix[NODE_COUNT][NODE_COUNT]); // Buat hubungan antar simpul
    // void EksporHasil(const std::vector<int>& dist, int start); // Ekspor hasil dijkstra

public:
    Graf(int matrix[NODE_COUNT][NODE_COUNT], int nodes[NODE_COUNT]); // Konstruktor
    void TampilkanGraf(); // Tampilkan graf
    // void Dijkstra(int start, std::vector<int>& path, int& totalDistance); // Algoritma dijkstra dengan rute
    void Dijkstra(int target, std::vector<int>& pathToTarget, std::vector<int>& pathFromTarget, int& totalDistance); // Dijkstra TPS -> Target -> TPS
    ~Graf(); // Destruktor
};