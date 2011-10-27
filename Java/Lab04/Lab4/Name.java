package Lab4;

import java.util.StringTokenizer;

public class Name {
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
