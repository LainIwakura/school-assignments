package assn6;

import java.util.StringTokenizer;

public class MyDate implements Sortable
{
  int day, month, year;

  public MyDate(String dateToParse)
  {
    StringTokenizer st = new StringTokenizer(dateToParse, "/");
    day = Integer.parseInt(st.nextToken());
    month = Integer.parseInt(st.nextToken());
    year = Integer.parseInt(st.nextToken());
  }

  public MyDate(MyDate date)
  {
    this(date.day + "/" + date.month + "/" + date.year);
  }

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
  
  public boolean lessThan(Sortable date)
  {
    MyDate temp;
    if (date instanceof MyDate)
    {
      temp = (MyDate)date;
      if (this.year < temp.year)
        return true;
      else if (this.year == temp.year && this.month < temp.month) 
        return true;
      else if (this.year == temp.year && this.month == temp.month && this.day < temp.day)
        return true;
      else
        return false;
    }
    else
      return true;
  } 

  public boolean equals(MyDate date)
  {
    return ((this.year == date.year && 
             this.month == date.month && 
             this.day == date.day) ? true : false);
  }
}
