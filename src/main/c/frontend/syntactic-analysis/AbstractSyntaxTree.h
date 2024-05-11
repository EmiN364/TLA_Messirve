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
typedef struct Groups Groups;
typedef struct Group Group;
typedef struct StadiumDatas StadiumDatas;
typedef struct StadiumData StadiumData;
typedef struct PlayerDatas PlayerDatas;
typedef struct PlayerData PlayerData;
typedef struct PlayerTypeString PlayerTypeString;
typedef struct PlayerTypeFloat PlayerTypeFloat;
typedef struct Teams Teams;
typedef struct TTeams TTeams;
typedef struct TTeam TTeam;
typedef struct Photo Photo;
typedef struct Homekit Homekit;

typedef struct Page Page;
typedef struct Figuritas Figuritas;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

typedef enum ProgamType {
	TOURNAMENT_TYPE,
	ELEMENTS_TYPE
} ProgamType;

typedef enum SingleOrMultiple {
	SINGLE,
	MULTIPLE
} SingleOrMultiple;

typedef enum ElementType {
	TROPHY_ELEMENT_TYPE,
	TEAM_ELEMENT_TYPE,
	STADIUM_ELEMENT_TYPE,
	BADGE_ELEMENT_TYPE,
	PLAYER_ELEMENT_TYPE,
	BALL_ELEMENT_TYPE,
	SPECIAL_ELEMENT_TYPE
} ElementType;

typedef enum TElementType {
	TROPHY_TELEMENT_TYPE,
	TEAM_TELEMENT_TYPE,
	GROUP_TELEMENT_TYPE,
	STADIUM_TELEMENT_TYPE,
	BALL_TELEMENT_TYPE
} TElementType;

typedef enum TTeamType {
	BADGE_TTEAM_TYPE,
	LINEUP_TTEAM_TYPE,
	HOMEKIT_TTEAM_TYPE,
	PLAYER_TTEAM_TYPE
} TTeamType;

typedef enum PlayerDataType {
	PLAYER_TYPE_STRING,
	PLAYER_TYPE_FLOAT
} PlayerDataType;

typedef enum PlayerTypeStringType {
	PLAYER_COUNTRY,
	PLAYER_BIRTHDATE,
	PLAYER_TEAM,
	PLAYER_PHOTO
} PlayerTypeStringType;

typedef enum PlayerTypeFloatType {
	PLAYER_HEIGHT,
	PLAYER_WEIGHT
} PlayerTypeFloatType;

typedef enum StadiumDataType {
	STADIUM_CAPACITY,
	STADIUM_PHOTO
} StadiumDataType;


struct Program {
	union {
		Tournament * tournament;
		Elements * elements;
	};
	ProgamType type;
};

struct Tournament {
	char * name;
	TElements * tElements;
};

struct Elements {
	union {
		struct {
			Element * leftElement;
			Elements * elements;
		};
		Element * element;
	};
	SingleOrMultiple type;
};

struct Element {
	union {
		Trophy * trophy;
		Team * team;
		Stadium * stadium;
		Badge * badge;
		Player * player;
		Ball * ball;
		Special * special;
	};
	ElementType type;
};

struct TElements {
	union {
		struct {
			TElement * leftTElement;
			TElements * tElements;
		};
		TElement * tElement;
	};
	SingleOrMultiple type;
};

struct TElement {
	union {
		Trophy * trophy;
		Team * team;
		Groups * group;
		Stadium * stadium;
		Ball * ball;
	};
	TElementType type;
};

struct Trophy {
	char * name;
	Photo * photo;
};

struct Group {
	char * name;
	Teams * teams;
};

struct Teams {
	union {
		struct {
			Team * leftTeam;
			Teams * teams;
		};
		Team * team;
	};
	SingleOrMultiple type;
};

struct Team {
	char * name;
	TTeam * tTeam;
};

struct TTeams {
	union {
		struct {
			TTeam * leftTTeam;
			TTeams * tTeams;
		};
		TTeam * tTeam;
	};
	SingleOrMultiple type;
};

struct TTeam {
	union {
		Badge * badge;
		Lineup * lineup;
		HomeKit * homeKit;
		Player * player;
	};
	TTeamType type;
};

struct player {
	char * name;
	PlayerDatas * playerDatas;
};

struct PlayerDatas {
	union {
		struct {
			PlayerData * leftPlayerData;
			PlayerDatas * playerDatas;
		};
		PlayerData * playerData;
	};
	SingleOrMultiple type;
};

struct PlayerData {
	union {
		struct {
			PlayerTypeString * playerTypeString;
			char * value;
		};
		struct {
			PlayerTypeFloat * playerTypeFloat;
			float floatValue;
		};
	};
	PlayerDataType type;
};

struct PlayerTypeString {
	PlayerTypeStringType type;
};

struct PlayerTypeFloat {
	PlayerTypeFloatType type;
};

struct stadium {
	char * name;
	StadiumDatas * stadiumDatas;
};

struct StadiumDatas {
	union {
		struct {
			StadiumData * leftStadiumData;
			StadiumDatas * stadiumDatas;
		};
		StadiumData * stadiumData;
	};
	SingleOrMultiple type;
};

struct StadiumData {
	union {
		int capacity;
		Photo * photo;
	};
	StadiumDataType type;
};

struct Badge {
	char * name;
	Photo * photo;
};

struct Lineup {
	char * name;
	Photo * photo;
};

struct HomeKit {
	char * name;
	Photo * photo;
};

struct Ball {
	char * name;
	Photo * photo;
};

struct Special {
	char * name;
	Photo * photo;
};

struct Photo {
	char * url;
};

/**
 * Node recursive destructors.
 */
/* void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor); */
void releaseTElement(TElement * tElement);
void releaseTournament(Tournament * tournament);
void releaseProgram(Program * program);

#endif