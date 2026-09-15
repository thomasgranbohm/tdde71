#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

struct Node
{
    int value;
    Node *prev;
    Node *next;
};

class LinkedList
{
    int size;
    Node *head;
    Node *tail;

public:
    LinkedList() : size{0}, head{nullptr}, tail{nullptr} {}; // ctor
    LinkedList(LinkedList &other);                           // copy ctor
    ~LinkedList() { empty_list(); }                          // dtor

    void push_front(const int a);
    void push_back(const int a);
    int pop_front();
    int pop_back();

    inline bool is_empty() const { return size == 0; }
    int get_size() const { return size; }

    int front() const { return head->value; }
    int back() const { return tail->value; }
    int get(const int n) const;

    std::string to_string() const;

    void empty_list();
};

#endif