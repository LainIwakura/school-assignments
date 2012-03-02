import java.io.*;
import java.util.*;

%%

%{ 
  int identifiers = 0, linecount = 0, quotedstrings = 0, numbers = 0, keywords = 0;
  public static void main(String[] args) throws java.io.IOException {
    A3 lexer = new A3(new BufferedReader(new FileReader(new File("A2.input"))));
    lexer.yylex();
  }
%}
%line
%type void
%class A3
%eofval{
    BufferedWriter out = new BufferedWriter(new FileWriter("A2.output"));
    out.write("identifiers: " + identifiers + "\nkeywords: " + keywords + "\n"+
               "numbers: " + numbers + "\nlines: " + yyline + "\nquotedString: " + quotedstrings + "\n");
    out.close();
    return;
%eofval}

%state COMMENT

IDENTIFIER = ([a-zA-Z][a-zA-Z0-9]*)
KEYWORD = (IF|ELSE|WRITE|READ|RETURN|BEGIN|END|MAIN|INT|REAL)
QUOTEDSTR = \"[^\"]*\"
NUMBER = [0-9]+(\.[0-9]+)?

%%

<YYINITIAL> {QUOTEDSTR} { ++quotedstrings; }
<YYINITIAL> "/**" { yybegin(COMMENT); }
<COMMENT> "**/" { yybegin(YYINITIAL); }
<COMMENT>.|\n|\r {}

<YYINITIAL> {KEYWORD} { ++keywords; }
<YYINITIAL> {NUMBER} { ++numbers; }
<YYINITIAL> {IDENTIFIER} { ++identifiers; }
<YYINITIAL> \r|\n {}
<YYINITIAL> . {}
