/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Started on: Mar. 25th / 2011
 * 
 * Purpose: A binomial heap is a data structure
 * that implements a priorety queue. It is highly
 * specialized to a few areas, such as bandwidth
 * management or discrete event simulation
 *
 * in the case of discrete event simulation, items
 * are added to the queue with their simulation time
 * as a priorety.
 */

#ifndef __BINOMIAL_HEAP_HXX
#define __BINOMIAL_HEAP_HXX

#include <vector> // we use a vector to store our trees.
#include <cmath> // need log2 and pow.
#include <stdexcept> // for errors
#include <boost/foreach.hpp> // a foreach loop as implemented by boost

#define foreach BOOST_FOREACH

// so we don't have to append std:: to a few things.
using namespace std;

// Class prototypes. This is a recursive data structure, nodes are made up of
// pointers to their parent / child / sibling trees...and trees are made up of
// one root node =P
template <typename T>
class BinomialHeap;

template <typename T>
class BinomialTree;

// Note: This node class should never be used outside of this file.
template <typename T>
class Node
{
    public:
        T _data;
        BinomialTree<T>* _parent;
        BinomialTree<T>* _child;
        BinomialTree<T>* _sibling;
        
        // Two constructors. 
        Node(T const&, BinomialTree<T>*, BinomialTree<T>*, BinomialTree<T>*);
        Node(Node<T> const&);
};

template <typename T>
Node<T>::Node(T const& data, BinomialTree<T>* parent, BinomialTree<T>* child, BinomialTree<T>* sibling)
    : _data(data), _parent(parent), _child(child), _sibling(sibling)
{
}

template <typename T>
Node<T>::Node(Node<T> const& node)
    : _data(node._data), _parent(node._parent), _child(node._child), _sibling(node._sibling)
{
}


/* The binomial tree class is used by our binomial heap class.
 * It has two constructors and a copy constructor, as well 
 * as three basic operations- min, merge, and size.
 *
 * It's structured as one root node (called roots because in a
 * previous verion it was a vector of nodes).
 * 
 * Note: See 00README.txt for notes on extractMin();
 */
template <typename T>
class BinomialTree
{
    protected:
        typedef Node<T>* node_t;

    public:
        BinomialTree(T);
        BinomialTree(node_t);
        BinomialTree(BinomialTree const&);

        const T& min();
        void merge(BinomialTree&);
        size_t size() const;

        BinomialTree& operator =(BinomialTree const&);

    private:
        size_t tree_depth;
        node_t roots;
};

// Construct a tree of depth 0 with a node containing data, and NULL
// pointers to the parent tree, child tree, and sibling tree
template <typename T>
BinomialTree<T>::BinomialTree(T data)
    : tree_depth(0)
{
    Node<T>* node;
    node = new Node<T>(data, NULL, NULL, NULL);
    roots = node;
}

// Invokes the copy constructor defined in node
template <typename T>
BinomialTree<T>::BinomialTree(node_t nodes)
    : roots(nodes)
{
}

// Copy constructor for our tree.
template <typename T>
BinomialTree<T>::BinomialTree(BinomialTree const& other)
    : tree_depth(other.tree_depth), roots(other.roots)
{
}

// This returned a constant reference to the data at the root node.
// Because of the structure of this tree, it is such that the root node
// will always contain the minimum element.
template <typename T>
const T& BinomialTree<T>::min()
{
    return roots->_data;
}

/* Merge two trees together.
 * This algorithm can be found in
 * Amortized Analysis - Yung H. Tsin (2008)
 * Page 33.
 */
template <typename T>
void BinomialTree<T>::merge(BinomialTree& other)
{
    // Trees to be merged MUST have equal depth
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

    if(other.roots->_data < roots->_data)
    {
        // If you want to see things being printed,
        // uncomment these next two lines.
        // cout << roots->_data << endl;
        // cout << other.roots->_data << endl;
        roots->_parent = &other;
        roots->_sibling = other.roots->_child;
        BinomialTree<T>* tmp;
        tmp = this;
        other.roots->_child = tmp;
        roots = other.roots;
    }
    else
    {
        other.roots->_parent = this;
        other.roots->_sibling = roots->_child;
        roots->_child = &other;
    }
    tree_depth++;
}

// The size of a binomial tree can be defined as 2^i where i is the depth of
// the tree. Proof of this algorithm is trivial. (Page 23 amortized analysis)
template <typename T>
size_t BinomialTree<T>::size() const
{
    return pow(2,tree_depth);
}

// Overloaded equals operator, but we're not sure it's needed...
template <typename T>
BinomialTree<T>& BinomialTree<T>::operator =(BinomialTree<T> const& tree)
{
    roots = tree.roots;
    tree_depth = tree.tree_depth;
    return *this;
}

