#include "BisonActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s", functionName);
}

/* PUBLIC FUNCTIONS */

/* Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Program * program) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
} */

Program * ProgramSemanticAction(CompilerState * compilerState, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}

Expression * ExpressionTournamentSemanticAction(Tournament * tournament) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->tournament = tournament;
	expression->type = TOURNAMENT_TYPE;
	return expression;
}

Expression * ExpressionElementsSemanticAction(Elements * elements) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->elements = elements;
	expression->type = ELEMENTS_TYPE;
	return expression;
}

Tournament * TournamentSemanticAction(char * tournamentName, TElements * tElements) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tournament * tournament = calloc(1, sizeof(Tournament));
	tournament->name = tournamentName;
	tournament->tElements = tElements;
	return tournament;
}

Elements * MultipleElementsSemanticAction(Element * element, Elements * elements){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Elements * newElement = calloc(1, sizeof(Elements));
	newElement->leftElement = element;
	newElement->elements = elements;
	newElement->type = MULTIPLE;
	return newElement;
}

Elements * SingleElementSemanticAction(Element * element){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Elements * newElement = calloc(1, sizeof(Elements));
	newElement->element = element;
	newElement->type = SINGLE;
	return newElement;
}

Element * TrophyElementSemanticAction(Trophy * trophy){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = TROPHY_ELEMENT_TYPE;
	newElement->trophy = trophy;
	return newElement;
}

Element * TeamElementSemanticAction(Team * team){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = TEAM_ELEMENT_TYPE;
	newElement->team = team;
	return newElement;
}

Element * StadiumElementSemanticAction(Stadium * stadium){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = STADIUM_ELEMENT_TYPE;
	newElement->stadium = stadium;
	return newElement;
}

Element * BadgeElementSemanticAction(Badge * badge){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = BADGE_ELEMENT_TYPE;
	newElement->badge = badge;
	return newElement;
}

Element * PlayerElementSemanticAction(Player * player){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = PLAYER_ELEMENT_TYPE;
	newElement->player = player;
	return newElement;
}

Element * BallElementSemanticAction(Ball * ball){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = BALL_ELEMENT_TYPE;
	newElement->ball = ball;
	return newElement;
}

Element * SpecialElementSemanticAction(Special * special){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Element * newElement = calloc(1, sizeof(Element));
	newElement->type = SPECIAL_ELEMENT_TYPE;
	newElement->special = special;
	return newElement;
}

tElements * SingleTournamentElementSemanticAction(TElement * tElement){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElements * newTElement = calloc(1, sizeof(TElements));
	newTElement->tElement = tElement;
	newTElement->type = SINGLE;
	return newTElement;
}

tElements *  MultipleTournamentSemanticAction(TElement * tElement, TElements * tElements){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TElements * newTElement = calloc(1, sizeof(TElements));
	newTElement->leftTElement = tElement;
	newTElement->tElements = tElements;
	newTElement->type = MULTIPLE;
	return newTElement;
}

tElement * TrophyTournamentElementSemanticAction(Trophy * trophy) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tElement * newTElement = calloc(1, sizeof(TElement));
	newTElement->type = TROPHY_TELEMENT_TYPE;
	newTElement->trophy = trophy;
	return newTElement;
}	

tElement * TeamTournamentElementSemanticAction(Team * team) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tElement * newTElement = calloc(1, sizeof(TElement));
	newTElement->type = TEAM_TELEMENT_TYPE;
	newTElement->team = team;
	return newTElement;

}

tElement * GroupTournamentElementSemanticAction(Groups * group) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tElement * newTElement = calloc(1, sizeof(TElement));
	newTElement->type = GROUP_TELEMENT_TYPE;
	newTElement->group = group;
	return newTElement;
}

tElement * StadiumTournamentElementSemanticAction(Stadium * stadium) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tElement * newTElement = calloc(1, sizeof(TElement));
	newTElement->type = STADIUM_TELEMENT_TYPE;
	newTElement->stadium = stadium;
	return newTElement;

}

