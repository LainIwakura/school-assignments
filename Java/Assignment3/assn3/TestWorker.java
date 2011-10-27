package assn3;

public class TestWorker {
  public static void main(String[] args) {
    Worker w1, w2, w3;
    w1 = new Worker ("Robert  William Hunter", "23/10/2005", 35000.00);
    w2 = new Worker ("John Smith", "15/11/2005", 25000.00);
    w3 = new Worker ("Mary Jane Hull", "06/09/2007");
    w2. setSalary(20000.00);
    w2.setSupervisor(w1);
    w3.setSupervisor(w1);
    System.out.println("Number of workers = " + Worker.getHowManyWorkers() +" \n");
    System.out.println("Supervisor of John is " + w2.getSupervisorName());
    System.out.println(w1.toString()+" \n");
    System.out.println(w2.toString()+" \n");
    System.out.println(w3.toString());
  }
}
