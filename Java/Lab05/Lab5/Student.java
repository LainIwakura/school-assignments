package Lab5;

public class Student extends Person
{
  // Hold the major!
  public String major;

  // Construct the student!
  public Student(String studentName, String major)
  {
    // Call the parent constructor!
    super(studentName);
    // Set the major!
    this.major = major;
  }

  // Get the salary!
  public double getSalary()
  {
    return 0.0;
  }

  // Describe the instance!
  public String toString()
  {
    String retString = "";
    retString += super.toString();
    retString += "Major: " + this.major + "\n";

    return retString;
  }
}