/* The star of our show! The binomial heap class defines a binomial heap H.
 * A Binomial heap has many cool properties, but the important thing to know
 * is that most of it's operations can be preformed in O(log n) time.
 */
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
        void merge(BinomialHeap&);
        void insertTree(BinomialTree<T>*);
        bool isEmpty() const;
        size_t size() const;
        size_t totalSize() const;

        BinomialHeap& operator =(BinomialTree<T> const&);

    private:
        // Variables only to be used by this class
        size_t _size;
        vector<tree_t> trees;
};

// An empty heap has a size of 0, but we resize the trees vector so
// it can handle some initial insertions.
template <typename T>
BinomialHeap<T>::BinomialHeap()
    : _size(0)
{
    trees.resize(32);
}

// A heap with 1 element has a size of one.
template <typename T>
BinomialHeap<T>::BinomialHeap(T data)
    : _size(1)
{
    trees.resize(32);
    BinomialTree<T>* tmp; // Construct a new tree
    tmp = new BinomialTree<T>(data);
    trees[0] = tmp; // Put the new tree into the first element of our vector
}

// Pretty basic copy constructor
template <typename T>
BinomialHeap<T>::BinomialHeap(BinomialHeap<T> const& heap)
    : _size(heap._size), trees(heap.trees)
{
}

/* This function right now works, but it's sort of bad.
 * It needs to be re-written to be pointer compatible- right
 * now it only works with integer types excluding short.
 * it has been tested for float, long, unsigned, double, int, etc.,
 */
template <typename T>
T BinomialHeap<T>::min()
{
    T min_ele = 999999999; // TODO: This is horrible. Please fix!! \(*;_;)/
    
    // We go through each tree and compare root nodes, the one with the
    // smallest root node is the smallest element in our heap.
    foreach(tree_t i, trees)
        if(i != NULL)
            if(i->min() < min_ele)
                min_ele = i->min();

    return min_ele;
}

/* The merge function, which is based off of binary addition.
 * to merge a heap H1 with k trees, and a heap H2 with i trees,
 * if k or i is null, we set a var to 0. We also have a carry tree
 * which acts exactly like the carry in addition.
 * in the case everything is null, we've merged nothing. (0 + 0 + 0)
 * in the case that one tree is set, we insert it to the heap H and
 * set the carry to null. (0 + 1 + 0 = 1, no carry.)
 *
 * In the case that two heaps are set, we add them and place the result in the
 * carry. (1 + 1 + 0 = 0, 1 is in the carry)
 *
 * If all three trees are set, we merge two, set it to the carry, and insert
 * the remaining tree into the heap. (1 + 1 + 1 = 1, with 1 in the carry)
 */
template <typename T>
void BinomialHeap<T>::merge(BinomialHeap& heap)
{
    BinomialHeap<T> result; // temporarily store things in here.
    size_t ord = 0;
    // The formula for largest depth comes from Amortized analysis, page 34.
    size_t largestDepth = max(floor(log2(totalSize())), floor(log2(heap.totalSize())));
    ++largestDepth;
    BinomialTree<T>* carry = NULL;
    for(; ord <= largestDepth; ++ord)
    {
        // Each time we iterate we check which ones are null and set our
        // addition bits appropriately.
        int heap1 = 0, heap2 = 0, h_carry = 0;
        if(carry != NULL)
            h_carry = 1;
        if(trees[ord] != NULL)
            heap1 = 1;
        if(heap.trees[ord] != NULL)
            heap2 = 1;

        switch(heap1 + heap2 + h_carry)
        {
            // Each of these cases have been described in the function
            // comments.
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

/* A helper function that serves to insert a tree into a heap.
 * We find the degree of the tree, which is log2 of the amount of
 * nodes in the tree. i.e, a tree with 256 nodes will have a degree of 8.
 *
 * While there is a tree existing at trees[degree], we merge the tree
 * with the tree at trees[degree], then recursively do it again.
 *
 * When there is no tree at trees[degree], we insert our tree into there.
 */
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
    ++_size;
}

// Simply check if we're empty or not!
template <typename T>
bool BinomialHeap<T>::isEmpty() const
{
    return size() == 0 ? true : false;
}

// return the amount of nodes in a tree.
template <typename T>
size_t BinomialHeap<T>::size() const
{
    return _size;
}

// total size is actually the amount of trees in the heap.
template <typename T>
size_t BinomialHeap<T>::totalSize() const
{
    size_t total = 0;
    foreach(tree_t i, trees)
        if(i != NULL)
            total += i->size();
    
    return total;
}

// Basic overloaded equals operator.
template <typename T>
BinomialHeap<T>& BinomialHeap<T>::operator =(BinomialTree<T> const& tree)
{
    trees.clear();
    foreach(tree_t i, tree.roots)
        trees.push_back(i);
    return *this;
}

#endif
