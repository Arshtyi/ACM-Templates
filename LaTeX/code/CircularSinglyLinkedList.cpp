// =================== 循环单向链表 ===================
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
    // 构造函数和析构函数
    CircularSinglyLinkedList() : head(nullptr) {}

    ~CircularSinglyLinkedList()
    {
        clear();
    }

    // 清空链表
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

    // 从数组创建链表
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

    // 在末尾插入节点
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
        {
            current = current->next;
        }

        newNode->next = head;
        current->next = newNode;
    }

    // 在头部插入节点
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
        {
            current = current->next;
        }

        current->next = newNode;
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

    // 删除指定值的第一个节点
    bool remove(T value)
    {
        if (!head)
            return false;

        // 如果只有一个节点且它是要删除的节点
        if (head->next == head && head->data == value)
        {
            delete head;
            head = nullptr;
            return true;
        }

        // 如果头节点是要删除的节点
        if (head->data == value)
        {
            Node *current = head;
            while (current->next != head)
            {
                current = current->next;
            }

            Node *temp = head;
            head = head->next;
            current->next = head;
            delete temp;
            return true;
        }

        // 其他情况
        Node *current = head;
        while (current->next != head && current->next->data != value)
        {
            current = current->next;
        }

        if (current->next == head)
            return false;

        Node *temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    // 查询值是否存在
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

    // 获取链表长度
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

    // 打印链表
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

    // 链表排序
    void sort()
    {
        if (!head || head->next == head)
            return;

        // 转换为数组，排序后重建链表
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

    // 合并两个循环链表
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
        {
            thisTail = thisTail->next;
        }

        Node *otherTail = other.head;
        while (otherTail->next != other.head)
        {
            otherTail = otherTail->next;
        }

        thisTail->next = other.head;
        otherTail->next = head;

        other.head = nullptr;
    }

    // 拆分链表
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
        {
            newTail = newTail->next;
        }

        newTail->next = newList.head;
        current->next = head;

        return newList;
    }
};