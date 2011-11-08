package assn6;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Assignment6
{
  private MainFrame mFrame;
  private NameFrame nFrame;
  private DateFrame dFrame;

  private JLabel mainText;
  private JLabel sortedNames;
  private JLabel sortedDates;

  private JButton findDates;
  private JButton findNames;

  private JTextField inputLine;

  private JTextArea namesOutput;
  private JTextArea datesOutput;

  private Sortable[] items = new Sortable[50];

  private int curItem = 0;

  class MainFrame extends JFrame 
  {
    public MainFrame() {
    super("Name-Date Frame");
      setLayout(new FlowLayout());
      mainText = new JLabel("Enter a Date or Name");
      add(mainText);
      inputLine = new JTextField(20);
      inputLine.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e)
        {
          String input;
          input = inputLine.getText();
          if (input.indexOf("/") > 0)
          {
            items[curItem++] = new MyDate(input); 
          }
          else
            items[curItem++] = new Name(input);

          inputLine.setText("");
        }
      });
      add(inputLine);
      findDates = new JButton("Find Sorted Dates");
      findDates.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e)
        {
          Sort.sortAnything(items, curItem);
          for(Sortable a : items)
            if (a instanceof MyDate)
              datesOutput.append(a + "\n"); 
        }
      });
      add(findDates);
      findNames = new JButton("Find Sorted Names");
      findNames.addActionListener(new ActionListener() {
        public void actionPerformed(ActionEvent e)
        {
          Sort.sortAnything(items, curItem);
          for(Sortable a : items)
            if (a instanceof Name)
              namesOutput.append(a + "\n");
        }
      });
      add(findNames);
      setSize(450, 450);
      setVisible(true);
    }
  }

  class NameFrame extends JFrame
  {
    public NameFrame() {
      super("Name Frame");
      setLayout(new FlowLayout());
      sortedNames = new JLabel("The sorted Names are as follows:");
      add(sortedNames);
      namesOutput = new JTextArea(20, 20);
      add(namesOutput);
      setSize(450, 450);
      setVisible(true);
    }
  }

  class DateFrame extends JFrame
  {
    public DateFrame() {
      super("Date Frame");
      setLayout(new FlowLayout());
      sortedDates = new JLabel("The sorted Dates are as follows:");
      add(sortedDates);
      datesOutput = new JTextArea(20, 20);
      add(datesOutput);
      setSize(450, 450);
      setVisible(true);
    }
  }

  public Assignment6()
  {
    mFrame = new MainFrame();
    nFrame = new NameFrame();
    dFrame = new DateFrame();
  }

  public static void main(String[] args)
  {
    Assignment6 a6 = new Assignment6();
  }
}
