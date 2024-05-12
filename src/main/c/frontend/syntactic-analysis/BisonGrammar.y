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
	HomeKit * homekit;
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
%token <string> URL
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

%%

program: elements													{ $$ = ProgramSemanticAction(currentCompilerState(), $1); }
	;

elements: element COMMA elements									{ $$ = MultipleElementsSemanticAction($1, $3); }
	| element														{ $$ = SingleElementsSemanticAction($1); }
	;

element: trophy														{ $$ = TrophyElementSemanticAction($1); }
	| team															{ $$ = TeamElementSemanticAction($1); }
	| stadium														{ $$ = StadiumElementSemanticAction($1); }
	| badge															{ $$ = BadgeElementSemanticAction($1); }
	| player														{ $$ = PlayerElementSemanticAction($1); }
	| ball															{ $$ = BallElementSemanticAction($1); }
	| special 														{ $$ = SpecialElementSemanticAction($1); }
	| tournament 													{ $$ = TournamentElementSemanticAction($1); }
	;

tournament: TOURNAMENT STRING OPEN_BRACE tElements CLOSE_BRACE		{ $$ = TournamentSemanticAction($2, $4); }
	;

tElements: tElement													{ $$ = SingleTournamentElementSemanticAction($1); }
	| tElement COMMA tElements										{ $$ = MultipleTournamentSemanticAction($1, $3); }
	;

tElement: trophy													{ $$ = TrophyTournamentElementSemanticAction($1); }
	| team															{ $$ = TeamTournamentElementSemanticAction($1); }
	| group															{ $$ = GroupTournamentElementSemanticAction($1); }
	| stadium														{ $$ = StadiumTournamentElementSemanticAction($1); }
	| ball															{ $$ = BallTournamentElementSemanticAction($1); }
	;

trophy: TROPHY OPEN_BRACE photo CLOSE_BRACE							{ $$ = TrophySemanticAction($3); }
	| TROPHY STRING OPEN_BRACE photo CLOSE_BRACE					{ $$ = TrophyWithNameSemanticAction($2, $4); }
	;

group: GROUP STRING OPEN_BRACE teams CLOSE_BRACE					{ $$ = GroupSemanticAction($2, $4); }
	;

teams: team COMMA teams												{ $$ = MultipleTeamsSemanticAction($1, $3); }
	| team															{ $$ = SingleTeamsSemanticAction($1); }
	;

team: TEAM STRING OPEN_BRACE tTeams CLOSE_BRACE						{ $$ = TeamSemanticAction($2, $4);}
	| TEAM STRING SEMICOLON											{ $$ = TeamSemanticAction($2, NULL); }
	;

tTeams: tTeam														{ $$ = SingleTTeamsSemanticAction($1); }	
	| tTeam COMMA tTeams											{ $$ = MultipleTTeamsSemanticAction($1, $3); }
	;

tTeam: badge														{ $$ = BadgeTTeamSemanticAction($1); }
	| lineup														{ $$ = LineupTTeamSemanticAction($1); }
	| homekit														{ $$ = HomekitTTeamSemanticAction($1); }
	| player														{ $$ = PlayerTTeamSemanticAction($1); }
	;

player: PLAYER STRING OPEN_BRACE playerDatas CLOSE_BRACE			{ $$ = PlayerSemanticAction($2, $4); }
	;

playerDatas: playerData playerDatas									{ $$ = MultiplePlayerDatasSemanticAction($1, $2); }
	| playerData													{ $$ = SinglePlayerDatasSemanticAction($1); }
	;

playerData: playerTypeString COLON STRING SEMICOLON					{ $$ = PlayerDataStringSemanticAction($1, $3); }
	| playerTypeFloat COLON FLOAT SEMICOLON							{ $$ = PlayerDataFloatSemanticAction($1, $3); }
	| playerTypeFloat COLON INTEGER SEMICOLON						{ $$ = PlayerDataFloatSemanticAction($1, $3); }
	| playerTypeString COLON DATE SEMICOLON							{ $$ = PlayerDataStringSemanticAction($1, $3); }
	| photo															{ $$ = PlayerDataPhotoSemanticAction($1); }
	;

playerTypeString: iCOUNTRY     										{ $$ = PlayerTypeCountrySemanticAction(); }
	| iBIRTHDATE 													{ $$ = PlayerTypeBirthdaySemanticAction(); }
	| iTEAM  														{ $$ = PlayerTypeTeamSemanticAction(); }
	;

playerTypeFloat: iHEIGHT											{ $$ = PlayerTypeHeightSemanticAction(); }
	| iWEIGHT														{ $$ = PlayerTypeWeightSemanticAction(); }
	;

stadium: STADIUM STRING OPEN_BRACE stadiumDatas CLOSE_BRACE			{ $$ = StadiumSemanticAction($2, $4); }
	;

stadiumDatas: stadiumData stadiumDatas								{ $$ = MultipleStadiumDatasSemanticAction($1, $2); }
	| stadiumData													{ $$ = SingleStadiumDatasSemanticAction($1); }
	;

stadiumData: iCAPACITY COLON INTEGER SEMICOLON						{ $$ = StadiumDataSemanticAction($3); }
	| photo															{ $$ = StadiumDataPhotoSemanticAction($1); }
	;

badge: BADGE OPEN_BRACE photo CLOSE_BRACE							{ $$ = BadgeSemanticAction($3); }
	| BADGE STRING OPEN_BRACE photo CLOSE_BRACE						{ $$ = BadgeWithNameSemanticAction($2, $4); }
	;

photo: iPHOTO COLON URL SEMICOLON									{ $$ = PhotoSemanticAction($3); }
	;

lineup: LINEUP STRING OPEN_BRACE photo CLOSE_BRACE					{ $$ = LineupWithNameSemanticAction($2, $4); }
	| LINEUP OPEN_BRACE photo CLOSE_BRACE							{ $$ = LineupSemanticAction($3); }
	;

homekit: HOMEKIT STRING OPEN_BRACE photo CLOSE_BRACE				{ $$ = HomekitWithNameSemanticAction($2, $4); }
	| HOMEKIT OPEN_BRACE photo CLOSE_BRACE							{ $$ = HomekitSemanticAction($3); }
	;

ball: BALL STRING OPEN_BRACE photo CLOSE_BRACE						{ $$ = BallWithNameSemanticAction($2, $4); }
	| BALL OPEN_BRACE photo CLOSE_BRACE								{ $$ = BallSemanticAction($3); }
	;

special: SPECIAL STRING OPEN_BRACE photo CLOSE_BRACE				{ $$ = SpecialWithNameSemanticAction($2, $4); }
	| SPECIAL OPEN_BRACE photo CLOSE_BRACE							{ $$ = SpecialSemanticAction($3); }
	;

%%