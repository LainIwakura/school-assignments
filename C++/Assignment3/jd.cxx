#include <iomanip>  // For std::setw, std::setprecision
#include <ctime>    // C's time.h
#include <cmath>    // C's math.h

#include "jd.hxx"

JD::JD()
    : jd_(calc_jd_now()) // initalize jd_ with the return value from calc_jd_now()
{
}

JD::JD(double jd)
    : jd_(jd)   // our defined constructor, set jd_ to jd.
{
}

JD::JD(int y, int mo, int d, int h, int mi, int s, double frac_of_sec)
    : jd_(calc_jd(y, mo, d, h, mi, s, frac_of_sec)) // another constructor, sets jd to the result of calc_jd
{
}

JD::JD(JD const& jd)
    : jd_(jd.jd_)
{
}

JD& JD::operator =(JD const& jd) // overloaded = operator
{
    this->assign(jd);
    return *this;
}

double const& JD::jd() const    // function that just returns the current jd_
{
    return jd_;
}

JD& JD::operator +=(double num_of_days) // overloaded += operator
{
    jd_ += num_of_days;
    return *this;
}

void JD::assign(double jd) // assigns jd_ to jd
{
    jd_ = jd;
}

void JD::assign(int y, int mo, int d, int h, int mi, int s, double frac_of_sec) // assigns jd_ to the result of calc_jd
{
    jd_ = calc_jd(y, mo, d, h, mi, s, frac_of_sec);
}

void JD::assign(JD const& jd)   // assigns jd_ to the jd_ of jd...@_@
{
    jd_ = jd.jd_;
}

// JD::calc_jd_now() has been done for you...
double JD::calc_jd_now()
{
  using namespace std;

  time_t lt = time(NULL);

  tm *t = localtime(&lt);     // Obtain local time.
  //tm *t = gmtime(&lt);      // If one wants GMT instead.

  return calc_jd(t->tm_year, t->tm_mon, t->tm_mday,
    t->tm_hour, t->tm_min, t->tm_sec);
}

// JD::calc_jdn() has been done for you...
int JD::calc_jdn(int y, int mo, int d)
{
  int t_a = (14-mo)/12;
  int t_y = y + 4800 - t_a;
  int t_mo = mo + 12*t_a - 3;
  return d + (153*t_mo + 2)/5 + 365*t_y + t_y/4 - t_y/100 + t_y/400 - 32045;
}

// JD::calc_jd() has been done for you...
double JD::calc_jd(int jdn, int h, int mi, int sec, double frac_of_sec)
{
  double dayfrac = (h-12)/24.0 + mi/1440.0 + sec/86400.0 + frac_of_sec;
  return jdn + dayfrac;
}

// JD::calc_jd() has been done for you...
double JD::calc_jd(int y, int mo, int d, int h, int mi, int sec, double frac_of_sec)
{
  return calc_jd(calc_jdn(y, mo, d), h, mi, sec, frac_of_sec);
}

// Comparison...
bool operator ==(JD const& a, JD const& b)
{
    return (a.jd() == b.jd());
}

bool operator !=(JD const& a, JD const& b)
{
    return (a.jd() != b.jd());
}

bool operator <(JD const& a, JD const& b)
{
    return (a.jd() < b.jd());
}

bool operator <=(JD const& a, JD const& b)
{
    return (a.jd() <= b.jd());
}

bool operator >(JD const& a, JD const& b)
{
    return (a.jd() > b.jd());
}

bool operator >=(JD const& a, JD const& b)
{
    return (a.jd() >= b.jd());
}

// overloaded +
JD operator +(JD const& jd, double num_of_days)
{
    JD retval = JD(jd);
    retval += num_of_days;
    return retval;
}

// overloaded -=
JD& operator -=(JD& jd, double num_of_days)
{
    jd += -num_of_days;
    return jd;
}

// overloaded -
JD operator -(JD const& jd, double num_of_days)
{
    JD retval = JD(jd);
    retval -= num_of_days;
    return retval;
}

// overloaded -
double operator -(JD const& a, JD const& b)
{
    return a.jd() - b.jd();
}

std::istream& operator >>(std::istream& is, JD& jd)
{
    // Our double
    double dubs;
    if(is >> dubs)
        jd.assign(dubs);
    return is;
}

// operator << has been done for you...
std::ostream& operator <<(std::ostream& os, JD& jd)
{
  std::ios::fmtflags save = os.flags();
  os << std::fixed << std::setprecision(8) << jd.jd();
  os.flags(save);
  return os;
}

