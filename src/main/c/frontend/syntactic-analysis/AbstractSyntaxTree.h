#ifndef ABSTRACT_SYNTAX_TREE_HEADER
#define ABSTRACT_SYNTAX_TREE_HEADER

#include "../../shared/Logger.h"
#include <stdlib.h>

/** Initialize module's internal state. */
void initializeAbstractSyntaxTreeModule();

/** Shutdown module's internal state. */
void shutdownAbstractSyntaxTreeModule();

/**
 * This typedefs allows self-referencing types.
 */

typedef struct Expression Expression;
typedef struct Program Program;
typedef struct Tournament Tournament;
typedef struct TElements TElements;
typedef struct TElement TElement;
typedef struct Elements Elements;
typedef struct Element Element;
typedef struct Player Player;
typedef struct Stadium Stadium;
typedef struct Badge Badge;
typedef struct Trophy Trophy;
typedef struct Lineup Lineup;
typedef struct HomeKit HomeKit;
typedef struct Ball Ball;
typedef struct Special Special;
typedef struct Team Team;
typedef struct Group Group;
typedef struct StadiumDatas StadiumDatas;
typedef struct StadiumData StadiumData;
typedef struct PlayerDatas PlayerDatas;
typedef struct PlayerData PlayerData;
typedef struct PlayerTypeString PlayerTypeString;
typedef struct PlayerTypeFloat PlayerTypeFloat;
typedef struct PlayerTypeDate PlayerTypeDate;
typedef struct Teams Teams;
typedef struct TTeams TTeams;
typedef struct TTeam TTeam;
typedef struct Photo Photo;
typedef struct HomeKit HomeKit;

typedef struct Page Page;
typedef struct Figuritas Figuritas;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

typedef enum SingleOrMultiple
{
	SINGLE,
	MULTIPLE
} SingleOrMultiple;

typedef enum ElementType
{
	TROPHY_ELEMENT_TYPE,
	TEAM_ELEMENT_TYPE,
	STADIUM_ELEMENT_TYPE,
	BADGE_ELEMENT_TYPE,
	PLAYER_ELEMENT_TYPE,
	BALL_ELEMENT_TYPE,
	SPECIAL_ELEMENT_TYPE,
	TOURNAMENT_ELEMENT_TYPE
} ElementType;

typedef enum TElementType
{
	TROPHY_TELEMENT_TYPE,
	TEAM_TELEMENT_TYPE,
	GROUP_TELEMENT_TYPE,
	STADIUM_TELEMENT_TYPE,
	BALL_TELEMENT_TYPE
} TElementType;

typedef enum TTeamType
{
	BADGE_TTEAM_TYPE,
	LINEUP_TTEAM_TYPE,
	HOMEKIT_TTEAM_TYPE,
	PLAYER_TTEAM_TYPE
} TTeamType;

typedef enum PlayerDataType
{
	PLAYER_TYPE_STRING,
	PLAYER_TYPE_FLOAT,
	PLAYER_TYPE_PHOTO
} PlayerDataType;

typedef enum PlayerTypeStringType
{
	PLAYER_COUNTRY,
	PLAYER_BIRTHDATE,
	PLAYER_TEAM
} PlayerTypeStringType;

typedef enum PlayerTypeFloatType
{
	PLAYER_HEIGHT,
	PLAYER_WEIGHT
} PlayerTypeFloatType;

typedef enum StadiumDataType
{
	STADIUM_CAPACITY,
	STADIUM_PHOTO
} StadiumDataType;

struct Program
{
	Elements *elements;
};

struct Tournament
{
	char *name;
	TElements *tElements;
};

struct Elements
{
	union
	{
		struct
		{
			Element *leftElement;
			Elements *elements;
		};
		Element *element;
	};
	SingleOrMultiple type;
};

struct Element
{
	union
	{
		Trophy *trophy;
		Team *team;
		Stadium *stadium;
		Badge *badge;
		Player *player;
		Ball *ball;
		Special *special;
		Tournament *tournament;
	};
	ElementType type;
};

