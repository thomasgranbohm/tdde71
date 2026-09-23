#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

class LinkedList
{
public:
    LinkedList() : size{0}, head{nullptr}, tail{nullptr} {}; // ctor
    LinkedList(LinkedList const &other);                     // copy ctor
    LinkedList &operator=(LinkedList const &b);              // copy assignment
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

    int front() const;
    int back() const;
    int get(const unsigned int n) const;

    std::string to_string() const;

private:
    struct Node
    {
        int value;
        Node *prev;
        Node *next;
    };

    unsigned int size;
    Node *head;
    Node *tail;

    void empty_list();
    Node *get_middle_node(Node *head) const;
    Node *merge(Node *head, Node *head2);
    Node *merge_sort(Node *head);
};

#endif