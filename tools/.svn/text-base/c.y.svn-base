
%{
/*#define YYDEBUG 1*/
	#include <iostream>
	#include <stdio.h>
	#include <string>
	#include <set>
	#include <stdlib.h>
	#include <vector>
	#include <stdarg.h>
	#include<map>
	#include<vector>
	using namespace std;
	map<string,string>mp;
	extern set<string>st[100];
	extern vector<string>sp;
	extern int level;
	extern vector<string>sl;
	extern string tmp;	
/* prototypes */
	

	int yylex(void);
	
	void yyerror(char *s);
	int yyparse();
	string tra2(string);

%}



%union {
	int iValue;
	void * pAST;
	char *strName;
};


%token CONSTANT STRING_LITERAL SIZEOF TYPENAME PARAFUNC

%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP

%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN

%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN

%token XOR_ASSIGN OR_ASSIGN TYPE_NAME



%token TYPEDEF EXTERN STATIC AUTO REGISTER RESTRICT INLINE

%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID _BOOL _COMPLEX _IMAGINARY

%token STRUCT UNION ENUM ELLIPSIS PARALLEL



%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token<pAST> IDENTIFIER 

%nonassoc IFX
%nonassoc ELSE

%start translation_unit

%type <pAST> primary_expression postfix_expression argument_expression_list unary_expression unary_operator cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression assignment_operator expression constant_expression declaration declaration_specifiers init_declarator_list init_declarator storage_class_specifier type_specifier struct_or_union_specifier struct_or_union struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list  struct_declarator enum_specifier enumerator_list enumerator type_qualifier function_specifier declarator direct_declarator pointer type_qualifier_list parameter_type_list parameter_list parameter_declaration identifier_list type_name abstract_declarator direct_abstract_declarator typedef_name initializer initializer_list designation designator_list designator statement labeled_statement compound_statement block_item_list block_item expression_statement selection_statement iteration_statement jump_statement translation_unit external_declaration function_definition declaration_list  boolean_and_expression
%%



primary_expression:
	 IDENTIFIER											
     | CONSTANT
     | STRING_LITERAL
	 | '(' expression ')'								{  }
	   ;



postfix_expression  :
	primary_expression									{ }
	| postfix_expression '[' expression ']'				{ }
	| postfix_expression '(' ')'						{  }
    | postfix_expression '(' argument_expression_list ')'		{ ;}
    | postfix_expression '.' IDENTIFIER					{ ; }
    | postfix_expression PTR_OP IDENTIFIER				{ ; }
    | postfix_expression INC_OP							{ ; }
    | postfix_expression DEC_OP							{; }
	| '(' type_name ')' '{' initializer_list '}'		{ ; }
	| '(' type_name ')' '{' initializer_list ',' '}'	{ ; }
	| parallel_function '(' ')'						{cout<<tra2(tmp)<<";";}
	| parallel_function '(' argument_expression_list ')'	{cout<<tra2(tmp)<<";";}
	| parallel_function '<' boolean_expression '>' '(' ')'	{ cout<<tra2(tmp)<<";"; }
	| parallel_function '<' boolean_expression '>' '(' argument_expression_list ')'		{ cout<<tra2(tmp)<<";"; }
	 ;



argument_expression_list :
	assignment_expression								{ ; }
	| argument_expression_list ',' assignment_expression	{ ; }
	;

unary_expression :
	postfix_expression									{ ; }
	| INC_OP unary_expression							{ ; }
	| DEC_OP unary_expression							{ ; }
	| unary_operator cast_expression					{ ; }
	| SIZEOF unary_expression							{ ; }
    | SIZEOF '(' type_name ')'							{ ; }
	 ;

unary_operator :
	'&'													{ ; }
	| '*'												{ ; }
	| '+'												{ ; }
	| '-'												{ ; }																								
	| '~'												{ ; }
	| '!'												{ ; }
	 ;

cast_expression :
	unary_expression							{;}
	| '(' type_name ')' cast_expression			{ ; }
	 ;