struct TElements
{
	union
	{
		struct
		{
			TElement *leftTElement;
			TElements *tElements;
		};
		TElement *tElement;
	};
	SingleOrMultiple type;
};

struct TElement
{
	union
	{
		Trophy *trophy;
		Team *team;
		Group *group;
		Stadium *stadium;
		Ball *ball;
	};
	TElementType type;
};

struct Trophy
{
	char *name;
	Photo *photo;
};

struct Group
{
	char *name;
	Teams *teams;
};

struct Teams
{
	union
	{
		struct
		{
			Team *leftTeam;
			Teams *teams;
		};
		Team *team;
	};
	SingleOrMultiple type;
};

struct Team
{
	char *name;
	TTeams *tTeams;
};

struct TTeams
{
	union
	{
		struct
		{
			TTeam *leftTTeam;
			TTeams *tTeams;
		};
		TTeam *tTeam;
	};
	SingleOrMultiple type;
};

struct TTeam
{
	union
	{
		Badge *badge;
		Lineup *lineup;
		HomeKit *homeKit;
		Player *player;
	};
	TTeamType type;
};

struct Player
{
	char *name;
	PlayerDatas *playerDatas;
};

struct PlayerDatas
{
	union
	{
		struct
		{
			PlayerData *leftPlayerData;
			PlayerDatas *playerDatas;
		};
		PlayerData *playerData;
	};
	SingleOrMultiple type;
};

struct PlayerData
{
	union
	{
		struct
		{
			PlayerTypeString *playerTypeString;
			char *value;
		};
		struct
		{
			PlayerTypeFloat *playerTypeFloat;
			float floatValue;
		};
		Photo *photo;
	};
	PlayerDataType type;
};

struct PlayerTypeString
{
	PlayerTypeStringType type;
};

struct PlayerTypeFloat
{
	PlayerTypeFloatType type;
};

struct Stadium
{
	char *name;
	StadiumDatas *stadiumDatas;
};

struct StadiumDatas
{
	union
	{
		struct
		{
			StadiumData *leftStadiumData;
			StadiumDatas *stadiumDatas;
		};
		StadiumData *stadiumData;
	};
	SingleOrMultiple type;
};

struct StadiumData
{
	union
	{
		int capacity;
		Photo *photo;
	};
	StadiumDataType type;
};

struct Badge
{
	char *name;
	Photo *photo;
};

struct Lineup
{
	char *name;
	Photo *photo;
};

struct HomeKit
{
	char *name;
	Photo *photo;
};

struct Ball
{
	char *name;
	Photo *photo;
};

struct Special
{
	char *name;
	Photo *photo;
};

struct Photo
{
	char *url;
};

/**
 * Node recursive destructors.
 */
void releaseProgram(Program *program);
void releaseTournament(Tournament *tournament);
void releaseElements(Elements *elements);
void releaseElement(Element *element);
void releaseTElements(TElements *tElements);
void releaseTElement(TElement *tElement);
void releaseTrophy(Trophy *trophy);
void releaseGroup(Group *group);
void releaseTeams(Teams *teams);
void releaseTeam(Team *team);
void releaseTTeams(TTeams *tTeams);
void releaseTTeam(TTeam *tTeam);
void releasePlayer(Player *player);
void releasePlayerDatas(PlayerDatas *playerDatas);
void releasePlayerData(PlayerData *playerData);
void releasePlayerTypeString(PlayerTypeString *playerTypeString);
void releasePlayerTypeFloat(PlayerTypeFloat *playerTypeFloat);
void releaseStadium(Stadium *stadium);
void releaseStadiumDatas(StadiumDatas *stadiumDatas);
void releaseStadiumData(StadiumData *stadiumData);
void releaseBadge(Badge *badge);
void releaseLineup(Lineup *lineup);
void releaseHomeKit(HomeKit *homeKit);
void releaseBall(Ball *ball);
void releaseSpecial(Special *special);
void releasePhoto(Photo *photo);

#endif