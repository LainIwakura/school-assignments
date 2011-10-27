/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * tested on arch linux, with g++
 */
#include <iostream>
#include <algorithm>

// Our class, defined in assignment
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

// Our default constructor
alternating_case::alternating_case()
    : state_(UPPER)
{
}

// default copy constructor
alternating_case::alternating_case(alternating_case const& state)
    : state_(state.state_)
{
}

// overloaded = operator
alternating_case& alternating_case::operator =(alternating_case const& state)
{
    state_ = state.state_;
    return *this;
}

// overloaded () operator
char alternating_case::operator ()(char c) const
{
    // Next two control statements actually
    // change the case of the letter
    if(state_ == UPPER)
    {
        state_ = LOWER;
        return std::toupper(c);
    }
    else if(state_ == LOWER)
    {
        state_ = UPPER;
        return std::tolower(c);
    }
}

// reset function
void alternating_case::reset()
{
    state_ = UPPER;
}

// code here given in assignment
int main()
{
    using namespace std;
    
    string line;
    while (getline(cin, line))
    {
        transform(line.begin(), line.end(), line.begin(), alternating_case());
        cout << line << endl;
    }
}
