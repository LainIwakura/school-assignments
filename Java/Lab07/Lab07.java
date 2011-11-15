import java.util.StringTokenizer;

class ArgumentNotValidException extends Exception
{
  private String error;

  public ArgumentNotValidException()
  {
    super();
    error = "The argument was not valid";
  }

  public String getMessage()
  {
    return error;
  }
}

class MyDate
{
  int day, month, year;

  public MyDate(String dateToParse)
  {
    try
    {
      StringTokenizer st = new StringTokenizer(dateToParse, "/");
      if (st.countTokens() != 3)
        throw new Exception("Wrong number of tokens");
      day = Integer.parseInt(st.nextToken());
      month = Integer.parseInt(st.nextToken());
      year = Integer.parseInt(st.nextToken());
      if (month == 2 && day >= 29)
        throw new Exception("Feburary date out of range");
    }
    catch (Exception e)
    {
      System.out.println("Error: " + e.getMessage());
    }
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
  
  public boolean lessThan(Object date) throws ArgumentNotValidException
  {
    if (!(date instanceof MyDate))
      throw new ArgumentNotValidException();

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

// DD/MM/YYYY
public class Lab07
{
  public static void main(String[] args)
  {
    MyDate d1, d2, d3, d4;
    d1 = new MyDate("30/02/1992");
    d3 = new MyDate("04/xx/xy");
    d2 = new MyDate("02/38");
    
    d4 = new MyDate("02/04/2011");
    try
    {
      d4.lessThan("Hello");
    }
    catch(Exception e)
    {
      System.out.println("Error: " + e.getMessage());
    }
  }
}
