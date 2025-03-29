// =================== 循环双向链表 ===================
template <typename T>
class CircularDoublyLinkedList
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

public:
    // 构造函数和析构函数
    CircularDoublyLinkedList() : head(nullptr) {}

    ~CircularDoublyLinkedList()
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
        head->next = head;
        head->prev = head;

        Node *current = head;
        for (size_t i = 1; i < arr.size(); i++)
        {
            Node *newNode = new Node(arr[i]);

            newNode->next = head;
            newNode->prev = current;
            current->next = newNode;
            head->prev = newNode;

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
            head->next = head;
            head->prev = head;
            return;
        }

        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
    }

    // 在头部插入节点
    void prepend(T value)
    {
        append(value);     // 添加到末尾
        head = head->prev; // 末尾节点变为头节点
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
            head->prev = head;
            return;
        }

        Node *current = head;
        int count = 0;

        while (count < position && current->next != head)
        {
            current = current->next;
            count++;
        }

        Node *newNode = new Node(value);
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

        // 如果只有一个节点且是要删除的节点
        if (head->next == head && head->data == value)
        {
            delete head;
            head = nullptr;
            return true;
        }

        Node *current = head;
        do
        {
            if (current->data == value)
            {
                // 如果是头节点
                if (current == head)
                {
                    head = head->next;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                return true;
            }
            current = current->next;
        } while (current != head);

        return false;
    }

    // 查询值是否存在
    bool search(T value) const
    {
        if (!head)
            return false;

        Node *current = head;
        do
        {
            if (current->data == value)
                return true;
            current = current->next;
        } while (current != head);

        return false;
    }

    // 获取链表长度
    int size() const
    {
        if (!head)
            return 0;

        int count = 0;
        Node *current = head;
        do
        {
            count++;
            current = current->next;
        } while (current != head);

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
                std::cout << " <-> ";
        } while (current != head);

        std::cout << " <-> (循环回到头部)" << std::endl;
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
    void merge(CircularDoublyLinkedList<T> &other)
    {
        if (!other.head)
            return;
        if (!head)
        {
            head = other.head;
            other.head = nullptr;
            return;
        }

        Node *thisTail = head->prev;
        Node *otherTail = other.head->prev;

        thisTail->next = other.head;
        other.head->prev = thisTail;

        otherTail->next = head;
        head->prev = otherTail;

        other.head = nullptr;
    }

    // 拆分链表
    CircularDoublyLinkedList<T> split(int position)
    {
        CircularDoublyLinkedList<T> newList;
        if (!head || position <= 0 || position >= size())
            return newList;

        Node *current = head;
        int count = 0;

        while (count < position)
        {
            current = current->next;
            count++;
        }

        newList.head = current;

        Node *prevNode = current->prev;
        Node *thisTail = head->prev;

        // 更新原链表
        prevNode->next = head;
        head->prev = prevNode;

        // 更新新链表
        thisTail->next = newList.head;
        newList.head->prev = thisTail;

        return newList;
    }
};