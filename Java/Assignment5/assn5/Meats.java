package assn5;

public class Meats extends Food
{
  public int amountOfFat = 0;
  
  // Construct some meat / fish
  public Meats(String name, double price, double quantity, int fat)
  {
    super(name, price, quantity);
    this.amountOfFat = fat;
  }

  public double getFat(double qty)
  {
    return amountOfFat * qty;
  }
}
