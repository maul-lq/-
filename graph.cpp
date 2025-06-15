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
// void Graf::Dijkstra(int start, std::vector<int>& path, int& totalDistance)
// {
//     int dist[NODE_COUNT];
//     int prev[NODE_COUNT];
//     bool visited[NODE_COUNT];

//     // Inisialisasi
//     for (int i = 0; i < NODE_COUNT; i++) {
//         dist[i] = INT_MAX;
//         prev[i] = -1;
//         visited[i] = false;
//     }
//     dist[start - 1] = 0;

//     for (int count = 0; count < NODE_COUNT - 1; count++) {
//         // Cari node dengan jarak minimum yang belum dikunjungi
//         int minDist = INT_MAX, minIndex = -1;
//         for (int v = 0; v < NODE_COUNT; v++) {
//             if (!visited[v] && dist[v] <= minDist) {
//                 minDist = dist[v];
//                 minIndex = v;
//             }
//         }

//         if (minIndex == -1) break; // Tidak ada node yang bisa diproses

//         visited[minIndex] = true;

//         // Update jarak ke tetangga
//         auto node = adjacencyLists[minIndex].getHead()->next;
//         while (node != nullptr) {
//             const std::string& neighbor = node->data;
//             size_t colonPos = neighbor.find(':');
//             if (colonPos == std::string::npos) {
//                 node = node->next;
//                 continue;
//             }
//             int neighborNode = std::stoi(neighbor.substr(0, colonPos)) - 1;
//             int weight = std::stoi(neighbor.substr(colonPos + 1));
//             if (!visited[neighborNode] && dist[minIndex] != INT_MAX && dist[minIndex] + weight < dist[neighborNode]) {
//                 dist[neighborNode] = dist[minIndex] + weight;
//                 prev[neighborNode] = minIndex;
//             }
//             node = node->next;
//         }
//     }

//     // Cari path ke TPS (node 6, index 5)
//     int target = NODE_COUNT - 1;
//     path.clear();
//     totalDistance = (dist[target] == INT_MAX ? -1 : dist[target]);
//     if (dist[target] == INT_MAX) {
//         // Tidak ada rute
//         return;
//     }
//     // Rekonstruksi path mundur
//     int at = target;
//     int tempPath[NODE_COUNT];
//     int len = 0;
//     while (at != -1) {
//         tempPath[len++] = at + 1; // Simpan 1-based
//         at = prev[at];
//     }
//     // Balik urutan path
//     for (int i = len - 1; i >= 0; i--) {
//         path.push_back(tempPath[i]);
//     }
// }

// Fungsi ekspor hasil dijkstra ke file CSV
// void Graf::EksporHasil(const std::vector<int> &dist, int start)
// {
//     ofstream file("hasil_dijkstra.csv"); // Buka file output
//     if (!file.is_open())
//     {
//         cerr << "Gagal membuka file untuk ekspor!" << endl;
//         return;
//     }

//     file << "Simpul Awal,Jarak Ke,Simpul Tujuan\n";
//     for (int i = 0; i < dist.size(); i++)
//     {
//         file << start << "," << (dist[i] == INT_MAX ? -1 : dist[i]) << "," << (i + 1) << "\n";
//     }

//     file.close();
//     cout << "Hasil diekspor ke 'hasil_dijkstra.csv'" << endl;
// }

