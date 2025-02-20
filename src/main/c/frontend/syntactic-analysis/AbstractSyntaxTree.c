#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger *_logger = NULL;

void initializeAbstractSyntaxTreeModule()
{
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule()
{
	if (_logger != NULL)
	{
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */

void releaseProgram(Program *program)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL)
	{
		releaseElements(program->elements);
		free(program);
	}
}
void releaseElements(Elements *elements)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (elements != NULL)
	{
		switch (elements->type)
		{
		case SINGLE:
			releaseElement(elements->element);
			break;
		case MULTIPLE:
			releaseElement(elements->leftElement);
			releaseElements(elements->elements);
			break;
		}
		free(elements);
	}
}
void releaseElement(Element *element)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (element != NULL)
	{
		switch (element->type)
		{
		case TROPHY_ELEMENT_TYPE:
			releaseTrophy(element->trophy);
			break;
		case TEAM_ELEMENT_TYPE:
			releaseTeam(element->team);
			break;
		case STADIUM_ELEMENT_TYPE:
			releaseStadium(element->stadium);
			break;
		case BADGE_ELEMENT_TYPE:
			releaseBadge(element->badge);
			break;
		case PLAYER_ELEMENT_TYPE:
			releasePlayer(element->player);
			break;
		case BALL_ELEMENT_TYPE:
			releaseBall(element->ball);
			break;
		case SPECIAL_ELEMENT_TYPE:
			releaseSpecial(element->special);
			break;
		case TOURNAMENT_ELEMENT_TYPE:
			releaseTournament(element->tournament);
			break;
		}
		free(element);
	}
}
void releaseTournament(Tournament *tournament)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tournament != NULL)
	{
		releaseTElements(tournament->tElements);
		free(tournament);
	}
}
void releaseTElements(TElements *tElements)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tElements != NULL)
	{
		switch (tElements->type)
		{
		case SINGLE:
			releaseTElement(tElements->tElement);
			break;
		case MULTIPLE:
			releaseTElement(tElements->leftTElement);
			releaseTElements(tElements->tElements);
			break;
		}
		free(tElements);
	}
}
void releaseTElement(TElement *tElement)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tElement != NULL)
	{
		switch (tElement->type)
		{
		case TROPHY_TELEMENT_TYPE:
			releaseTrophy(tElement->trophy);
			break;
		case TEAM_TELEMENT_TYPE:
			releaseTeam(tElement->team);
			break;
		case GROUP_TELEMENT_TYPE:
			releaseGroup(tElement->group);
			break;
		case STADIUM_TELEMENT_TYPE:
			releaseStadium(tElement->stadium);
			break;
		case BALL_TELEMENT_TYPE:
			releaseBall(tElement->ball);
			break;
		}
		free(tElement);
	}
}
void releaseTrophy(Trophy *trophy)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (trophy != NULL)
	{
		releasePhoto(trophy->photo);
		free(trophy);
	}
}
void releaseGroup(Group *group)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (group != NULL)
	{
		releaseTeams(group->teams);
		free(group);
	}
}
void releaseTeams(Teams *teams)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (teams != NULL)
	{
		switch (teams->type)
		{
		case SINGLE:
			releaseTeam(teams->team);
			break;
		case MULTIPLE:
			releaseTeam(teams->leftTeam);
			releaseTeams(teams->teams);
			break;
		}
		free(teams);
	}
}
void releaseTeam(Team *team)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (team != NULL)
	{
		releaseTTeams(team->tTeams);
		free(team);
	}
}
void releaseTTeams(TTeams *tTeams)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tTeams != NULL)
	{
		switch (tTeams->type)
		{
		case SINGLE:
			releaseTTeam(tTeams->tTeam);
			break;
		case MULTIPLE:
			releaseTTeam(tTeams->leftTTeam);
			releaseTTeams(tTeams->tTeams);
			break;
		}
		free(tTeams);
	}
}
void releaseTTeam(TTeam *tTeam)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (tTeam != NULL)
	{
		switch (tTeam->type)
		{
		case BADGE_TTEAM_TYPE:
			releaseBadge(tTeam->badge);
			break;
		case LINEUP_TTEAM_TYPE:
			releaseLineup(tTeam->lineup);
			break;
		case HOMEKIT_TTEAM_TYPE:
			releaseHomeKit(tTeam->homeKit);
			break;
		case PLAYER_TTEAM_TYPE:
			releasePlayer(tTeam->player);
			break;
		}
		free(tTeam);
	}
}
void releasePlayer(Player *player)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (player != NULL)
	{
		releasePlayerDatas(player->playerDatas);
		free(player);
	}
}
void releasePlayerDatas(PlayerDatas *playerDatas)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (playerDatas != NULL)
	{
		switch (playerDatas->type)
		{
		case SINGLE:
			releasePlayerData(playerDatas->playerData);
			break;
		case MULTIPLE:
			releasePlayerData(playerDatas->leftPlayerData);
			releasePlayerDatas(playerDatas->playerDatas);
			break;
		}
		free(playerDatas);
	}
}
void releasePlayerData(PlayerData *playerData)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (playerData != NULL)
	{
		free(playerData);
	}
}
void releasePlayerTypeString(PlayerTypeString *playerTypeString)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (playerTypeString != NULL)
	{
		free(playerTypeString);
	}
}
void releasePlayerTypeFloat(PlayerTypeFloat *playerTypeFloat)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (playerTypeFloat != NULL)
	{
		free(playerTypeFloat);
	}
}
void releaseStadium(Stadium *stadium)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stadium != NULL)
	{
		releaseStadiumDatas(stadium->stadiumDatas);
		free(stadium);
	}
}
void releaseStadiumDatas(StadiumDatas *stadiumDatas)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stadiumDatas != NULL)
	{
		switch (stadiumDatas->type)
		{
		case SINGLE:
			releaseStadiumData(stadiumDatas->stadiumData);
			break;
		case MULTIPLE:
			releaseStadiumData(stadiumDatas->leftStadiumData);
			releaseStadiumDatas(stadiumDatas->stadiumDatas);
			break;
		}
		free(stadiumDatas);
	}
}
void releaseStadiumData(StadiumData *stadiumData)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (stadiumData != NULL)
	{
		switch (stadiumData->type)
		{
		case STADIUM_CAPACITY:
			break;
		case STADIUM_PHOTO:
			releasePhoto(stadiumData->photo);
			break;
		}
		free(stadiumData);
	}
}
void releaseBadge(Badge *badge)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (badge != NULL)
	{
		releasePhoto(badge->photo);
		free(badge);
	}
}
void releaseLineup(Lineup *lineup)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (lineup != NULL)
	{
		releasePhoto(lineup->photo);
		free(lineup);
	}
}
void releaseHomeKit(HomeKit *homeKit)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (homeKit != NULL)
	{
		releasePhoto(homeKit->photo);
		free(homeKit);
	}
}
void releaseBall(Ball *ball)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (ball != NULL)
	{
		releasePhoto(ball->photo);
		free(ball);
	}
}
void releaseSpecial(Special *special)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (special != NULL)
	{
		releasePhoto(special->photo);
		free(special);
	}
}
void releasePhoto(Photo *photo)
{
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (photo != NULL)
	{
		free(photo);
	}
}