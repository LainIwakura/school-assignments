package Lab4;

public class NewWorker extends Person
{
  // Some variables we need for this class.
  // Private so we don't have access concerns.
  private static int howManyWorkers;
  private int workerNumber;
  private MyDate dateJoiningCompany;
  private double salary;
  private NewWorker supervisor;

  public NewWorker(String name, String date)
  {
    this(name, date, 0.0);
  }

  public NewWorker(String name, String date, double salary)
  {
    super(name);
    this.dateJoiningCompany = new MyDate(date);
    this.salary = salary;

    ++howManyWorkers; // Increment the number of workers

    this.workerNumber = howManyWorkers; // Set the workers unique number to the current value of howManyWorkers
  }

  public void setSalary(double salary)
  {
    this.salary = salary;
  }

  public double getSalary()
  {
    return this.salary;
  }

  public void setSupervisor(NewWorker supervisor)
  {
    this.supervisor = supervisor;
  }

  public static int getHowManyWorkers()
  {
    return howManyWorkers;
  }

  public Name getSupervisor()
  {
    return supervisor.getPersonName();
  }

  public String toString()
  {
    String retString = "";
    String supervisorName = "";

    if (this.supervisor == null)
      supervisorName = "None";
    else
      supervisorName = this.supervisor.getPersonName().toString();

    retString = "Worker Number: " + Integer.toString(this.workerNumber) + "\n";
    retString += super.toString();
    retString += "Date Joined: " + this.dateJoiningCompany.toString() + "\n";
    retString += "Supervisor: " + supervisorName + "\n";
    retString += "Salary: " + Double.toString(this.salary);

    return retString;
  }
} 
