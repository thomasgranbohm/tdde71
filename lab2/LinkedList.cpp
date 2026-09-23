#include <iostream>
#include <sstream>
#include <stdexcept>
#include "LinkedList.hpp"

// Copy constructor
LinkedList::LinkedList(LinkedList const &b) : size{0}, head{nullptr}, tail{nullptr}
{
    for (unsigned int i{0}; i < b.size; i++)
    {
        this->push_back(b.get(i));
    }
}

// Copy assignment
LinkedList &LinkedList::operator=(LinkedList const &b)
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

// Move constructor
LinkedList::LinkedList(LinkedList &&other) : size{0}, head{nullptr}, tail{nullptr}
{
    head = other.head;
    tail = other.tail;
    size = other.size;
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

// Move assignment
LinkedList &LinkedList::operator=(LinkedList &&other)
{
    if (this == &other)
    {
        return *this;
    }
    LinkedList::Node *t_head{other.head};
    LinkedList::Node *t_tail{other.tail};
    unsigned int t_size{other.size};

    other.head = head;
    other.tail = tail;
    other.size = size;

    other.empty_list();

    head = t_head;
    tail = t_tail;
    size = t_size;

    return *this;
}

void LinkedList::push_front(const int a)
{
    LinkedList::Node *old{head}; // Store old head

    head = new LinkedList::Node{a, nullptr, old}; // Create new head node

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
    LinkedList::Node *old{tail}; // Store old tail

    tail = new LinkedList::Node{a, old, nullptr}; // Create new tail node

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
    int value{head->value};
    LinkedList::Node *next_head{head->next};

    delete head;
    head = next_head;
    head->prev = nullptr;

    size--;

    return value;
}

int LinkedList::pop_back()
{
    int value{tail->value};
    LinkedList::Node *next_tail{tail->prev};

    delete tail;
    tail = next_tail;
    tail->next = nullptr;

    size--;

    return value;
}

// Returns the value of the nth node
int LinkedList::get(const unsigned int n) const
{
    if (n > size - 1)
    {
        throw std::out_of_range("n too big");
    }

    LinkedList::Node curr{*head};

    for (unsigned int i{0}; i < n; i++)
    {
        curr = *curr.next;
    }

    return curr.value;
}

int LinkedList::front() const
{
    if (head == nullptr)
    {
        throw std::out_of_range("list empty");
    }

    return head->value;
}
int LinkedList::back() const
{
    if (tail == nullptr)
    {
        throw std::out_of_range("list empty");
    }

    return tail->value;
}

std::string LinkedList::to_string() const
{
    std::stringstream ss{};

    ss << '[';

    LinkedList::Node *curr{head};

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
    LinkedList::Node *curr{head}; // curr is of pointer type

    while (true)
    {
        // Get pointer of next node in line
        LinkedList::Node *n{curr->next}; // curr-> is the same as (*curr)

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

LinkedList::Node *LinkedList::get_middle_node(LinkedList::Node *head) const
{
    if (head == nullptr)
        throw std::logic_error("Do not pass nullptr to get_middle_node (in LinkedList.cpp)!");
    LinkedList::Node *slow{head};
    LinkedList::Node *fast{head};
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

LinkedList::Node *LinkedList::merge(LinkedList::Node *head, LinkedList::Node *head2)
{
    LinkedList::Node *new_head{};
    LinkedList::Node *new_tail{};

    while (head != nullptr || head2 != nullptr)
    {
        LinkedList::Node *chosen{}; // Element chosen to be "added" to the new (merged) list

        if (head == nullptr) // Choose next element of list 2 if list 1 is empty
        {
            chosen = head2;
            head2 = head2->next; // "Move forward to next element of list 2"
        }
        else if (head2 == nullptr) // Choose next element of list 1 if list 2 is empty
        {
            chosen = head;
            head = head->next; // "Move forward to next element of list 1"
        }

        // If both lists aren't empty, choose the element with lowest value
        else if (head->value <= head2->value)
        {
            chosen = head;
            head = head->next; // "Move forward to next element of list 1"
        }
        else
        {
            chosen = head2;
            head2 = head2->next; // "Move forward to next element of list 2"
        }

        // Make the chosen element new head if new head has not yet been chosen
        if (new_head == nullptr)
        {
            new_head = chosen;
        }

        // Otherwise add the new element to the end of the list
        else
        {
            new_tail->next = chosen; // "Add" new node to the list
            chosen->prev = new_tail; // Set its prev value
        }
        new_tail = chosen; // Set tail to the new node
    }

    new_tail->next = nullptr; // Set tail's next value to nullptr

    return new_head; // Return head of new list
}

LinkedList::Node *LinkedList::merge_sort(LinkedList::Node *head)
{
    if (head->next == nullptr) // Base case: the list with head node 'head' has only one element
        return head;

    // Find "middle" node in the linked list
    //                                   middle
    // example - 4 nodes: nullptr <- a <-> b <-> c <-> d -> nullptr
    //                                         middle
    // example - 5 nodes: nullptr <- a <-> b <-> c <-> d <-> e -> nullptr
    LinkedList::Node *middle{get_middle_node(head)};

    // "Split list in half"          head                                     head2
    // example - 4 nodes:    nullptr <- a <-> b -> nullptr        |   nullptr <- c <-> d -> nullptr
    // example - 5 nodes:    nullptr <- a <-> b <-> c -> nullptr  |   nullptr <- d <-> e -> nullptr
    LinkedList::Node *head2{middle->next}; // Head node of the other "list half"
    head2->prev = nullptr;                 // Separate the lists
    middle->next = nullptr;

    head = merge_sort(head);
    head2 = merge_sort(head2);

    return merge(head, head2);
}

// Merge sort
void LinkedList::sort()
{
    if (size < 2)
        return;

    head = merge_sort(head);

    // Update the tail member
    tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
}
