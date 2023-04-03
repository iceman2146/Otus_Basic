#pragma once

template <typename T>
class SequenceContainer
{

  size_t m_size; // kol-vo elementov
  size_t m_cap;  // emkost konteinera
  T *m_region{}; // ukazatel na pervii element

public:
  SequenceContainer() : m_size{0}, m_cap{0}, m_region{nullptr} // def const
  {
    std::cout << "SequenceContainer constructor" << std::endl;
  }

  SequenceContainer(const SequenceContainer &other)
  {
    std::cout << "SequenceContainer copy constructor" << std::endl;
    if (other.m_region != nullptr)
    {
      m_region = new T[other.m_cap];
      m_cap = other.m_cap;

      for (size_t i = 0; i < other.m_size; ++i)
      {
        m_region[i] = other.m_region[i];
      }

      m_size = other.m_size;
    }
  }

  SequenceContainer(SequenceContainer &&other)
  {
    m_cap = other.m_cap;
    other.m_cap = 0;

    m_size = other.m_size;
    other.m_size = 0;

    m_region = other.m_region;
    other.m_region = nullptr;
    std::cout << "SequenceContainer move constructor" << std::endl;
  }

  ~SequenceContainer()
  {
    delete[] m_region;
    std::cout << "SequenceContainer destructor" << std::endl;
    return;
  }

  SequenceContainer &operator=(const SequenceContainer &rhs)
  {
    std::cout << "SequenceContainer::operator=" << std::endl;
    SequenceContainer temp{rhs};
    if ((this != &temp) && (temp.m_region != nullptr))
    {
      clr();

      T *data = m_region;
      m_region = temp.m_region;
      temp.m_region = data;

      size_t size = m_size;
      m_size = temp.m_size;
      temp.m_size = size;

      size_t cap = m_cap;
      m_cap = temp.m_cap;
      temp.m_cap = cap;
    }

    return *this;
  }

  SequenceContainer &operator=(SequenceContainer &&rhs)
  {
    std::cout << "&&SequenceContainer::operator=" << std::endl;
    SequenceContainer temp{std::move(rhs)};
    return *this = temp;
  }

  size_t size() const { return m_size; }
  size_t capacity() const { return m_cap; }

  bool push_back(const T &val)
  {
    if (m_size < m_cap)
    {
      m_region[m_size] = std::move(val);
      ++m_size;
    }
    else
    {
      T *new_region = new T[((m_size + 1) * 2)];
      m_cap = std::move(((m_size + 1) * 2));

      for (size_t i = 0; i < m_size; ++i)
      {
        new_region[i] = m_region[i];
      }

      new_region[m_size] = std::move(val);
      delete[] m_region;
      m_region = std::move(new_region);

      ++m_size;
    }

    return true;
  }
  void clr()
  {
    if (m_region != nullptr)
    {
      for (size_t i = 0; i < m_size; ++i)
      {
        m_region[i].~T(); 
      }

      delete[] m_region;
      m_region = nullptr;
    }

    m_cap = 0;
    m_size = 0;
  }
  bool insert(const size_t &pos, const T &val)
  {
    if (m_size < m_cap)
    {
      for (size_t i = m_size; i != pos; --i)
      {
        m_region[i] = m_region[i - 1];
      }

      m_region[pos] = std::move(val);
      ++m_size;
    }
    else
    {
      T *new_region = new T[((m_size + 1) * 2)];
      m_cap = std::move(((m_size + 1) * 2));

      for (size_t i = 0; i < pos; ++i)
      {
        new_region[i] = m_region[i];
      }

      for (size_t i = m_size; i != pos; --i)
      {
        new_region[i] = m_region[i - 1];
      }

      new_region[pos] = std::move(val);

      delete[] m_region;
      m_region = std::move(new_region);
      ++m_size;
    }
    return true;
  }

  bool erase(const size_t pos)
  {
    if (pos >= m_size)
    {
      return false;
    }

    for (size_t i = pos - 1; i < m_size + 1; ++i)
    {
      m_region[i] = m_region[i + 1];
    }
    --m_size;

    return true;
  }

  bool is_empty() const
  {
    if (m_size == 0)
    {
      std::cout << "container is empty" << std::endl;
      return true;
    }
    else
    {
      return false;
    }
  }

  struct Iterator
  {
    Iterator(const size_t index, SequenceContainer &container)
        : m_index(index), m_cont(&container) {}

    explicit Iterator(const size_t size) : m_index(size) {}

    T &get() { return (*m_cont)[m_index]; }
    T &operator*() { return (*m_cont)[m_index]; }

    Iterator &operator++()
    {
      m_index++;
      return *this;
    }
    Iterator &operator++(int)
    {
      Iterator it(*this);
      ++(*this);
      return *this;
    }

    bool operator==(const Iterator &it) const { return m_index == it.m_index; }

    bool operator!=(const Iterator &it) const { return !(*this == it); }

  private:
    size_t m_index = 0;
    SequenceContainer *m_cont = nullptr;
  };

  Iterator begin() { return Iterator{0, *this}; }

  Iterator end() const { return Iterator{m_size}; }

  T &operator[](size_t i) { return m_region[i]; }
};
