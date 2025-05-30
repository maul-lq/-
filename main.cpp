#include <iostream>
#include <string>
#include <stdio.h>
#include <map>
#include <sql.h>
#include <array>
#include "main.h"
// #include "adt/queue.cpp"
// #include "adt/graph.cpp"
using namespace std;

int main()
{
    map<string, string> data;
    string userInput;
    bool appIsRun = true;
    system("cls");

    // Antrian q;

    // // Define adjacency matrix and node array
    // int adjacencyMatrix[6][6] = {
    //     {0, 5, 0, 2, 0, 0},
    //     {6, 0, 3, 0, 0, 0},
    //     {0, 0, 0, 0, 9, 0},
    //     {0, 0, 12, 0, 7, 0},
    //     {0, 14, 0, 0, 0, 3},
    //     {0, 1, 0, 3, 0, 0}
    // };
    // int nodes[6] = {1, 2, 3, 4, 5, 6};

    // // Pass the arrays to the Graf constructor
    // Graf graf(adjacencyMatrix, nodes);

    // graf.TampilkanGraf();

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
                judul();
                printf("1. Lihat Laporan");
                printf("2. Keluar");
                // if (condition)
                // {
                //     /* code */
                // }
                // else
                // {
                //     /* code */
                // }
            }
            else
            {
                printf("Username / password yang anda masukan salah!\n");
                system("pause");
            }
        }
        if (userInput == "2")
        {
        }
        if (userInput == "3")
        {
            appIsRun = false;
        }
    }

    cout << endl;
    system("pause");

    return 0;
}

void judul()
{
    system("cls");
    printf("Selamat datang di Trans Trash\n");
    printf("=============================\n");
}
