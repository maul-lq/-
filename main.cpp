#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <array>
#include "main.h"
#include "queue.cpp"
#include "graph.cpp"
using namespace std;

void judul()
{
    system("cls");
    printf("Selamat datang di Trans Trash\n");
    printf("=============================\n");
}

int main()
{
    map<string, string> data;
    string userInput;
    bool appIsRun = true;
    Antrian laporan;
    system("cls");

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
                // masuk menu admin
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
                        printf("Pilihan tidak valid!\n");
                        system("pause");
                    }
                }
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
            laporan.enqueue(userInput);
            printf("Laporan berhasil ditambahkan!\n");
            system("pause");
        }
        else if (userInput == "3")
        {
            appIsRun = false;
        }
        else
        {
            printf("Pilihan tidak valid!\n");
            system("pause");
        }
    }

    cout << endl;
    system("pause");

    return 0;
}
