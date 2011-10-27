/* This merge sort program was written
 * by *************** on Jan-29th
 * 2011.
 *
 * Student ID: **********
 *
 */

#include <iostream>
#include <list>
#include <string>
#include <iterator>

using namespace std;

typedef list<string> LIST;                // linked list type
typedef LIST::size_type LIST_SIZE;        // size type for list, e.g., unsigned
typedef LIST::iterator LIST_ITER;         // iterator type
typedef LIST::value_type LIST_CONTAINS;   // type in the list, i.e., a string

// Prototypes to preform our merge sort function
void merge_sort(LIST_ITER beg, LIST_ITER end, LIST_SIZE sz);
void merge(LIST_ITER bLeft, LIST_ITER bRight, LIST_ITER end);

int main()
{
    LIST l;
    LIST_CONTAINS v;

    // Read in the data...
    while (cin >> v)
        l.push_back(v);
    
    // Merge the data...
    LIST_ITER i = l.begin();
    LIST_ITER iEnd = l.end();
    LIST_SIZE size = distance(i, iEnd);
   
    merge_sort(i, iEnd, size);
    
    // Output everything...
    for (; i != iEnd; ++i)
        cout << *i << '\n';

    return 0;
}

void merge_sort(LIST_ITER beg, LIST_ITER end, LIST_SIZE sz)
{
    // The smallest possible list size. Lists less than size
    // two will already be sorted.
    if(sz < 2)
        return;

    LIST_SIZE half_size = sz / 2;
    LIST_ITER middle = beg;
    advance(middle, half_size);

    merge_sort(beg, middle, half_size);
    merge_sort(middle, end, half_size + sz % 2);

    merge(beg, middle, end);
}

void merge(LIST_ITER bLeft, LIST_ITER bRight, LIST_ITER end)
{
    LIST result;
    LIST_ITER first = bLeft;
    LIST_ITER mid = bRight;

    // While the left isn't equal to the middle, and the middle isn't equal to
    // the end we keep iterating through and preform our sort.
    while(bLeft != mid && bRight != end)
    {
        if(*bLeft < *bRight)
        {
            result.push_back(*bLeft);
            ++bLeft;
        }
        else
        {
            result.push_back(*bRight);
            ++bRight;
        }
    }
    // These next two while loops push data into our temporary list
    while(bLeft != mid)
    {
        result.push_back(*bLeft);
        ++bLeft;
    }
    while(bRight != end)
    {
        result.push_back(*bRight);
        ++bRight;
    }
    LIST_ITER i = result.begin();
    // Copy the sorted list to the original list. Both lists are the same size.
    for(; first != end; ++first, ++i)
        *first = *i;
}
