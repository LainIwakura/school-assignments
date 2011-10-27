package assn4;

public class Person {
  
  protected Name personName;
  private Person spouseOfPerson;

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

    if (this instanceof NewWorker)
      sum += ((NewWorker)this).getSalary();

    if (spouseOfPerson instanceof NewWorker)
      sum += ((NewWorker)this.spouseOfPerson).getSalary();

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
