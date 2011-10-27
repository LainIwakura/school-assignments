package Lab5;

// Abstract class person, we won't ever create a specific person but
// we will create objects that inherit from this.
public abstract class Person {
  
  protected Name personName;
  private Person spouseOfPerson;
  
  public abstract double getSalary();

  public Person(String fullName)
  {
    this.personName = new Name(fullName);
  }

  public void setSpouse(Person spouse)
  {
    this.spouseOfPerson = spouse;
  }

  public double getFamilyIncome()
  {
    double sum = 0;

    // It knows. Just...trust it. It knows which one to call...JVM is crazzzy
    sum += getSalary();
    sum += spouseOfPerson.getSalary();

    return sum;
  }

  public Name getPersonName()
  {
    return personName;
  }

  public String toString()
  {
    String retString = "Name is: " + personName.toString() + (spouseOfPerson == null ? "\n" : "");
    if (spouseOfPerson != null)
      retString += " Married to: " + this.spouseOfPerson.personName.toString() + "\n";

    return retString;
  }


}