multiplicative_expression : 
	cast_expression										{ ; }
	| multiplicative_expression '*' cast_expression		{ ; }
	| multiplicative_expression '/' cast_expression		{ ; }
	| multiplicative_expression '%' cast_expression		{ ; }
	 ;


additive_expression : 
	multiplicative_expression							{ ; }
	| additive_expression '+' multiplicative_expression	{ ; }
	| additive_expression '-' multiplicative_expression	{ ; }
	;

shift_expression :
	additive_expression									{ ; }
	| shift_expression LEFT_OP additive_expression		{ ; }
	| shift_expression RIGHT_OP additive_expression		{ ; }
	;



relational_expression : 
	shift_expression									{; }
	| relational_expression '<' shift_expression		{ ; }
	| relational_expression '>' shift_expression		{ ; }
	| relational_expression LE_OP shift_expression		{ ; }
	| relational_expression GE_OP shift_expression		{ ; }
	;



equality_expression :
	relational_expression								{ ; }
	| equality_expression EQ_OP relational_expression	{ }
	| equality_expression NE_OP relational_expression	{ ; }
	;



and_expression : 
	equality_expression									{ ; }
	| and_expression '&' equality_expression			{ ; }
	;


exclusive_or_expression : 
	and_expression										{ ; }
	| exclusive_or_expression '^' and_expression		{ ; }
	;

inclusive_or_expression : 
	exclusive_or_expression								{ ; }
	| inclusive_or_expression '|' exclusive_or_expression	{ ; }
	;



logical_and_expression :		
	inclusive_or_expression								{ ; }		
	| logical_and_expression AND_OP inclusive_or_expression	{ ; }
	;

logical_or_expression :
	logical_and_expression								{ ; }
	| logical_or_expression OR_OP logical_and_expression	{ ; }
	;



conditional_expression :
	logical_or_expression								{ ; }
	| logical_or_expression '?' expression ':' conditional_expression	{ ; }
	;



assignment_expression :
	conditional_expression								{ ; }
	| unary_expression assignment_operator assignment_expression	{ ; }
	;


assignment_operator : 
	'='													{ ; }
	| MUL_ASSIGN										{ ; }
	| DIV_ASSIGN										{ ; }
    | MOD_ASSIGN										{ ; }
    | ADD_ASSIGN										{ ; }
    | SUB_ASSIGN										{ ; }
    | LEFT_ASSIGN										{ ; }
    | RIGHT_ASSIGN										{; }
    | AND_ASSIGN										{ ; }
    | XOR_ASSIGN										{ ; }
    | OR_ASSIGN										{ ; }
	 ;

expression : 
	assignment_expression								{ ; }
	| expression ',' assignment_expression				{ ; }
	;



constant_expression :
	conditional_expression								{ ; }
	;



declaration :
	declaration_specifiers ';'							{ ; }
	| declaration_specifiers init_declarator_list ';'	{ ; }
	| PARALLEL IDENTIFIER parallel_function_list ';'	{ 
		int i;
		for (i=sl.size()-1;i>=0;i--) {
			if (sl[i]=="parallel") break;
		}
		for (i=i+2;i<sl.size();i++) {st[level].insert(sl[i]);}
		cout<<tra1(tmp)<<';';
	}
	;

declaration_specifiers :
	storage_class_specifier								{ ; }
	| storage_class_specifier declaration_specifiers	{ ; }
	| type_specifier									{ ; }
	| type_specifier declaration_specifiers				{; }
	| type_qualifier									{ ; }
	| type_qualifier declaration_specifiers				{ ; }
	| function_specifier								{ ;}
	| function_specifier declaration_specifiers			{ ;}
	;


init_declarator_list : 
	init_declarator										{ ; }
	| init_declarator_list ',' init_declarator			{ ; }
	;

init_declarator : 
	declarator											{ ; }
	| declarator '=' initializer						{ ; }
	;

storage_class_specifier :
	TYPEDEF												{ ; }
	| EXTERN											{ ; }
	| STATIC											{ ; }
	| AUTO												{; }
	| REGISTER											{ ; }
	;


