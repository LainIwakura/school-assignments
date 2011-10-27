package assn5;

import java.util.*;
import java.io.*;

public class GroceryInventory
{
  public static void main(String[] args)
  {
    // Make objects of all of our inventory stuff
    Meats chicken = new Meats("Chicken", 3.50, 538.32, 100);  
    Meats lamb    = new Meats("Lamb", 5.50, 365.82, 230);  
    Meats shrimp  = new Meats("Shrimp", 4.50, 404.57, 50);  

    Fruit apples  = new Fruit("Apple", 1.89, 234.65, 200);
    Fruit orange  = new Fruit("Orange", 2.36, 38, 150);

    Carbs rice    = new Carbs("Rice", 0.89, 20.0, 600);
    Carbs bread   = new Carbs("Bread", 1.14, 672, 350);

    // Some variables we need to track things / get input..
    double totalPrice = 0.0;
    double totalFat = 0.0;
    double totalSugar = 0.0;
    String thingToBuy;
    String item;
    double quantity = 0.0;

    Scanner keyboard = new Scanner(System.in);

    // We want to do this at least once so we use a do-while loop..
    do {
      // Ask what they want to buy
      System.out.println("Enter what you want to buy followed by the Amount. Enter only \"Nothing\" exit.");
      thingToBuy = keyboard.nextLine();
      StringTokenizer st = new StringTokenizer(thingToBuy, " ");
      if (thingToBuy.equalsIgnoreCase("Nothing"))
          break; // If they type nothing, we exit.
      item = st.nextToken();
      quantity = Double.parseDouble(st.nextToken());
      
      // Based on what they typed, calculate the proper info defined in the
      // classes and then update our inventory
      if (item.equalsIgnoreCase("Chicken")) 
      {
        totalPrice += chicken.totalPrice(quantity);
        totalFat += chicken.getFat(quantity);
        chicken.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Lamb")) 
      {
        totalPrice += lamb.totalPrice(quantity);
        totalFat += lamb.getFat(quantity);
        lamb.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Shrimp")) 
      {
        totalPrice += shrimp.totalPrice(quantity);
        totalFat += shrimp.getFat(quantity);
        shrimp.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Apples")) 
      {
        totalPrice += apples.totalPrice(quantity);
        totalSugar += apples.getSugar(quantity);
        apples.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Oranges")) 
      {
        totalPrice += orange.totalPrice(quantity);
        totalSugar += orange.getSugar(quantity);
        orange.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Rice")) 
      {
        totalPrice += rice.totalPrice(quantity);
        totalSugar += rice.getSugar(quantity);
        rice.updateInventory(quantity);
      }
      else if (item.equalsIgnoreCase("Bread")) 
      {
        totalPrice += bread.totalPrice(quantity);
        totalSugar += bread.getSugar(quantity);
        bread.updateInventory(quantity);
      }
    } while (true);

    // Print out the info at the end..
    System.out.printf("You spent: $%.2f\nTotal fat in the food: %.3fmg/kg\nRoughly total sugar: %.3fmg/kg\n", totalPrice, totalFat, totalSugar);
  }
}
