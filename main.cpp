#include <iostream> // Library untuk input/output standar
#include <string> // Library untuk tipe data string
#include <stdio.h> // Library untuk fungsi printf, system, dll
#include <map> // Library untuk struktur data map
#include <array> // Library untuk array STL
#include "main.h" // Header fungsi-fungsi utama
#include "queue.h" // Header kelas Antrian
#include "doublelinkedlist.h" // Header kelas DoubleLinkedList
#include "graph.h" // Header kelas Graf
#include <vector> // Library untuk vector STL
#include <cctype> // Library untuk fungsi karakter (toupper)

using namespace std; // Menggunakan namespace std

// Matriks graf: A=1, B=2, C=3, D=4, E=5, $=6 (TPS)
const int NODE_COUNT = 6; // Jumlah node pada graf
int adjacencyMatrix[NODE_COUNT][NODE_COUNT] = {
    // A  B  C  D  E  $
    {0, 3, 0, 0, 0, 0}, // A
    {0, 0, 0, 0, 0, 6}, // B
    {0, 0, 0, 0, 0, 7}, // C
    {3, 0, 0, 0, 0, 0}, // D
    {3, 0, 0, 0, 0, 0}, // E
    {0, 0, 0, 0, 0, 0}  // $
};
int nodeLabels[NODE_COUNT] = {1, 2, 3, 4, 5, 6}; // Label node: 1:A, 2:B, 3:C, 4:D, 5:E, 6:$

// Helper: konversi lokasi string ke index graf
int lokasiKeIdx(const std::string &lokasi)
{
    if (lokasi.empty()) // Jika string kosong, return -1
        return -1;
    char c = std::toupper(lokasi[0]); // Ambil karakter pertama dan ubah ke huruf besar
    if (c >= 'A' && c <= 'E')
        return c - 'A'; // Konversi A-E ke 0-4
    if (c == '$')
        return 5; // $ ke index 5
    return -1; // Jika tidak valid, return -1
}

// Fungsi untuk menampilkan judul aplikasi
void judul()
{
    system("cls"); // Bersihkan layar
    printf("Selamat datang di Trans Trash\n");
    printf("=============================\n");
}

// Fungsi untuk menampilkan pesan error pilihan tidak valid
void tampilkanPesanError()
{
    printf("Pilihan tidak valid!\n");
    system("pause");
}

// Fungsi untuk menampilkan statistik mingguan berat sampah
void tampilkanStatistikMingguan(Antrian &laporan)
{
    // Statistik berat sampah per hari
    map<string, double> statistik; // Map hari ke total berat
    vector<string> hariList = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"}; // Daftar hari

    // Ambil semua laporan tanpa mengubah antrian
    vector<string> semuaLaporan; // Vector untuk menampung semua laporan
    int n = laporan.HitungAntrian(); // Hitung jumlah laporan
    for (int i = 0; i < n; ++i) {
        string data = laporan.depan(); // Ambil data paling depan
        semuaLaporan.push_back(data); // Simpan ke vector
        laporan.enqueue(data); // Masukkan kembali ke antrian
        laporan.dequeue(); // Keluarkan dari depan (rotasi)
    }

    // Proses laporan: ambil hari dan berat
    for (const string &lap : semuaLaporan) {
        size_t h = lap.find("Hari: "); // Cari posisi substring "Hari: "
        size_t b = lap.find("Berat: "); // Cari posisi substring "Berat: "
        if (h == string::npos || b == string::npos) continue; // Jika tidak ditemukan, lanjut

        string hari, beratStr;
        // Ambil hari
        size_t h1 = h + 6; // Posisi awal nama hari
        size_t h2 = lap.find(',', h1); // Posisi koma setelah hari
        hari = lap.substr(h1, h2 - h1); // Ambil substring hari

        // Ambil berat
        size_t b1 = b + 7; // Posisi awal angka berat
        size_t b2 = lap.find('.', b1); // Posisi titik setelah berat
        beratStr = lap.substr(b1, b2 - b1); // Ambil substring berat

        double berat = 0;
        try { berat = stod(beratStr); } catch (...) { berat = 0; } // Konversi string ke double
        statistik[hari] += berat; // Tambahkan ke statistik hari terkait
    }

    // Tampilkan statistik
    double total = 0; // Total berat semua hari
    printf("Statistik Mingguan Berat Sampah (kg):\n");
    for (const string &hari : hariList) {
        printf("%-8s : %.2f\n", hari.c_str(), statistik[hari]); // Tampilkan berat per hari
        total += statistik[hari]; // Tambahkan ke total
    }
    printf("-----------------------------\n");
    printf("Total    : %.2f\n", total); // Tampilkan total
    printf("-----------------------------\n");
}

