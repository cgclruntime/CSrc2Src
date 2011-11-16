D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include <stdio.h>
#include "y.tab.h"
#include <string>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
set<string> st[100];
vector<string>sl;
vector<string>sp;
int level=0;
void count();

int holdprint;
int comment();
int include_stuff();
int define_stuff();
int check_type();
string tmp;
%}

%%
"/*"			{ comment(); }
#\s*include		{ include_stuff(); }
#\s*define		{ define_stuff();}
"auto"			{ count(); return(AUTO); }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count();sp.push_back("char"); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); sp.push_back("double");return(DOUBLE); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ count(); return(EXTERN); }
"float"			{ count();sp.push_back("float"); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"inline"		{ count(); return(INLINE); }
"int"			{ count(); sp.push_back("int");return(INT); }
"long"			{ count(); sp.push_back("long");return(LONG); }
"register"		{ count(); return(REGISTER); }
"restrict"		{ count(); return(RESTRICT); }
"return"		{ count(); return(RETURN); }
"short"			{ count(); sp.push_back("short");return(SHORT); }
"signed"		{ count(); sp.push_back("signed");return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ count(); sp.push_back("unsigned");return(UNSIGNED); }
"void"			{ count(); sp.push_back("void");return(VOID); }
"volatile"		{ count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }
"_Bool"			{ count(); return(_BOOL); }
"_Complex"		{ count(); return(_COMPLEX); }
"_Imaginary"	{ count(); return(_IMAGINARY); }
"parallel"		{ holdprint=1;tmp="parallel";sl.push_back("parallel");return(PARALLEL); }

{L}({L}|{D})*		{ count(); sl.push_back(string(yytext));return(check_type()); }

0[xX]{H}+{IS}?		{ count(); return(CONSTANT); }
0{D}+{IS}?		{ count(); return(CONSTANT); }
{D}+{IS}?		{ count(); return(CONSTANT); }
L?'(\\.|[^\\'])+'	{ count(); return(CONSTANT); }

{D}+{E}{FS}?		{ count(); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ count(); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ count(); return(CONSTANT); }

L?\"(\\.|[^\\"])*\"	{ count(); return(STRING_LITERAL); }

"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); } 
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ if (holdprint) holdprint=0;else count(); sp.push_back(";");return(';'); }
("{"|"<%")		{ count(); level++;sp.push_back("{");sl.push_back("{");return('{'); }
("}"|"%>")		{ 
	count();
	st[level].clear(); 
	level--;
	sl.push_back("}");
	sp.push_back("}");
	//printf("level=%d",level);
	return('}'); 
}
","			{ count(); sp.push_back(",");return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); sl.push_back("(");sp.push_back("(");return('('); }
")"			{ count(); sl.push_back(")");sp.push_back(")");return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
"?"			{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* ignore bad characters */ }

%%



int yywrap()
{
	return(1);
}




int comment()
{
	/*char c, c1;

loop:
	while ((c = yyinput()) != '*' && c != 0)
		putchar(c);

	if ((c1 = yyinput()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);*/
		return 1;
}


int column = 0;
int	row = 0;
void count()
{
	int i;
	if (!holdprint)	printf("%s",yytext);
	else tmp+=yytext;
	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			{column = 0;row ++;}
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

}
int include_stuff() {
	char c;
	printf("#include");
	while ((c=yyinput())!='\n') printf("%c",c);
	printf("\n");
	return 1;
}
int define_stuff() {
	char c;
	printf("#define");
	while ((c=yyinput())!='\n') printf("%c",c);
	printf("\n");
	return 1;
}

int check_type()
{
	string tocheck(yytext);
	for (int i=level;i>=0;i--) {
		if (st[i].find(tocheck)!=st[i].end()) {
			//cout<<"ret para";
			if (!holdprint) {
				holdprint=1;
				tmp="";
			}
			return(PARAFUNC); 
		}
	}
	return(IDENTIFIER);
}


