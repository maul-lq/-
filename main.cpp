#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <array>
#include "main.h"
#include "queue.h"
#include "doublelinkedlist.h"
#include "graph.h"

using namespace std;

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
            printf("Masukkan laporan anda: ");
            getline(cin, userInput);
            try
            {
                laporan.enqueue(userInput);
                printf("Laporan berhasil ditambahkan!\n");
            }
            catch (const exception &e)
            {
                printf("Terjadi kesalahan saat menambahkan laporan: %s\n", e.what());
            }
            printf("Laporan berhasil ditambahkan!\n");
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
        printf("5. Keluar\n");
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
            getline(cin, temp);laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp);laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp);laporanBaru += "Berat: " + temp + ". ";
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
            getline(cin, temp);laporanBaru += "Lokasi: " + temp + ", ";
            printf("Hari\t: ");
            getline(cin, temp);laporanBaru += "Hari: " + temp + ", ";
            printf("Berat\t: ");
            getline(cin, temp);laporanBaru += "Berat: " + temp + ". ";

            int total = laporan.HitungAntrian();
            if (idx < 1 || idx > total) {
                printf("Nomor laporan tidak valid!\n");
            } else {
                Antrian temp;
                // Pindahkan semua sebelum idx ke temp
                for (int i = 1; i < idx; ++i) {
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
                for (int i = 0; i < sisa; ++i) {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                // Salin kembali ke laporan utama
                while (!temp.isEmpty()) {
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
            if (idx < 1 || idx > total) {
                printf("Nomor laporan tidak valid!\n");
            } else {
                Antrian temp;
                for (int i = 1; i < idx; ++i) {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                laporan.dequeue();
                int sisa = laporan.HitungAntrian();
                for (int i = 0; i < sisa; ++i) {
                    string data = laporan.depan();
                    temp.enqueue(data);
                    laporan.dequeue();
                }
                while (!temp.isEmpty()) {
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
            adminMenu = false;
        }
        else
        {
            tampilkanPesanError();
        }
    }
}
