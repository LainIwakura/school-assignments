/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Written on: Friday September 9th, 2011
 *
 * This program is supplied a command line argument, an integer.
 * It takes this intenger and finds the next prime number greater than
 * the integer. For example, if supplied with 9 it will output 11.
 * If supplied with a prime number, it outputs that number.
 */

// We use Math.sqrt- this improves the speed of the program by 1ms.
import static java.lang.Math.sqrt;

public class nextPrimeNumber {

  /* This function takes an integer and determines if it is prime.
   * It has been optimized and will break at the first indication a number is
   * not prime.
   */
  public static boolean isPrime(int num) {
    if (num % 2 == 0 && num != 2) return false;
    for (int i = 3; i <= sqrt(num); i += 2)
      if (num % i == 0)
        return false;
    return true;
  }

  /* Main function. We take a command line argument
   * and parse it as an int- this isn't safe but we expect
   * an integer to be entered.
   */ 
  public static void main(String[] args) {
    int numberSupplied = Integer.parseInt(args[0]);
    int i = numberSupplied;

    // If it's a prime number we increment it so we find the NEXT
    // prime number
    if (isPrime(i))
      ++i;

    // While the test fails for the current number we increment and try
    // again...this is the only way to find the next prime
    while (!isPrime(i))
      ++i;
    System.out.printf("The first prime number greater than %d is %d%n", numberSupplied, i);
  }
}
