#include <vector>
#include <iostream>

using namespace std;

void insertion_sort(vector<int>& x)
{
  for (int i = 1; i < x.size(); ++i)
  {
    int temp = x[i];
    int j = i - 1;
    while (j >= 0 && x[j] > temp)
    {
      x[j+1] = x[j];
      --j;
    }
    x[j+1] = temp;
  }
}

int main()
{
  vector<int> nums = {1, 4, 3, 2, 5, 7, 9};
  insertion_sort(nums);

  for (auto i = nums.begin(); i != nums.end(); ++i)
    cout << *i << endl;

  return 0;
}
