#include <iostream>
#include <sstream>
#include <stdexcept>
#include "LinkedList.hpp"

// Copy constructor
LinkedList::LinkedList(const LinkedList &b) : size{0}, head{nullptr}, tail{nullptr}
{ // This doesn't copy, it just creates a new LinkedList that points to the same values.
    size = 0;

    for (int i{0}; i < b.size; i++)
    {
        this->push_back(b.get(i));
    }
}

LinkedList &LinkedList::operator=(const LinkedList &b)
{
    if (this == &b)
        return *this;

    // Reset list
    empty_list();

    // Set default variables
    size = 0;
    head = nullptr;
    tail = nullptr;

    for (int i{0}; i < b.size; i++)
    {
        this->push_back(b.get(i));
    }

    return *this;
}

void LinkedList::push_front(const int a)
{
    Node *old = head; // Store old head

    head = new Node{a, nullptr, old}; // Create new head node

    // If list is empty, set new head as tail too
    if (is_empty())
    {
        tail = head;
    }
    else // If list isn't empty, point prev head to new head
    {
        old->prev = head;
    }

    size++;
}

void LinkedList::push_back(const int a)
{
    Node *old = tail; // Store old tail

    tail = new Node{a, old, nullptr}; // Create new tail node

    // If list is empty, set new tail as head too
    if (is_empty())
    {
        head = tail;
    }
    else // If list isn't empty, point old tail to new tail
    {
        old->next = tail;
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

// Returns the value of the nth node
int LinkedList::get(const unsigned int n) const
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

    while (curr != nullptr)
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
    // Pointer to head, ie adress of head
    Node *curr = head; // curr is of pointer type

    if (size == 0)
        return;

    while (true)
    {
        // Get pointer of next node in line
        Node *n = curr->next; // curr-> is the same as (*curr)

        delete curr;      // delete the value at curr
        if (n == nullptr) // check if end of list and break
        {
            break;
        }

        // otherwise, continue with n as curr
        curr = n;
    }
}
