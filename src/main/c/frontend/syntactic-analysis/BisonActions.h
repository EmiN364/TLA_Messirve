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

Elements * SingleElementSemanticAction(Element * element);

Element * TrophyElementSemanticAction(Trophy * trophy);

Element * TeamElementSemanticAction(Team * team);

Element * StadiumElementSemanticAction(Stadium * stadium);

Element * BadgeElementSemanticAction(Badge * badge);

Element * PlayerElementSemanticAction(Player * player);

Element * BallElementSemanticAction(Ball * ball);

Element * SpecialElementSemanticAction(Special * special);

tElements * SingleTournamentElementSemanticAction(TElement * tElement);

tElements *  MultipleTournamentSemanticAction(TElement * tElement, TElements * tElements);

tElement * TrophyTournamentElementSemanticAction(Trophy * trophy);

tElement * TeamTournamentElementSemanticAction(Team * team);

tElement * GroupTournamentElementSemanticAction(Groups * group);

tElement * StadiumTournamentElementSemanticAction(Stadium * stadium);

tElement * BallTournamentElementSemanticAction(Ball * ball);

Trophy * TrophySemanticAction(char * name, Photo * photo);

Group * GroupSemanticAction(char * name, Teams * teams);

Teams * MultipleTeamsSemanticAction(Team * team, Teams * teams);

Teams * SingleTeamProgramSemanticAction(Team * team);

Team * TeamSemanticAction(char * name, TTeams * tTeams);

TTeams * SingleTTeamsSemanticAction(TTeam * tTeam);

TTeams * MultipleTTeamsSemanticAction(TTeam * tTeam, TTeams * tTeams);

TTeam * BadgeTTeamSemanticAction(Badge * badge);

TTeam * LineupTTeamSemanticAction(Lineup * lineup);

TTeam * HomekitTTeamSemanticAction(Homekit * homekit);

TTeam * PlayerTTeamSemanticAction(Player * player);

#endif
