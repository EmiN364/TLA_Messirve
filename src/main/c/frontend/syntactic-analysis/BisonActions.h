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

Program *ProgramSemanticAction(CompilerState *compilerState, Elements *elements);

Elements *MultipleElementsSemanticAction(Element *element, Elements *elements);

Elements *SingleElementsSemanticAction(Element *element);

Element *TournamentElementSemanticAction(Tournament *tournament);

Element *TrophyElementSemanticAction(Trophy *trophy);

Element *TeamElementSemanticAction(Team *team);

Element *StadiumElementSemanticAction(Stadium *stadium);

Element *BadgeElementSemanticAction(Badge *badge);

Element *PlayerElementSemanticAction(Player *player);

Element *BallElementSemanticAction(Ball *ball);

Element *SpecialElementSemanticAction(Special *special);

Tournament *TournamentSemanticAction(char *tournamentName, TElements *tElements);

TElements *SingleTournamentElementSemanticAction(TElement *tElement);

TElements *MultipleTournamentSemanticAction(TElement *tElement, TElements *tElements);

TElement *TrophyTournamentElementSemanticAction(Trophy *trophy);

TElement *TeamTournamentElementSemanticAction(Team *team);

TElement *GroupTournamentElementSemanticAction(Group *group);

TElement *StadiumTournamentElementSemanticAction(Stadium *stadium);

TElement *BallTournamentElementSemanticAction(Ball *ball);

Trophy *TrophySemanticAction(Photo *photo);

Trophy *TrophyWithNameSemanticAction(char *name, Photo *photo);

Group *GroupSemanticAction(char *name, Teams *teams);

Teams *MultipleTeamsSemanticAction(Team *team, Teams *teams);

Teams *SingleTeamsSemanticAction(Team *team);

Team *TeamSemanticAction(char *name, TTeams *tTeams);

TTeams *SingleTTeamsSemanticAction(TTeam *tTeam);

TTeams *MultipleTTeamsSemanticAction(TTeam *tTeam, TTeams *tTeams);

TTeam *BadgeTTeamSemanticAction(Badge *badge);

TTeam *LineupTTeamSemanticAction(Lineup *lineup);

TTeam *HomekitTTeamSemanticAction(HomeKit *homekit);

TTeam *PlayerTTeamSemanticAction(Player *player);

Player *PlayerSemanticAction(char *name, PlayerDatas *playerDatas);

PlayerDatas *SinglePlayerDatasSemanticAction(PlayerData *playerData);

PlayerDatas *MultiplePlayerDatasSemanticAction(PlayerData *playerData, PlayerDatas *playerDatas);

PlayerData *PlayerDataStringSemanticAction(PlayerTypeString *playerTypeString, char *value);

PlayerData *PlayerDataFloatSemanticAction(PlayerTypeFloat *playerTypeFloat, float floatValue);

PlayerData *PlayerDataPhotoSemanticAction(Photo *photo);

PlayerTypeString *PlayerTypeCountrySemanticAction();

PlayerTypeString *PlayerTypeBirthdaySemanticAction();

PlayerTypeString *PlayerTypeTeamSemanticAction();

PlayerTypeFloat *PlayerTypeHeightSemanticAction();

PlayerTypeFloat *PlayerTypeWeightSemanticAction();

Stadium *StadiumSemanticAction(char *name, StadiumDatas *stadiumDatas);

StadiumDatas *SingleStadiumDatasSemanticAction(StadiumData *stadiumData);

StadiumDatas *MultipleStadiumDatasSemanticAction(StadiumData *stadiumData, StadiumDatas *stadiumDatas);

StadiumData *StadiumDataSemanticAction(int value);

StadiumData *StadiumDataPhotoSemanticAction(Photo *photo);

Badge *BadgeSemanticAction(Photo *photo);

Badge *BadgeWithNameSemanticAction(char *name, Photo *photo);

Photo *PhotoSemanticAction(char *value);

Lineup *LineupSemanticAction(Photo *photo);

Lineup *LineupWithNameSemanticAction(char *name, Photo *photo);

HomeKit *HomekitSemanticAction(Photo *photo);

HomeKit *HomekitWithNameSemanticAction(char *name, Photo *photo);

Ball *BallSemanticAction(Photo *photo);

Ball *BallWithNameSemanticAction(char *name, Photo *photo);

Special *SpecialSemanticAction(Photo *photo);

Special *SpecialWithNameSemanticAction(char *name, Photo *photo);
#endif
