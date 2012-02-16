#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "SList.hxx"

using namespace std;

int main()
{
  StackList<unsigned char> s;
  string opening = "{[(";
  string closing = "}])";
  map<unsigned char, unsigned char> m = {
    {'{','}'},
    {'[',']'},
    {'(',')'}
  };
  string allowed = "0123456789+-*/{}[]()";
  string expr;
  bool valid;

  cout << "========= Testing error messages =========\n";
  // Checking to see if our error messages work
  // and report things correctly.
  try
  {
    s.pop();
  }
  catch (range_error const& e)
  {
    cerr << e.what() << '\n';
  }
  try
  {
    s.top();
  }
  catch (range_error const& e)
  {
    cerr << e.what() << '\n';
  }
  cout << "========= At this point we begin pushing onto the stack =========\n";

  do
  {
    bool balanced = true;
    cout << "Enter an expression to evaluate, exit to exit: ";
    cin >> expr;
    if (expr == "exit") break;
    for (auto i = expr.begin(); i != expr.end(); ++i)
    {
      if (opening.find(*i) != string::npos) s.push(*i);
      else if (closing.find(*i) != string::npos) {
	unsigned char t = s.pop();
	balanced = (m.find(t)->second == *i) ? true : false;
	if (balanced == false) break;
      }
      valid = (allowed.find(*i) == string::npos) ? false : true;
    }
    if (!balanced || !valid || !s.isEmpty()) cout << "Your expression is unbalanced, or invalid.\n";
    else cout << "Your expression is balanced.\n";
    s.clear();
  } while (1);

  return 0;
}
