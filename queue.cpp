#include <iostream>
#include <string>
using namespace std;
#include "main.h"
#include "queue.h"
#include "doublelinkedlist.h"

// Define the Antrian class
// class Antrian {
// private:
//     int maks;
//     int count;
//     DoubleLinkedList* list;

// public:
//     Antrian();
//     ~Antrian();

//     bool isFull();
//     bool isEmpty();
//     void enqueue(string data);
//     void dequeue();
//     int HitungAntrian();
//     void Tampil();
//     void destroy();
// };

Antrian::Antrian()
{
    maks = 100;
    count = 0;
    list = new DoubleLinkedList();
}

bool Antrian::isFull()
{
    return (count == maks);
}

bool Antrian::isEmpty()
{
    return (count == 0);
}

void Antrian::enqueue(string data)
{
    if (isFull())
    {
        cout << "Queue sudah penuh!" << endl;
        return;
    }
    list->insertAtEnd(data);
    count++;
}

void Antrian::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue kosong!" << endl;
        return;
    }
    list->deleteAtStart();
    count--;
}

int Antrian::HitungAntrian()
{
    return count;
}

void Antrian::Tampil()
{
    cout << "Antrian Order" << endl;
    list->displayList();
    cout << "Jumlah Antrian : " << HitungAntrian() << "\n--------------------------------------------" << endl;
}

void Antrian::destroy()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

Antrian::~Antrian()
{
    destroy();
    delete list;
}