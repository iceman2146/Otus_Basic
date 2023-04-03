#pragma once

template <typename T>
class OneWayContainer
{
    struct Node
    {
        Node *next; // ukazatel na sleduushuu nodu
        T data;     // kakieto dannie
        Node() : next{nullptr} {}
        Node(const T &value) : next{nullptr}, data{value} {}
    };

    size_t m_size; // kol-vo nod
    Node *m_first; // ukazatel na pervuu nodu
    Node *m_last;  // ukazatel na poslednuu nodu

public:
    OneWayContainer() : m_size{0}, m_first{nullptr}, m_last{nullptr}
    {
        std::cout << "OneWayContainer constructor" << std::endl;
    }

    OneWayContainer(const OneWayContainer &other)
    {
        if (other.m_first != nullptr)
        {

            Node *other_ptr_toCopy = other.m_first;
            Node *otherPtrTemp = nullptr;

            while (other_ptr_toCopy != nullptr)
            {
                otherPtrTemp = new Node(other_ptr_toCopy->data);

                if (m_first == nullptr)
                {
                    m_first = otherPtrTemp;
                    m_last = otherPtrTemp;
                }
                else
                {
                    m_last->next = otherPtrTemp;
                    m_last = otherPtrTemp;
                }

                other_ptr_toCopy = other_ptr_toCopy->next;
            }

            m_size = other.m_size;
        }
        std::cout << "OneWayContainer copy constructor" << std::endl;
    }

    OneWayContainer(OneWayContainer &&other)
    {
        m_first = other.m_first;
        other.m_first = nullptr;

        m_last = other.m_last;
        other.m_last = nullptr;

        m_size = other.m_size;
        m_size = 0;
        std::cout << "OneWayContainer move constructor" << std::endl;
    }

    ~OneWayContainer()
    {
        delete[] m_first;
        delete[] m_last;
        std::cout << " OneWayContainer destructor" << std::endl;
    }

    OneWayContainer &operator=(const OneWayContainer &rhs)
    {
        OneWayContainer temp{rhs};
        Node *last = m_last;
        m_last = temp.m_last;
        temp.m_last = last;

        Node *first = m_first;
        m_first = temp.m_first;
        temp.m_first = first;

        size_t size = m_size;
        m_size = temp.m_size;
        temp.m_size = size;

        return *this;
    }

    OneWayContainer &operator=(OneWayContainer &&other)
    {
        OneWayContainer temp{std::move(other)};
        return *this = temp;
    }
    const T operator[](size_t index) const
    {
        size_t i = 0;
        Node *first = m_first;
        while (i != index)
        {
            first = first->next;
            ++i;
        }
        return first->data;
    }
    size_t size() const { return m_size; }

    bool push_back(const T &value)
    {
        Node *new_node = new Node{};
        new_node->next = nullptr;
        new_node->data = value;

        if (m_size == 0)
        {
            m_first = std::move(new_node);
        }

        if (m_size >= 1)
        {
            m_last->next = std::move(new_node);
        }
        m_last = std::move(new_node);

        ++m_size;

        return true;
    }

    bool insert(size_t pos, const T &value)
    {
        Node *first = std::move(m_first);
        if (pos == 0)
        {
            Node *new_node = new Node{};
            new_node->next = first;
            new_node->data = std::move(value);
            m_first = std::move(new_node);
        }
        else
        {
            size_t i = 0;
            while (i != (pos - 1))
            {
                first = first->next;
                ++i;
            }
            Node *prev = std::move(first);
            first = first->next;

            Node *new_node = new Node{};
            new_node->next = first;
            new_node->data = std::move(value);
            prev->next = std::move(new_node);
        }

        ++m_size;

        return true;
    }

    bool erase(const size_t pos)
    {
        Node *first = m_first;
        if (pos >= m_size)
        {
            return false;
        }

        else
        {
            size_t i = 1;
            while (i != (pos - 1))
            {
                first = first->next;
                ++i;
            }

            Node *prev = std::move(first);
            Node *del = first->next;
            first = del->next;
            prev->next = std::move(first);

            delete[] del;

            --m_size;
        }

        return true;
    }

    bool isExist() const
    {
        for (Node *elem = m_first; elem != m_last->next; elem = elem->next)
        {
            std::cout << elem->data << ' ';
        }
        return true;
    }

    bool is_empty() const
    {
        if (m_size == 0)
        {
            std::cout << "Error: container is empty" << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    struct Iterator
    {
        Node *m_one;
        Iterator(Node *one) : m_one{one} {}

        T &operator*() const { return m_one->data; }
        T &get() const { return m_one->data; }

        Iterator &operator++()
        {
            m_one = m_one->next;
            return *this;
        }

        Iterator &operator++(int)
        {
            Iterator it(*this);
            (*this) = m_one->next;
            return *this;
        }

        bool operator==(const Iterator &it) const { return m_one == it.m_one; }

        bool operator!=(const Iterator &it) const { return !(*this == it); }
    };

    Iterator begin() const { return m_first; }

    Iterator end() const { return {nullptr}; }
};