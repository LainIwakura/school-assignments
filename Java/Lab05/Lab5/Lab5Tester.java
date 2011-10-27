package Lab5;

public class Lab5Tester{
	public static void main(String[] args){
		NewWorker w1, w2, w3, w4, w5;
		Student s1, s2;
		Household myFamily;
		s1 = new Student("Edward Teller", "Physics");
		s2 = new Student("Liz Powell", "Computer Science");

		w1 = new NewWorker("Robert William Hunter", 
                                "23/10/2005", 35000.00);
		w2 = new NewWorker("Mary Jane Hull", "06/09/2007");

		w2.setSalary(40000.00);

		myFamily = new Household(5);

		myFamily.insertNewHouseholdMember(s1);
		myFamily.insertNewHouseholdMember(s2);
		myFamily.insertNewHouseholdMember(w1);
		myFamily.insertNewHouseholdMember(w2);


		w1.setSpouse(w2);
		w2.setSpouse(w1);

		System.out.println("Total family income of Robert and Mary "
			                + w1.getFamilyIncome());
		System.out.println("\nDescription of the family is\n"
			                + myFamily.toString());
	}
}
