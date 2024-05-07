%{

#include "BisonActions.h"

%}

%define api.value.union.name SemanticValue

%union {
	/** Terminals. */

	int integer;
  	float floatNumber;
  	char * string;
	Token token;

	/** Non-terminals. */

	Constant * constant;
	Expression * expression;
	Factor * factor;
	Program * program;
}

/**
 * Destructors. This functions are executed after the parsing ends, so if the
 * AST must be used in the following phases of the compiler you shouldn't used
 * this approach.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Destructor-Decl.html
 */
/*
%destructor { releaseConstant($$); } <constant>
%destructor { releaseExpression($$); } <expression>
%destructor { releaseFactor($$); } <factor>
%destructor { releaseProgram($$); } <program>
*/

/** Terminals. */
%token <integer> INTEGER
%token <token> CLOSE_PARENTHESIS
%token <token> OPEN_PARENTHESIS
%token <string> STRING
%token <floatNumber> FLOAT
%token <string> DATE
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> SEMICOLON
%token <token> COMMA
%token <token> UNKNOWN
%token <token> PLAYER
%token <token> TOURNAMENT
%token <token> STADIUM
%token <token> BADGE
%token <token> TROPHY
%token <token> COUNTRY
%token <token> TEAM
%token <token> GROUP
%token <token> LINEUP
%token <token> HOMEKIT
%token <token> BALL
%token <token> SPECIAL
%token <token> iCOUNTRY
%token <token> iBIRTHDATE
%token <token> iCLUB
%token <token> iHEIGHT
%token <token> iWEIGHT
%token <token> iPHOTO
%token <token> iCAPACITY
%token <token> iNAME
%token <token> iBRAND
%token <token> URL

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program
%token <token> URL

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: album													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| figurita
	;

expression: expression[left] ADD expression[right]					{ $$ = ArithmeticExpressionSemanticAction($left, $right, ADDITION); }
	| expression[left] DIV expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, DIVISION); }
	| expression[left] MUL expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, MULTIPLICATION); }
	| expression[left] SUB expression[right]						{ $$ = ArithmeticExpressionSemanticAction($left, $right, SUBTRACTION); }
	| factor														{ $$ = FactorExpressionSemanticAction($1); }
	;

factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS				{ $$ = ExpressionFactorSemanticAction($2); }
	| constant														{ $$ = ConstantFactorSemanticAction($1); }
	;

constant: INTEGER													{ $$ = IntegerConstantSemanticAction($1); }
	;

%%
