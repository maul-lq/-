#include <iostream> // Library untuk input/output standar
#include <string> // Library untuk tipe data string
using namespace std; // Menggunakan namespace std
#include "main.h" // Header fungsi utama
#include "queue.h" // Header kelas Antrian
#include "doublelinkedlist.h" // Header kelas DoubleLinkedList

// Konstruktor kelas Antrian
Antrian::Antrian()
{
    maks = 100; // Maksimal antrian 100
    count = 0; // Jumlah data awal 0
    list = new DoubleLinkedList(); // Buat list baru
}

// Fungsi cek apakah antrian penuh
bool Antrian::isFull()
{
    return (count == maks); // True jika count = maks
}

// Fungsi cek apakah antrian kosong
bool Antrian::isEmpty()
{
    return (count == 0); // True jika count = 0
}

// Fungsi menambah data ke antrian
void Antrian::enqueue(string data)
{
    if (isFull()) // Jika penuh, tampilkan pesan
    {
        cout << "Queue sudah penuh!" << endl;
        return;
    }
    list->insertAtEnd(data); // Tambah data di akhir list
    count++; // Tambah jumlah data
}

// Fungsi menghapus data dari depan antrian
void Antrian::dequeue()
{
    if (isEmpty()) // Jika kosong, tampilkan pesan
    {
        cout << "Queue kosong!" << endl;
        return;
    }
    list->deleteAtStart(); // Hapus data di awal list
    count--; // Kurangi jumlah data
}

// Fungsi menghitung jumlah data antrian
int Antrian::HitungAntrian()
{
    return count; // Return jumlah data
}

// Fungsi menampilkan semua data antrian
void Antrian::Tampil()
{
    cout << "Laporan Yang Tersedia" << endl;
    list->displayList(); // Tampilkan isi list
    cout << "Jumlah Laporan : " << HitungAntrian() << "\n--------------------------------------------" << endl;
}

// Fungsi menghapus semua data antrian
void Antrian::destroy()
{
    while (!isEmpty()) // Selama tidak kosong
    {
        dequeue(); // Hapus data dari depan
    }
}

// Destruktor kelas Antrian
Antrian::~Antrian()
{
    destroy(); // Hapus semua data
    delete list; // Hapus list
}

// Fungsi mengambil data paling depan antrian
string Antrian::depan()
{
    if (isEmpty()) {
        throw runtime_error("Queue kosong!"); // Jika kosong, lempar error
    }
    // Ambil data node pertama setelah head
    return list->getHead()->next->data;
}