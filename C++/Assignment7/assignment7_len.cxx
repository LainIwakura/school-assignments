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

typedef map<string, unsigned> WordHist;
typedef map<WordHist::mapped_type, list<WordHist::key_type>, std::greater<WordHist::mapped_type> > WordsByFreq;

int main()
{
    string word;
    WordHist wh;
    WordsByFreq whbf;
    while(cin >> word)
    {
        pair<WordHist::iterator, bool> result = wh.insert(make_pair(word,word.size()));
        if(!result.second)
            continue;
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

    for(; j != jEnd; ++j)
    {
        cout << j->first << ": ";
        WordsByFreq::mapped_type::iterator k = j->second.begin();
        WordsByFreq::mapped_type::iterator kEnd = j->second.end();
        for(; k != kEnd; ++k)
            cout << *k << " ";
        cout << endl;
    }

    return 0;
}
