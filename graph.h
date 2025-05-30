#pragma once
#include <vector> // Add this line

class DoubleLinkedList; // Forward declaration

struct Simpul { // Move struct Simpul here, outside the class
    int info;
    Simpul *left, *right;
};

class Graf {
private:
    // Remove struct Simpul definition from here
    Simpul *first, *last;
    static const int NODE_COUNT = 6;
    DoubleLinkedList* adjacencyLists; // or DoubleLinkedList adjacencyLists[NODE_COUNT];

    void InisialisasiSimpul(int nodes[NODE_COUNT]);
    void BuatHubungan(int matrix[NODE_COUNT][NODE_COUNT]);
    void EksporHasil(const std::vector<int>& dist, int start); // Fix declaration

public:
    Graf(int matrix[NODE_COUNT][NODE_COUNT], int nodes[NODE_COUNT]);
    void TampilkanGraf();
    void Dijkstra(int start);
    ~Graf();
};