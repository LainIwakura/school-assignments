#include <vector>
#include <iostream>
#include <random>
#include <functional>

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
  vector<int> nums;
  vector<int> nums_small;
  clock_t t1, t2;
  std::mt19937 engine;
  std::uniform_int_distribution<int> dist;
  auto gen = std::bind(dist,engine);

  for (int m = 0; m < 40000; ++m)
    nums.push_back(gen());

  for (int n = 0; n < 1000; ++n)
    nums_small.push_back(gen());

  t1 = clock();
  insertion_sort(nums);
  t2 = clock();
  float diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
  cout << "Started algorithm for large n at: " << (float)t1 / CLOCKS_PER_SEC << "s" << endl;
  cout << "Running time took: " << diff << "s" << endl;
  cout << "Ended at: " << (float)t2 / CLOCKS_PER_SEC << "s" << endl;

  t1 = clock();
  insertion_sort(nums_small);
  t2 = clock();
  diff = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;
  cout << "Started algorithm for small n at: " << (float)t1 / CLOCKS_PER_SEC << "s" << endl;
  cout << "Running time took: " << diff << "s" << endl;
  cout << "Ended at: " << (float)t2 / CLOCKS_PER_SEC << "s" << endl;

  for (auto i = nums_small.begin() + 980; i != nums_small.end(); ++i)
    cout << *i << endl;

  return 0;
}
