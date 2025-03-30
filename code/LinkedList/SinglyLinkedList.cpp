// #include <iostream>
// #include <vector>
// #include <algorithm>
template <typename T>
class SinglyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(T value) : data(value), next(nullptr) {}
    };
    Node *head;

public:
    SinglyLinkedList() : head(nullptr) {}
    ~SinglyLinkedList()
    {
        clear();
    }
    void clear()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void createFromArray(const std::vector<T> &arr)
    {
        clear();
        if (arr.empty())
            return;
        head = new Node(arr[0]);
        Node *current = head;
        for (size_t i = 1; i < arr.size(); i++)
        {
            current->next = new Node(arr[i]);
            current = current->next;
        }
    }
    void append(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            return;
        }
        Node *current = head;
        while (current->next)
            current = current->next;
        current->next = newNode;
    }
    void prepend(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    void insertAt(int position, T value)
    {
        if (position <= 0)
        {
            prepend(value);
            return;
        }
        Node *newNode = new Node(value);
        Node *current = head;
        int count = 0;
        while (current && count < position - 1)
        {
            current = current->next;
            count++;
        }
        if (!current)
        { // 如果位置超出链表长度，在末尾插入
            append(value);
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    bool remove(T value)
    {
        if (!head)
            return false;
        if (head->data == value)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node *current = head;
        while (current->next && current->next->data != value)
            current = current->next;
        if (!current->next)
            return false;
        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    bool removeAt(int position)
    {
        if (!head || position < 0)
            return false;
        if (!position)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        Node *current = head;
        int count = 0;
        while (current && count < position - 1)
        {
            current = current->next;
            count++;
        }
        if (!current || !current->next)
            return false;
        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    bool search(T value) const
    {
        Node *current = head;
        while (current)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }
    int size() const
    {
        int count = 0;
        Node *current = head;
        while (current)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    void print() const
    {
        Node *current = head;
        while (current)
        {
            std::cout << current->data;
            if (current->next)
                std::cout << " -> ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    void sort()
    {
        head = mergeSort(head);
    }
    void merge(SinglyLinkedList<T> &other)
    {
        if (!other.head)
            return;
        if (!head)
        {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node *current = head;
        while (current->next)
            current = current->next;
        current->next = other.head;
        other.head = nullptr;
    }
    SinglyLinkedList<T> split(int position)
    {
        SinglyLinkedList<T> newList;
        if (position <= 0 || !head)
            return newList;
        if (position >= size())
            return newList;
        Node *current = head;
        int count = 0;
        while (current && count < position - 1)
        {
            current = current->next;
            count++;
        }
        if (!current || !current->next)
            return newList;
        newList.head = current->next;
        current->next = nullptr;
        return newList;
    }

private:
    Node *mergeSort(Node *start)
    {
        if (!start || !start->next)
            return start;
        Node *slow = start;
        Node *fast = start->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node *mid = slow->next;
        slow->next = nullptr;
        Node *left = mergeSort(start);
        Node *right = mergeSort(mid);
        return mergeSortedLists(left, right);
    }
    Node *mergeSortedLists(Node *a, Node *b)
    {
        if (!a)
            return b;
        if (!b)
            return a;
        Node *result = nullptr;
        if (a->data <= b->data)
        {
            result = a;
            result->next = mergeSortedLists(a->next, b);
        }
        else
        {
            result = b;
            result->next = mergeSortedLists(a, b->next);
        }
        return result;
    }
};