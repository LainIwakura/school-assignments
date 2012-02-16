import java.io.*;
import java.util.*;

class UseLexer {
  public static void main(String[] args) throws java.io.IOException {
    MyLexer2 lexer=new MyLexer2(new BufferedReader(new FileReader(new File("A2.input"))));
    Token t;
    int identifiers = 0;
    int linecount = 0;
    int quotedstrings = 0;
    int numbers = 0;
    int keywords = 0;
    while ((t=lexer.yylex())!=null)
    {
      if (t.type.equals("COMMENT")) continue;
      if (t.line >= linecount) linecount = t.line;
      if (t.type.equals("QUOTE")) ++quotedstrings;
      if (t.type.equals("KEY")) ++keywords;
      if (t.type.equals("NUM")) ++numbers;
      if (t.type.equals("ID")) ++identifiers;
    }
    linecount++;

    BufferedWriter out = new BufferedWriter(new FileWriter("A2.output"));
    out.write("identifiers: " + identifiers + "\nkeywords: " + keywords + "\n"+
               "numbers: " + numbers + "\nlines: " + linecount + "\nquotedString: " + quotedstrings + "\n");
    out.close();
  }
}

class Token {
  String type;
  String text;
  int line;
  Token(String t, String txt, int l){type=t; text=txt; line=l; }
  public String toString(){ return text+" " +type + " " +line; }
}

%%

%line
%type Token
%class MyLexer2
%eofval{ return null;
%eofval}

IDENTIFIER = [a-zA-Z][a-zA-Z0-9]*
KEYWORD = (IF|ELSE|WRITE|READ|RETURN|BEGIN|END|MAIN|INT|REAL)
COMMENT = (/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)|(//.*) 
QUOTEDSTR = \"[^\"]*\"
NUMBER = [0-9]*\.?[0-9]+

%%
{COMMENT} { return(new Token("COMMENT", yytext(), yyline));}
{KEYWORD} { return(new Token("KEY", yytext(), yyline));}
{QUOTEDSTR} { return(new Token("QUOTE", yytext(), yyline));}
{NUMBER} { return(new Token("NUM", yytext(), yyline));}
{IDENTIFIER} { return(new Token("ID", yytext(), yyline));}
\r|\n {}
. {}
