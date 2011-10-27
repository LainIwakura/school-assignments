#ifndef utils_hxx__
#define utils_hxx__
#include <ios>  // For std::ios_base

//
// From Stroustrup's "Programming: Principles and Practice Using C++" 
// Section 11.2 (page 381)...
//
inline std::ios_base& general(std::ios_base& b)
{
  b.setf(std::ios_base::fmtflags(0), std::ios_base::floatfield);
  return b;
}

#endif // utils_hxx__

