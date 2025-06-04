#include "graph.h" // Header kelas Graf
#include "doublelinkedlist.h" // Header DoubleLinkedList
#include <iostream> // Library untuk input/output standar
#include <queue> // Library untuk priority_queue
#include <vector> // Library untuk vector
#include <climits> // Library untuk konstanta INT_MAX
#include <fstream> // Library untuk file output
using namespace std; // Menggunakan namespace std

// Konstruktor kelas Graf
Graf::Graf(int matrix[NODE_COUNT][NODE_COUNT], int nodes[NODE_COUNT])
{
    adjacencyLists = new DoubleLinkedList[NODE_COUNT]; // Alokasi array adjacency list
    // Inisialisasi simpul
    InisialisasiSimpul(nodes);
    // Buat hubungan antar simpul
    BuatHubungan(matrix);
}

// Fungsi inisialisasi simpul graf
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

// Fungsi membuat hubungan antar simpul berdasarkan matriks adjacency
void Graf::BuatHubungan(int matrix[NODE_COUNT][NODE_COUNT])
{
    Simpul *Q = first;

    for (int i = 0; i < NODE_COUNT; i++)
    {
        for (int j = 0; j < NODE_COUNT; j++)
        {
            if (matrix[i][j] != 0)
            {
                adjacencyLists[i].insertAtEnd(to_string(j + 1) + ":" + to_string(matrix[i][j])); // Format "node:bobot"
            }
        }
        Q = Q->left;
    }
}

// Fungsi menampilkan graf
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

// Fungsi algoritma Dijkstra dengan rute dan total jarak (versi sederhana)
void Graf::Dijkstra(int start, std::vector<int>& path, int& totalDistance)
{
    int dist[NODE_COUNT];
    int prev[NODE_COUNT];
    bool visited[NODE_COUNT];

    // Inisialisasi
    for (int i = 0; i < NODE_COUNT; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        visited[i] = false;
    }
    dist[start - 1] = 0;

    for (int count = 0; count < NODE_COUNT - 1; count++) {
        // Cari node dengan jarak minimum yang belum dikunjungi
        int minDist = INT_MAX, minIndex = -1;
        for (int v = 0; v < NODE_COUNT; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) break; // Tidak ada node yang bisa diproses

        visited[minIndex] = true;

        // Update jarak ke tetangga
        auto node = adjacencyLists[minIndex].getHead()->next;
        while (node != nullptr) {
            const std::string& neighbor = node->data;
            size_t colonPos = neighbor.find(':');
            if (colonPos == std::string::npos) {
                node = node->next;
                continue;
            }
            int neighborNode = std::stoi(neighbor.substr(0, colonPos)) - 1;
            int weight = std::stoi(neighbor.substr(colonPos + 1));
            if (!visited[neighborNode] && dist[minIndex] != INT_MAX && dist[minIndex] + weight < dist[neighborNode]) {
                dist[neighborNode] = dist[minIndex] + weight;
                prev[neighborNode] = minIndex;
            }
            node = node->next;
        }
    }

    // Cari path ke TPS (node 6, index 5)
    int target = NODE_COUNT - 1;
    path.clear();
    totalDistance = (dist[target] == INT_MAX ? -1 : dist[target]);
    if (dist[target] == INT_MAX) {
        // Tidak ada rute
        return;
    }
    // Rekonstruksi path mundur
    int at = target;
    int tempPath[NODE_COUNT];
    int len = 0;
    while (at != -1) {
        tempPath[len++] = at + 1; // Simpan 1-based
        at = prev[at];
    }
    // Balik urutan path
    for (int i = len - 1; i >= 0; i--) {
        path.push_back(tempPath[i]);
    }
}

// Fungsi ekspor hasil dijkstra ke file CSV
void Graf::EksporHasil(const std::vector<int> &dist, int start)
{
    ofstream file("hasil_dijkstra.csv"); // Buka file output
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

// Destruktor kelas Graf
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
    delete[] adjacencyLists; // Hapus array adjacencyLists
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