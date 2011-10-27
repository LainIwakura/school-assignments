#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int size;

    typedef vector<string> ITEMS;
    ITEMS words;

    string s;
    while(cin >> s)
        words.push_back(s);

    ITEMS::iterator i = words.begin();
    ITEMS::iterator iEnd = words.end();
    ITEMS::iterator iTwoBeforeEnd = iEnd;
    size = words.size();

    if(size == 0)
    {    
        cout << "There were no words read in." << endl;
        return 0;
    }
    else if(size == 1)
    {
        cout << "The word is: \"" << *i << "\".";
        cout << " A total of 1 word was read in." << endl;
    }
    else
    {
        --iTwoBeforeEnd;
        --iTwoBeforeEnd;
        cout << "The words are: ";
        for(; i != iTwoBeforeEnd; ++i)
            cout << "\"" << *i << "\", ";
        if (i != iEnd)
        {
            cout << "\"" << *i << "\" and ";
            ++i;
            cout <<"\"" << *i << "\".";
        }

        cout << " A total of " << size << " words were read in." << endl;
    }

    return 0;
}
