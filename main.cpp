#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <array>
#include "main.h"
#include "queue.h"
#include "doublelinkedlist.h"
#include "graph.h"
#include <vector>
#include <cctype>

using namespace std;

// Matriks graf: A=1, B=2, C=3, D=4, E=5, $=6 (TPS)
const int NODE_COUNT = 6;
int adjacencyMatrix[NODE_COUNT][NODE_COUNT] = {
    // A  B  C  D  E  $
    {0, 3, 0, 0, 0, 0}, // A
    {0, 0, 0, 0, 0, 6}, // B
    {0, 0, 0, 0, 0, 7}, // C
    {3, 0, 0, 0, 0, 0}, // D
    {3, 0, 0, 0, 0, 0}, // E
    {0, 0, 0, 0, 0, 0}  // $
};
int nodeLabels[NODE_COUNT] = {1, 2, 3, 4, 5, 6}; // 1:A, 2:B, 3:C, 4:D, 5:E, 6:$

// Helper: konversi lokasi string ke index graf
int lokasiKeIdx(const std::string &lokasi)
{
    if (lokasi.empty())
        return -1;
    char c = std::toupper(lokasi[0]);
    if (c >= 'A' && c <= 'E')
        return c - 'A'; // 0-4
    if (c == '$')
        return 5;
    return -1;
}

void judul()
{
    system("cls");
    printf("Selamat datang di Trans Trash\n");
    printf("=============================\n");
}

void tampilkanPesanError()
{
    printf("Pilihan tidak valid!\n");
    system("pause");
}

int main()
{
    map<string, string> data;
    string userInput;
    bool appIsRun = true;
    Antrian laporan;
    system("cls");

    // The 'akun' array stores the username and password for admin authentication.
    array<string, 2> akun = {"root", "admin"};

    while (appIsRun)
    {
        judul();
        printf("1. Masuk (Khusus Admin)\n");
        printf("2. Masuk\n");
        printf("3. Keluar\n");
        getline(cin, userInput);
        data["input"] = userInput;

        if (userInput == "1")
        {
            judul();
            printf("Username: ");
            getline(cin, userInput);
            data["username"] = userInput;
            printf("Password: ");
            getline(cin, userInput);
            data["password"] = userInput;
            if (data["username"] == akun[0] && data["password"] == akun[1])
            {
                tampilanAdmin(userInput, laporan);
            }
            else
            {
                printf("Username / password yang anda masukan salah!\n");
                system("pause");
            }
        }
        else if (userInput == "2")
        {
            judul();
            string laporanBaru, temp;
            printf("Lokasi\t: ");
            getline(cin, temp);
            laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp);
            laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp);
            laporanBaru += "Berat: " + temp + ". ";
            try
            {
                laporan.enqueue(laporanBaru);
                printf("Laporan berhasil ditambahkan!\n");
            }
            catch (const exception &e)
            {
                printf("Terjadi kesalahan saat menambahkan laporan: %s\n", e.what());
            }
            system("pause");
        }
        else if (userInput == "3")
        {
            appIsRun = false;
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

void tampilanAdmin(string userInput, Antrian &laporan)
{
    bool adminMenu = true;
    while (adminMenu)
    {
        judul();
        printf("Menu Admin Laporan:\n");
        printf("1. Lihat Laporan\n");
        printf("2. Tambah Laporan\n");
        printf("3. Edit Laporan\n");
        printf("4. Hapus Laporan\n");
        printf("5. Tanggapi Laporan\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");
        getline(cin, userInput);

        if (userInput == "1")
        {
            judul();
            laporan.Tampil();
            system("pause");
        }
        else if (userInput == "2")
        {
            judul();
            string laporanBaru, temp;
            printf("Lokasi (Wilayah A-E\t: ");
            getline(cin, temp);
            laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp);
            laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp);
            laporanBaru += "Berat: " + temp + ". ";
            laporan.enqueue(laporanBaru);
            printf("Laporan berhasil ditambahkan!\n");
            system("pause");
        }
        else if (userInput == "3")
        {
            judul();
            laporan.Tampil();
            printf("Masukkan nomor laporan yang ingin diedit: ");
            string idxStr;
            getline(cin, idxStr);
            int idx = stoi(idxStr);
            string laporanBaru, temp;
            printf("Lokasi\t: ");
            getline(cin, temp);
            laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp);
            laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp);
            laporanBaru += "Berat: " + temp + ". ";

            int total = laporan.HitungAntrian();
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
        else if (userInput == "4")
        {
            judul();
            laporan.Tampil();
            printf("Masukkan nomor laporan yang ingin dihapus: ");
            string idxStr;
            getline(cin, idxStr);
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
        else if (userInput == "5")
        {
            // Tanggapi laporan: pilih, tampilkan rute terdekat, hapus laporan
            judul();
            laporan.Tampil();
            printf("Masukkan nomor laporan yang ingin ditanggapi: ");
            string idxStr;
            getline(cin, idxStr);
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
            printf("Laporan dipilih: %s\n", laporanDipilih.c_str());
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
            graf.Dijkstra(idxAwal + 1); // +1 karena nodeLabels 1-based
            printf("Laporan telah ditanggapi dan dihapus!\n");
            system("pause");
        }
        else if (userInput == "6")
        {
            adminMenu = false;
        }
        else
        {
            tampilkanPesanError();
        }
    }
}
