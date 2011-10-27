package assn3;

import java.util.StringTokenizer;

public class MyDate
{
  // Declare some variables to hold the numeric date values
  int day, month, year;

  public MyDate(String dateToParse)
  {
    // String tokenizer uses / as a token
    StringTokenizer st = new StringTokenizer(dateToParse, "/");
    day = Integer.parseInt(st.nextToken());   // Parse the day
    month = Integer.parseInt(st.nextToken()); // Parse the month
    year = Integer.parseInt(st.nextToken());  // Parse the year
  }

  // Copy constructor
  public MyDate(MyDate date)
  {
    this(date.day + "/" + date.month + "/" + date.year);
  }

  // Output the date
  public String toString()
  {
    String dateString = "";
    String yearString = Integer.toString(this.year);
    yearString = yearString.substring(2, 4);

    switch (this.month)
    {
      case 1:
        dateString += "January ";
        break;
      case 2:
        dateString += "February ";
        break;
      case 3:
        dateString += "March ";
        break;
      case 4:
        dateString += "April ";
        break;
      case 5:
        dateString += "May ";
        break;
      case 6:
        dateString += "June ";
        break;
      case 7:
        dateString += "July ";
        break;
      case 8:
        dateString += "August ";
        break;
      case 9:
        dateString += "September ";
        break;
      case 10:
        dateString += "October ";
        break;
      case 11:
        dateString += "November ";
        break;
      case 12:
        dateString += "December ";
        break;
    }

    dateString += Integer.toString(this.day);
    dateString += ", '";
    dateString += yearString;

    return dateString;
  }
  
  // Check if a date is less than the date held by the object
  public boolean lessThan(MyDate date)
  {
    if (year < date.year)
      return true;
    else if (year == date.year && month < date.month) 
      return true;
    else if (year == date.year && month == date.month && day < date.day)
      return true;
    else
      return false;
  } 

  // Check if the dates are equal
  public boolean equals(MyDate date)
  {
    return ((year == date.year && 
             month == date.month && 
             day == date.day) ? true : false);
  }
}
