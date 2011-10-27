/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Date: Sept. 25th 2011
 *
 * Purpose: To do various functions with strings.
 *
 */

import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.*;

class ProcessString
{
  // Display all of the words in our string using the string Tokenizer class
  public void displayWords(String str)
  {
    StringTokenizer st = new StringTokenizer(str);
    while (st.hasMoreTokens())
      System.out.println(st.nextToken());
  }

  // Find the longest word
  public String findLongestWord(String str)
  {
    String longestWord = ""; // We keep a variable for the longest word, initially it's empty.
    String temp = ""; // Temp variable.
    int len = 0;
    StringTokenizer st = new StringTokenizer(str);
    while (st.hasMoreTokens())
    {
      temp = st.nextToken(); // The temp variable is the next token
      if (temp.length() > longestWord.length()) // If it's longer than the current longest word
        longestWord = temp; // that token becomes the new longest word
    }

    return longestWord;
  }

  // Same as Lab02
  public static int findVowels(String str)
  {
    int num = 0;

    // For each character in the string
    for (int i = 0; i < str.length(); i++)
    {
      // If it's a vowel...
      if ("AEIOUaeiou".indexOf(str.charAt(i)) >= 0)
        num++; // Increment our counter...
    }

    return num; // Return the count.
  }
}

public class moreStrings
{
  public static void main(String[] args)
  {
    Scanner scan = new Scanner(System.in);
    String ourString = scan.nextLine();
    String longestWord = "";
    int numVowels = 0;

    ProcessString processor = new ProcessString();

    processor.displayWords(ourString);
    longestWord = processor.findLongestWord(ourString);
    numVowels = processor.findVowels(ourString);

    System.out.println("The longest word is: " + longestWord);
    System.out.println("The total number of vowels is: " + numVowels);
  } 
}
