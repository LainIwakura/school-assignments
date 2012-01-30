#include <iostream>
#include "SList.hxx"

using namespace std;

int main()
{
  SList<int> myList(5);
  myList.addFirst(3);

  cout << myList.getFirst() << endl;
  cout << myList.getLast() << endl;
  myList.addFirst(4);

  myList.removeFirst();
  cout << myList.getFirst() << endl;
  myList.addFirst(2);
  cout << myList.getFirst() << endl;
  cout << myList.getLast() << endl;
  cout << myList.getSize() << endl;
  return 0;
}
