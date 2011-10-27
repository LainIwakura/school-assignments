package assn5;

public class Fruit extends Food
{
  public int amountOfSugar = 0;  
  
  // Construct a fruit
  public Fruit(String name, double price, double quantity, int sugar)
  {
    super(name, price, quantity);
    this.amountOfSugar = sugar;
  }
  
  public double getSugar(double quantity)
  {
    return amountOfSugar * quantity;
  }
}
