import java.lang.System;

class A2 {
  public static void main(String[] args) throws java.io.IOException {
    Yylex yy = new Yylex(System.in);
    Yytoken t;
    while ((t = yy.yylex()) != null)
      System.out.println(t);
  }
}

class Yytoken {
  Yytoken(int index, String text, int line, int charBegin, int charEnd)
  {
    m_index = index;
    m_text = new String(text);
    m_line = line;
    m_charBegin = charBegin;
    m_charEnd = charEnd;
  }

  public int m_index;
  public String m_text;
  public int m_line;
  public int m_charBegin;
  public int m_charEnd;

  public String toString() {
    return "Token #" + m_index + ": " + m_text + " (line " + m_line + ")";
  }
}

%%

%{
  private int comment_count = 0;
%}
%line
%char
%state COMMENT

ALPHA=[A-Za-z]
DIGIT=[0-9]
NONNEWLINE_WS_CHAR=[\  \t\b\012]
WS_CHAR=[\n\  \t\b\012]
STRING_TEXT=(\\\"|[^\n\"]|\\{WS_CHAR}+\\)*
COMMENT_TEXT=([^/*\n]|[^*\n]"/"[^*\n]|[^/\n]"*"[^/\n]|"*"[^/\n]|"/"[^*\n])*

%%

<YYINITIAL> ";"  { return (new Yytoken(0, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> ","  { return (new Yytoken(1, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> "("  { return (new Yytoken(2, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> ")"  { return (new Yytoken(3, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> "+"  { return (new Yytoken(4, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> "-"  { return (new Yytoken(5, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> "*"  { return (new Yytoken(6, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> "/"  { return (new Yytoken(7, yytext(), yyline, yychar, yychar+1)); }
<YYINITIAL> ":=" { return (new Yytoken(8, yytext(), yyline, yychar, yychar+2)); }
<YYINITIAL> "==" { return (new Yytoken(9, yytext(), yyline, yychar, yychar+2)); }
<YYINITIAL> "!=" { return (new Yytoken(10, yytext(), yyline, yychar, yychar+2)); }

<YYINITIAL> {NONNEWLINE_WS_CHAR}+ { }

<YYINITIAL,COMMENT> \n { }

<YYINITIAL> "/*" { yybegin(COMMENT); comment_count = comment_count + 1; }

<COMMENT> "/*" { comment_count = comment_count + 1; }
<COMMENT> "*/" {
  comment_count = comment_count - 1;
  if (comment_count == 0)
    yybegin(YYINITIAL);
  }
<COMMENT> {COMMENT_TEXT} { }

<YYINITIAL> \"{STRING_TEXT}\" {
  String str = yytext().substring(1, yytext().length() - 1);
  return (new Yytoken(40, str, yyline, yychar, yychar + str.length()));
}
<YYINITIAL> \"{STRING_TEXT} {
  String str =  yytext().substring(1,yytext().length());
  return (new Yytoken(41,str,yyline,yychar,yychar + str.length()));
} 
<YYINITIAL> {DIGIT}+ { 
  return (new Yytoken(42,yytext(),yyline,yychar,yychar + yytext().length()));
} 
<YYINITIAL> {ALPHA}({ALPHA}|{DIGIT}|_)* {
  return (new Yytoken(43,yytext(),yyline,yychar,yychar + yytext().length()));
} 