// Fungsi algoritma Dijkstra untuk rute round-trip: TPS -> Target -> TPS
void Graf::Dijkstra(int target, std::vector<int>& pathToTarget, std::vector<int>& pathFromTarget, int& totalDistance)
{
    int idxTPS = NODE_COUNT - 1; // idxTPS = index TPS (node terakhir, 5)
    int idxTarget = target - 1; // idxTarget = index lokasi tujuan (mulai dari 0)

    // Variabel untuk simpan path dan jarak TPS ke target
    std::vector<int> jalurSementara; // jalurSementara = path sementara (tidak dipakai di bawah)
    int jarakKeTarget = 0; // jarakKeTarget = jarak TPS ke target

    // Array Dijkstra TPS ke Target
    int dist1[NODE_COUNT]; // dist1 = jarak minimum dari TPS ke node lain
    int prev1[NODE_COUNT]; // prev1 = node sebelumnya di path
    bool visited1[NODE_COUNT]; // visited1 = status node sudah dikunjungi

    // Inisialisasi array Dijkstra TPS ke Target
    for (int i = 0; i < NODE_COUNT; i++) {
        dist1[i] = INT_MAX; // Set jarak awal tak hingga
        prev1[i] = -1; // Belum ada node sebelumnya
        visited1[i] = false; // Belum dikunjungi
    }
    dist1[idxTPS] = 0; // Jarak TPS ke TPS = 0

    // Proses Dijkstra TPS ke Target
    for (int count = 0; count < NODE_COUNT - 1; count++) {
        int minDist = INT_MAX, idxMin = -1; // Cari node dengan jarak minimum
        for (int v = 0; v < NODE_COUNT; v++) {
            if (!visited1[v] && dist1[v] <= minDist) { // Jika belum dikunjungi dan jaraknya lebih kecil
                minDist = dist1[v]; // Update jarak minimum
                idxMin = v; // Simpan index node
            }
        }

        if (idxMin == -1) break; // Jika tidak ada node, keluar loop
        visited1[idxMin] = true; // Tandai sudah dikunjungi

        // Update jarak ke tetangga dari node idxMin
        auto node = adjacencyLists[idxMin].getHead()->next; // Ambil node tetangga pertama
        while (node != nullptr) {
            const std::string& tetangga = node->data; // Data tetangga (format: "x:y")
            size_t titikDua = tetangga.find(':'); // Cari posisi ':'
            if (titikDua == std::string::npos) {
                node = node->next; // Jika format salah, lanjut
                continue;
            }
            int idxTetangga = std::stoi(tetangga.substr(0, titikDua)) - 1; // Ambil index tetangga
            int bobot = std::stoi(tetangga.substr(titikDua + 1)); // Ambil bobot edge
            // Jika belum dikunjungi dan jarak lebih kecil, update
            if (!visited1[idxTetangga] && dist1[idxMin] != INT_MAX && dist1[idxMin] + bobot < dist1[idxTetangga]) {
                dist1[idxTetangga] = dist1[idxMin] + bobot; // Update jarak
                prev1[idxTetangga] = idxMin; // Simpan node sebelumnya
            }
            node = node->next; // Lanjut ke tetangga berikutnya
        }
    }

    // Rekonstruksi path TPS ke Target
    pathToTarget.clear(); // Kosongkan path
    jarakKeTarget = (dist1[idxTarget] == INT_MAX ? -1 : dist1[idxTarget]); // Jika tidak terjangkau, -1
    if (dist1[idxTarget] != INT_MAX) { // Jika ada path
        int at = idxTarget; // Mulai dari target
        int tempPath[NODE_COUNT]; // Tempat simpan path
        int len = 0; // Panjang path
        while (at != -1) { // Telusuri mundur ke TPS
            tempPath[len++] = at + 1; // Simpan node (1-based)
            at = prev1[at]; // Ke node sebelumnya
        }
        for (int i = len - 1; i >= 0; i--) { // Balik urutan path
            pathToTarget.push_back(tempPath[i]); // Masukkan ke pathToTarget
        }
    }

    // Array Dijkstra Target ke TPS (perjalanan pulang)
    int dist2[NODE_COUNT]; // dist2 = jarak minimum dari Target ke node lain
    int prev2[NODE_COUNT]; // prev2 = node sebelumnya di path
    bool visited2[NODE_COUNT]; // visited2 = status node sudah dikunjungi

    // Inisialisasi array Dijkstra Target ke TPS
    for (int i = 0; i < NODE_COUNT; i++) {
        dist2[i] = INT_MAX; // Set jarak awal tak hingga
        prev2[i] = -1; // Belum ada node sebelumnya
        visited2[i] = false; // Belum dikunjungi
    }
    dist2[idxTarget] = 0; // Jarak Target ke Target = 0

    // Proses Dijkstra Target ke TPS
    for (int count = 0; count < NODE_COUNT - 1; count++) {
        int minDist = INT_MAX, idxMin = -1; // Cari node dengan jarak minimum
        for (int v = 0; v < NODE_COUNT; v++) {
            if (!visited2[v] && dist2[v] <= minDist) { // Jika belum dikunjungi dan jaraknya lebih kecil
                minDist = dist2[v]; // Update jarak minimum
                idxMin = v; // Simpan index node
            }
        }

        if (idxMin == -1) break; // Jika tidak ada node, keluar
        visited2[idxMin] = true; // Tandai sudah dikunjungi

        // Update jarak ke tetangga dari node idxMin
        auto node = adjacencyLists[idxMin].getHead()->next; // Ambil node tetangga pertama
        while (node != nullptr) {
            const std::string& tetangga = node->data; // Data tetangga (format: "x:y")
            size_t titikDua = tetangga.find(':'); // Cari posisi ':'
            if (titikDua == std::string::npos) {
                node = node->next; // Jika format salah, lanjut
                continue;
            }
            int idxTetangga = std::stoi(tetangga.substr(0, titikDua)) - 1; // Ambil index tetangga
            int bobot = std::stoi(tetangga.substr(titikDua + 1)); // Ambil bobot edge
            // Jika belum dikunjungi dan jarak lebih kecil, update
            if (!visited2[idxTetangga] && dist2[idxMin] != INT_MAX && dist2[idxMin] + bobot < dist2[idxTetangga]) {
                dist2[idxTetangga] = dist2[idxMin] + bobot; // Update jarak
                prev2[idxTetangga] = idxMin; // Simpan node sebelumnya
            }
            node = node->next; // Lanjut ke tetangga berikutnya
        }
    }

    // Rekonstruksi path Target ke TPS
    pathFromTarget.clear(); // Kosongkan path
    int jarakDariTarget = (dist2[idxTPS] == INT_MAX ? -1 : dist2[idxTPS]); // Jika tidak terjangkau, -1
    if (dist2[idxTPS] != INT_MAX) { // Jika ada path
        int at = idxTPS; // Mulai dari TPS
        int tempPath[NODE_COUNT]; // Tempat simpan path
        int len = 0; // Panjang path
        while (at != -1) { // Telusuri mundur ke Target
            tempPath[len++] = at + 1; // Simpan node (1-based)
            at = prev2[at]; // Ke node sebelumnya
        }
        for (int i = len - 1; i >= 0; i--) { // Balik urutan path
            pathFromTarget.push_back(tempPath[i]); // Masukkan ke pathFromTarget
        }
    }

    // Hitung total jarak round-trip TPS -> Target -> TPS
    totalDistance = (jarakKeTarget == -1 || jarakDariTarget == -1) ? -1 : (jarakKeTarget + jarakDariTarget); // Jika salah satu tidak terjangkau, -1
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