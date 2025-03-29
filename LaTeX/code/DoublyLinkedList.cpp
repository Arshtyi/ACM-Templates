// =================== 双向链表 ===================
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
    // 构造函数和析构函数
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList()
    {
        clear();
    }

    // 清空链表
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

    // 从数组创建链表
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

    // 在末尾插入节点
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

    // 在头部插入节点
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

    // 在指定位置插入节点
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

    // 删除指定值的第一个节点
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
        {
            current = current->next;
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

    // 删除指定位置的节点
    bool removeAt(int position)
    {
        if (!head || position < 0)
            return false;

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

    // 查询值是否存在
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

    // 获取链表长度
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

    // 打印链表（正向）
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

    // 打印链表（反向）
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

    // 链表排序（使用归并排序）
    void sort()
    {
        if (!head || !head->next)
            return;

        // 转换为数组，排序后重建链表
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

    // 合并两个链表
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

    // 拆分链表为两部分
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