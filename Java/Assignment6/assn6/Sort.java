package assn6;

public class Sort
{
  public static void sortAnything(Sortable items[], int numOfItems)
  {
    Sortable temp;
    int indexSmallest, index1, index2;
    for (index1 = 0; index1 < numOfItems - 1; index1++)
    {
      indexSmallest = index1;
      for (index2 = index1 + 1; index2 < numOfItems; index2++)
        if (items[index2].lessThan(items[indexSmallest]))
          indexSmallest = index2;
      temp = items[index1];
      items[index1] = items[indexSmallest];
      items[indexSmallest] = temp;
    }
  }
}
