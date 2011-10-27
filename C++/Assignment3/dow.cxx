#include <sstream>    // For std::ostringstream
#include <stdexcept>  // For std::domain_error
#include <string>     // For std::string

#include "dow.hxx"

DayOfWeek::DayOfWeek()
  : day_(MON)
{
}

DayOfWeek::DayOfWeek(DAY d)
{
  this->assign(d);
}

DayOfWeek::DayOfWeek(std::string const& day)
{
  this->assign(day);
}

DayOfWeek::DayOfWeek(DayOfWeek const& dow)
  : day_(dow.day_)
{
}

DayOfWeek& DayOfWeek::operator =(DayOfWeek const& dow)
{
  this->assign(dow);
  return *this;
}
    
void DayOfWeek::assign(DAY d)
{
  if (d >= 0 && d < NUM_DAYS)
    this->day_ = d;
  else
  {
    // Create an error message and throw std::domain_error...
    std::ostringstream buf;
    buf << "Invalid DayOfWeek day value: " << d;
    throw std::domain_error(buf.str());
  }
}

void DayOfWeek::assign(std::string const& day)
{
  int i;

  for (i=0; i != DayOfWeek::NUM_DAYS; ++i)
  {
    //
    // The following code invokes operator ==() as seen in 
    // C++ In A Nutshell (CIAN), Chapter 13 <string>, pages 682-683.
    //
    // Notice in CIAN these operator ==() functions are defined OUTSIDE
    // the std::string class.
    //
    if (day == DayOfWeek::NAMES_[i] || day == DayOfWeek::ABBREV_[i])
      break;
  }

  if (i != DayOfWeek::NUM_DAYS)
  {
    // NOTE: An explicit cast is required here in C++ --unlike C...
    this->day_ = static_cast<DAY>(i);
  }
  else
  {
    // We reached the "end" (i.e., NUM_DAYS) so days is invalid!
    
    // Create an error message and throw std::domain_error...
    std::ostringstream buf;
    buf << "Invalid DayOfWeek day value: \"" << day << "\".";
    throw std::domain_error(buf.str());
  }
}

void DayOfWeek::assign(DayOfWeek const& dow)
{
  this->day_ = dow.day_;
}

//
// Notice that DAY is prefixed by DayOfWeek::! Why? Because the return
// type is OUTSIDE the definition of the function and DAY is defined
// INSIDE the DayOfWeek class. In other words, the C++ compiler cannot 
// find the DAY type in the current (global) namespace (and it won't search 
// inside any struct/class/union) so we need to tell it WHERE to find it
// i.e., in DayOfWeek!
//
DayOfWeek::DAY DayOfWeek::day() const
{
  return this->day_;
}

std::string DayOfWeek::name() const
{
  return std::string(NAMES_[this->day_]);
}

std::string DayOfWeek::abbrev() const
{
  return std::string(ABBREV_[this->day_]);
}

DayOfWeek& DayOfWeek::operator +=(int days)
{
  this->day_ = static_cast<DAY>((this->day_ + days) % NUM_DAYS);

  // Handle case if % returns a negative value...
  if (this->day_ < 0)
    this->day_ = static_cast<DAY>(this->day_ + NUM_DAYS);

  return *this;
}


//
// Static variables must be defined OUTSIDE the class they are declared in.
// This is how you do it. Since we are outside the class, we MUST
// prefix any symbol names defined inside the class with the name of the
// class, e.g., DayOfWeek::NAMES_.
//
const char* const DayOfWeek::NAMES_[NUM_DAYS] = {
  "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", 
  "Saturday", "Sunday"
};

const char* const DayOfWeek::ABBREV_[NUM_DAYS] = {
  "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};


std::istream& operator >>(std::istream& is, DayOfWeek& dow)
{
  std::string day;

  if (is >> day)
  {
    try
    {
      dow.assign(day);
    }
    catch (std::domain_error& e)
    {
      // We were unable to read in DayOfWeek, so fail the stream
      // instead of re-throwing the exception (see Chapter 10.9: 
      // User-defined input operators)...
      is.clear(std::ios_base::failbit);
    }
  }

  return is;
}

std::ostream& operator <<(std::ostream& os, DayOfWeek const& dow)
{
  os << dow.abbrev();
  return os;
}