// Fungsi utama program
int main()
{
    map<string, string> data; // Map untuk menyimpan input user
    string userInput; // Variabel input user
    bool appIsRun = true; // Status aplikasi berjalan
    Antrian laporan; // Objek antrian laporan
    system("cls"); // Bersihkan layar

    // Array akun untuk autentikasi admin
    array<string, 2> akun = {"root", "admin"}; // Username dan password admin

    while (appIsRun) // Loop utama aplikasi
    {
        judul(); // Tampilkan judul
        printf("1. Masuk (Khusus Admin)\n");
        printf("2. Masuk\n");
        printf("3. Keluar\n");
        getline(cin, userInput); // Ambil input menu
        data["input"] = userInput; // Simpan input

        if (userInput == "1") // Jika pilih admin
        {
            judul();
            printf("Username: ");
            getline(cin, userInput); // Input username
            data["username"] = userInput;
            printf("Password: ");
            getline(cin, userInput); // Input password
            data["password"] = userInput;
            if (data["username"] == akun[0] && data["password"] == akun[1]) // Cek autentikasi
            {
                tampilanAdmin(userInput, laporan); // Masuk menu admin
            }
            else
            {
                printf("Username / password yang anda masukan salah!\n");
                system("pause");
            }
        }
        else if (userInput == "2") // Jika pilih user biasa
        {
            judul();
            string laporanBaru, temp;
            printf("Lokasi (Wilayah A-E)\t: ");
            getline(cin, temp); // Input lokasi
            laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp); // Input hari
            laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp); // Input berat
            laporanBaru += "Berat: " + temp + ". ";
            try
            {
                laporan.enqueue(laporanBaru); // Masukkan laporan ke antrian
                printf("Laporan berhasil ditambahkan!\n");
            }
            catch (const exception &e)
            {
                printf("Terjadi kesalahan saat menambahkan laporan: %s\n", e.what());
            }
            system("pause");
        }
        else if (userInput == "3") // Jika pilih keluar
        {
            appIsRun = false; // Set aplikasi berhenti
        }
        else
        {
            cout << '\n';
            system("pause");
        }
    }

    cout << endl;
    system("pause");
}

