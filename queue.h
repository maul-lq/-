#ifndef QUEUE_H // Cegah duplikasi include
#define QUEUE_H

#include <string> // Library untuk string
#include "doublelinkedlist.h" // Header DoubleLinkedList
using namespace std; // Menggunakan namespace std

// Deklarasi kelas Antrian
class Antrian {
private:
    int maks; // Maksimal jumlah antrian
    int count; // Jumlah data saat ini
    DoubleLinkedList* list; // Pointer ke list data

public:
    Antrian(); // Konstruktor
    ~Antrian(); // Destruktor

    bool isFull(); // Cek penuh
    bool isEmpty(); // Cek kosong
    void enqueue(string data); // Tambah data
    void dequeue(); // Hapus data depan
    int HitungAntrian(); // Hitung jumlah data
    void Tampil(); // Tampilkan semua data
    void destroy(); // Hapus semua data
    string depan(); // Ambil data paling depan
};

#endif // QUEUE_H