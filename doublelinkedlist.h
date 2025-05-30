#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
using namespace std;

class DoubleLinkedList {
public:
    struct DNODE {
        string data;
        DNODE* prev;
        DNODE* next;
    };

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
    DNODE* getHead();

private:
    DNODE* head;
    DNODE* tail;
};

#endif // DOUBLELINKEDLIST_H
