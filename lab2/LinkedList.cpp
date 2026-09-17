#include <iostream>
#include <sstream>
#include <stdexcept>
#include "LinkedList.hpp"

// Copy constructor
LinkedList::LinkedList(const LinkedList &b) : size{0}, head{nullptr}, tail{nullptr}
{
    for (unsigned int i{0}; i < b.size; i++)
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

    for (unsigned int i{0}; i < b.size; i++)
    {
        this->push_back(b.get(i));
    }

    return *this;
}

LinkedList::LinkedList(LinkedList &&other) : size{0}, head{nullptr}, tail{nullptr}
{
    head = other.head;
    tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

LinkedList &LinkedList::operator=(LinkedList &&other)
{
    if (this == &other)
    {
        return *this;
    }
    Node *t_head = other.head;
    Node *t_tail = other.tail;
    unsigned int t_size = other.size;

    other.head = this->head;
    other.tail = this->tail;
    other.size = this->size;

    other.empty_list();

    this->head = t_head;
    this->tail = t_tail;
    this->size = t_size;

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

    for (unsigned int i{0}; i < n; i++)
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
    if (is_empty())
        return;

    // Pointer to head, ie adress of head
    Node *curr = head; // curr is of pointer type

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

    size = 0;
    head = nullptr;
    tail = nullptr;
}

void swap_nodes(Node *node1, Node *node2)
{ // Kan vara fel
    node1->next = node2->next;
    node2->prev = node1->prev;

    if (node1->prev != nullptr)
    {
        node1->prev->next = node2;
    }
    if (node2->next != nullptr)
    {
        node2->next->prev = node1;
    }

    node1->prev = node2;
    node2->next = node1;
}

void LinkedList::bubble_sort()
{
    if (is_empty())
        return;

    bool has_swapped = false;

    do
    {
        has_swapped = false;
        Node *current = head;
        Node *next = current->next;
        while (next != nullptr)
        {
            if (current->value > next->value)
            {
                if (current == head)
                {
                    head = next;
                }
                else if (next == tail)
                {
                    tail = current;
                }

                swap_nodes(current, next);

                has_swapped = true;
            }
            else
            {
                current = next;
            }
            next = current->next;
        }
    } while (has_swapped);
}
