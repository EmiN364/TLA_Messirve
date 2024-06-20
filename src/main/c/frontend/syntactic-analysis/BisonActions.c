#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger *_logger = NULL;

void initializeBisonActionsModule()
{
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule()
{
	if (_logger != NULL)
	{
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char *functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char *functionName)
{
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

Program *ProgramSemanticAction(CompilerState *compilerState, Elements *elements)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program *program = calloc(1, sizeof(Program));
	program->elements = elements;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext())
	{
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else
	{
		compilerState->succeed = true;
	}
	return program;
}

Elements *MultipleElementsSemanticAction(Element *element, Elements *elements)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Elements *newElement = calloc(1, sizeof(Elements));
	newElement->leftElement = element;
	newElement->elements = elements;
	newElement->type = MULTIPLE;
	return newElement;
}

Elements *SingleElementsSemanticAction(Element *element)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Elements *newElement = calloc(1, sizeof(Elements));
	newElement->element = element;
	newElement->type = SINGLE;
	return newElement;
}

Element *TournamentElementSemanticAction(Tournament *tournament)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *element = calloc(1, sizeof(Element));
	element->type = TOURNAMENT_ELEMENT_TYPE;
	element->tournament = tournament;
	return element;
}

Element *TrophyElementSemanticAction(Trophy *trophy)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = TROPHY_ELEMENT_TYPE;
	newElement->trophy = trophy;
	return newElement;
}

Element *TeamElementSemanticAction(Team *team)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = TEAM_ELEMENT_TYPE;
	newElement->team = team;
	return newElement;
}

Element *StadiumElementSemanticAction(Stadium *stadium)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = STADIUM_ELEMENT_TYPE;
	newElement->stadium = stadium;
	return newElement;
}

Element *BadgeElementSemanticAction(Badge *badge)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = BADGE_ELEMENT_TYPE;
	newElement->badge = badge;
	return newElement;
}

Element *PlayerElementSemanticAction(Player *player)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = PLAYER_ELEMENT_TYPE;
	newElement->player = player;
	return newElement;
}

Element *BallElementSemanticAction(Ball *ball)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = BALL_ELEMENT_TYPE;
	newElement->ball = ball;
	return newElement;
}

Element *SpecialElementSemanticAction(Special *special)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element *newElement = calloc(1, sizeof(Element));
	newElement->type = SPECIAL_ELEMENT_TYPE;
	newElement->special = special;
	return newElement;
}

Tournament *TournamentSemanticAction(char *tournamentName, TElements *tElements)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tournament *tournament = calloc(1, sizeof(Tournament));
	tournament->name = tournamentName;
	tournament->tElements = tElements;
	return tournament;
}

TElements *SingleTournamentElementSemanticAction(TElement *tElement)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElements *newTElement = calloc(1, sizeof(TElements));
	newTElement->tElement = tElement;
	newTElement->type = SINGLE;
	return newTElement;
}

TElements *MultipleTournamentSemanticAction(TElement *tElement, TElements *tElements)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElements *newTElement = calloc(1, sizeof(TElements));
	newTElement->leftTElement = tElement;
	newTElement->tElements = tElements;
	newTElement->type = MULTIPLE;
	return newTElement;
}

TElement *TrophyTournamentElementSemanticAction(Trophy *trophy)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElement *newTElement = calloc(1, sizeof(TElement));
	newTElement->type = TROPHY_TELEMENT_TYPE;
	newTElement->trophy = trophy;
	return newTElement;
}

TElement *TeamTournamentElementSemanticAction(Team *team)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElement *newTElement = calloc(1, sizeof(TElement));
	newTElement->type = TEAM_TELEMENT_TYPE;
	newTElement->team = team;
	return newTElement;
}

TElement *GroupTournamentElementSemanticAction(Group *group)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElement *newTElement = calloc(1, sizeof(TElement));
	newTElement->type = GROUP_TELEMENT_TYPE;
	newTElement->group = group;
	return newTElement;
}

TElement *StadiumTournamentElementSemanticAction(Stadium *stadium)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElement *newTElement = calloc(1, sizeof(TElement));
	newTElement->type = STADIUM_TELEMENT_TYPE;
	newTElement->stadium = stadium;
	return newTElement;
}

