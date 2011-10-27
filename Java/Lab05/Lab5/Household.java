package Lab5;

public class Household
{
  // An array of household members!
  public Person[] householdMembers;
  // We're counting the number of people!
  public int numOfPeople = 0;

  // Construct a household with 10 members!
  public Household()
  {
    householdMembers = new Person[10];
  }

  // Construct a household with n members!
  public Household(int n)
  {
    householdMembers = new Person[n];
  }

  // Add a new member to our household!
  public void insertNewHouseholdMember(Person p)
  {
    householdMembers[numOfPeople] = p;
    ++numOfPeople;
  }

  public String toString()
  {
    String retString = "";
    for (int i = 0; i < numOfPeople; i++)
    {
      // Based on the object type it will call the appropriate toString()
      // method.
      retString += householdMembers[i].toString();
    }

    return retString;
  }
}
