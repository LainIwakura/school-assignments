#ifndef jd_hxx__
#define jd_hxx__

#include <istream>  // For std::istream
#include <ostream>  // For std::ostream

#include <ctime>    // C's time.h
#include <cmath>    // C's math.h

//
// JD
// Stores the current date in astronomical Julian Date format.
//
// See http://en.wikipedia.org/wiki/Julian_day for details about
// this date encoding.
//
// NOTE: This code only converts from a Gregorian date to JD.
//
class JD
{
  public:
    JD();                                  // Use current date.
    explicit JD(double jd);                // Use jd as date.
    JD(
      int y, int mo, int d, 
      int h, int mi, int s, double frac_of_sec=0.0
    );
    JD(JD const& jd);                    // Used to create copies
    JD& operator =(JD const& jd);        // Handle assignment

    double const& jd() const;              // Return the JD

    JD& operator +=(double num_of_days);   // Add num_of_days to JD

    // Set this to the provided date...
    void assign(double jd);                               // Set date
    void assign(
      int y, int mo, int d, 
      int h, int mi, int s, double frac_of_sec=0.0
    );
    void assign(JD const& jd);                          // Set date

  protected:
    static double calc_jd_now();
    static int calc_jdn(int y, int mo, int d);
    static double calc_jd(int jdn, int h, int mi, int sec, 
      double frac_of_sec=0.0);
    static double calc_jd(int y, int mo, int d, int h, int mi, int sec,
      double frac_of_sec=0.0);

  private:
    double jd_;
};

// Comparison...
bool operator ==(JD const& a, JD const& b);
bool operator !=(JD const& a, JD const& b);
bool operator <(JD const& a, JD const& b);
bool operator <=(JD const& a, JD const& b);
bool operator >(JD const& a, JD const& b);
bool operator >=(JD const& a, JD const& b);

// Add num_of_days to jd...
JD operator +(JD const& jd, double num_of_days);

// Subtract num_of_days from jd...
JD& operator -=(JD& jd, double num_of_days);
JD operator -(JD const& jd, double num_of_days);

// Determine number of days between two ADJs...
double operator -(JD const& a, JD const& b);

// Read/Write JD...
std::istream& operator >>(std::istream& is, JD& jd);
std::ostream& operator <<(std::ostream& os, JD& jd);

#endif // jd_hxx__

