#ifndef __BINOMIAL_HEAP_HXX
#define __BINOMIAL_HEAP_HXX

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <stdexcept>
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

using namespace std;

template <typename T>
class Node
{
    public:
        T _data;
        BinomialTree<T>* _parent;
        BinomialTree<T>* _child;
        BinomialTree<T>* _sibling;

        Node(T const&, BinomialTree<T>*, BinomialTree<T>*, BinomialTree<T>*);
};

template <typename T>
Node<T>::Node(T const& data, Node* parent, Node* child, Node* sibling)
    : _data(data), _parent(parent), _child(child), _sibling(sibling)
{
}

template <typename T>
class BinomialTree
{
    protected:
        typedef Node<T>* node_t;

    public:
        BinomialTree(T);
        BinomialTree(vector<node_t>);
        BinomialTree(BinomialTree const&);
        ~BinomialTree();

        const T& min();
        T& extractMin();
        void merge(BinomialTree&);
        size_t size() const;

        BinomialTree& operator =(BinomialTree const&);

    private:
        void DestroyTree(node_t);
        size_t tree_depth;
        vector<node_t> roots;
};

template <typename T>
BinomialTree<T>::BinomialTree(T data)
    : tree_depth(0)
{
    Node<T>* node;
    node = new Node<T>(data, NULL, NULL, NULL);
    roots.push_back(node);
}

template <typename T>
BinomialTree<T>::BinomialTree(vector<node_t> nodes)
    : roots(nodes.roots)
{
}

template <typename T>
BinomialTree<T>::BinomialTree(BinomialTree const& other)
    : tree_depth(other.tree_depth), roots(other.roots)
{
}

template <typename T>
BinomialTree<T>::~BinomialTree()
{
}

template <typename T>
const T& BinomialTree<T>::min()
{
    Node<T>* min = roots[0]; 
    return min->_data;
}

template <typename T>
size_t BinomialTree<T>::size() const
{
    return pow(2,tree_depth);
}

template <typename T>
BinomialTree<T>& BinomialTree<T>::operator =(BinomialTree<T> const& tree)
{
    roots.clear();
    foreach(node_t i, tree.roots)
        roots.push_back(i);
    return *this;
}

template <typename T>
T& BinomialTree<T>::extractMin()
{
    T minData = min();
    
    node_t temp_child = NULL;
    node_t child = roots[0]->_child;
    vector<BinomialTree<T> > trees;
    vector<node_t> nodes;

    do
    {
        temp_child = child->_sibling;
        child->_sibling = NULL;
        child->_parent = NULL;
        nodes.push_back(child);
        child = temp_child;
    }
    while(child != NULL);
}

template <typename T>
void BinomialTree<T>::merge(BinomialTree& other)
{
    try
    {
        if(other.tree_depth != tree_depth)
            // It's sort of a range error...
            throw range_error("DEPTHS_NOT_EQUAL");
    }

    catch(range_error const& e)
    {
        cerr << e.what() << endl;
    }

    if(other.roots[0]->_data < roots[0]->_data)
    {
        roots[0]->_parent = other.roots[0];
        roots[0]->_sibling = other.roots[0]->_child;
        other.roots[0]->_child = roots[0];
        copy(roots.begin(), roots.end(), back_inserter(other.roots));
        roots = other.roots;
    }
    else
    {
        other.roots[0]->_parent = roots[0];
        other.roots[0]->_sibling = roots[0]->_child;
        roots[0]->_child = other.roots[0];
        copy(other.roots.begin(), other.roots.end(), back_inserter(roots));
    }
    tree_depth++;
}

template <typename T>
class BinomialHeap
{
    protected:
        typedef BinomialTree<T>* tree_t;

    public:
        // Constructors / Deconstructors
        BinomialHeap();
        BinomialHeap(T);
        BinomialHeap(BinomialHeap const&);

        // Basic functions you'd want for this data structure
        T min();
        T extractMin();
        void merge(BinomialHeap&);
        void merge(BinomialTree<T>&);
        bool isEmpty() const;
        size_t size() const;
        size_t totalSize() const;

        BinomialHeap& operator =(BinomialTree<T> const&);

    private:
        void insertTree(BinomialTree<T>*);
        // Variables only to be used by this class
        size_t _size;
        vector<tree_t> trees;
};

template <typename T>
BinomialHeap<T>::BinomialHeap()
    : _size(0)
{
    trees.resize(32);
}

template <typename T>
BinomialHeap<T>::BinomialHeap(T data)
    : _size(1)
{
    trees.resize(32);
    BinomialTree<T>* tmp;
    tmp = new BinomialTree<T>(data);
    trees[0] = tmp;
}

template <typename T>
BinomialHeap<T>::BinomialHeap(BinomialHeap<T> const& heap)
    : _size(heap._size), trees(heap.trees)
{
}

template <typename T>
bool BinomialHeap<T>::isEmpty() const
{
    return size() == 0 ? true : false;
}

template <typename T>
size_t BinomialHeap<T>::size() const
{
    return _size;
}

template <typename T>
size_t BinomialHeap<T>::totalSize() const
{
    size_t total = 0;
    foreach(tree_t i, trees)
        if(i != NULL)
            total += i->size();
    
    return total;
}

template <typename T>
BinomialHeap<T>& BinomialHeap<T>::operator =(BinomialTree<T> const& tree)
{
    trees.clear();
    foreach(tree_t i, tree.roots)
        trees.push_back(i);
    return *this;
}

template <typename T>
T BinomialHeap<T>::min()
{
    T min_ele = 999999999; // TODO: This is horrible. Please fix!! \(*;_;)/
    
    foreach(tree_t i, trees)
        if(i != NULL)
            if(i->min() < min_ele)
                min_ele = i->min();

    return min_ele;
}

template <typename T>
void BinomialHeap<T>::insertTree(BinomialTree<T>* tree)
{
    size_t degree = log2(tree->size());

    if(trees[degree] != NULL)
    {
        tree->merge(*trees[degree]);
        insertTree(tree);
        return;
    }
    trees[degree] = tree;
}

template <typename T>
void BinomialHeap<T>::merge(BinomialHeap& heap)
{
    BinomialHeap<T> result;
    size_t ord = 0;
    size_t largestDepth = max(floor(log2(totalSize())), floor(log2(heap.totalSize())));
    ++largestDepth;
    BinomialTree<T>* carry = NULL;
    for(; ord <= largestDepth; ++ord)
    {
        int heap1 = 0, heap2 = 0, h_carry = 0;
        if(carry != NULL)
            h_carry = 1;
        if(trees[ord] != NULL)
            heap1 = 1;
        if(heap.trees[ord] != NULL)
            heap2 = 1;

        switch(heap1 + heap2 + h_carry)
        {
            case 0:
                break;
            case 1:
                if(h_carry == 1) {
                    result.insertTree(carry);
                    carry = NULL;
                } else if(heap1 == 1)
                    result.insertTree(trees[ord]);
                else
                    result.insertTree(heap.trees[ord]);
                break;
            case 2:
                if(h_carry == 1 && heap1 == 1)
                    carry->merge(*trees[ord]);
                else if(h_carry == 1 && heap2 == 1)
                    carry->merge(*heap.trees[ord]);
                else
                {
                   trees[ord]->merge(*heap.trees[ord]);
                   carry = trees[ord];
                }
                break;
            case 3:
                carry->merge(*trees[ord]);
                result.insertTree(heap.trees[ord]);
                break;
        }
    }

    trees = result.trees;
    _size = ord - 1;
}

#endif