// Fungsi tampilan menu admin
void tampilanAdmin(string userInput, Antrian &laporan)
{
    bool adminMenu = true; // Status menu admin
    while (adminMenu)
    {
        judul(); // Tampilkan judul
        printf("Menu Admin Laporan:\n");
        printf("1. Lihat Laporan\n");
        printf("2. Edit Laporan\n");
        printf("3. Hapus Laporan\n");
        printf("4. Tanggapi Laporan\n");
        printf("5. Statistik Mingguan\n"); // Menu statistik
        printf("6. Keluar\n"); // Menu keluar
        printf("Pilih menu: ");
        getline(cin, userInput); // Input menu

        if (userInput == "1") // Lihat laporan
        {
            judul();
            laporan.Tampil(); // Tampilkan semua laporan
            system("pause");
        }
        else if (userInput == "2") // Edit laporan
        {
            judul();
            laporan.Tampil(); // Tampilkan laporan
            printf("Masukkan nomor laporan yang ingin diedit: ");
            string idxStr;
            getline(cin, idxStr); // Input nomor laporan
            int idx = stoi(idxStr); // Konversi ke int
            string laporanBaru, temp;
            printf("Lokasi\t: ");
            getline(cin, temp); // Input lokasi baru
            laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp); // Input hari baru
            laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp); // Input berat baru
            laporanBaru += "Berat: " + temp + ". ";

            int total = laporan.HitungAntrian(); // Hitung total laporan
            if (idx < 1 || idx > total)
            {
                printf("Nomor laporan tidak valid!\n");
            }
            else
            {
                Antrian temp;
                // Pindahkan semua sebelum idx ke temp
                for (int i = 1; i < idx; ++i)
                {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                // Hapus laporan lama (pada posisi idx)
                laporan.dequeue();
                // Tambahkan laporan baru
                temp.enqueue(laporanBaru);
                // Pindahkan sisa laporan
                int sisa = laporan.HitungAntrian();
                for (int i = 0; i < sisa; ++i)
                {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                // Salin kembali ke laporan utama
                while (!temp.isEmpty())
                {
                    string data = temp.depan();
                    laporan.enqueue(data);
                    temp.dequeue();
                }
                printf("Laporan berhasil diedit!\n");
            }
            system("pause");
        }
        else if (userInput == "3") // Hapus laporan
        {
            judul();
            laporan.Tampil(); // Tampilkan laporan
            printf("Masukkan nomor laporan yang ingin dihapus: ");
            string idxStr;
            getline(cin, idxStr); // Input nomor laporan
            int idx = stoi(idxStr);

            int total = laporan.HitungAntrian();
            if (idx < 1 || idx > total)
            {
                printf("Nomor laporan tidak valid!\n");
            }
            else
            {
                Antrian temp;
                for (int i = 1; i < idx; ++i)
                {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                laporan.dequeue();
                int sisa = laporan.HitungAntrian();
                for (int i = 0; i < sisa; ++i)
                {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                while (!temp.isEmpty())
                {
                    string data = temp.depan();
                    laporan.enqueue(data);
                    temp.dequeue();
                }
                printf("Laporan berhasil dihapus!\n");
            }
            system("pause");
        }
        else if (userInput == "4") // Tanggapi laporan
        {
            // Tanggapi laporan: pilih, tampilkan rute terdekat, hapus laporan
            judul();
            laporan.Tampil(); // Tampilkan laporan
            printf("Masukkan nomor laporan yang ingin ditanggapi: ");
            string idxStr;
            getline(cin, idxStr); // Input nomor laporan
            int idx = stoi(idxStr);

            int total = laporan.HitungAntrian();
            if (idx < 1 || idx > total)
            {
                printf("Nomor laporan tidak valid!\n");
                system("pause");
                continue;
            }

            // Ambil data laporan ke-idx
            Antrian temp;
            string laporanDipilih;
            for (int i = 1; i <= total; ++i)
            {
                string data = laporan.depan();
                if (i == idx)
                {
                    laporanDipilih = data;
                }
                else
                {
                    temp.enqueue(data);
                }
                laporan.dequeue();
            }
            // Salin kembali sisa laporan
            while (!temp.isEmpty())
            {
                string data = temp.depan();
                laporan.enqueue(data);
                temp.dequeue();
            }

            // Ekstrak lokasi dari laporanDipilih
            size_t posLokasi = laporanDipilih.find("Lokasi: ");
            string lokasi = "A";
            if (posLokasi != string::npos)
            {
                size_t start = posLokasi + 8;
                size_t end = laporanDipilih.find(',', start);
                lokasi = laporanDipilih.substr(start, end - start);
            }
            printf("========================================\n");
            printf("Detail Laporan:\n");
            printf("  %s\n", laporanDipilih.c_str());
            printf("========================================\n");
            printf("Lokasi awal laporan: %s\n", lokasi.c_str());

            // Admin bisa pilih titik awal (A-E), default dari laporan
            printf("Masukkan titik awal (A-E, default %s): ", lokasi.c_str());
            string titikAwal;
            getline(cin, titikAwal);
            if (titikAwal.empty())
                titikAwal = lokasi;
            int idxAwal = lokasiKeIdx(titikAwal);
            if (idxAwal < 0 || idxAwal > 4)
            {
                printf("Titik awal tidak valid! (A-E)\n");
                system("pause");
                continue;
            }

            // Buat graf dan tampilkan rute terpendek ke TPS ($)
            Graf graf(adjacencyMatrix, nodeLabels);
            judul();
            printf("Menampilkan rute terdekat dari %c ke TPS ($):\n", 'A' + idxAwal);

            // Tampilkan rute terpendek dengan detail lokasi dan jarak
            std::vector<int> path;
            int totalDistance = 0;
            graf.Dijkstra(idxAwal + 1, path, totalDistance); // +1 karena nodeLabels 1-based

            // Tampilkan rute secara menarik
            printf("Rute terpendek:\n  ");
            const char* namaLokasi[] = {"A", "B", "C", "D", "E", "TPS"};
            for (size_t i = 0; i < path.size(); ++i) {
                int idx = path[i] - 1;
                printf("%s", namaLokasi[idx]);
                if (i != path.size() - 1) printf(" -> ");
            }
            printf("\nTotal jarak: %d satuan\n", totalDistance);
            printf("========================================\n");
            printf("Laporan telah ditanggapi dan dihapus!\n");
            system("pause");
        }
        else if (userInput == "5") // Statistik mingguan
        {
            judul();
            tampilkanStatistikMingguan(laporan); // Tampilkan statistik
            system("pause");
        }
        else if (userInput == "6") // Keluar menu admin
        {
            adminMenu = false;
        }
        else
        {
            tampilkanPesanError();
        }
    }
}
