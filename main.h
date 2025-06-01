#pragma once // Cegah duplikasi include

#include <string> // Library untuk string
using std::string; // Menggunakan string dari std

// Forward declaration of Antrian jika definisi penuh tidak dibutuhkan di sini
class Antrian; // Deklarasi kelas Antrian

void judul(); // Deklarasi fungsi judul

void tampilanAdmin(string userInput, Antrian &laporan); // Deklarasi fungsi menu admin
void tampilkanStatistikMingguan(Antrian &laporan); // Deklarasi fungsi statistik mingguan