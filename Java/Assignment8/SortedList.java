package Assignment8;

import java.util.ArrayList;

public class SortedList<T extends Sortable>
{
  public ArrayList<T> arr;
  public int currentIndex = 0;

  public void sort()
  {
    boolean swapped = true;
    int j = 0;
    int cur = 0;
    T tmp;
    while (swapped)
    {
      swapped = false;
      j++;
      for (int i = 0; i < arr.size() - j; ++i)
      {
        if (arr.get(i + 1).lessThan(arr.get(i)))
        {
          tmp = arr.get(i);
          arr.set(i, arr.get(i + 1));
          arr.set(i + 1, tmp);
          swapped = true;
        }
      }
    }
  }

  public SortedList()
  {
    arr = new ArrayList<T>();
  }

  public T insert(T x)
  {
    arr.add(x);
    this.sort();
    return arr.get(currentIndex++);
  }

  public T getFirst()
  {
    currentIndex = 0;
    return arr.get(currentIndex);
  }

  public T getNext()
  {
    currentIndex++;
    if (currentIndex >= arr.size())
      return null;
    else
      return arr.get(currentIndex);
  }
}
