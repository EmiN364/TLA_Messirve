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

	Program * program;
	Tournament * tournament;
	Elements * elements;
	Element * element;
	TElements * tElements;
	TElement * tElement;
	Trophy * trophy;
	Group * group;
	Groups * groups;
	Stadium * stadium;
	StadiumDatas * stadiumDatas;
	StadiumData * stadiumData;
	Badge * badge;
	Player * player;
	PlayerDatas * playerDatas;
	PlayerData * playerData;
	PlayerTypeString * playerTypeString;
	PlayerTypeFloat * playerTypeFloat;
	Team * team;
	Teams * teams;
	TTeams * tTeams;
	TTeam * tTeam;
	Lineup * lineup;
	Homekit * homekit;
	Ball * ball;
	Special * special;
	Photo * photo;
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
%token <string> STRING
%token <floatNumber> FLOAT
%token <token> OPEN_BRACE
%token <token> CLOSE_BRACE
%token <token> SEMICOLON
%token <token> COLON
%token <token> COMMA
%token <token> UNKNOWN
%token <token> PLAYER
%token <token> TOURNAMENT
%token <token> STADIUM
%token <token> BADGE
%token <token> TROPHY
%token <token> TEAM
%token <token> GROUP
%token <token> LINEUP
%token <token> HOMEKIT
%token <token> BALL
%token <token> SPECIAL
%token <token> iCOUNTRY
%token <token> iBIRTHDATE
%token <token> iTEAM
%token <token> iHEIGHT
%token <token> iWEIGHT
%token <token> iPHOTO
%token <token> iCAPACITY
%token <token> iNAME
%token <token> iBRAND
%token <token> URL
%token <string> DATE


/** Non-terminals. */
%type <program> program
%type <tournament> tournament
%type <elements> elements
%type <element> element
%type <tElements> tElements
%type <tElement> tElement
%type <trophy> trophy
%type <group> group
%type <groups> groups
%type <stadium> stadium
%type <stadiumDatas> stadiumDatas
%type <stadiumData> stadiumData
%type <badge> badge
%type <player> player
%type <playerDatas> playerDatas
%type <playerData> playerData
%type <playerTypeString> playerTypeString
%type <playerTypeFloat> playerTypeFloat
%type <team> team
%type <teams> teams
%type <tTeams> tTeams
%type <tTeam> tTeam
%type <lineup> lineup
%type <homekit> homekit
%type <ball> ball
%type <special> special
%type <photo> photo

/**
 * Precedence and associativity.
 *
 * @see https://www.gnu.org/software/bison/manual/html_node/Precedence.html
 */
/* %left ADD SUB
%left MUL DIV */

%%

program: tournament													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| elements														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

tournament: TOURNAMENT STRING OPEN_BRACE tElements CLOSE_BRACE		{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

elements: element COMMA elements									{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	| element														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

element: trophy														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| team															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| stadium														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| badge															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| player														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| ball															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| special 														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

tElements: tElement													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| tElement COMMA tElements										{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	;

tElement: trophy													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| team															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| groups														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| stadium														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| ball															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

trophy: TROPHY OPEN_BRACE photo CLOSE_BRACE							{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $3); }
	;

groups: group COMMA groups												{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	| group															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

group: GROUP STRING OPEN_BRACE teams CLOSE_BRACE					{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

teams: team COMMA teams													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	| team															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

team: TEAM STRING OPEN_BRACE tTeams CLOSE_BRACE						{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

tTeams: tTeam														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }	
	| tTeam COMMA tTeams													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }

tTeam: badge														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| lineup														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| homekit														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| player														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
;

player: PLAYER STRING OPEN_BRACE playerDatas CLOSE_BRACE				{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

playerDatas: playerData playerDatas									{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $2); }
	| playerData													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }

playerData: playerTypeString COLON STRING SEMICOLON					{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	| playerTypeFloat COLON FLOAT SEMICOLON							{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	;

playerTypeString: iCOUNTRY     										{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| iBIRTHDATE 													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| iTEAM  														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| iPHOTO  														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

playerTypeFloat: iHEIGHT											{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| iWEIGHT														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

stadium: STADIUM STRING OPEN_BRACE stadiumDatas CLOSE_BRACE			{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

stadiumDatas: stadiumData stadiumDatas								{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $2); }
	| stadiumData													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }

stadiumData: iCAPACITY COLON INTEGER SEMICOLON						{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1, $3); }
	| photo															{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

badge: BADGE STRING OPEN_BRACE photo CLOSE_BRACE					{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

photo: iPHOTO COLON URL SEMICOLON									{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $3); }
	;

lineup: LINEUP STRING OPEN_BRACE photo CLOSE_BRACE					{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

homekit: HOMEKIT STRING OPEN_BRACE photo CLOSE_BRACE				{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

ball: BALL STRING OPEN_BRACE photo CLOSE_BRACE						{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

special: SPECIAL STRING OPEN_BRACE photo CLOSE_BRACE				{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $2, $4); }
	;

%%

/*
Should accept:
tournament Copa America {
	trophy {
		Photo: http://foto.google.com/trofeo_copa.png;
	},
	group A {
		team Argentina {
			badge { // Creación de figurita del escudo de Argentina
				Photo: http://foto.google.com/afa.png;
			},
			player Angel Di Maria { // Creación de figurita de Di Maria
				BirthDay: 14/2/1988;
				Height: 1.78;
				Weight: 75;
				team: Benfica;
				Photo: http://foto.google.com/dimaria.png;
			},
			player Nicolas Otamendi { // Creación de figurita de Otamendi
				BirthDay: 12/2/1988;
				Height: 1.83;
				Weight: 82;
				Photo: http://foto.google.com/dimaria.png;
			}
		},
		team Brasil; // Already defined elsewhere
	}
}

Should not accept because of the repeated attribute Photo:

// Error al repetir el atributo Photo a la hora de crear una figurita de un
escudo
badge Argentina {
	Photo: http://foto.google.com/FotoDeArgentinaEnHd.jpg;
	Photo: http://foto.google.com/FotoDeArgentinaEnHd2.jpg;
}

Should accept:

// Creación de la figurita de uno de los estadios del torneo
stadium Lusail Stadium {
	Capacity: 88966;
	Photo: http://foto.google.com/FotoDelLusailEnHd.jpg;
}

Should accept:

// Creación de la figurita del mejor jugador de la historia del fútbol
player Lionel Messi {
	Country: Argentina;
	BirthDay: 24/6/1987;
	Team: Inter Miami CF;
	Height: 1.69;
	Weight: 67;
	Photo: http://foto.google.com/FotoDeMessiEnHd.jpg;
}



*/