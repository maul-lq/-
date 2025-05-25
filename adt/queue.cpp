#include <iostream>
#include <string>
using namespace std;
#include "doublelinkedlist.cpp"

class queue
{
private:
    int maks;
    int count;
    DoubleLinkedList *list;

public:
    queue();
    bool isFull();
    bool isEmpty();
    void enqueue(string data);
    void dequeue();
    void Tampil();
    void destroy();
    int HitungAntrian();
    ~queue();
};

queue::queue()
{
    maks = 5;
    count = 0;
    list = new DoubleLinkedList();
}

bool queue::isFull()
{
    return (count == maks);
}

bool queue::isEmpty()
{
    return (count == 0);
}

void queue::enqueue(string data)
{
    if (isFull())
    {
        cout << "Queue sudah penuh!" << endl;
        return;
    }
    list->insertAtEnd(data);
    count++;
}

void queue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue kosong!" << endl;
        return;
    }
    list->deleteAtStart();
    count--;
}

int queue::HitungAntrian()
{
    return count;
}

void queue::Tampil()
{
    cout << "Antrian Order" << endl;
    list->displayList();
    cout << "Jumlah Antrian : " << HitungAntrian() << "\n--------------------------------------------" << endl;
}

void queue::destroy()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

queue::~queue()
{
    destroy();
    delete list;
}