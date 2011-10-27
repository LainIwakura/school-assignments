#include <iostream>
#include "BinomialHeap.hxx"

using namespace std;

void Trees()
{
    BinomialTree<int> h(5);
    BinomialTree<int> h1(3);
    BinomialTree<int> h2(4);
    BinomialTree<int> h3(2345);
    BinomialTree<int> h4(23948562);
    BinomialTree<int> h5(54);

    cout << "TREE RELATED FUNCTIONS:" << endl;
    cout << "TREE1 (h1) min: " << h1.min() << endl;
    cout << "TREE2 (h2) min: " << h2.min() << endl;
    cout << "TREE3 (h3) min: " << h3.min() << endl;
    cout << "TREE4 (h4) min: " << h4.min() << endl;
    cout << "TREE5 (h5) min: " << h5.min() << endl;

    h1.merge(h3);
    cout << "After merge (h1 with h3): " << h1.min() << endl;
    cout << "Size (h1): " << h1.size() << endl;

    h.merge(h2);
    cout << "After merge (h with h2): " << h.min() << endl;
    cout << "Size (h): " << h.size() << endl;

    h.merge(h1);
    cout << "After merge (h with h1): " << h.min() << endl;
    cout << "Size (h): " << h.size() << endl;

    h4.merge(h3);
    cout << "After merge (h3 with h4): " << h4.min() << endl;
    cout << "Size (h3): " << h4.size() << endl;

    h5.merge(h3);
    cout << "After merge (h5 with h3): " << h5.min() << endl;
    cout << "Size (h5): " << h5.size() << endl;

    h4.merge(h5);
    cout << "After merge (h4 with h5): " << h4.min() << endl;
    cout << "Size (h4): " << h4.size() << endl;

    h4.merge(h);
    cout << "After merge (h4 with h): " << h4.min() << endl;
    cout << "Size (h4): " << h4.size() << endl;
}

int main()
{
    Trees();

    BinomialHeap<int> h1;
    int i = 2;
    while(i < 250)
    {
        BinomialHeap<int> tmp(i++);
        h1.merge(tmp);
    }

    cout << "\nHEAP RELATED FUNCTIONS: " << endl; 
    cout << "Smallest value in the heap: " << h1.min() << endl;
    cout << "Total size of the heap: " << h1.totalSize() << endl;

    return 0;
}
