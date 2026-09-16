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

    void empty_list();
    LinkedList copy_list(const LinkedList &b);

public:
    LinkedList() : size{0}, head{nullptr}, tail{nullptr} {}; // ctor
    LinkedList(const LinkedList &other);                     // copy ctor
    ~LinkedList() { empty_list(); }                          // dtor

    void push_front(const int a);
    void push_back(const int a);
    int pop_front();
    int pop_back();

    inline bool is_empty() const { return size == 0; }
    int get_size() const { return size; }

    int front() const { return head->value; }
    int back() const { return tail->value; }
    int get(const unsigned int n) const;

    std::string to_string() const;

    LinkedList &operator=(const LinkedList &b);
};

#endif