tElement * BallTournamentElementSemanticAction(Ball * ball) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	tElement * newTElement = calloc(1, sizeof(TElement));
	newTElement->type = BALL_TELEMENT_TYPE;
	newTElement->ball = ball;
	return newTElement;

}

Trophy * TrophySemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Trophy * trophy = calloc(1, sizeof(Trophy));
	trophy->photo = photo;
	trophy->name = name;
	return trophy;
}

Group * GroupSemanticAction(char * name, Teams * teams){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Group * group = calloc(1, sizeof(Group));
	group->name = name;
	group->teams = teams;
	return group;
}

Teams * MultipleTeamsSemanticAction(Team * team, Teams * teams){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Teams * newTeam = calloc(1, sizeof(Teams));
	newTeams->leftTeam = team;
	newTeams->teams = teams;
	newTeams->type = MULTIPLE;
	return newTeams;
}

Teams * SingleTeamProgramSemanticAction(Team * team){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Teams * newTeams = calloc(1, sizeof(Teams));
	newTeams->team = team;
	newTeams->type = SINGLE;
	return newTeams;
}

Team * TeamSemanticAction(char * name, TTeams * tTeams){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Team * team = calloc(1, sizeof(Team));
	team->name = name;
	team->tTeams = tTeams;
	return team;
}

TTeams * SingleTTeamsSemanticAction(TTeam * tTeam){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeams * newTTeams = calloc(1, sizeof(TTeams));
	newTTeams->tTeam = tTeam;
	newTTeams->type = SINGLE;
	return newTTeams;
}

TTeams * MultipleTTeamsSemanticAction(TTeam * tTeam, TTeams * tTeams){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeams * newTTeams = calloc(1, sizeof(TTeams));
	newTTeams->leftTTeam = tTeam;
	newTTeams->tTeams = tTeams;
	newTTeams->type = MULTIPLE;
	return newTTeams;
}

TTeam * BadgeTTeamSemanticAction(Badge * badge){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam * newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = BADGE_TTEAM_TYPE;
	newTTeam->badge = badge;
	return newTTeam;
}

TTeam * LineupTTeamSemanticAction(Lineup * lineup){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam * newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = LINEUP_TTEAM_TYPE;
	newTTeam->lineup = lineup;
	return newTTeam;
}

TTeam * HomekitTTeamSemanticAction(Homekit * homekit){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam * newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = HOMEKIT_TTEAM_TYPE;
	newTTeam->homekit = homekit;
	return newTTeam;

}

TTeam * PlayerTTeamSemanticAction(Player * player){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	TTeam * newTTeam = calloc(1, sizeof(TTeam));
	newTTeam->type = PLAYER_TTEAM_TYPE;
	newTTeam->player = player;
	return newTTeam;
}

Player * PlayerSemanticAction(char * name, playerDatas * playerDatas){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Player * player = calloc(1, sizeof(Player));
	player->name = name;
	player->playerDatas = playerDatas;
	return player;
} 

PlayerDatas * SinglePlayerDatasSemanticAction(PlayerData * playerData){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerDatas * newPlayerDatas = calloc(1, sizeof(PlayerDatas));
	newPlayerDatas->playerData = playerData;
	newPlayerDatas->type = SINGLE;
	return newPlayerDatas;
}

PlayerDatas * MultiplePlayerDatasSemanticAction(PlayerData * playerData, PlayerDatas * playerDatas){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerDatas * newPlayerDatas = calloc(1, sizeof(PlayerDatas));
	newPlayerDatas->leftPlayerData = playerData;
	newPlayerDatas->playerDatas = playerDatas;
	newPlayerDatas->type = MULTIPLE;
	return newPlayerDatas;
}

PlayerData * PlayerDataStringSemanticAction(char * value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerData * playerData = calloc(1, sizeof(PlayerData));
	playerData->type = PLAYER_TYPE_STRING;
	playerData->value = name;
	return playerData;
}

