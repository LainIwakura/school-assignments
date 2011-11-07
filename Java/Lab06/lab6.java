import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class myFrame extends JFrame implements ActionListener
{
  private JLabel mainText;
  private JTextField inputLine;
  private JTextArea outputBox;
  private JButton oddNums;
  private JButton evenNums;
  private int[] intArray = new int[10];
  private int curInt = 0;
  
  public myFrame()
  {
    super("Laboratory 6");
    setLayout(new FlowLayout());
    mainText = new JLabel("Enter an Integer and press CR\n");
    add(mainText);
    inputLine = new JTextField(20);
    inputLine.addActionListener(this);
    add(inputLine);
    oddNums = new JButton("Find Odd Numbers");
    oddNums.addActionListener(this);
    add(oddNums);
    evenNums = new JButton("Find Even Numbers");
    evenNums.addActionListener(this);
    add(evenNums);
    outputBox = new JTextArea(15, 15);
    add(outputBox);
  }

  public void actionPerformed(ActionEvent event)
  {
    String input;
    if (event.getSource() == inputLine)
    {
      input = inputLine.getText();
      intArray[curInt++] = Integer.parseInt(input);
      inputLine.setText("");
    }
    else if (event.getSource() == oddNums)
    {
      outputBox.append("The odd numbers are:\n");
      for (int i = 0; i < curInt; i++)
      {
        if (!isEven(intArray[i]))
          outputBox.append(intArray[i] + "\n");
      }
    }
    else if (event.getSource() == evenNums)
    {
      outputBox.append("The even numbers are:\n");
      for (int i = 0; i < curInt; i++)
      {
        if (isEven(intArray[i]))
          outputBox.append(intArray[i] + "\n");
      }
    }
  }

  private boolean isEven(int i)
  {
    return ((i % 2 == 0) ? true : false);
  }
}

public class lab6
{
  public static void main(String[] args)
  {
    myFrame aFrame = new myFrame();
    aFrame.setSize(350, 300);
    aFrame.setVisible(true);
  }
}
