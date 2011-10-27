/* Written by Zachary Easterbrook
 * Student ID: 103163420
 * Written on February 24th 2011
 */

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <utility>


using namespace std;

// The two typedefs needed
typedef map<string, unsigned> WordHist;
typedef map<WordHist::mapped_type, list<WordHist::key_type>, std::greater<WordHist::mapped_type> > WordsByFreq;

int main()
{
    // Declare some variables
    string word;
    WordHist wh;
    WordsByFreq whbf;
    while(cin >> word)
    {
        // Insert the stuff into our word histogram. This line is condensed
        // from the alternative which checks the return value.
        wh.insert(make_pair(word,0U)).first->second++;
    }

    WordHist::iterator i = wh.begin();
    WordHist::iterator iEnd = wh.end();

    for(; i != iEnd; ++i)
    {
        /* This is confusing so I'll explain
         * make_pair makes creates a tuple with an unsigned int from WordHist,
         * and an empty list of WordsByFreq::mapped_type.
         * Insert inserts the words from i->first into the list pointed to by
         * the first->second part.
         */
        whbf.insert(make_pair(i->second, WordsByFreq::mapped_type())).first->second.push_back(i->first);
    }

    WordsByFreq::iterator j = whbf.begin();
    WordsByFreq::iterator jEnd = whbf.end();

    // Iterate through everything in our by-frequency map
    for(; j != jEnd; ++j)
    {
        cout << j->first << ": ";
        // Iterate through the items in the list, the second item of the
        // by-frequency map.
        WordsByFreq::mapped_type::iterator k = j->second.begin();
        WordsByFreq::mapped_type::iterator kEnd = j->second.end();
        for(; k != kEnd; ++k)
            cout << *k << " ";
        cout << endl;
    }

    return 0;
}
