/* Written By: Zachary Easterbrook
 * Student ID: 103163420
 * Written On: Friday, September 9th, 2011
 * 
 * The purpose of this program is to read in values
 * from the console and calculate a net pay based on
 * parameters defined in the assignment.
 */

import java.io.*;
import java.util.Scanner;

public class employeeSalary {

  /* Since 9999 is a sort of arbitrary number
   * we make it constant for better readability
   * and to avoid "Magic Numbers"
   */
  private static final int STOP_NUM = 9999;

  /* This function takes the salary as input and
   * based on parameters defined in the assignment
   * it calculates a net pay for the employee
   */
  public static double calculateNetSalary(double salary)
  {
    if (salary <= 1000.00)
      return (salary - 0.0);
    else if (salary > 1000.00 && salary <= 3000.00)
      return (salary - ((salary - 1000.00) * 0.10));
    else
      return (salary - ((salary - 1000.00) * 0.25));
  }

  /* This is our main entrance point for the program.
   * We declare some variables we'll need as well
   * as create a scanner object so we can read input.
   *
   * We use a do/while loop for getting the data since we
   * expect to run this code at least once, even if it only
   * runs to receive 9999 as input.
   */
  public static void main(String[] args) 
  {
    int employeeNumber = 0;
    double employeeSalary = 0.0;
    double netPay = 0.0;
    Scanner scan = new Scanner(System.in);

    do
    {
      System.out.println("type an employee #, a space, his/her salary followed by a CR (Carriage Return)");
      employeeNumber = scan.nextInt();
      // Before scanning the salary we check if it's STOP_NUM, if it is we break
      if (employeeNumber == STOP_NUM)
        break;

      employeeSalary = scan.nextDouble();
      netPay = calculateNetSalary(employeeSalary);
      System.out.printf("The net pay of employee %d is %.3f%n", employeeNumber, netPay); 
    } while (true); // This condition is fine since we break out of the loop in the if statement
  }
}
