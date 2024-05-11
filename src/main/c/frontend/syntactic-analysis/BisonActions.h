#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../shared/CompilerState.h"
#include "../../shared/Logger.h"
#include "../../shared/Type.h"
#include "AbstractSyntaxTree.h"
#include "SyntacticAnalyzer.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeBisonActionsModule();

/** Shutdown module's internal state. */
void shutdownBisonActionsModule();



/**
 * Bison semantic actions.
 */

/* Constant * IntegerConstantSemanticAction(const int value);
Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type);
Expression * FactorExpressionSemanticAction(Factor * factor);
Factor * ConstantFactorSemanticAction(Constant * constant);
Factor * ExpressionFactorSemanticAction(Expression * expression);*/

Program * ProgramSemanticAction(CompilerState * compilerState, Expression * expression); 

Expression * ExpressionTournamentSemanticAction(Tournament * tournament); 

Expression * ExpressionElementsSemanticAction(Elements * elements); 

Tournament * TournamentSemanticAction(char * tournamentName, TElements * tElements);

Elements * MultipleElementsSemanticAction(Element * element, Elements * elements);

Elements * SingleElementsSemanticAction(Element * element);

Element * TrophyElementSemanticAction(Trophy * trophy);

Element * TeamElementSemanticAction(Team * team);

Element * StadiumElementSemanticAction(Stadium * stadium);

Element * BadgeElementSemanticAction(Badge * badge);

Element * PlayerElementSemanticAction(Player * player);

Element * BallElementSemanticAction(Ball * ball);

Element * SpecialElementSemanticAction(Special * special);

TElements * SingleTournamentElementSemanticAction(TElement * tElement);

TElements *  MultipleTournamentSemanticAction(TElement * tElement, TElements * tElements);

TElement * TrophyTournamentElementSemanticAction(Trophy * trophy);

TElement * TeamTournamentElementSemanticAction(Team * team);

TElement * GroupTournamentElementSemanticAction(Group * group);

TElement * StadiumTournamentElementSemanticAction(Stadium * stadium);

TElement * BallTournamentElementSemanticAction(Ball * ball);

Trophy * TrophySemanticAction(char * name, Photo * photo);

Group * GroupSemanticAction(char * name, Teams * teams);

Teams * MultipleTeamsSemanticAction(Team * team, Teams * teams);

Teams * SingleTeamsSemanticAction(Team * team);

Team * TeamSemanticAction(char * name, TTeams * tTeams);

TTeams * SingleTTeamsSemanticAction(TTeam * tTeam);

TTeams * MultipleTTeamsSemanticAction(TTeam * tTeam, TTeams * tTeams);

TTeam * BadgeTTeamSemanticAction(Badge * badge);

TTeam * LineupTTeamSemanticAction(Lineup * lineup);

TTeam * HomekitTTeamSemanticAction(HomeKit * homekit);

TTeam * PlayerTTeamSemanticAction(Player * player);

Player * PlayerSemanticAction(char * name, PlayerDatas * playerDatas);

PlayerDatas * SinglePlayerDatasSemanticAction(PlayerData * playerData);

PlayerDatas * MultiplePlayerDatasSemanticAction(PlayerData * playerData, PlayerDatas * playerDatas);

PlayerData * PlayerDataStringSemanticAction(char * value);

PlayerData * PlayerDataFloatSemanticAction(float floatValue);

PlayerTypeString * PlayerTypeCountrySemanticAction();

PlayerTypeString * PlayerTypeBirthdaySemanticAction();

PlayerTypeString * PlayerTypeTeamSemanticAction();

PlayerTypeString * PlayerTypePhotoSemanticAction();

PlayerTypeFloat * PlayerTypeHeightSemanticAction();

PlayerTypeFloat * PlayerTypeWeightSemanticAction();

Stadium * StadiumSemanticAction(char * name, StadiumDatas * stadiumDatas);

StadiumDatas * SingleStadiumDatasSemanticAction(StadiumData * stadiumData);

StadiumDatas * MultipleStadiumDatasSemanticAction(StadiumData * stadiumData, StadiumDatas * stadiumDatas);

StadiumData * StadiumDataSemanticAction(int value);

StadiumData * StadiumDataPhotoSemanticAction(Photo * photo);

Badge * BadgeSemanticAction(char * name, Photo * photo);

Photo * PhotoSemanticAction(char * value);

Lineup * LineupSemanticAction(char * name, Photo * photo);

HomeKit * HomekitSemanticAction(char * name, Photo * photo);

Ball * BallSemanticAction(char * name, Photo * photo);

Special * SpecialSemanticAction(char * name, Photo * photo);
#endif
