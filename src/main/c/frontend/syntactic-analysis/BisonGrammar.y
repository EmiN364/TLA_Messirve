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
	Program * program;
	Tournament * tournament;
	Element * element;
	TElements * tElements;
	Trophy * trophy;
	Group * group;
	Groups * groups;
	Stadium * stadium;
	StadiumData * stadiumData;
	Badge * badge;
	Player * player;
	PlayerData * playerData;
	PlayerTypeString * playerTypeString;
	PlayerTypeFloat * playerTypeFloat;
	Team * team;
	Teams * teams;
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


/** Non-terminals. */
%type <constant> constant
%type <program> program
%type <tournament> tournament
%type <element> element
%type <tElements> tElements
%type <trophy> trophy
%type <group> group
%type <groups> groups
%type <stadium> stadium
%type <stadiumData> stadiumData
%type <badge> badge
%type <player> player
%type <playerData> playerData
%type <playerTypeString> playerTypeString
%type <playerTypeFloat> playerTypeFloat
%type <team> team
%type <teams> teams
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
%left ADD SUB
%left MUL DIV

%%

program: tournament													{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	| element														{ $$ = ExpressionProgramSemanticAction(currentCompilerState(), $1); }
	;

tournament: TOURNAMENT STRING OPEN_BRACE tElements CLOSE_BRACE		{ $$ = ExpressionTournamentSemanticAction(currentCompilerState(), $4); }
	;

element: trophy														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| team															{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| stadium														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| badge															{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| player														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| ball															{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| element element												{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	;

tElements: trophy													{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| team															{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| groups														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| stadium														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| ball															{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| tElements tElements											{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	;

trophy: TROPHY OPEN_BRACE photo CLOSE_BRACE	{ $$ = ExpressionTrophySemanticAction(currentCompilerState(), $5); }
	;

groups: groups group												{ $$ = ExpressionGroupsSemanticAction(currentCompilerState(), $1, $2); }
	| group															{ $$ = ExpressionGroupsSemanticAction(currentCompilerState(), $1, NULL); }
	;

group: GROUP STRING OPEN_BRACE teams CLOSE_BRACE					{ $$ = ExpressionGroupSemanticAction(currentCompilerState(), $2, $4); }
	;

teams: teams team													{ $$ = ExpressionTeamsSemanticAction(currentCompilerState(), $1, $2); }
	| team															{ $$ = ExpressionTeamsSemanticAction(currentCompilerState(), NULL, $1); }
	;

team: TEAM STRING OPEN_BRACE tTeam CLOSE_BRACE						{ $$ = ExpressionTeamSemanticAction(currentCompilerState(), $2, $4, $5); }
	;

tTeam: badge														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| lineup														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| homekit														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| player														{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
	| tTeam tTeam													{ $$ = ExpressionElementSemanticAction(currentCompilerState(), $1); }
;

player: PLAYER STRING OPEN_BRACE playerData CLOSE_BRACE				{ $$ = ExpressionPlayerSemanticAction(currentCompilerState(), $2, $5, $8, $11, $14, $17); }
	;

playerData: playerTypeString COLON STRING SEMICOLON					{ $$ = ExpressionPlayerDataSemanticAction(currentCompilerState(), $1); }
	| playerTypeFloat COLON FLOAT SEMICOLON							{ $$ = ExpressionPlayerDataSemanticAction(currentCompilerState(), $1); }
	| playerData playerData											{ $$ = ExpressionPlayerDataSemanticAction(currentCompilerState(), $1); }
	;

playerTypeString: iCOUNTRY     										{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	| iBIRTHDATE 													{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	| iTEAM  														{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	| iPHOTO  														{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	;

playerTypeFloat: iHEIGHT											{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	| iWEIGHT														{ $$ = ExpressionPlayerTypeSemanticAction(currentCompilerState(), $1); }
	;

stadium: STADIUM STRING OPEN_BRACE stadiumData CLOSE_BRACE			{ $$ = ExpressionStadiumSemanticAction(currentCompilerState(), $2, $5, $8); }
	;

stadiumData: iCAPACITY COLON INTEGER SEMICOLON						{ $$ = ExpressionStadiumDataSemanticAction(currentCompilerState(), $1); }
	| photo															{ $$ = ExpressionStadiumDataSemanticAction(currentCompilerState(), $1); }
	| stadiumData stadiumData										{ $$ = ExpressionStadiumDataSemanticAction(currentCompilerState(), $1); }
	;

badge: BADGE STRING OPEN_BRACE photo CLOSE_BRACE					{ $$ = ExpressionBadgeSemanticAction(currentCompilerState(), $2, $5); }
	;

photo: iPHOTO COLON URL SEMICOLON									{ $$ = ExpressionPhotoSemanticAction(currentCompilerState(), $3); }
	;

lineup: LINEUP STRING OPEN_BRACE elements CLOSE_BRACE			{ $$ = ExpressionLineupSemanticAction(currentCompilerState(), $2, $4, $5); }
	;

homekit: HOMEKIT STRING OPEN_BRACE elements CLOSE_BRACE			{ $$ = ExpressionHomekitSemanticAction(currentCompilerState(), $2, $4, $5); }
	;

ball: BALL STRING OPEN_BRACE elements CLOSE_BRACE				{ $$ = ExpressionBallSemanticAction(currentCompilerState(), $2, $4, $5); }
	;

special: SPECIAL STRING OPEN_BRACE elements CLOSE_BRACE			{ $$ = ExpressionSpecialSemanticAction(currentCompilerState(), $2, $4, $5); }
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