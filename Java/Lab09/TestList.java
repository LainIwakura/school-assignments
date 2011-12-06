package Lab09;

public class TestList
{
  public static void main(String[] args)
  {
    int testData[] = {5, 2, 7, 8, 3, 10, 2, 6};
    SortedListOfInt myList = new SortedListOfInt();
    for (int i = 0; i < testData.length; i++)
      myList.addElement(testData[i]);
    
    System.out.printf("%s", myList.retrieve(3, 7));
  }
}
