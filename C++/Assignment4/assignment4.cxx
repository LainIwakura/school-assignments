/* Programmed by Zachary Easterbrook
 * Student ID: 103163420
 * Programmed on Feb. 7th 2011
 */

#include <iostream>
#include <stdexcept>
#include <cerrno>
#include <cmath>
#include <vector>
#include <iterator>

using namespace std;

// Short hand stuff
typedef vector<double> V;

// Our prototypes
int sgn(double const& x);
void quadroots(double const& a, double const& b, double const& c, vector<double>& soln);

int main()
{
    double a, b, c;
    while (cin >> a >> b >> c)
    {
        V roots;
        // Try the function
        try
        {
            quadroots(a, b, c, roots);
            V::iterator i = roots.begin();
            V::iterator iEnd = roots.end();
            for(; i != iEnd; ++i)
                cout << *i << " ";
            cout << endl;
        }
        // If we get an error, display it.
        catch(range_error const& e)
        {
            cerr << e.what() << endl;
        }
    }   

    return 0;
}

int sgn(double const& x)
{
    /* return 0 if x == 0
     * otherwise return -1 if x < 0
     * otherwise just return 1
     */

    return x == 0 ?  1 
         : x <  0 ? -1
         :           1;
}

// This function actually computes our roots
void quadroots(double const& a, double const& b, double const& c, vector<double>& soln)
{
    // The vector that will store our result
    V result;
    double q;
    double sq_root;

    errno = 0;
    sq_root = sqrt((pow(b,2)) - (4 * a * c));
    
    // If errno gets set to EDOM (DOMain Error), throw NO_REAL_ROOTS
    if(errno == EDOM)
        throw range_error("NO_REAL_ROOTS");
    // Quotient formula
    q = (-0.5) * (b + (sgn(b) * sq_root));

    if(q == 0 || a == 0)
        result.push_back(0);
    else
    {
        // Only push back one answer if the answers are equal
        if(q / a == c / q)
            result.push_back(q / a);
        else
        {
            result.push_back(q / a);
            result.push_back(c / q);
        }
    }
    // Swap the elements in the result vector into the soln vector.
    soln.swap(result);
}
