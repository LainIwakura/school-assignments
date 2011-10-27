#include <iostream>
#include <sstream>
#include <string>

#include "dow.hxx"
#include "jd.hxx"

int main()
{
  using namespace std;

  int y, mo, d, h, mi, s;
  double frac_of_sec;

  while (cin >> y >> mo >> d >> h >> mi >> s >> frac_of_sec)
  {
    JD jd(y, mo, d, h, mi, s, frac_of_sec);

    cout << "JD = " << jd << '\n';

    // Calc DOW...
    DayOfWeek dow(static_cast<DayOfWeek::DAY>(fmod(jd.jd()+0.5, 7.0)));
    cout << "DAY OF WEEK is " << dow.name() << '\n';

    // Perform comparison tests...
    {
      // Check equality...
      ostringstream cmp;
      cmp 
        << (jd == jd) << (jd != jd) 
        << (jd < jd) << (jd <= jd) 
        << (jd > jd) << (jd >= jd);
      cout 
        << "EQUALITY TEST: " << cmp.str() 
        << (cmp.str() == "100101" ? " GOOD" : " BAD")
        << '\n';

      cmp.str(string()); // Clear out buffer

      // Check less than...
      JD less(jd.jd()-0.5);
      cmp 
        << (less == jd) << (less != jd) 
        << (less < jd) << (less <= jd) 
        << (less > jd) << (less >= jd);
      cout << "LESS TRUE TEST: " << cmp.str() 
        << (cmp.str() == "011100" ? " GOOD" : " BAD")
        << '\n';

      cmp.str(string()); // Clear out buffer

      cmp 
        << (jd == less) << (jd != less) 
        << (jd < less) << (jd <= less) 
        << (jd > less) << (jd >= less);
      cout << "LESS FALSE TEST: " << cmp.str() 
        << (cmp.str() == "010011" ? " GOOD" : " BAD")
        << '\n';

      cmp.str(string()); // Clear out buffer

      // Check greater than...
      JD more(jd.jd()+0.5);

      cmp 
        << (jd == more) << (jd != more) 
        << (jd < more) << (jd <= more) 
        << (jd > more) << (jd >= more);
      cout << "MORE TRUE TEST: " << cmp.str() 
        << (cmp.str() == "011100" ? " GOOD" : " BAD")
        << '\n';

      cmp.str(string()); // Clear out buffer

      cmp 
        << (more == jd) << (more != jd) 
        << (more < jd) << (more <= jd) 
        << (more > jd) << (more >= jd);
      cout << "MORE FALSE TEST: " << cmp.str() 
        << (cmp.str() == "010011" ? " GOOD" : " BAD")
        << '\n';
    }

    // Date adjustments...
    {
      {
      JD jd2(jd); jd2 += 1.5;
      JD jd3(jd+1.5);
      cout << jd3 << ((jd3 == jd2) ? " == " : " != ") << jd2 << '\n';
      cout << "DIFF TEST 1: " << (jd2-jd) 
        << ((jd2-jd) == 1.5 ? " GOOD" : " BAD") << '\n';
      }

      {
      JD jd2(jd); jd2 -= 1.5;
      JD jd3(jd-1.5);
      cout << jd3 << ((jd3 == jd2) ? " == " : " != ") << jd2 << '\n';
      cout << "DIFF TEST 2: " << (jd2-jd) 
        << ((jd2-jd) == -1.5 ? " GOOD" : " BAD") << '\n';
      // This line was added to make things more readable.
      cout << endl;
      }
    }
  }
}

