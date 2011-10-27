package assn4;

public class Manager extends NewWorker
{
  private NewWorker[] employeesSupervised = new NewWorker[10];
  private int numWorkersSupervised = 0;
  
  public Manager(String name, String date)
  {
    super(name, date);
  }

  public Manager(String name, String date, double salary)
  {
    super(name, date, salary);
  }

  public double getSalary()
  {
    double sum = 0;

    if (this instanceof NewWorker)
      sum += super.getSalary();

    sum += (numWorkersSupervised * 100.00);

    return sum;
  }

  public void addWorker(NewWorker w)
  {
    if (numWorkersSupervised != 10)
    {
      employeesSupervised[numWorkersSupervised] = w;
      ++numWorkersSupervised;
    }
  }

  public void deleteWorker(NewWorker w)
  {
    for (int i = 0; i < numWorkersSupervised; i++)
    {
      if (employeesSupervised[i].equals(w))
        employeesSupervised[i] = null;

      for (int j = i; j < numWorkersSupervised - 1; j++)
        employeesSupervised[j] = employeesSupervised[j + 1];
    }
    --numWorkersSupervised;
  }

  public String toString()
  {
    String retString = "";

    retString += "Worker ID: " + workerNumber + "\n";
    retString += "Employee Name: " + personName.toString() + "\n";
    retString += "Date Joining Company: " + dateJoiningCompany.toString() + "\n";
    if (this.supervisor != null)
      retString += "Supervisor: " + this.supervisor.personName.toString() + "\n";
    else
      retString += "Supervisor: None\n";
    retString += "Salary: " + this.getSalary() + "\n";
    retString += "Employees of this Manager:\n";
    for (int i = 0; i < numWorkersSupervised; i++)
      retString += "\t" + employeesSupervised[i].personName.toString() + "\n";

    return retString;
  }
}
