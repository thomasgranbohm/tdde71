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
public:
    LinkedList() : size{0}, head{nullptr}, tail{nullptr} {}; // ctor
    LinkedList(const LinkedList &other);                     // copy ctor
    LinkedList &operator=(const LinkedList &b);              // copy assignment
    LinkedList(LinkedList &&other);                          // move ctor
    LinkedList &operator=(LinkedList &&other);               // move assignment
    ~LinkedList() { empty_list(); }                          // dtor
    
    void push_front(const int a);
    void push_back(const int a);
    int pop_front();
    int pop_back();
    void sort();
    
    bool is_empty() const { return size == 0; }
    int get_size() const { return size; }
    
    int front() const { return head->value; }
    int back() const { return tail->value; }
    int get(const unsigned int n) const;
    
    std::string to_string() const;

private:
    unsigned int size;
    Node *head;
    Node *tail;
    
    void empty_list();
    LinkedList copy_list(const LinkedList &b);
};

#endif