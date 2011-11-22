package Assignment8;

public class Assignment8Tester {
	public static void main(String[] args)
	{
		SortedList<MyDate> myDateList;
		SortedList<Name> myNameList;

		myDateList = new SortedList<MyDate>();
		myDateList.insert(new MyDate("25/2/2008"));
		myDateList.insert(new MyDate("10/4/2009"));
		myDateList.insert(new MyDate("7/11/2007"));
		myDateList.insert(new MyDate("24/2/2008"));

		for(MyDate aDate = myDateList.getFirst(); !(aDate == null);
		    aDate = myDateList.getNext()){
			System.out.println(aDate + "\n");
		}

		myNameList = new SortedList<Name>();
		myNameList.insert(new Name("John Smith"));
		myNameList.insert(new Name("Mary Nicole Smith"));
		myNameList.insert(new Name("Joseph Banks"));
		myNameList.insert(new Name("Chad Burman"));
		myNameList.insert(new Name("Sam Todd"));
		myNameList.insert(new Name("Tammy Todd"));

		for(Name aName = myNameList.getFirst(); !(aName == null);
		    aName = myNameList.getNext()){
			System.out.println(aName + "\n");
		}

	}

}