type_specifier :
	VOID												{ ; }
	| CHAR												{ ; }
	| SHORT												{ ; }
	| INT												{ ; }
	| LONG												{ ; }
	| FLOAT												{ ; }
	| DOUBLE											{;  }
	| SIGNED											{; }
	| UNSIGNED											{; }
	| _BOOL												{; }
	| _COMPLEX											{; }
	| _IMAGINARY										{ ; }
	| struct_or_union_specifier							{ ; }
	| enum_specifier									{ ; }
	| typedef_name										{ ; }
	;


struct_or_union_specifier : 
	struct_or_union IDENTIFIER '{' struct_declaration_list '}'			{; }
	| struct_or_union '{' struct_declaration_list '}'					{ ; }
	| struct_or_union IDENTIFIER										{; }
	;


struct_or_union :
	STRUCT																{ ; }
	| UNION																{ ; }
	;


struct_declaration_list : 
	struct_declaration													{ ; }
	| struct_declaration_list struct_declaration						{ ; }
	;


struct_declaration :
	specifier_qualifier_list struct_declarator_list ';'					{ ; }
	;



specifier_qualifier_list :
	type_specifier specifier_qualifier_list								{ ; }
	| type_specifier													{ ; }
	| type_qualifier specifier_qualifier_list							{ }
	| type_qualifier													{ ; }
	;


struct_declarator_list :
	struct_declarator													{ ; }
	| struct_declarator_list ',' struct_declarator						{ ; }
	;


struct_declarator : 
	declarator															{  }
	| ':' constant_expression											{  }
	| declarator ':' constant_expression								{ ; }
	;


enum_specifier :
	ENUM '{' enumerator_list '}'										{ ; }
	| ENUM IDENTIFIER '{' enumerator_list '}'							{ ; }
	| ENUM '{' enumerator_list ',' '}'									{ ; }
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'						{ ; }
	| ENUM IDENTIFIER													{ ; }
	;

enumerator_list : 
	enumerator									{ ; }
	| enumerator_list ',' enumerator			{ ; }
	;

enumerator :
	IDENTIFIER									{ ; }
	| IDENTIFIER '=' constant_expression		{ ; }
	;



type_qualifier :
	CONST										{ ; }
	| VOLATILE									{ ; }
	| RESTRICT									{ ; }
	;
	
function_specifier :
	INLINE										{ ; }
	;


declarator :
	pointer direct_declarator					{ ;}
	| direct_declarator							{ ; }
	;


direct_declarator :
	IDENTIFIER									{ ; }
	| '(' declarator ')'						{ ; }
	| direct_declarator '[' ']'					{ ;}
	| direct_declarator '[' type_qualifier_list ']'	{ ;}
	| direct_declarator '[' type_qualifier_list assignment_expression ']'	{ ;}
	| direct_declarator '[' assignment_expression ']'	{ ;}
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' {;} 
	| direct_declarator '[' STATIC assignment_expression ']'	{;}
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'	{ ;}
	| direct_declarator '[' type_qualifier_list '*' ']'	{; }
	| direct_declarator '[' '*' ']'				{;}
	| direct_declarator '(' parameter_type_list ')'	{;}
	| direct_declarator '(' identifier_list ')'	{;}
	| direct_declarator '(' ')'					{;}
	;


pointer :
	'*'									{ ;}
	| '*' type_qualifier_list			{ ;}
	| '*' pointer						{ ;}
	| '*' type_qualifier_list pointer	{ ;}
	;

type_qualifier_list :
	type_qualifier						{ ;}
	| type_qualifier_list type_qualifier	{ ;}
	;

parameter_type_list :
	parameter_list						{ ;}
	| parameter_list ',' ELLIPSIS		{ ;}
	;

parameter_list :
	parameter_declaration				{ ;}
	| parameter_list ',' parameter_declaration	{;}
	;

