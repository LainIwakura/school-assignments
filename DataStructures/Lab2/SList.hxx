#ifndef SLIST_HXX
#define SLIST_HXX

#include <iostream>
#include <stdexcept>

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
    void print();
    void clear();

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
  SListNode<T>* newNode = new SListNode<T>(val);
  this->first = newNode;
  this->last  = newNode;
  this->size = 1;
}

template <typename T>
void SList<T>::print()
{
  auto cur = this->first;
  do
  {
    std::cout << std::hex << cur << ": " << cur->value << " -> ";
    cur = cur->next;
  } while (cur != nullptr);
  std::cout << "null" << std::endl;
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
    return;
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
  auto newNode = new SListNode<T>(val);
  if (this->size == 0)
  {
    this->first = newNode;
    this->last = newNode;
    ++this->size;
  }
  else
  {
    auto cur = this->first;
    while (cur->next != nullptr) cur = cur->next;
    cur->next = newNode;
    this->last = newNode;
    ++this->size;
  }
}

template <typename T>
void SList<T>::removeLast()
{
  if (this->size == 0) {
    std::cout << "Nothing to remove!\n";
    return;
  }

  if (this->size == 1) {
    delete this->last;
    this->first = nullptr;
    this->last = nullptr;
    this->size = 0;
    return;
  }

  int i = 0;
  auto cur = this->first;
  while (i < (this->size - 2)) {
    cur = cur->next;
    ++i;
  }

  cur->next = nullptr;
  delete this->last;
  this->last = cur;
  --this->size;
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

template <typename T>
void SList<T>::clear()
{
  auto cur = this->first;
  while (cur != nullptr)
  {
    this->first = this->first->next;
    delete cur;
    cur = this->first;
  }

  this->size = 0;
  this->last = nullptr;
  this->first = nullptr;
}

 /* Begin our stack implementation using a linked list.
  */
template <typename T>
class StackList
{
  public:
   StackList();
   StackList(T);

   T top();
   T pop();
   void push(T);
   size_t size() { return this->internalStack.getSize(); }
   bool isEmpty() { return (size() == 0) ? true : false; }
   void clear();

  private:
   SList<T> internalStack;
};

template <typename T>
StackList<T>::StackList()
  : internalStack()
{
}

template <typename T>
StackList<T>::StackList(T val)
  : internalStack(val)
{
}

template <typename T>
T StackList<T>::top()
{
  if (internalStack.getSize() == 0)
    throw std::range_error("top(): Operation not permitted on stack of size 0");
  else
    return this->internalStack.getLast();
}

template <typename T>
T StackList<T>::pop()
{
  if (internalStack.getSize() == 0)
    throw std::range_error("pop: Operation not permitted on stack of size 0");
  else
  {
    T val = this->internalStack.getLast();
    this->internalStack.removeLast();
    return val;
  }
}

template <typename T>
void StackList<T>::push(T val)
{
  this->internalStack.addLast(val);
}

template <typename T>
void StackList<T>::clear()
{
  this->internalStack.clear();
}

/* Begin our queue
 */
template <typename T>
class SQueue
{
  public:
    SQueue();
    SQueue(T);

    T front();
    T dequeue();
    void enqueue(T);
    size_t size();
    bool isEmpty();

  private:
    SList<T> internalQ;
};

template <typename T>
SQueue<T>::SQueue()
  : internalQ()
{
}

template <typename T>
SQueue<T>::SQueue(T val)
  : internalQ(val)
{
}

template <typename T>
T SQueue<T>::front()
{
  return this->internalQ->last->value;
}

template <typename T>
T SQueue<T>::dequeue()
{
  if (internalQ.getSize() == 0) {
    std::cout << "Queue is empty!" << std::endl;
    return 0;
  } else {
    T val = this->internalQ.getLast();
    this->internalQ.removeLast();
    return val;
  }
}

template <typename T>
void SQueue<T>::enqueue(T val)
{
  this->internalQ.addFirst(val);
}

template <typename T>
size_t SQueue<T>::size()
{
  return this->internalQ.getSize();
}

template <typename T>
bool SQueue<T>::isEmpty()
{
  return (this->internalQ.getSize() == 0 ? true : false);
}

#endif