PlayerData * PlayerDataFloatSemanticAction(float value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerData * playerData = calloc(1, sizeof(PlayerData));
	playerData->type = PLAYER_TYPE_FLOAT;
	playerData->floatValue = value;
	return playerData;
}

PlayerTypeString * PlayerTypeCountrySemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString * playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_COUNTRY;
	return playerTypeString;
}

PlayerTypeString * PlayerTypeBirthdaySemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString * playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_BIRTHDAY;
	return playerTypeString;
}

PlayerTypeString * PlayerTypeTeamSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString * playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_TEAM;
	return playerTypeString;
}

PlayerTypeString * PlayerTypePhotoSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeString * playerTypeString = calloc(1, sizeof(PlayerTypeString));
	playerTypeString->type = PLAYER_PHOTO;
	return playerTypeString;
}

PlayerTypeFloat * PlayerTypeHeightSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeFloat * playerTypeFloat = calloc(1, sizeof(PlayerTypeFloat));
	playerTypeFloat->type = PLAYER_HEIGHT;
	return playerTypeFloat;
}

PlayerTypeFloat * PlayerTypeWeightSemanticAction(){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	PlayerTypeFloat * playerTypeFloat = calloc(1, sizeof(PlayerTypeFloat));
	playerTypeFloat->type = PLAYER_WEIGHT;
	return playerTypeFloat;
} 

Stadium * StadiumSemanticAction(char * name, StadiumDatas * stadiumDatas){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Stadium * stadium = calloc(1, sizeof(Stadium));
	stadium->name = name;
	stadium->stadiumDatas = stadiumDatas;
	return stadium;
}

StadiumDatas * SingleStadiumDatasSemanticAction(StadiumData * stadiumData){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumDatas * newStadiumDatas = calloc(1, sizeof(StadiumDatas));
	newStadiumDatas->stadiumData = stadiumData;
	newStadiumDatas->type = SINGLE;
	return newStadiumDatas;
}

StadiumDatas * MultipleStadiumDatasSemanticAction(StadiumData * stadiumData, StadiumDatas * stadiumDatas){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumDatas * newStadiumDatas = calloc(1, sizeof(StadiumDatas));
	newStadiumDatas->leftStadiumData = stadiumData;
	newStadiumDatas->stadiumDatas = stadiumDatas;
	newStadiumDatas->type = MULTIPLE;
	return newStadiumDatas;
}

StadiumData * StadiumDataSemanticAction(int value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumData * stadiumData = calloc(1, sizeof(StadiumData));
	stadiumData->type = STADIUM_CAPACITY;
	stadiumData->capacity = value;
	return stadiumData;
}

StadiumData * StadiumDataPhotoSemanticAction(Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	StadiumData * stadiumData = calloc(1, sizeof(StadiumData));
	stadiumData->type = STADIUM_PHOTO;
	stadiumData->photo = photo;
	return stadiumData;
}

Badge * BadgeSemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Badge * badge = calloc(1, sizeof(Badge));
	badge->name = name;
	badge->photo = photo;
	return badge;
}

Photo * PhotoSemanticAction(char * url){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Photo * photo = calloc(1, sizeof(Photo));
	photo->url = url;
	return photo;
}

Lineup * LineupSemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Lineup * lineup = calloc(1, sizeof(Lineup));
	lineup->name = name;
	lineup->photo = photo;
	return lineup;
}

homekit * HomekitSemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Homekit * homekit = calloc(1, sizeof(Homekit));
	homekit->name = name;
	homekit->photo = photo;
	return homekit;
}

Ball * BallSemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Ball * ball = calloc(1, sizeof(Ball));
	ball->name = name;
	ball->photo = photo;
	return ball;
}

Special * SpecialSemanticAction(char * name, Photo * photo){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Special * special = calloc(1, sizeof(Special));
	special->name = name;
	special->photo = photo;
	return special;
}