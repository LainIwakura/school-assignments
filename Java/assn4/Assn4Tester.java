package assn4;

public class Assn4Tester
{
  public static void main(String[] args)
  {
    Manager m1, m2;  
    NewWorker w1, w2, w3, w4, w5, w6;

    m1 = new Manager("Haruhi Suzumiya", "10/17/2011", 50000.00);
    m2 = new Manager("Konata Izumi", "10/15/2011", 60000.00);

    w1 = new NewWorker("Yuki A. Nagato", "12/13/2011", 3000.00);
    w2 = new NewWorker("Mikuru Asahina", "12/14/2011", 5000.00);
    w3 = new NewWorker("Itsuki Koizumi", "12/15/2011", 4000.00);

    w4 = new NewWorker("Tsukasa Hiiragi", "11/13/2010");
    w5 = new NewWorker("Kagami Hiiragi", "10/12/2009", 7000.00);
    w6 = new NewWorker("Miyuki Takara", "10/10/2010", 6000.00);

    m1.addWorker(w1);
    m1.addWorker(w2);
    m1.addWorker(w3);

    m2.addWorker(w4);
    m2.addWorker(w5);
    m2.addWorker(w6);

    m1.setSupervisor(m2);

    m1.deleteWorker(w2);

    System.out.println(m1.toString());
    System.out.println(m2.toString());
  }
}
