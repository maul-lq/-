#ifndef DOUBLELINKEDLIST_H // Cegah duplikasi include
#define DOUBLELINKEDLIST_H

#include <string> // Library untuk string
using namespace std; // Menggunakan namespace std

// Deklarasi kelas DoubleLinkedList
class DoubleLinkedList {
public:
    struct DNODE { // Struktur node double linked list
        string data; // Data string
        DNODE* prev; // Pointer ke node sebelumnya
        DNODE* next; // Pointer ke node berikutnya
    };

    DoubleLinkedList(); // Konstruktor
    ~DoubleLinkedList(); // Destruktor
    void insertAtStart(string data); // Tambah data di awal
    void insertAtEnd(string data); // Tambah data di akhir
    void insertAfter(string target, string data); // Tambah data setelah node tertentu
    void insertBefore(string target, string data); // Tambah data sebelum node tertentu
    void deleteAtStart(); // Hapus data di awal
    void deleteAtEnd(); // Hapus data di akhir
    void deleteByValue(string data); // Hapus data berdasarkan nilai
    void displayList(bool reverse = false); // Tampilkan isi list
    DNODE* getHead(); // Ambil pointer ke head

private:
    DNODE* head; // Pointer ke head
    DNODE* tail; // Pointer ke tail
};

#endif // DOUBLELINKEDLIST_H
