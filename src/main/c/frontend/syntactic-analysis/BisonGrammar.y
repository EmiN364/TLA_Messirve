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
	Player * player;
	Tournament * tournament;
	Stadium * stadium;
	Badge * badge;
	Trophy * trophy;
	Country * country;
	Team * team;
	Group * group;
	Lineup * lineup;
	Homekit * homekit;
	Ball * ball;
	Special * special;
	iCountry * icountry;
	iBirthday * ibirthday;
	iClub * iclub;
	iHeight * iheight;
	iWeight * iweight;
	iPhoto * iphoto;
	iCapacity * icapacity;
	iName * iname;
	iBrand * ibrand;
	Url * url;
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
%token <token> COLON
%token <token> COMMA
%token <token> UNKNOWN

/** Non-terminals. */
%type <constant> constant
%type <expression> expression
%type <factor> factor
%type <program> program
%type <Player> PLAYER
%type <Tournament> TOURNAMENT
%type <Stadium> STADIUM
%type <Badge> BADGE
%type <Trophy> TROPHY
%type <Country> COUNTRY
%type <Team> TEAM
%type <Group> GROUP
%type <Lineup> LINEUP
%type <Homekit> HOMEKIT
%type <Ball> BALL
%type <Special> SPECIAL
%type <iCountry> iCOUNTRY
%type <iBirthday> iBIRTHDATE
%type <iClub> iCLUB
%type <iHeight> iHEIGHT
%type <iWeight> iWEIGHT
%type <iPhoto> iPHOTO
%type <iCapacity> iCAPACITY
%type <iName> iNAME
%type <iBrand> iBRAND
%type <Url> URL

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
%left ADD SUB
%left MUL DIV

%%

program: tournament													{ $$ = null }
	;

tournament: TOURNAMENT STRING OPEN_BRACE body CLOSE_BRACE			{ $$ = null }
	;

body: constructions													{ $$ = null }
	;

constructions: construction COMMA construction						{ $$ = null }
 | construction														{ $$ = null }
	;

construction: TROPHY OPEN_BRACE iPHOTO COLON STRING CLOSE_BRACE		{ $$ = null }
 | ETCCCCCCCCCCCCCC													{ $$ = null }
	;

%%
