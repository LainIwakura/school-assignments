//
// dow.hxx
// DayOfWeek header file
//
// Copyright (c) 2011 Paul Preney. All Rights Reserved.
// Contact URL: http://preney.ca/paul/
//
#ifndef dow_hxx__
#define dow_hxx__

#include <istream>    // For std::istream
#include <ostream>    // For std::ostream
#include <string>     // For std::string

//
// DayOfWeek
// Stores the day of the week.
//
class DayOfWeek
{
  public:
    enum DAY { MON=0, TUE, WED, THU, FRI, SAT, SUN, NUM_DAYS };

    DayOfWeek();
    explicit DayOfWeek(DAY d);
    explicit DayOfWeek(std::string const& day);
    DayOfWeek(DayOfWeek const& dow);
    DayOfWeek& operator =(DayOfWeek const& dow);
    
    void assign(DAY d);
    void assign(std::string const& day);
    void assign(DayOfWeek const& dow);

    DAY day() const;
    std::string name() const;
    std::string abbrev() const;

    DayOfWeek& operator +=(int days);

  private:
    static const char* const NAMES_[NUM_DAYS];
    static const char* const ABBREV_[NUM_DAYS];

    DAY day_;
};

// Allow binary + to be used...
inline DayOfWeek operator +(DayOfWeek const& dow, int days)
{ 
  DayOfWeek retval(dow); 
  return retval += days; 
}

inline DayOfWeek operator +(int days, DayOfWeek const& dow)
{
  // Simply reverse the arguments and call the other operator +()...
  return operator +(dow, days); 
}

// Read/Write DayOfWeek functions...
std::istream& operator >>(std::istream& is, DayOfWeek& dow);
std::ostream& operator <<(std::ostream& os, DayOfWeek const& dow);

#endif // dow_hxx__

