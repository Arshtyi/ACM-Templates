template <typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };
    Node *head;
    Node *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList()
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
        tail = nullptr;
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
            Node *newNode = new Node(arr[i]);
            current->next = newNode;
            newNode->prev = current;
            current = newNode;
        }
        tail = current;
    }
    void append(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    void prepend(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
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
        while (current && count < position)
        {
            current = current->next;
            count++;
        }
        if (!current)
        { // 如果位置超出链表长度，在末尾插入
            append(value);
            return;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    bool remove(T value)
    {
        if (!head)
            return false;
        if (head->data == value)
        {
            Node *temp = head;
            head = head->next;
            if (head)
                head->prev = nullptr;
            else
                tail = nullptr;
            delete temp;
            return true;
        }
        Node *current = head;
        while (current && current->data != value)
            current = current->next;
        if (!current)
            return false;
        if (current == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
            return true;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        return true;
    }
    bool removeAt(int position)
    {
        if (!head || position < 0)

            if (position == 0)
            {
                Node *temp = head;
                head = head->next;
                if (head)
                    head->prev = nullptr;
                else
                    tail = nullptr;
                delete temp;
                return true;
            }
        Node *current = head;
        int count = 0;
        while (current && count < position)
        {
            current = current->next;
            count++;
        }
        if (!current)
            return false;
        if (current == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
            return true;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
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
                std::cout << " <-> ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    void printReverse() const
    {
        Node *current = tail;
        while (current)
        {
            std::cout << current->data;
            if (current->prev)
                std::cout << " <-> ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
    void sort()
    {
        if (!head || !head->next)
            return;
        std::vector<T> arr;
        Node *current = head;
        while (current)
        {
            arr.push_back(current->data);
            current = current->next;
        }
        std::sort(arr.begin(), arr.end());
        createFromArray(arr);
    }
    void merge(DoublyLinkedList<T> &other)
    {
        if (!other.head)
            return;
        if (!head)
        {
            head = other.head;
            tail = other.tail;
            other.head = other.tail = nullptr;
            return;
        }
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
        other.head = other.tail = nullptr;
    }
    DoublyLinkedList<T> split(int position)
    {
        DoublyLinkedList<T> newList;
        if (position <= 0 || !head)
            return newList;

        if (position >= size())
            return newList;
        Node *current = head;
        int count = 0;
        while (current && count < position)
        {
            current = current->next;
            count++;
        }
        if (!current)
            return newList;
        newList.head = current;
        newList.tail = tail;
        tail = current->prev;
        tail->next = nullptr;
        current->prev = nullptr;
        return newList;
    }
};