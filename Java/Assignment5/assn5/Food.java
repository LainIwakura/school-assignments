package assn5;

public abstract class Food
{
  public String name;
  public double price = 0.0;
  public double quantity = 0.0;

  public Food(String name, double price, double quantity)
  {
    this.name = name;
    this.price = price;
    this.quantity = quantity;
  }
  
  public double totalPrice(double qty)
  {
    return this.price * qty;
  }

  // After we sell something, we update the instance variable 
  public void updateInventory(double sold)
  {
    this.quantity -= sold;
  }
}
