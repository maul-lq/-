#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include "doublelinkedlist.h"
using namespace std;

class Antrian {
private:
    int maks;
    int count;
    DoubleLinkedList* list;

public:
    Antrian();
    ~Antrian();

    bool isFull();
    bool isEmpty();
    void enqueue(string data);
    void dequeue();
    int HitungAntrian();
    void Tampil();
    void destroy();
    string depan(); // Tambahkan ini
};

#endif // QUEUE_H