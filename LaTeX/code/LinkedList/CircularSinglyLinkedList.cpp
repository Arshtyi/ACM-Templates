template <typename T>
class CircularSinglyLinkedList
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
    CircularSinglyLinkedList() : head(nullptr) {}
    ~CircularSinglyLinkedList()
    {
        clear();
    }
    void clear()
    {
        if (!head)
            return;
        Node *current = head->next;
        while (current != head)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }
    void createFromArray(const std::vector<T> &arr)
    {
        clear();
        if (arr.empty())
            return;
        head = new Node(arr[0]);
        head->next = head; // 循环指向自己
        Node *current = head;
        for (size_t i = 1; i < arr.size(); i++)
        {
            Node *newNode = new Node(arr[i]);
            newNode->next = head; // 指向头节点
            current->next = newNode;
            current = newNode;
        }
    }
    void append(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            head->next = head; // 指向自己
            return;
        }
        Node *current = head;
        while (current->next != head)
            current = current->next;
        newNode->next = head;
        current->next = newNode;
    }
    void prepend(T value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
            head->next = head; // 指向自己
            return;
        }
        newNode->next = head;
        Node *current = head;
        while (current->next != head)
            current = current->next;
        current->next = newNode;
        head = newNode;
    }
    void insertAt(int position, T value)
    {
        if (position <= 0)
        {
            prepend(value);
            return;
        }
        if (!head)
        {
            Node *newNode = new Node(value);
            head = newNode;
            head->next = head;
            return;
        }
        Node *current = head;
        int count = 0;
        while (count < position - 1 && current->next != head)
        {
            current = current->next;
            count++;
        }
        Node *newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }
    bool remove(T value)
    {
        if (!head)
            return false;
        if (head->next == head && head->data == value)
        {
            delete head;
            head = nullptr;
            return true;
        }
        if (head->data == value)
        {
            Node *current = head;
            while (current->next != head)
                current = current->next;
            Node *temp = head;
            head = head->next;
            current->next = head;
            delete temp;
            return true;
        }
        Node *current = head;
        while (current->next != head && current->next->data != value)
            current = current->next;
        if (current->next == head)
            return false;
        Node *temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }
    bool search(T value) const
    {
        if (!head)
            return false;
        if (head->data == value)
            return true;
        Node *current = head->next;
        while (current != head)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }
    int size() const
    {
        if (!head)
            return 0;
        int count = 1;
        Node *current = head->next;
        while (current != head)
        {
            count++;
            current = current->next;
        }
        return count;
    }
    void print() const
    {
        if (!head)
        {
            std::cout << "Empty list" << std::endl;
            return;
        }
        Node *current = head;
        do
        {
            std::cout << current->data;
            current = current->next;
            if (current != head)
                std::cout << " -> ";
        } while (current != head);
        std::cout << " -> (循环回到头部)" << std::endl;
    }
    void sort()
    {
        if (!head || head->next == head)
            return;
        std::vector<T> arr;
        Node *current = head;
        do
        {
            arr.push_back(current->data);
            current = current->next;
        } while (current != head);
        std::sort(arr.begin(), arr.end());
        createFromArray(arr);
    }
    void merge(CircularSinglyLinkedList<T> &other)
    {
        if (!other.head)
            return;
        if (!head)
        {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node *thisTail = head;
        while (thisTail->next != head)
            thisTail = thisTail->next;
        Node *otherTail = other.head;
        while (otherTail->next != other.head)
            otherTail = otherTail->next;
        thisTail->next = other.head;
        otherTail->next = head;
        other.head = nullptr;
    }
    CircularSinglyLinkedList<T> split(int position)
    {
        CircularSinglyLinkedList<T> newList;
        if (!head || position <= 0 || position >= size())
            return newList;
        Node *current = head;
        int count = 0;
        while (count < position - 1)
        {
            current = current->next;
            count++;
        }
        newList.head = current->next;
        Node *newTail = newList.head;
        while (newTail->next != head)
            newTail = newTail->next;
        newTail->next = newList.head;
        current->next = head;
        return newList;
    }
};