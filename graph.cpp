#include "graph.h"
#include "doublelinkedlist.h"
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include <fstream>
using namespace std;

// Implementasi method-method Graf

Graf::Graf(int matrix[NODE_COUNT][NODE_COUNT], int nodes[NODE_COUNT])
{
    adjacencyLists = new DoubleLinkedList[NODE_COUNT]; // Allocate array
    // Inisialisasi simpul
    InisialisasiSimpul(nodes);
    // Buat hubungan antar simpul
    BuatHubungan(matrix);
}

void Graf::InisialisasiSimpul(int nodes[NODE_COUNT])
{
    Simpul *P;
    first = last = nullptr;

    // Buat simpul pertama
    P = new Simpul;
    P->info = nodes[0];
    first = last = P;
    P->left = P->right = nullptr;

    // Buat simpul berikutnya
    for (int i = 1; i < NODE_COUNT; i++)
    {
        P = new Simpul;
        P->info = nodes[i];
        last->left = P;
        last = P;
        P->left = P->right = nullptr;
    }
}

void Graf::BuatHubungan(int matrix[NODE_COUNT][NODE_COUNT])
{
    Simpul *Q = first;

    for (int i = 0; i < NODE_COUNT; i++)
    {
        for (int j = 0; j < NODE_COUNT; j++)
        {
            if (matrix[i][j] != 0)
            {
                adjacencyLists[i].insertAtEnd(to_string(j + 1) + ":" + to_string(matrix[i][j]));
            }
        }
        Q = Q->left;
    }
}

void Graf::TampilkanGraf()
{
    Simpul *Q = first;

    for (int i = 0; i < NODE_COUNT; i++)
    {
        cout << "Vertex " << Q->info << endl;
        cout << "  Berhubungan dengan: ";
        adjacencyLists[i].displayList();
        Q = Q->left;
    }
}

void Graf::Dijkstra(int start)
{
    // Array untuk menyimpan jarak minimum dari simpul awal
    vector<int> dist(NODE_COUNT, INT_MAX);
    dist[start - 1] = 0;

    // Priority Antrian untuk memilih simpul dengan jarak minimum
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start - 1}); // {jarak, simpul}

    while (!pq.empty())
    {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // Jika jarak saat ini lebih besar dari jarak yang sudah diketahui, lewati
        if (currentDist > dist[currentNode])
            continue;

        // Iterasi melalui tetangga simpul saat ini
        auto node = adjacencyLists[currentNode].getHead()->next; // Pastikan mulai dari node pertama
        while (node != nullptr)
        {
            const string &neighbor = node->data;

            // Validasi format data "simpul:bobot"
            size_t colonPos = neighbor.find(':');
            if (colonPos == string::npos)
            {
                cerr << "Format data tidak valid: " << neighbor << endl;
                node = node->next;
                continue;
            }

            // Pisahkan data "simpul:bobot"
            int neighborNode = stoi(neighbor.substr(0, colonPos)) - 1;
            int weight = stoi(neighbor.substr(colonPos + 1));

            // Relaksasi jarak
            if (dist[currentNode] + weight < dist[neighborNode])
            {
                dist[neighborNode] = dist[currentNode] + weight;
                pq.push({dist[neighborNode], neighborNode});
            }
            node = node->next;
        }
    }

    // Tampilkan hasil
    cout << "Jarak terpendek dari simpul " << start << ":\n";
    for (int i = 0; i < NODE_COUNT; i++)
    {
        cout << "Ke simpul " << (i + 1) << ": " << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
    }

    // Ekspor hasil ke file
    EksporHasil(dist, start);
}

void Graf::EksporHasil(const std::vector<int> &dist, int start)
{
    ofstream file("hasil_dijkstra.csv");
    if (!file.is_open())
    {
        cerr << "Gagal membuka file untuk ekspor!" << endl;
        return;
    }

    file << "Simpul Awal,Jarak Ke,Simpul Tujuan\n";
    for (int i = 0; i < dist.size(); i++)
    {
        file << start << "," << (dist[i] == INT_MAX ? -1 : dist[i]) << "," << (i + 1) << "\n";
    }

    file.close();
    cout << "Hasil diekspor ke 'hasil_dijkstra.csv'" << endl;
}

Graf::~Graf()
{
    // Hapus semua simpul
    Simpul *current = first, *next;
    while (current != nullptr)
    {
        next = current->left;
        delete current;
        current = next;
    }
    delete[] adjacencyLists; // Free adjacencyLists array
}

// int main()
// {
//     try
//     {
//         system("cls");

//         // Adjacency matrix dan nomor simpul
//         int A[6][6] = {
//             {0, 3, 0, 0, 0, 0},
//             {0, 0, 0, 0, 0, 6},
//             {0, 0, 0, 0, 0, 7},
//             {3, 0, 0, 0, 0, 0},
//             {3, 0, 0, 0, 0, 0},
//             {0, 0, 0, 0, 0, 0},
//         };
//         int NoSimpul[6] = {1, 2, 3, 4, 5, 6};
//         // Buat dan tampilkan graf
//         Graf graf(A, NoSimpul);
//         graf.TampilkanGraf();

//         // Panggil fungsi Dijkstra
//         int startSimpul;
//         cout << "Masukkan simpul awal untuk mencari jarak terpendek (1-6): ";
//         cin >> startSimpul;
//         if (startSimpul < 1 || startSimpul > 6)
//         {
//             throw runtime_error("Simpul awal harus antara 1 sampai 6.");
//         }
//         graf.Dijkstra(startSimpul);
//         graf.Dijkstra(startSimpul);

//         system("pause");
//     }
//     catch (const exception &e)
//     {
//         cerr << "Terjadi kesalahan: " << e.what() << endl;
//         system("pause");
//         return 1;
//     }
//     return 0;
// }