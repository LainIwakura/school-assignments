package assn5;

public class Carbs extends Food
{
  public int amountOfSugar = 0; 

  // Construct some items containing carbs
  public Carbs(String name, double price, double quantity, int sugar)
  {
    super(name, price, quantity);
    this.amountOfSugar = sugar;
  }

  public double getSugar(double quantity)
  {
    return amountOfSugar * quantity;
  }
}
