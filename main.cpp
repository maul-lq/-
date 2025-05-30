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

int main()
{
    // map<string, string> data;
    // string userInput;
    // bool appIsRun = true;
    // Antrian laporan;
    // system("cls");

    // array<string, 2> akun = {"root", "admin"};

    // while (appIsRun)
    // {
    //     judul();
    //     printf("1. Masuk (Khusus Admin)\n");
    //     printf("2. Masuk\n");
    //     printf("3. Keluar\n");
    //     getline(cin, userInput);
    //     data["input"] = userInput;

    //     if (userInput == "1")
    //     {
    //         judul();
    //         printf("Username: ");
    //         getline(cin, userInput);
    //         data["username"] = userInput;
    //         printf("Password: ");
    //         getline(cin, userInput);
    //         data["password"] = userInput;
    //         if (data["username"] == akun[0] && data["password"] == akun[1])
    //         {
    //             // masuk menu admin
    //             bool adminMenu = true;
    //             while (adminMenu)
    //             {
    //                 judul();
    //                 printf("1. Lihat Laporan\n");
    //                 printf("2. Keluar\n");
    //                 getline(cin, userInput);

    //                 if (userInput == "1")
    //                 {
    //                     judul();
    //                     laporan.Tampil();
    //                     system("pause");
    //                 }
    //                 else if (userInput == "2")
    //                 {
    //                     adminMenu = false;
    //                 }
    //                 else
    //                 {
    //                     printf("Pilihan tidak valid!\n");
    //                     system("pause");
    //                 }
    //             }
    //         }
    //         else
    //         {
    //             printf("Username / password yang anda masukan salah!\n");
    //             system("pause");
    //         }
    //     }
    //     else if (userInput == "2")
    //     {
    //         judul();
    //         printf("Masukkan laporan anda: ");
    //         getline(cin, userInput);
    //         laporan.enqueue(userInput);
    //         printf("Laporan berhasil ditambahkan!\n");
    //         system("pause");
    //     }
    //     else if (userInput == "3")
    //     {
    //         appIsRun = false;
    //     }
    //     else
    //     {
    //         printf("Pilihan tidak valid!\n");
    //         system("pause");
    //     }
    // }

    // cout << endl;
    // system("pause");

    // return 0;

    try
    {
        system("cls");

        // Adjacency matrix dan nomor simpul
        int A[6][6] = {
            {0, 3, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 6},
            {0, 0, 0, 0, 0, 7},
            {3, 0, 0, 0, 0, 0},
            {3, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0},
        };
        int NoSimpul[6] = {1, 2, 3, 4, 5, 6};
        // Buat dan tampilkan graf
        Graf graf(A, NoSimpul);
        graf.TampilkanGraf();

        // Panggil fungsi Dijkstra
        int startSimpul;
        cout << "Masukkan simpul awal untuk mencari jarak terpendek (1-6): ";
        cin >> startSimpul;
        if (startSimpul < 1 || startSimpul > 6)
        {
            throw runtime_error("Simpul awal harus antara 1 sampai 6.");
        }
        graf.Dijkstra(startSimpul);
        graf.Dijkstra(startSimpul);

        system("pause");
    }
    catch (const exception &e)
    {
        cerr << "Terjadi kesalahan: " << e.what() << endl;
        system("pause");
        return 1;
    }
    return 0;
}
