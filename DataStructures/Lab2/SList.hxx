#ifndef SLIST_HXX
#define SLIST_HXX

#include <cstdlib>

template <typename T>
class SList;

template <typename T>
class SListNode
{
  friend class SList<T>;
  public:
    SListNode();
    SListNode(T);

  private:
    T value;
    SListNode *next;
};

template <typename T>
SListNode<T>::SListNode()
  : value(0), next(nullptr)
{
}

template <typename T>
SListNode<T>::SListNode(T val)
  : value(val), next(nullptr)
{
}

template <typename T>
class SList
{
  public:
    SList();
    SList(T);
    void addFirst(T);
    void removeFirst();
    void addLast(T);
    void removeLast();
    T getFirst();
    T getLast();
    size_t getSize();

  private:
    SListNode<T>* first;
    SListNode<T>* last;
    size_t size;
};

template <typename T>
SList<T>::SList()
  : first(nullptr), last(nullptr), size(0)
{
}

template <typename T>
SList<T>::SList(T val)
{
  auto newNode = new SListNode<T>(val);
  this->first = newNode;
  this->last  = newNode;
  this->size = 1;
}

template <typename T>
void SList<T>::addFirst(T val)
{
  auto newNode = new SListNode<T>(val);
  newNode->next = this->first;
  this->first = newNode;
  ++this->size;
  if (this->size == 1)
    this->last = this->first;
}

template <typename T>
void SList<T>::removeFirst()
{
  if (this->size == 0) {
    std::cout << "Nothing to remove!\n";
    return;
  } else if (this->size == 1) {
    delete this->first;
    this->first = nullptr;
    this->last = nullptr;
    --this->size;
  }

  auto newFirst = this->first->next;
  delete this->first;
  this->first = newFirst;
  --this->size;
}

template <typename T>
T SList<T>::getFirst()
{
  return this->first->value;
}

template <typename T>
void SList<T>::addLast(T val)
{
  auto cur = this->first;
  while (cur->next != nullptr) cur = cur->next;
  this->last->next = cur;
  cur->value = val;
  cur->next = nullptr;
  ++this->size;
}

template <typename T>
void SList<T>::removeLast()
{

}

template <typename T>
T SList<T>::getLast()
{
  return this->last->value;
}

template <typename T>
size_t SList<T>::getSize()
{
  return this->size;
}

#endif
