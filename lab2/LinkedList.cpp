#include <stdexcept>
#include <sstream>
#include <iostream>
#include "LinkedList.hpp"

// Copy constructor
LinkedList::LinkedList(LinkedList &other)
{
    size = other.size;
    head = other.head;
    tail = other.tail;
}

void LinkedList::push_front(int a)
{
    Node *prev = head;

    head = new Node{a, nullptr, prev};

    prev->prev = head;
    size++;
}

void LinkedList::push_back(int a)
{
    Node *prev = tail;

    tail = new Node{a, prev, nullptr};

    if (head == nullptr)
    {
        head = tail;
    }

    if (prev != nullptr)
    {
        prev->next = tail;
    }

    size++;
}

int LinkedList::pop_front()
{
    int value = head->value;
    Node *next_head = head->next;

    delete head;
    head = next_head;
    head->prev = nullptr;

    size--;

    return value;
}

int LinkedList::pop_back()
{
    int value = tail->value;
    Node *next_tail = tail->prev;

    delete tail;
    tail = next_tail;
    tail->next = nullptr;

    size--;

    return value;
}

int LinkedList::get(const int n) const
{
    if (n > size)
    {
        throw std::out_of_range("n too big");
    }

    Node curr = *head;

    for (int i{0}; i < n; i++)
    {
        curr = *curr.next;
    }

    return curr.value;
}

std::string LinkedList::to_string() const
{
    std::stringstream ss{};

    ss << '[';

    Node *curr = head;

    while (true)
    {
        ss << curr->value;

        curr = curr->next;

        if (curr == nullptr)
        {
            break;
        }

        ss << ", ";
    }

    ss << ']';

    return ss.str();
}

void LinkedList::empty_list()
{
    Node *curr = head;

    // TODO: jag vet faktiskt inte om det här gör någonting
    // jag ändrade lite från tidigare implementationen
    while (true)
    {
        Node *n = curr->next;

        delete curr;
        if (n == nullptr)
        {
            break;
        }

        curr = n;
    }
}
