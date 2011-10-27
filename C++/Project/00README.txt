Welcome to the readme file for our binomial heap!

The purpose of this project was to write an advanced
data structure, a binomial heap was chosen because of
some of it's unique features and also it's real
applications.

HOW TO RUN THE CODE:
in the directory type cmake .
then type make
then ./bi_heap

enjoy!

ABOUT THE CODE:
A binomial heap has a few less functions than other
data structures, but this is what it can do:
-Insert elements (every insert is a merge)
-Merge heaps
-Return the minimum value in a heap
-Extract the minimum value (not implemented in our program)

There are also some trivial things we can do, such as detect if it's
empty or return the size of the heap / amount of trees in it.

The extract min function was not implemented, because for some
unknown reason the sibling trees are turning out to be null-
which is a bit strange since we can construct it properly and
verify the amount of elements.

Here we have some partially correct code for extract min

In the heap:
template <typename T>
T BinomialHeap<T>::extractMin()
{
    T min_ele = 999999999; // TODO: This is horrible. Please fix!! \(*;_;)/
    int degree;
    BinomialTree<T>* min_tree = NULL;
    tree_t i;
    
    foreach(i, trees)
        if(i != NULL)
            if(i->min() < min_ele)
                min_tree = i;
    
    BinomialHeap<T>* min_heap;
    min_heap = new BinomialHeap();
    min_ele = min_tree->extractMin(min_heap);
    degree = log2(min_tree->size());
    trees[degree] = NULL;
    merge(*min_heap);
    return min_ele;
}

In the tree:
template <typename T>
T BinomialTree<T>::extractMin(BinomialHeap<T>* heap)
{
    T minData = min();
    BinomialTree<T>* tmp_child;
    tmp_child = roots->_child;
    heap->insertTree(tmp_child);
    while(tmp_child->roots->_sibling != NULL)
    {
        tmp_child = tmp_child->roots->_sibling;
        heap->insertTree(tmp_child);
    }

    return minData;
}

The idea is to find the tree with the minimum element in the heap,
using the same process we use usually. Then we make a new heap
and preform extract min on the tree. This -should- give us a new
heap without the minimum element, but alas it doesn't work =(

In conclusion, this was a really fun project. I learned about heaps
and trees and some properties of complex data structures. I also
gained a much better understanding of the templating system in C++

On my own time, I plan to finish this data structure so I can possibly
use it in the future.
