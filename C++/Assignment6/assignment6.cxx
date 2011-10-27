/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Date: Feb 23rd / 2011
 */

#include <iostream>
#include <iterator>
#include <cctype>
#include <string>

// Our custom definition of transform.
template <typename InIter, typename OutIter, typename Op>
OutIter update(InIter first, InIter last, OutIter out, Op o)
{
    for(; first != last; ++first, ++out)
        *out = o(*first);
    return out;
}

// Append to iterator template / class prototype
template <typename Cont>
class append_to_iterator
{
    public:
        explicit append_to_iterator(Cont& cont);
        append_to_iterator<Cont>& operator =(typename Cont::const_reference value);
        append_to_iterator<Cont>& operator *();
        append_to_iterator<Cont>& operator ++();
        append_to_iterator<Cont> operator ++(int);

    private:
        Cont* cont_;
};

// Constructor
template <typename Cont>
append_to_iterator<Cont>::append_to_iterator(Cont& cont)
    : cont_(&cont)
{
}

// Overloaded =
template <typename Cont>
append_to_iterator<Cont>& append_to_iterator<Cont>::operator =(typename Cont::const_reference value)
{
    cont_->push_back(value);
    return *this;
}

// Overloaded *
template <typename Cont>
append_to_iterator<Cont>& append_to_iterator<Cont>::operator *()
{
    return *this;
}

// Overloaded ++
template <typename Cont>
append_to_iterator<Cont>& append_to_iterator<Cont>::operator ++()
{
    return *this;
}

// Overloaded ++ for int types
template <typename Cont>
append_to_iterator<Cont> append_to_iterator<Cont>::operator ++(int)
{
    return *this;
}

template <typename Cont>
append_to_iterator<Cont> append_to_container(Cont& cont)
{
    return append_to_iterator<Cont>(cont);
}

// Our function that alternates things
template <typename F>
std::string to_xxx(std::string const& str, F f)
{
    std::string retval;
    update(str.begin(), str.end(), append_to_container(retval), f);
    return retval;
}

// To upper-case
std::string to_upper(std::string const& str)
{
    int(* const ptrfunc)(int) = std::toupper;
    return to_xxx(str, ptrfunc);
}

// To lower-case
std::string to_lower(std::string const& str)
{
    int(* const ptrfunc)(int) = std::tolower;
    return to_xxx(str, ptrfunc);
}

// Prototype for alternating case
class alternating_case
{
    public:
        alternating_case();
        alternating_case(alternating_case const&);
        alternating_case& operator =(alternating_case const& f);

        char operator ()(char c) const;
        void reset();
        
    private:
        enum STATE { UPPER, LOWER };
        mutable STATE state_;
};

// See assignment 5.
alternating_case::alternating_case()
    : state_(UPPER)
{
}

alternating_case::alternating_case(alternating_case const& state)
    : state_(state.state_)
{
}

alternating_case& alternating_case::operator =(alternating_case const& state)
{
    state_ = state.state_;
    return *this;
}

char alternating_case::operator ()(char c) const
{
    if(state_ == UPPER)
    {
        state_ = LOWER;
        return toupper(c);
    }
    else if(state_ == LOWER)
    {
        state_ = UPPER;
        return tolower(c);
    }
}

void alternating_case::reset()
{
    state_ = UPPER;
}
// End of assignment 5 functions

// alternating case function
std::string to_alternating(std::string const& str)
{
    return to_xxx(str, alternating_case());
}

// Entry point
int main()
{
    using namespace std;
    
    string line;
    // Read a line, print the three variations of that line
    while (getline(cin, line))
    {
        cout << "to_upper: " << to_upper(line) << endl;
        cout << "to_lower: " << to_lower(line) << endl;
        cout << "to_alternating: " << to_alternating(line) << endl;
    }

    return 0;
}
