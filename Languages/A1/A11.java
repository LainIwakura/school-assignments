import java.io.*;
import java.util.*;

public class A11
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader fileInput = new BufferedReader(new FileReader(args[0]));
		ArrayList<String> keywords = new ArrayList<String>(Arrays.asList("IF", "ELSE", "WRITE", "READ", "RETURN", "BEGIN", "END", "MAIN", "INT", "REAL")); 
		String line = "";
		HashSet<String> s = new HashSet<String>();
		int identifiers = 0;

		while ((line = fileInput.readLine()) != null)
		{
			StringTokenizer st = new StringTokenizer(line, ";,()+-*/:=! ");
			while (st.hasMoreTokens())
			{
				String tok = st.nextToken();
				if (keywords.contains(tok) || tok.startsWith("\""))
					continue;
				else
					s.add(tok);
			}
		}
		fileInput.close();
		BufferedWriter out = new BufferedWriter(new FileWriter("A1.output"));
		out.write("identifiers:"+s.size()+"\n");
		out.close();
	}
}