TElement *BallTournamentElementSemanticAction(Ball *ball)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElement *newTElement = calloc(1, sizeof(TElement));
	newTElement->type = BALL_TELEMENT_TYPE;
	newTElement->ball = ball;
	return newTElement;
}

Trophy *TrophyWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Trophy *trophy = calloc(1, sizeof(Trophy));
	trophy->photo = photo;
	trophy->name = name;
	return trophy;
}

Trophy *TrophySemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Trophy *trophy = calloc(1, sizeof(Trophy));
	trophy->photo = photo;
	return trophy;
}

Group *GroupSemanticAction(char *name, Teams *teams)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Group *group = calloc(1, sizeof(Group));
	group->name = name;
	group->teams = teams;
	return group;
}

Teams *MultipleTeamsSemanticAction(Team *team, Teams *teams)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Teams *newTeams = calloc(1, sizeof(Teams));
	newTeams->leftTeam = team;
	newTeams->teams = teams;
	newTeams->type = MULTIPLE;
	return newTeams;
}

Teams *SingleTeamsSemanticAction(Team *team)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Teams *newTeams = calloc(1, sizeof(Teams));
	newTeams->team = team;
	newTeams->type = SINGLE;
	return newTeams;
}

Team *TeamSemanticAction(char *name, TTeams *tTeams)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Team *team = calloc(1, sizeof(Team));
	team->name = name;
	team->tTeams = tTeams;
	return team;
}

TTeams *SingleTTeamsSemanticAction(TTeam *tTeam)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeams *newTTeams = calloc(1, sizeof(TTeams));
	newTTeams->tTeam = tTeam;
	newTTeams->type = SINGLE;
	return newTTeams;
}

TTeams *MultipleTTeamsSemanticAction(TTeam *tTeam, TTeams *tTeams)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeams *newTTeams = calloc(1, sizeof(TTeams));
	newTTeams->leftTTeam = tTeam;
	newTTeams->tTeams = tTeams;
	newTTeams->type = MULTIPLE;
	return newTTeams;
}

TTeam *BadgeTTeamSemanticAction(Badge *badge)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam *newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = BADGE_TTEAM_TYPE;
	newTTeam->badge = badge;
	return newTTeam;
}

TTeam *LineupTTeamSemanticAction(Lineup *lineup)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam *newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = LINEUP_TTEAM_TYPE;
	newTTeam->lineup = lineup;
	return newTTeam;
}

TTeam *HomekitTTeamSemanticAction(HomeKit *homekit)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam *newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = HOMEKIT_TTEAM_TYPE;
	newTTeam->homeKit = homekit;
	return newTTeam;
}

TTeam *PlayerTTeamSemanticAction(Player *player)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam *newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = PLAYER_TTEAM_TYPE;
	newTTeam->player = player;
	return newTTeam;
}

Player *PlayerSemanticAction(char *name, PlayerDatas *playerDatas)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Player *player = calloc(1, sizeof(Player));
	player->name = name;
	player->playerDatas = playerDatas;
	return player;
}

PlayerDatas *SinglePlayerDatasSemanticAction(PlayerData *playerData)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerDatas *newPlayerDatas = calloc(1, sizeof(PlayerDatas));
	newPlayerDatas->playerData = playerData;
	newPlayerDatas->type = SINGLE;
	return newPlayerDatas;
}

PlayerDatas *MultiplePlayerDatasSemanticAction(PlayerData *playerData, PlayerDatas *playerDatas)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerDatas *newPlayerDatas = calloc(1, sizeof(PlayerDatas));
	newPlayerDatas->leftPlayerData = playerData;
	newPlayerDatas->playerDatas = playerDatas;
	newPlayerDatas->type = MULTIPLE;
	return newPlayerDatas;
}

PlayerData *PlayerDataStringSemanticAction(PlayerTypeString *playerTypeString, char *value)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerData *playerData = calloc(1, sizeof(PlayerData));
	playerData->type = PLAYER_TYPE_STRING;
	playerData->value = value;
	playerData->playerTypeString = playerTypeString;
	return playerData;
}

PlayerData *PlayerDataFloatSemanticAction(PlayerTypeFloat *playerTypeFloat, float value)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerData *playerData = calloc(1, sizeof(PlayerData));
	playerData->type = PLAYER_TYPE_FLOAT;
	playerData->floatValue = value;
	playerData->playerTypeFloat = playerTypeFloat;
	return playerData;
}

