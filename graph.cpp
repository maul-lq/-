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

// Fungsi algoritma Dijkstra dengan rute dan total jarak
void Graf::Dijkstra(int start, std::vector<int>& path, int& totalDistance)
{
    // Array untuk menyimpan jarak minimum dari simpul awal
    vector<int> dist(NODE_COUNT, INT_MAX);
    vector<int> prev(NODE_COUNT, -1); // Untuk rekonstruksi path
    dist[start - 1] = 0; // Jarak ke diri sendiri 0

    // Priority queue untuk memilih simpul dengan jarak minimum
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start - 1}); // {jarak, simpul}

    while (!pq.empty())
    {
        int currentDist = pq.top().first; // Jarak saat ini
        int currentNode = pq.top().second; // Simpul saat ini
        pq.pop();

        // Jika jarak saat ini lebih besar dari jarak yang sudah diketahui, lewati
        if (currentDist > dist[currentNode])
            continue;

        // Iterasi melalui tetangga simpul saat ini
        auto node = adjacencyLists[currentNode].getHead()->next; // Mulai dari node pertama
        while (node != nullptr)
        {
            const string &neighbor = node->data; // Data tetangga

            // Validasi format data "simpul:bobot"
            size_t colonPos = neighbor.find(':');
            if (colonPos == string::npos)
            {
                // cerr << "Format data tidak valid: " << neighbor << endl;
                node = node->next;
                continue;
            }

            // Pisahkan data "simpul:bobot"
            int neighborNode = stoi(neighbor.substr(0, colonPos)) - 1; // Index node tetangga
            int weight = stoi(neighbor.substr(colonPos + 1)); // Bobot edge

            // Relaksasi jarak
            if (dist[currentNode] + weight < dist[neighborNode])
            {
                dist[neighborNode] = dist[currentNode] + weight;
                prev[neighborNode] = currentNode;
                pq.push({dist[neighborNode], neighborNode});
            }
            node = node->next;
        }
    }

    // Cari path ke TPS (node 6, index 5)
    int target = NODE_COUNT - 1; // TPS ($)
    path.clear();
    totalDistance = (dist[target] == INT_MAX ? -1 : dist[target]);
    if (dist[target] == INT_MAX) {
        // Tidak ada rute
        return;
    }
    // Rekonstruksi path mundur
    vector<int> reversePath;
    for (int at = target; at != -1; at = prev[at]) {
        reversePath.push_back(at + 1); // Simpan 1-based
    }
    // Balik urutan path
    for (auto it = reversePath.rbegin(); it != reversePath.rend(); ++it) {
        path.push_back(*it);
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