parameter_declaration :
	declaration_specifiers declarator	{ ;}
	| declaration_specifiers abstract_declarator	{ ;}
	| declaration_specifiers			{ ;}
	;

identifier_list :
	IDENTIFIER							{ ; }
	| identifier_list ',' IDENTIFIER	{ ; }
	;


type_name :
	specifier_qualifier_list			{ ;}
	| specifier_qualifier_list abstract_declarator {;}
	;

abstract_declarator :
	pointer								{ ;}
	| direct_abstract_declarator		{ ;}
	| pointer direct_abstract_declarator	{ ;}
	;

direct_abstract_declarator :
	'(' abstract_declarator ')'				{;}
	|  '['  ']'
	| '[' type_qualifier_list ']'
	| '[' assignment_expression ']'
	| '[' STATIC type_qualifier_list ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list ']'
	|  '('  ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

typedef_name:
	TYPENAME			{ ;}
	;

initializer :
	assignment_expression					{ ;}
	| '{' initializer_list '}'				{ ;}
	| '{' initializer_list ',' '}'			{ ;}
	;

initializer_list :
	initializer								{ ;}
	| initializer_list ',' initializer		{ ;}
	| initializer_list ',' designation initializer	{ ;}
	;

designation:
	designator_list '='			{ ;}
	;
	
designator_list:
	designator					{ ;}
	| designator_list designator	{ ;}
	;
	
designator :
	'[' constant_expression ']'	{ ;}
	| '.' IDENTIFIER			{ ;}
	;
	
statement :
	labeled_statement								{ ; }
	| compound_statement							{ ; }
	| expression_statement							{ ; }
	| selection_statement							{ ; }
	| iteration_statement							{; }
	| jump_statement								{ ; }
	;

labeled_statement :
	IDENTIFIER ':' statement						{ ; }
	| CASE constant_expression ':' statement		{ ; }
	| DEFAULT ':' statement							{ ; }
	;

compound_statement :
	 '{' '}'										{ ; }
	| '{' block_item_list '}'						{ ; }
	;

block_item_list :
	block_item										{ ; }
	| block_item_list block_item					{ ; }
	;
	
block_item :
	declaration										{ ; }
	| statement										{ ; }
	;
	
expression_statement :
	';'												{ ; }
	| expression ';'								{ ; }
	;
	

selection_statement :
	IF '(' expression ')' statement %prec IFX		{ ; }
	| IF '(' expression ')' statement ELSE statement	{ ; }
	| SWITCH '(' expression ')' statement			{ ; }
	;

iteration_statement :
	WHILE '(' expression ')' statement				{ ; }
	| DO statement WHILE '(' expression ')' ';'		{ ; }
	| FOR '(' ';' ';' ')' statement					{ ; }
	| FOR '(' ';' ';' expression ')' statement		{; }
	| FOR '(' ';' expression ';' expression ')' statement	{ ; }
	| FOR '(' expression ';' expression ';' expression ')' statement	{ ; }
	| FOR '(' expression ';' ';' ')' statement		{ ; }
	| FOR '(' expression ';' expression ';' ')' statement	{ ; }
	| FOR '(' ';' expression ';' ')' statement		{ ; }
	| FOR '(' expression ';' ';' expression ')' statement	{ ; }
	| FOR '(' declaration ';' ')' statement			{ ; }
	| FOR '(' declaration ';' expression ')' statement	{ ; }
	| FOR '(' declaration expression ';' ')' statement	{; }
	| FOR '(' declaration expression ';' expression ')' statement	{ ; }
	;

jump_statement :
	GOTO IDENTIFIER ';'									{ ; }
	| CONTINUE ';'										{ ; }
	| BREAK ';'											{ ; }
	| RETURN ';'										{ ; }
	| RETURN expression ';'								{ ; }
	;


translation_unit:
	external_declaration						{ ; }
	| translation_unit external_declaration		{ ; }
	;


external_declaration : 
	function_definition							{;}
    | declaration								{;}
	;


