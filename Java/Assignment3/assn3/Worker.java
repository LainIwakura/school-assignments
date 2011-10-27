package assn3;

public class Worker
{
  // Some variables we need for this class.
  // Private so we don't have access concerns.
  private static int howManyWorkers;
  private int workerNumber;
  private Name workerName;
  private MyDate dateJoiningCompany;
  private double salary;
  private Worker supervisor;

  public Worker(String name, String date, double salary)
  {
    this.workerName = new Name(name);
    this.dateJoiningCompany = new MyDate(date);
    this.salary = salary;

    ++howManyWorkers; // Increment the number of workers

    this.workerNumber = howManyWorkers; // Set the workers unique number to the current value of howManyWorkers
  }

  public Worker(String name, String date)
  {
    this.workerName = new Name(name);
    this.dateJoiningCompany = new MyDate(date);
    this.salary = 0.0;

    ++howManyWorkers;

    this.workerNumber = howManyWorkers;
  }

  public void setSalary(double salary)
  {
    this.salary = salary;
  }

  public void setSupervisor(Worker supervisor)
  {
    this.supervisor = supervisor;
  }

  public static int getHowManyWorkers()
  {
    return howManyWorkers;
  }

  public Name getSupervisorName()
  {
    return supervisor.workerName;
  }

  public String toString()
  {
    String retString = "";
    String supervisorName = "";

    if (this.supervisor == null)
      supervisorName = "None";
    else
      supervisorName = this.supervisor.workerName.toString();

    retString = "Worker Number: " + Integer.toString(this.workerNumber) + "\n";
    retString += "Name: " + this.workerName.toString() + "\n";
    retString += "Date Joined: " + this.dateJoiningCompany.toString() + "\n";
    retString += "Supervisor: " + supervisorName + "\n";
    retString += "Salary: " + Double.toString(this.salary);

    return retString;
  }
} 
