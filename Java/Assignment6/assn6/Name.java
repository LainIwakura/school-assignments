package assn6;

import java.util.StringTokenizer;

public class Name implements Sortable
{
  // These are our name variables
  String firstName, middleName, lastName;

  public Name(String nameToParse)
  {
    StringTokenizer st = new StringTokenizer(nameToParse);
    if (st.countTokens() == 2) // If we only have two tokens, we have no middle name.
    {
      firstName = st.nextToken();
      middleName = "";
      lastName = st.nextToken();
    }
    else
    {
      firstName = st.nextToken();
      middleName = st.nextToken();
      lastName = st.nextToken();
    } 
  }

  // Copy constructor
  public Name(Name name)
  {
    this(name.firstName + name.middleName + name.lastName);
  }

  public void setName(String firstName, String middleName, String lastName)
  {
    this.firstName = firstName;
    this.middleName = middleName;
    this.lastName = lastName;
  }

  public boolean lessThan(Sortable anotherName)
  {
    Name temp;
    if (anotherName instanceof Name)
    {
      temp = (Name)anotherName;
      if (this.firstName.compareTo(temp.firstName) < 0)
      {
        return true;
      }
      else if (this.firstName.compareTo(temp.firstName) == 0 && 
               this.lastName.compareTo(temp.lastName)    < 0)
      {
        return true;
      }
      else if (this.firstName.compareTo(temp.firstName) == 0 && 
               this.lastName.compareTo(temp.lastName)   == 0 &&
               this.middleName.compareTo(temp.middleName) < 0)
      {
        return true;
      }
      else
        return false;
    }
    else
      return false;
  }

  // Print the name out in a specified format
  public String toString()
  {
    String retString = "";
    retString += this.lastName + ", " + this.firstName + " ";
    if (!this.middleName.equals(""))
      retString += this.middleName.charAt(0) + ".";

    return retString;
  }
}
