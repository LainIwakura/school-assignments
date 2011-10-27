/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Written on: Thursday September 15th, 2011
 *
 */

public class stringStuff {

  // Determine if a string is a palindrome
  public static boolean isPalindrome(String str)
  {
    int i = 0;
    int j = str.length() - 1;

    while (true)
    {
      if (i == j) break; // If we reach the middle 
      if (str.charAt(i) != str.charAt(j)) // If the character at i does not equal the char at j we return false, not a palindrome.
        return false;
      i++; // Increment the beginning of the string
      j--; // Decrement the ending.
    }

    return true;
  }

  // Count the number of vowels
  public static int numVowels(String str)
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

  public static String reverseString(String str)
  {
    // We use StringBuffers reverse and toString method to reverse our string
    // Although we could create a new string and push characters onto it from
    // the ending of the original string.
    String reverse = new StringBuffer(str).reverse().toString();
    return reverse;
  }

  /* Main function. We take a command line argument
   * and parse it as an int- this isn't safe but we expect
   * an integer to be entered.
   */ 
  public static void main(String[] args) {
    String ourString = args[0];
    String rev = reverseString(ourString);

    if (isPalindrome(ourString))
      System.out.println("The string: \"" + ourString + "\" is a palindrome");
    else
      System.out.println("The string: \"" + ourString + "\" is not a palindrome");

    int numOfVowels = numVowels(ourString);

    System.out.println("The string: \"" + ourString + "\" has " + numOfVowels + " vowels");

    System.out.println("The string reverse is: " + rev);

  }
}
