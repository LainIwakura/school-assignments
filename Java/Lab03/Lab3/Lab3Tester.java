package Lab3;

public class Lab3Tester {
  public static void main(String args[]){    
    MyDate dateArray1[], dateArray2[], anotherDate;
    int index1, index2;

    dateArray1 = new MyDate[3]; // Create an array of MyDate
    dateArray1[0] = new MyDate("26/05/1999"); // Create three elements of dataArray1 by creating three objects of class MyDate
    dateArray1[1] = new MyDate("08/06/1994");
    dateArray1[2] = new MyDate("15/03/2000");

    dateArray2 = new MyDate[3];
    dateArray2[0] = new MyDate("25/05/1999"); // Create three elements of dataArray1 by creating three objects of class MyDate
    dateArray2[1] = new MyDate("25/01/2000");
    dateArray2[2] = new MyDate("26/05/1999"); 

    for (index2 = 0; index2 < dateArray2.length;index2++){   
      for (index1 = 0; index1 < dateArray1.length; index1++){   
        if (dateArray2[index2].lessThan(dateArray1[index1])) // Compare each elements in dataArray1 with each element of dateArray2
          System.out.println(dateArray2[index2].toString() 
              + " is less than " 
              + dateArray1[index1].toString());
        else System.out.println(dateArray2[index2].toString() 
              + " is not less than " 
              + dateArray1[index1].toString() + " \n");
        } 
    }

    if (dateArray2[2].equals(dateArray1[0])){
      System.out.println(dateArray2[2].toString() 
        + " is the same date as " 
        + dateArray1[0].toString());
    } else {
      System.out.println("Cannot happen!!");
    }

    if (dateArray2[2].equals(dateArray1[1])){
      System.out.println(dateArray2[2].toString() 
        + " is not the same date as " 
        + dateArray1[0].toString() + "\n are you sure this is OK?");
    } else {
      System.out.println("You got it right!!");
    }

    anotherDate = new MyDate(dateArray2[1]);
    if (dateArray2[1].equals(anotherDate)){
      System.out.println(dateArray2[1] 
        + " is the same date as " 
        + anotherDate);
    } else {
      System.out.println("Are you sure???");
    }

  }
}
