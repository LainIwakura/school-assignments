package Lab08;

import java.util.ArrayList;

public class Queue<T>
{
  private ArrayList<T> arr;

  public Queue()
  {
    this.arr = new ArrayList<T>();
  }

  public T addToBack(T t)
  {
    this.arr.add(t);
    return t;
  }

  public T removeFromFront()
  {
    T t = this.arr.remove(this.arr.size() -1);
    return t;
  }

  public boolean emptyQueue()
  {
    return this.arr.isEmpty();
  }
}
