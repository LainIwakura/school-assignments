#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <functional>

using namespace std;

void quicksort_impl(vector<int>& nums, int start, int end)
{
  if (start < end)
  {
    int pivot = nums[end];
    int i = start;
    int j = end;
    while (i != j)
    {
      if (nums[i] < pivot) {
	i = i + 1;
      } else {
	nums[j] = nums[i];
	nums[i] = nums[j-1];
	--j;
      }
    }
    nums[j] = pivot;
    quicksort_impl(nums, start, j - 1);
    quicksort_impl(nums, j + 1, end);
  }
}

void quicksort(vector<int>& nums)
{
  quicksort_impl(nums, 0, nums.size() - 1);
}

int main()
{
  vector<int> nums;
  vector<int> nums_small;
  int j, k = 0;
  string yesno;
  clock_t t1, t2;

  std::mt19937 engine;
  std::uniform_int_distribution<int> dist;
  auto gen = std::bind(dist,engine);
  for (int m = 0; m < 10000000; ++m)
    nums.push_back(gen());

  for (int n = 0; n < 100; ++n)
    nums_small.push_back(n);

  t1 = clock();
  quicksort(nums);
  t2 = clock();
  float diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
  cout << "Started algorithm for large n at: " << (float)t1 / CLOCKS_PER_SEC << "s" << endl;
  cout << "Running time took: " << diff << "s" << endl;
  cout << "Ended at: " << (float)t2 / CLOCKS_PER_SEC << "s" << endl;

  t1 = clock();
  quicksort(nums_small);
  t2 = clock();
  diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
  cout << "Started algorithm for small n at: " << (float)t1 / CLOCKS_PER_SEC << "s" << endl;
  cout << "Running time took: " << diff << "s" << endl;
  cout << "Ended at: " << (float)t2 / CLOCKS_PER_SEC << "s" << endl;
  /*
  cout << "Nums have been sorted, display nums?" << endl;
  cin >> yesno;
  if (yesno == "yes")
    for (auto i = nums.begin(); i != nums.end(); ++i)
      cout << *i << endl;
  */

  return 0;
}
