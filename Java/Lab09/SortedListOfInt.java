package Lab09;

public class SortedListOfInt extends ListGeneral
{
  public void addElement(int x)
  {
    if (listIsEmpty())
      addAfterCurrent(x);
    else
    {
      for (restart(); !endOfList(); getNextNode())
      {
        if ((Integer)currentValue() >= x)
        {
          addBeforeCurrent(x);
          return;
        }
      }
      addBeforeCurrent(x);
    }
  }

  public String retrieve(int lowerLimit, int upperLimit)
  {
    String retString = "";
    restart();

    retString += "The numbers between " + lowerLimit + " and " + upperLimit + " are as follows:\n";
    while (!endOfList())
    {
      if ((Integer)currentValue() >= lowerLimit && (Integer)currentValue() <= upperLimit)
        retString += currentValue() + ";\n";

      getNextNode();
    }

    return retString;
  }
}
