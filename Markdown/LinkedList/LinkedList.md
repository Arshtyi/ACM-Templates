# 单向链表

```c++
// #include <iostream>
// #include <vector>
// #include <algorithm>
// =================== 单向链表 ===================
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
    // 构造函数和析构函数
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList()
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
            current->next = new Node(arr[i]);
            current = current->next;
        }
    }

    // 在末尾插入节点
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
        {
            current = current->next;
        }
        current->next = newNode;
    }

    // 在头部插入节点
    void prepend(T value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
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

    // 删除指定值的第一个节点
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
        {
            current = current->next;
        }

        if (!current->next)
            return false;

        Node *temp = current->next;
        current->next = current->next->next;
        delete temp;
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

    // 打印链表
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

    // 链表排序（使用归并排序）
    void sort()
    {
        head = mergeSort(head);
    }

    // 合并两个链表
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
        {
            current = current->next;
        }

        current->next = other.head;
        other.head = nullptr;
    }

    // 拆分链表为两部分
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
    // 归并排序辅助函数
    Node *mergeSort(Node *start)
    {
        if (!start || !start->next)
            return start;

        // 找到中间节点
        Node *slow = start;
        Node *fast = start->next;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node *mid = slow->next;
        slow->next = nullptr;

        // 递归排序两部分
        Node *left = mergeSort(start);
        Node *right = mergeSort(mid);

        // 合并两个有序链表
        return mergeSortedLists(left, right);
    }

    // 合并两个有序链表
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
```



# 双向链表

```c++
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
```

# 单向循环链表

```c++
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
```

# 双向循环链表

```c++
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
```

