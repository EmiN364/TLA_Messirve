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

typedef enum ExpressionType ExpressionType;
typedef enum FactorType FactorType;
typedef enum ProgamType ProgamType;
typedef enum figType figType;

typedef struct Constant Constant;
typedef struct Expression Expression;
typedef struct Factor Factor;
typedef struct Program Program;
typedef struct Album Album;
typedef struct Figurita Figurita;
typedef struct Player Player;
typedef struct Stadium Stadium;
typedef struct Badge Badge;
typedef struct Trophy Trophy;
typedef struct Lineup Lineup;
typedef struct HomeKit HomeKit;
typedef struct Ball Ball;
typedef struct Special Special;

typedef struct Page Page;
typedef struct Figuritas Figuritas;

/**
 * Node types for the Abstract Syntax Tree (AST).
 */

enum ProgamType{
	ALBUM,
	FIGURITA
};

enum figType{
	PLAYER,
	STADIUM,
	BADGE,
	TROPHY,
	LINEUP,
	HOMEKIT,
	BALL,
	SPECIAL
};

enum ExpressionType {
	ADDITION,
	DIVISION,
	FACTOR,
	MULTIPLICATION,
	SUBTRACTION
};

enum FactorType {
	CONSTANT,
	EXPRESSION
};

struct Constant {
	int value;
};

struct Factor {
	union {
		Constant * constant;
		Expression * expression;
	};
	FactorType type;
};

struct Expression {
	union {
		Factor * factor;
		struct {
			Expression * leftExpression;
			Expression * rightExpression;
		};
	};
	ExpressionType type;
};

struct Figuritas {
	Figurita * figurita;
	Figuritas * next;
};

struct Page {
	union {
		Figuritas * figurita;
		Page * next;
	}
};

struct Album {
	Page * page;
};

struct Figurita {
	union {
		Player * player;
		Stadium * stadium;
		Badge * badge;
		Trophy * trophy;
		Lineup * lineup;
		HomeKit * homeKit;
		Ball * ball;
		Special * special;
	};
	figType type;
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

struct Program {
	union {
		Album * album;
		Figurita * figurita;
	};
	ProgamType type;
};

/**
 * Node recursive destructors.
 */
void releaseConstant(Constant * constant);
void releaseExpression(Expression * expression);
void releaseFactor(Factor * factor);
void releaseProgram(Program * program);

#endif