function_definition :
	declaration_specifiers declarator declaration_list compound_statement		{; }
	| declaration_specifiers declarator compound_statement						
	{
		//for (int i=0;i<sp.size();i++) cout<<sp[i];
		int temp=0,pos,posbegin;
    for (int i=sp.size()-1;i>=0;i--) {
        if (sp[i]=="}") temp++;
        else if (sp[i]=="{") {
             temp--;
             if (temp==0) {pos=i;break;}
        }
    }
    for (int i=pos-1;i>=0;i--) {
        if (sp[i]=="(") {
            if (i>=2&&(sp[i-2]=="signed"||sp[i-2]=="unsigned")) posbegin=i-2;
            else posbegin=i-1;
            break;
        }
    }
	string toinsert;
	for (int i=posbegin;i<pos;i++) {
		if (sp[i]==")"&&sp[i-1]=="(") toinsert+="void";
		toinsert+=sp[i];
	}
	//cout<<toinsert;


		sp.clear();
		int tem=0,tem2=0,ok=0;
		for (int i=sl.size()-1;i>=0;i--) {
			if (ok==0&&sl[i]=="}") tem--;
			else if (ok==0&&sl[i]=="{") {
				tem++;
				if (tem==0) ok=1;
			}
			
			else if (ok&&sl[i]==")") tem2--;
			else if (ok&&sl[i]=="(") {
				tem2++;
				if (ok&&tem2==0) {
					mp[sl[i-1]]=toinsert;
					break;
				}
			}
		} 
	}
	;
	
declaration_list :
	declaration								{ ;}
	| declaration_list declaration			{ ;}
	;

	
parallel_function_list :		
	IDENTIFIER									{ ; }
	| parallel_function_list ',' IDENTIFIER		{ ; }
	;

parallel_function :
	PARAFUNC								{;}
	;

boolean_expression :
	boolean_and_expression								{ ; }
	| boolean_expression OR_OP boolean_and_expression	{ ; }
	;

boolean_and_expression:
	| boolean_primary_expression							{ ; }
	| boolean_and_expression AND_OP boolean_primary_expression	{ ; }
	;
	
boolean_primary_expression:
	parallel_function									{ ; }
	| AND_OP parallel_function							{ ; }
	| OR_OP parallel_function							{ ; }
	| '(' boolean_expression ')'						{ ; }
%%

#include <stdio.h>



extern char yytext[];
extern FILE * yyin;
extern int column;
extern int row;

vector<string> outputvec(string s) {
    vector<string>ret;
    string tmp="";
    for (int i=0;i<s.size();i++) {
        if (s[i]!=' '&&s[i]!='\t') tmp+=s[i];
        else {
             ret.push_back(tmp);
             tmp="";
        }
    }
    if (!tmp.empty()) ret.push_back(tmp);
    return ret;
}
string tra1(string s) {
    for (int i=0;i<=s.size();i++) if (s[i]==',') s[i]=' ';
	vector<string> arraystring=outputvec(s);
	//Parallel<int (int, int)> f2(fff);
    string ret="Parallel<";
    if (mp.find(arraystring[1])!=mp.end()) ret+=mp[arraystring[1]];
	ret+=">";
	for (int i=2;i<arraystring.size();i++) {
        if (i==2) ret+=' ';
        else ret+=',';
        ret+=arraystring[i]+'('+arraystring[1]+')';
    }
	return ret;
}
string tra2(string s) {
	if (s.find('<')==string::npos) return s;
	int a=s.find('<'),b=s.find('>');
	string t1=s.substr(0,a),t2=s.substr(a+1,b-a-1),t3=s.substr(b+1,s.size()-b-1);
	return t1+".waiting("+t2+')'+t3;
}

void yyerror(char *s)
{

  fflush(stdout);

  printf("\nrow:%d column:%d:%s \" %s \"\n", row, column,  s, yytext);

}
int main(int argc, char *argv[])
{
	yyin = fopen(argv[1],"r");
	yyparse();
//	for (int i=0;i<sl.size();i++) cout<<sl[i]<<' ';
	return 1;
}
