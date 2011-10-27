package Lab4;

public class Lab4Tester {
	public static void main(String[] args){
		NewWorker w1, w2, w3, w4, w5;
		Person p1, p2;
		MyDate d1, d2, d3, d4;

		p1 = new Person("Edward Teller");
		p2 = new Person("Liz Powell");

		w1 = new NewWorker ("Robert William Hunter", "23/10/2005", 35000.00);
		w2 = new NewWorker ("John Smith", "15/11/2005", 25000.00);
		w3 = new NewWorker ("Mary Jane Hull", "06/09/2007");
		w4 = new NewWorker ("Richard M. Harry", "01/08/2004");
		w5 = new NewWorker ("Jessica Chowhan", "21/01/2006", 30000.00);

		w3.setSalary(40000.00);
		w4.setSalary(53000.00);
		w4.setSalary(55000.00);
		w4.setSalary(58000.00);

		w2.setSupervisor(w3);
		w3.setSupervisor(w4);
		w1.setSupervisor(w3);
		w5.setSupervisor(w4);

		w3.setSpouse(p1);
		p1.setSpouse(w3);

		w2.setSpouse(p2);
		p2.setSpouse(w2);

		w1.setSpouse(w5);
		w5.setSpouse(w1);


		System.out.println("Supervisor of w1 is " + w1.getSupervisor());
		System.out.println("w2 is " + w2);
		System.out.println("w3 is " + w3);
		System.out.println("w4 is " + w4);
		System.out.println("w5 is " + w5);
		System.out.println("Total family income of Robert "
			                + w1.getFamilyIncome());
		System.out.println("Total family income of Edward "
			                + p1.getFamilyIncome());
	}

}
