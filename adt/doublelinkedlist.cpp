#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

class DoubleLinkedList
{
private:
    struct DNODE
    {
        string data;
        DNODE *prev;
        DNODE *next;
    };
    DNODE *head;
    DNODE *tail;
public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    void insertAtStart(string data);
    void insertAtEnd(string data);
    void insertAfter(string target, string data);
    void insertBefore(string target, string data);
    void deleteAtStart();
    void deleteAtEnd();
    void deleteByValue(string data);
    void displayList(bool reverse = false);
    DNODE* getHead(); // Added method to return the head of the list
};

DoubleLinkedList::DoubleLinkedList()
{
    head = new DNODE;
    head->next = nullptr;
    head->prev = nullptr;
    tail = new DNODE;
    tail->next = nullptr;
    tail->prev = nullptr;
};

DoubleLinkedList::~DoubleLinkedList()
{
    DNODE* current = head;
    while(current != nullptr) {
        DNODE* next = current->next;
        delete current;
        current = next;
    }
    // cout << "Objek dihapus!" << endl;
};

void DoubleLinkedList::insertAtStart(string data)
{
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->next = nullptr; baru->prev = nullptr;
    if(head->next == nullptr)
    {
        head->next = baru;
        tail->prev = baru;
        return;
    }
    baru->next = head->next;
    head->next->prev = baru;
    head->next = baru;
}

void DoubleLinkedList::insertAtEnd(string data)
{
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->next = nullptr; baru->prev = nullptr;
    if(head->next == nullptr)
    {
        head->next = baru;
        tail->prev = baru;
        return;
    }
    baru->prev = tail->prev;
    tail->prev->next = baru;
    tail->prev = baru;
}

void DoubleLinkedList::insertAfter(string target, string data)
{
    DNODE *current = head->next;
    while(current != nullptr && current->data != target)
    {
        current = current->next;
    }
    if(current == nullptr) return; // target not found
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->prev = current;
    baru->next = current->next;
    if(current->next != nullptr) {
        current->next->prev = baru;
    } else {
        tail->prev = baru;
    }
    current->next = baru;
}

void DoubleLinkedList::insertBefore(string target, string data)
{
    DNODE *current = head->next;
    while(current != nullptr && current->data != target)
    {
        current = current->next;
    }
    if(current == nullptr) return; // target not found
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->prev = current->prev;
    baru->next = current;
    if(current->prev != nullptr) {
        current->prev->next = baru;
    } else {
        head->next = baru;
    }
    current->prev = baru;
}

void DoubleLinkedList::deleteAtStart()
{
    if(head->next == nullptr)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = head->next;
    head->next = temp->next;
    if(temp->next != nullptr)
    {
        temp->next->prev = head;
    }
    else
    {
        tail->prev = nullptr;
    }
    delete temp;
}

void DoubleLinkedList::deleteAtEnd()
{
    if(tail->prev == nullptr)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = tail->prev;
    tail->prev = temp->prev;
    if(temp->prev != nullptr)
    {
        temp->prev->next = nullptr;
    }
    else
    {
        head->next = nullptr;
    }
    delete temp;
}

void DoubleLinkedList::deleteByValue(string data)
{
    if(head->next == nullptr)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *current = head->next;
    while(current != nullptr && current->data != data)
    {
        current = current->next;
    }
    if(current == nullptr)
    {
        cout << "Data tidak ditemukan!" << endl;
        return;
    }
    if(current == head->next)
    {
        deleteAtStart();
    }
    else if(current == tail->prev)
    {
        deleteAtEnd();
    }
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

void DoubleLinkedList::displayList(bool reverse)
{
    if(head->next == nullptr)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    if(reverse)
    {
        DNODE *current = tail->prev;
        while(current != nullptr)
        {
            cout << current->data << " ";
            current = current->prev;
        }
    }
    else
    {
        DNODE *current = head->next;
        while(current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << endl;
}

DoubleLinkedList::DNODE *DoubleLinkedList::getHead()
{
    return head;
}

// int main(int argc, char const *argv[])
// {
//     system("cls");
//     DoubleLinkedList list;
//     list.insertAtStart("1");
//     list.insertAtStart("2");
//     list.insertAtStart("3");
//     list.insertAtStart("4");
//     list.insertAfter("2", "99");
//     list.insertBefore("3", "88");
//     list.insertAtEnd("40");
//     list.insertAtEnd("45");

//     cout << "Menampilkan list : ";
//     list.displayList();
//     cout << "Menampilkan list (Terbalik): ";
//     list.displayList(true);
    
//     list.deleteByValue("99");
//     list.deleteAtEnd();
//     list.deleteAtEnd();
//     list.deleteAtStart();
//     list.deleteByValue("88");
    
//     cout << "Menampilkan list : ";
//     list.displayList();
//     cout << "Menampilkan list (Terbalik): ";
//     list.displayList(true);

//     cout << endl;
//     system("pause");
//     return 0;
// }