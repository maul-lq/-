#include <iostream>
#include <Windows.h>
#include <string>
#include "doublelinkedlist.h"

using namespace std;

DoubleLinkedList::DoubleLinkedList()
{
    head = new DNODE;
    tail = new DNODE;
    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
}

DoubleLinkedList::~DoubleLinkedList()
{
    DNODE* current = head;
    while(current != nullptr) {
        DNODE* next = current->next;
        delete current;
        current = next;
    }
}

void DoubleLinkedList::insertAtStart(string data)
{
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->prev = head;
    baru->next = head->next;
    head->next->prev = baru;
    head->next = baru;
}

void DoubleLinkedList::insertAtEnd(string data)
{
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->next = tail;
    baru->prev = tail->prev;
    tail->prev->next = baru;
    tail->prev = baru;
}

void DoubleLinkedList::insertAfter(string target, string data)
{
    DNODE *current = head->next;
    while(current != tail && current->data != target)
    {
        current = current->next;
    }
    if(current == tail) return; // target not found
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->prev = current;
    baru->next = current->next;
    current->next->prev = baru;
    current->next = baru;
}

void DoubleLinkedList::insertBefore(string target, string data)
{
    DNODE *current = head->next;
    while(current != tail && current->data != target)
    {
        current = current->next;
    }
    if(current == tail) return; // target not found
    DNODE *baru = new DNODE;
    baru->data = data;
    baru->next = current;
    baru->prev = current->prev;
    current->prev->next = baru;
    current->prev = baru;
}

void DoubleLinkedList::deleteAtStart()
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = head->next;
    head->next = temp->next;
    temp->next->prev = head;
    delete temp;
}

void DoubleLinkedList::deleteAtEnd()
{
    if(tail->prev == head)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *temp = tail->prev;
    tail->prev = temp->prev;
    temp->prev->next = tail;
    delete temp;
}

void DoubleLinkedList::deleteByValue(string data)
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    DNODE *current = head->next;
    while(current != tail && current->data != data)
    {
        current = current->next;
    }
    if(current == tail)
    {
        cout << "Data tidak ditemukan!" << endl;
        return;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
}

void DoubleLinkedList::displayList(bool reverse)
{
    if(head->next == tail)
    {
        cout << "Listnya kosong!" << endl;
        return;
    }
    if(reverse)
    {
        DNODE *current = tail->prev;
        while(current != head)
        {
            cout << current->data << " ";
            current = current->prev;
        }
    }
    else
    {
        DNODE *current = head->next;
        while(current != tail)
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