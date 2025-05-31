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

void tampilanAdmin(string &userInput, Antrian &laporan)
{
    bool adminMenu = true;
    while (adminMenu)
    {
        judul();
        printf("1. Lihat Laporan\n");
        printf("2. Keluar\n");
        getline(cin, userInput);

        if (userInput == "1")
        {
            judul();
            laporan.Tampil();
            system("pause");
        }
        else if (userInput == "2")
        {
            adminMenu = false;
        }
        else
        {
            tampilkanPesanError();
        }
    }
}
