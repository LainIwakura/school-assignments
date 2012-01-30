import java.io.*;
import java.util.*;
import java.util.regex.*;

public class A12
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader fileInput = new BufferedReader(new FileReader(args[0]));
		String line = "";
		String[] lines;
		HashSet<String> s = new HashSet<String>();
    ArrayList<String> keywords = new ArrayList<String>(Arrays.asList("INT", "IF", "ELSE", "WRITE", "READ", "RETURN", "BEGIN", "END", "MAIN", "REAL"));
		Pattern p = Pattern.compile("\\b[a-zA-Z][\\w]*\\b");

		while ((line = fileInput.readLine()) != null)
		{
      line = line.replaceAll("\"[^\"]*\"", " ");
      Matcher m = p.matcher(line);
      while(m.find())
        if (keywords.contains(m.group()))
          continue;
        else
          s.add(m.group());
		}
		fileInput.close();
		BufferedWriter out = new BufferedWriter(new FileWriter("A1.output"));
		out.write("identifiers:"+s.size()+"\n");
		out.close();
	}
}
