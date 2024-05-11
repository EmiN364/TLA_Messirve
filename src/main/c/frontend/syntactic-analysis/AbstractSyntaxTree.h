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

typedef enum ProgamType ProgamType;
typedef enum TElementType TElementType;
typedef enum ElementType ElementType;

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

enum ProgamType {
	TOURNAMENT_TYPE,
	ELEMENTS_TYPE
};

enum TElementType {
	TROPHY_TYPE,
	TEAM_TYPE,
	GROUPS_TYPE,
	STADIUM_TYPE,
	BALL_TYPE
};

enum ElementType {
	TROPHY_TYPE2,
	TEAM_TYPE2,
	STADIUM_TYPE2,
	BADGE_TYPE2,
	PLAYER_TYPE2,
	BALL_TYPE2
};

struct Program {
	union {
		Tournament * tournament;
		Elements * elements;
	};
	ProgamType type;
};

struct Elements {
	Element ** elements;
};

struct Tournament {
	TElements * tElements;
};

struct TElements {
	TElement ** tElements;
};

struct TElement {
	union {
		Trophy * trophy;
		Team * team;
		Groups * groups;
		Stadium * stadium;
		Ball * ball;
	};
	TElementType type;
};

struct Element {
	union {
		Trophy * trophy;
		Team * team;
		Stadium * stadium;
		Badge * badge;
		Player * player;
		Ball * ball;
	};
	ElementType type;
};

struct Player {
	char * name;
	char * country;
	char * birthday;
	char * team;
	float height;
	float weight;
	char * photo;
};

struct Stadium {
	char * name;
	int capacity;
	char * photo;
};

struct Badge {
	char * name;
	char * photo;
};

struct Trophy {
	char * name;
	char * photo;
};

struct Lineup {
	char * name;
	char * photo;
};

struct HomeKit {
	char * name;
	char * photo;
};

struct Ball {
	char * name;
	char * photo;
};

struct Special {
	char * name;
	char * photo;
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