PlayerData *PlayerDataPhotoSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerData *playerData = calloc(1, sizeof(PlayerData));
	playerData->type = PLAYER_TYPE_PHOTO;
	playerData->photo = photo;
	return playerData;
}

PlayerTypeString *PlayerTypeCountrySemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString *playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_COUNTRY;
	return playerTypeString;
}

PlayerTypeString *PlayerTypeBirthdaySemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString *playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_BIRTHDATE;
	return playerTypeString;
}

PlayerTypeString *PlayerTypeTeamSemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString *playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_TEAM;
	return playerTypeString;
}

PlayerTypeFloat *PlayerTypeHeightSemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeFloat *playerTypeFloat = calloc(1, sizeof(PlayerTypeFloat));
	playerTypeFloat->type = PLAYER_HEIGHT;
	return playerTypeFloat;
}

PlayerTypeFloat *PlayerTypeWeightSemanticAction()
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeFloat *playerTypeFloat = calloc(1, sizeof(PlayerTypeFloat));
	playerTypeFloat->type = PLAYER_WEIGHT;
	return playerTypeFloat;
}

Stadium *StadiumSemanticAction(char *name, StadiumDatas *stadiumDatas)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Stadium *stadium = calloc(1, sizeof(Stadium));
	stadium->name = name;
	stadium->stadiumDatas = stadiumDatas;
	return stadium;
}

StadiumDatas *SingleStadiumDatasSemanticAction(StadiumData *stadiumData)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumDatas *newStadiumDatas = calloc(1, sizeof(StadiumDatas));
	newStadiumDatas->stadiumData = stadiumData;
	newStadiumDatas->type = SINGLE;
	return newStadiumDatas;
}

StadiumDatas *MultipleStadiumDatasSemanticAction(StadiumData *stadiumData, StadiumDatas *stadiumDatas)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumDatas *newStadiumDatas = calloc(1, sizeof(StadiumDatas));
	newStadiumDatas->leftStadiumData = stadiumData;
	newStadiumDatas->stadiumDatas = stadiumDatas;
	newStadiumDatas->type = MULTIPLE;
	return newStadiumDatas;
}

StadiumData *StadiumDataSemanticAction(int value)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumData *stadiumData = calloc(1, sizeof(StadiumData));
	stadiumData->type = STADIUM_CAPACITY;
	stadiumData->capacity = value;
	return stadiumData;
}

StadiumData *StadiumDataPhotoSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumData *stadiumData = calloc(1, sizeof(StadiumData));
	stadiumData->type = STADIUM_PHOTO;
	stadiumData->photo = photo;
	return stadiumData;
}

Badge *BadgeSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Badge *badge = calloc(1, sizeof(Badge));
	badge->photo = photo;
	return badge;
}

Badge *BadgeWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Badge *badge = calloc(1, sizeof(Badge));
	badge->photo = photo;
	badge->name = name;
	return badge;
}

Photo *PhotoSemanticAction(char *url)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Photo *photo = calloc(1, sizeof(Photo));
	photo->url = url;
	return photo;
}

Lineup *LineupSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Lineup *lineup = calloc(1, sizeof(Lineup));
	lineup->photo = photo;
	return lineup;
}

Lineup *LineupWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Lineup *lineup = calloc(1, sizeof(Lineup));
	lineup->name = name;
	lineup->photo = photo;
	return lineup;
}

HomeKit *HomekitSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HomeKit *hk = calloc(1, sizeof(HomeKit));
	hk->photo = photo;
	return hk;
}

HomeKit *HomekitWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	HomeKit *hk = calloc(1, sizeof(HomeKit));
	hk->name = name;
	hk->photo = photo;
	return hk;
}

Ball *BallSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ball *ball = calloc(1, sizeof(Ball));
	ball->photo = photo;
	return ball;
}

Ball *BallWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ball *ball = calloc(1, sizeof(Ball));
	ball->name = name;
	ball->photo = photo;
	return ball;
}

Special *SpecialSemanticAction(Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Special *special = calloc(1, sizeof(Special));
	special->photo = photo;
	return special;
}

Special *SpecialWithNameSemanticAction(char *name, Photo *photo)
{
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Special *special = calloc(1, sizeof(Special));
	special->name = name;
	special->photo = photo;
	return special;
}