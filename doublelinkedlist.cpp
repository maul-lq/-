#include <iostream> // Library untuk input/output standar
#include <Windows.h> // Library untuk fungsi Windows (jika diperlukan)
#include <string> // Library untuk string
#include "doublelinkedlist.h" // Header DoubleLinkedList

using namespace std; // Menggunakan namespace std

// Konstruktor DoubleLinkedList
DoubleLinkedList::DoubleLinkedList()
{
    head = new DNODE; // Buat node head
    tail = new DNODE; // Buat node tail
    head->prev = nullptr; // Head tidak punya prev
    head->next = tail; // Head next ke tail
    tail->prev = head; // Tail prev ke head
    tail->next = nullptr; // Tail tidak punya next
}

// Destruktor DoubleLinkedList
DoubleLinkedList::~DoubleLinkedList()
{
    DNODE* current = head; // Mulai dari head
    while(current != nullptr) {
        DNODE* next = current->next; // Simpan pointer berikutnya
        delete current; // Hapus node sekarang
        current = next; // Lanjut ke node berikutnya
    }
}

// Fungsi menambah data di awal list
void DoubleLinkedList::insertAtStart(string data)
{
    if (!this) return; // Cek null pointer
    DNODE *baru = new DNODE; // Buat node baru
    baru->data = data; // Isi data
    baru->prev = head; // Prev ke head
    baru->next = head->next; // Next ke node setelah head
    head->next->prev = baru; // Node setelah head prev ke baru
    head->next = baru; // Head next ke baru
}

// Fungsi menambah data di akhir list
void DoubleLinkedList::insertAtEnd(string data)
{
    if (!this) return; // Cek null pointer
    DNODE *baru = new DNODE; // Buat node baru
    baru->data = data; // Isi data
    baru->next = tail; // Next ke tail
    baru->prev = tail->prev; // Prev ke node sebelum tail
    tail->prev->next = baru; // Node sebelum tail next ke baru
    tail->prev = baru; // Tail prev ke baru
}

// Fungsi menambah data setelah node tertentu
void DoubleLinkedList::insertAfter(string target, string data)
{
    if (!this) return; // Cek null pointer
    DNODE *current = head->next; // Mulai dari node pertama
    while(current != tail && current->data != target)
    {
        current = current->next; // Cari node target
    }
    if(current == tail) return; // Jika tidak ketemu, return
    DNODE *baru = new DNODE; // Buat node baru
    baru->data = data; // Isi data
    baru->prev = current; // Prev ke current
    baru->next = current->next; // Next ke node setelah current
    current->next->prev = baru; // Node setelah current prev ke baru
    current->next = baru; // Current next ke baru
}

// Fungsi menambah data sebelum node tertentu
void DoubleLinkedList::insertBefore(string target, string data)
{
    DNODE *current = head->next; // Mulai dari node pertama
    while(current != tail && current->data != target)
    {
        current = current->next; // Cari node target
    }
    if(current == tail) return; // Jika tidak ketemu, return
    DNODE *baru = new DNODE; // Buat node baru
    baru->data = data; // Isi data
    baru->next = current; // Next ke current
    baru->prev = current->prev; // Prev ke node sebelum current
    current->prev->next = baru; // Node sebelum current next ke baru
    current->prev = baru; // Current prev ke baru
}

// Fungsi hapus data di awal list
void DoubleLinkedList::deleteAtStart()
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = head->next; // Node pertama
    head->next = temp->next; // Head next ke node kedua
    temp->next->prev = head; // Node kedua prev ke head
    delete temp; // Hapus node pertama
}

// Fungsi hapus data di akhir list
void DoubleLinkedList::deleteAtEnd()
{
    if(tail->prev == head)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = tail->prev; // Node terakhir
    tail->prev = temp->prev; // Tail prev ke node sebelum terakhir
    temp->prev->next = tail; // Node sebelum terakhir next ke tail
    delete temp; // Hapus node terakhir
}

// Fungsi hapus data berdasarkan nilai
void DoubleLinkedList::deleteByValue(string data)
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *current = head->next; // Mulai dari node pertama
    while(current != tail && current->data != data)
    {
        current = current->next; // Cari node dengan data
    }
    if(current == tail)
    {
        cout << "Data tidak ditemukan!" << endl;
        return;
    }
    current->prev->next = current->next; // Node sebelum current next ke node setelah current
    current->next->prev = current->prev; // Node setelah current prev ke node sebelum current
    delete current; // Hapus node current
}

// Fungsi menampilkan isi list
void DoubleLinkedList::displayList(bool reverse)
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    if(reverse)
    {
        DNODE *current = tail->prev; // Mulai dari belakang
        while(current != head)
        {
            cout << current->data << " ";
            current = current->prev;
        }
    }
    else
    {
        DNODE *current = head->next; // Mulai dari depan
        while(current != tail)
        {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}

// Fungsi mengambil pointer ke head
DoubleLinkedList::DNODE *DoubleLinkedList::getHead()
{
    return head;
}