#include "Generator.h"
#include <string.h>

// Archivo de salida
FILE * f;

struct teamMap {
	struct teamMap * next;
	char * key;
	Team * team;
};
struct playerMap {
	struct playerMap * next;
	char * key;
	Player * player;
	boolean printed;
};

struct teamMap * teamMapHead;
struct playerMap * playerMapHead;
//playerMap * noTeamPlayerMapHead;

/* MODULE INTERNAL STATE */
const char _indentationCharacter = ' ';
const char _indentationSize = 4;
static Logger * _logger = NULL;

void initializeGeneratorModule() {
	_logger = createLogger("Generator");
}

void shutdownGeneratorModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PRIVATE FUNCTIONS */
static void _generatePrologue();
static void _generateProgram(Program * program);
static void _generateEpilogue();
static void _generateElements(const unsigned int indentationLevel, Elements * elements);
static void _generateElement(const unsigned int indentationLevel, Element * element);
static void _generateTrophy(const unsigned int indentationLevel, Trophy * trophy);
static void _generateTeam(const unsigned int indentationLevel, Team * team);
static void _addTeam(Team * team);
static void _generateTeams(const unsigned int indentationLevel, Teams * teams);
static void _generateStadium(const unsigned int indentationLevel, Stadium * stadium);
static void _generateBadge(const unsigned int indentationLevel, Badge * badge);
static void _generatePlayer(const unsigned int indentationLevel, Player * player);
// static void _addPlayer(Player * player);
static void _generateBall(const unsigned int indentationLevel, Ball * ball);
static void _generateSpecial(const unsigned int indentationLevel, Special * special);
static void _generateTournament(const unsigned int indentationLevel, Tournament * tournament);
static char * _indentation(const unsigned int indentationLevel);
static void _printURL(const unsigned int indentationLevel, char * url);
static void _generateCard(const unsigned int indentationLevel, char * url, char * name);
static void _generatePlayerDatas(const unsigned int indentationLevel, PlayerDatas * playerDatas);
static void _generatePlayerData(const unsigned int indentationLevel, PlayerData * playerData);
static void _generatePlayerTypeString(const unsigned int indentationLevel, PlayerTypeString * playerTypeString, char * value);
static void _generatePlayerTypeFloat(const unsigned int indentationLevel, PlayerTypeFloat * playerTypeFloat, float floatValue);
static void _generateStadiumDatas(const unsigned int indentationLevel, StadiumDatas * stadiumDatas);
static void _generateStadiumData(const unsigned int indentationLevel, StadiumData * stadiumData);
static void _generateTTeams(const unsigned int indentationLevel, TTeams * tTeams);
static void _generateTTeam(const unsigned int indentationLevel, TTeam * tTeam);
static void _generateLineup(const unsigned int indentationLevel, Lineup * lineup);
static void _generateHomeKit(const unsigned int indentationLevel, HomeKit * homeKit);
static void _generateTElements(const unsigned int indentationLevel, TElements * tElements);
static void _generateTElement(const unsigned int indentationLevel, TElement * tElement);
static void _generateTElementExtra(const unsigned int indentationLevel, TElement * tElement);
static void _generateTElementsExtras(const unsigned int indentationLevel, TElements * tElements);
static void _generateGroup(const unsigned int indentationLevel, Group * group);

/**
 * Generates an indentation string for the specified level.
 */
static char * _indentation(const unsigned int level) {
	return indentation(_indentationCharacter, level, _indentationSize);
}

/**
 * Generates the output of the specified program.
 */
void generate(CompilerState * compilerState) {
	logDebugging(_logger, "Generating final output...");
	f = fopen("Output.html", "w");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue();
	fclose(f);
	logDebugging(_logger, "Generation is done.");
}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue() {
	fprintf(f, "<!DOCTYPE html>\n");
	fprintf(f, "<html>\n");
	fprintf(f, "%s<head>\n", _indentation(1));
	fprintf(f, "%s<title>Figuritas</title>\n", _indentation(2));
	fprintf(f, "%s<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n", _indentation(2));
	fprintf(f, "%s<link href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\">\n", _indentation(2));
	fprintf(f, "%s<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js\"></script>\n", _indentation(2));
	fprintf(f, "%s</head>\n", _indentation(1));
	fprintf(f, "%s<body>\n", _indentation(1));
}

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program * program) {
	_generateElements(2, program->elements);
}

/**
 * Creates the epilogue of the generated output.
 */
static void _generateEpilogue() {
	fprintf(f, "%s</body>\n", _indentation(1));
	fprintf(f, "</html>\n");
}

/**
 * Generates the output of the elements.
 */
static void _generateElements(const unsigned int indentationLevel, Elements * elements) {
	switch (elements->type) {
		case SINGLE:
			_generateElement(indentationLevel, elements->element);
			break;
		case MULTIPLE:
			_generateElement(indentationLevel, elements->leftElement);
			_generateElements(indentationLevel, elements->elements);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", elements->type);
			break;
	}
}

/**
 * Generates the output of an element.
 */
static void _generateElement(const unsigned int indentationLevel, Element * element) {
	switch (element->type) {
		case TROPHY_ELEMENT_TYPE:
			_generateTrophy(indentationLevel, element->trophy);
			break;
		case TEAM_ELEMENT_TYPE:
			_generateTeam(indentationLevel, element->team);
			break;
		case STADIUM_ELEMENT_TYPE:
			_generateStadium(indentationLevel, element->stadium);
			break;
		case BADGE_ELEMENT_TYPE:
			_generateBadge(indentationLevel, element->badge);
			break;
		case PLAYER_ELEMENT_TYPE:
			_generatePlayer(indentationLevel, element->player);
			break;
		case BALL_ELEMENT_TYPE:
			_generateBall(indentationLevel, element->ball);
			break;
		case SPECIAL_ELEMENT_TYPE:
			_generateSpecial(indentationLevel, element->special);
			break;
		case TOURNAMENT_ELEMENT_TYPE:
			_generateTournament(indentationLevel, element->tournament);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", element->type);
			break;
	}
}


static void _generateTrophy(const unsigned int indentationLevel, Trophy * trophy) {
	_generateCard(indentationLevel, trophy->photo->url, trophy->name);
}

static void _generateBadge(const unsigned int indentationLevel, Badge * badge) {
	fprintf(f, "%s<div class=\"card\" style=\"width: 18rem;\">\n", _indentation(indentationLevel));
	_printURL(indentationLevel + 1, badge->photo->url);
	char * name = badge->name;
	if (name != NULL) {
		fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));	
		fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), name);
		fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));
	}
	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generateBall(const unsigned int indentationLevel, Ball * ball) {
	_generateCard(indentationLevel, ball->photo->url, ball->name);
}

static void _generateSpecial(const unsigned int indentationLevel, Special * special) {
	_generateCard(indentationLevel, special->photo->url, special->name);
}

char * _getPhotoFromStadium(Stadium * stadium) {
	if (stadium->stadiumDatas->type == SINGLE) {
		if (stadium->stadiumDatas->stadiumData->type == STADIUM_PHOTO) {
			return stadium->stadiumDatas->stadiumData->photo->url;
		}
	}
	StadiumDatas * stadiumDatas = stadium->stadiumDatas;
	while (stadiumDatas->leftStadiumData-> type != STADIUM_PHOTO) {
		stadiumDatas = stadiumDatas->stadiumDatas;
	}
	return stadiumDatas->leftStadiumData->type == STADIUM_PHOTO ? stadiumDatas->leftStadiumData->photo->url : "https://placehold.co/400?text=No%20player%20image";
}

typedef struct StadiumAttributes {
	boolean capacity;
	boolean photo;
} StadiumAttributes;

static void _checkValidStadium(StadiumAttributes * attributes, StadiumDatas * stadiumDatas) {
	// Same as player, but with photo and capacity

	StadiumData * stadiumData = stadiumDatas->type == SINGLE ? stadiumDatas->stadiumData : stadiumDatas->leftStadiumData;

	if (stadiumDatas->stadiumData->type == STADIUM_CAPACITY) {
		if (attributes->capacity) {
			logError(_logger, "The stadium has repeated attributes");
			exit(1);
		}
		attributes->capacity = true;
	} else if (stadiumDatas->stadiumData->type == STADIUM_PHOTO) {
		if (attributes->photo) {
			logError(_logger, "The stadium has repeated attributes");
			exit(1);
		}
		attributes->photo = true;
	} else {
		logError(_logger, "The specified element type is unknown: %d", stadiumDatas->stadiumData->type);
		exit(1);
	}

	if (stadiumDatas->type == MULTIPLE) {
		_checkValidStadium(attributes, stadiumDatas->stadiumDatas);
	}
}

static void _generateStadium(const unsigned int indentationLevel, Stadium * stadium) {
	fprintf(f, "%s<div class=\"card mb-4\" style=\"width: 18rem;\">\n", _indentation(indentationLevel));

	_printURL(indentationLevel + 1, _getPhotoFromStadium(stadium));

	fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), stadium->name);
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

	StadiumAttributes attributes = {0};
	_checkValidStadium(&attributes, stadium->stadiumDatas);
	_generateStadiumDatas(indentationLevel + 1, stadium->stadiumDatas);

	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generateStadiumDatas(const unsigned int indentationLevel, StadiumDatas * stadiumDatas) {

	switch(stadiumDatas->type) {
		case SINGLE:
			_generateStadiumData(indentationLevel, stadiumDatas->stadiumData);
			break;
		case MULTIPLE:
			_generateStadiumData(indentationLevel, stadiumDatas->leftStadiumData);
			_generateStadiumDatas(indentationLevel, stadiumDatas->stadiumDatas);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", stadiumDatas->type);
			break;
	}
}

static void _generateStadiumData(const unsigned int indentationLevel, StadiumData * stadiumData) {
	switch(stadiumData->type) {
		case STADIUM_CAPACITY:
			fprintf(f, "%s<ul class=\"list-group list-group-flush\">\n", _indentation(indentationLevel));
			fprintf(f, "%s<li class=\"list-group-item\">Capacidad: %d espectadores</li>\n", _indentation(indentationLevel + 1), stadiumData->capacity);
			fprintf(f, "%s</ul>\n", _indentation(indentationLevel));
			break;
		case STADIUM_PHOTO:
			// _printURL(indentationLevel, stadiumData->photo->url); // Done in generateStadium
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", stadiumData->type);
			break;
	}
}

char * _getPhotoFromPlayer(Player * player) {
	if (player->playerDatas->type == SINGLE) {
		if (player->playerDatas->playerData->type == PLAYER_TYPE_PHOTO) {
			return player->playerDatas->playerData->photo->url;
		}
	}
	PlayerDatas * playerDatas = player->playerDatas;
	while (playerDatas->leftPlayerData-> type != PLAYER_TYPE_PHOTO) {
		playerDatas = playerDatas->playerDatas;
	}
	return playerDatas->leftPlayerData->type == PLAYER_TYPE_PHOTO ? playerDatas->leftPlayerData->photo->url : "https://placehold.co/400?text=No%20player%20image";
}

/* static void _addPlayer(Player * player) {
	for (struct playerMap * current = playerMapHead; current != NULL; current = current->next) {
		if (strcmp(current->key, player->name) == 0) {
			return;
		}
	}
	struct playerMap * newPlayerMap = (struct playerMap*) malloc(sizeof(struct playerMap));
	newPlayerMap->key = player->name;
	newPlayerMap->player = player;
	newPlayerMap->next = playerMapHead;
	playerMapHead = newPlayerMap;
} */

typedef struct playerAttributes {
	boolean name;
	boolean country;
	boolean birthdate;
	boolean team;
	boolean height;
	boolean weight;
	boolean photo;
} PlayerAttributes;

// This function checks that there are not repeated atributes
static void _checkValidPlayer(PlayerAttributes * attributes, PlayerDatas * playerDatas) {
	PlayerData * playerData = playerDatas->type == SINGLE ? playerDatas->playerData : playerDatas->leftPlayerData;

	if (playerDatas->playerData->type == PLAYER_TYPE_STRING) {
		switch (playerDatas->playerData->playerTypeString->type) {
			case PLAYER_COUNTRY:
				if (attributes->country) {
					logError(_logger, "The player has repeated attributes");
					exit(1);
				}
				attributes->country = true;
				break;
			case PLAYER_BIRTHDATE:
				if (attributes->birthdate) {
					logError(_logger, "The player has repeated attributes");
					exit(1);
				}
				attributes->birthdate = true;
				break;
			case PLAYER_TEAM:
				if (attributes->team) {
					logError(_logger, "The player has repeated attributes");
					exit(1);
				}
				attributes->team = true;
				break;
			default:
				logError(_logger, "1) The specified element type is unknown: %d", playerDatas->playerData->playerTypeString->type);
				exit(1);
				break;
		}
	} else if (playerDatas->playerData->type == PLAYER_TYPE_FLOAT) {
		switch (playerDatas->playerData->playerTypeFloat->type) {
			case PLAYER_HEIGHT:
				if (attributes->height) {
					logError(_logger, "The player has repeated attributes");
					exit(1);
				}
				attributes->height = true;
				break;
			case PLAYER_WEIGHT:
				if (attributes->weight) {
					logError(_logger, "The player has repeated attributes");
					exit(1);
				}
				attributes->weight = true;
				break;
			default:
				logError(_logger, "2) The specified element type is unknown: %d", playerDatas->playerData->playerTypeFloat->type);
				exit(1);
				break;
		}
	} else if (playerDatas->playerData->type == PLAYER_TYPE_PHOTO) {
		if (attributes->photo) {
			logError(_logger, "The player has repeated attributes");
			exit(1);
		}
		attributes->photo = true;
	} else {
		logError(_logger, "3) The specified element type is unknown: %d", playerDatas->playerData->type);
		exit(1);
	}
	if (playerDatas->type == MULTIPLE) {
		_checkValidPlayer(attributes, playerDatas->playerDatas);
	}
}

static void _generatePlayer(const unsigned int indentationLevel, Player * player) {
	PlayerAttributes attributes = {0};
	_checkValidPlayer(&attributes, player->playerDatas);

	fprintf(f, "%s<div class=\"card\" style=\"width: 18rem;\">\n", _indentation(indentationLevel));
	_printURL(indentationLevel, _getPhotoFromPlayer(player));
	fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), player->name);
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<ul class=\"list-group list-group-flush\">\n", _indentation(indentationLevel + 1));

	_generatePlayerDatas(indentationLevel + 2, player->playerDatas);

	fprintf(f, "%s</ul>\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generatePlayerDatas(const unsigned int indentationLevel, PlayerDatas * playerDatas) {
switch (playerDatas->type) {
		case SINGLE:
			_generatePlayerData(indentationLevel, playerDatas->playerData);
			break;
		case MULTIPLE:
			_generatePlayerData(indentationLevel, playerDatas->leftPlayerData);
			_generatePlayerDatas(indentationLevel, playerDatas->playerDatas);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", playerDatas->type);
			break;
	}
}

static void _generatePlayerData (const unsigned int indentationLevel, PlayerData * playerData) {
	switch (playerData->type) {
		case PLAYER_TYPE_STRING:
			_generatePlayerTypeString(indentationLevel, playerData->playerTypeString, playerData->value);
			break;
		case PLAYER_TYPE_FLOAT:
			_generatePlayerTypeFloat(indentationLevel, playerData->playerTypeFloat, playerData->floatValue);
			break;
		case PLAYER_TYPE_PHOTO:
			// _printURL(indentationLevel, playerData->photo->url); // Already done in generatePlayer
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", playerData->type);
			break;
	}
}

static void _generatePlayerTypeString(const unsigned int indentationLevel, PlayerTypeString * playerTypeString, char * value) {
	switch (playerTypeString->type) {
		case PLAYER_COUNTRY:
			fprintf(f, "%s<li class=\"list-group-item\">Pais: %s</li>\n", _indentation(indentationLevel), value);
			break;
		case PLAYER_BIRTHDATE:
			fprintf(f, "%s<li class=\"list-group-item\">Nacimiento: %s</li>\n", _indentation(indentationLevel), value);
			break;
		case PLAYER_TEAM:
			fprintf(f, "%s<li class=\"list-group-item\">Equipo: %s</li>\n", _indentation(indentationLevel), value);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", playerTypeString->type);
			break;
	}
}

static void _generatePlayerTypeFloat(const unsigned int indentationLevel, PlayerTypeFloat * playerTypeFloat, float floatValue) {
	switch (playerTypeFloat->type) {
		case PLAYER_HEIGHT:
			fprintf(f, "%s<li class=\"list-group-item\">Altura: %.2fcm</li>\n", _indentation(indentationLevel), floatValue);
			break;
		case PLAYER_WEIGHT:
			fprintf(f, "%s<li class=\"list-group-item\">Peso: %.2fkg</li>\n", _indentation(indentationLevel), floatValue);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", playerTypeFloat->type);
			break;
	}
}

static void _addTeam(Team * team) {
	// agrego el equipo al mapa, me tengo que fijar si ya existe

	for (struct teamMap * current = teamMapHead; current != NULL; current = current->next) {
		if (strcmp(current->key, team->name) == 0) {
			return;
		}
	}

	struct teamMap * newTeamMap = (struct teamMap*) malloc(sizeof(struct teamMap));
	newTeamMap->key = team->name;
	newTeamMap->team = team;
	newTeamMap->next = teamMapHead;
	teamMapHead = newTeamMap;
}

static void _generateTeam(const unsigned int indentationLevel, Team * team) {
	fprintf(f, "%s<div class=\"card\">\n", _indentation(indentationLevel));
	fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), team->name);
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

	if (team->tTeams != NULL) {
		_addTeam(team);

		fprintf(f, "%s<div class=\"container text-center\">\n", _indentation(indentationLevel + 1));
		fprintf(f, "%s<div class=\"row row-cols-4 gap-4 pb-4\">\n", _indentation(indentationLevel + 2));

		_generateTTeams(indentationLevel + 1, team->tTeams);

		fprintf(f, "%s</div>\n", _indentation(indentationLevel + 2));
		fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));
	} else {
		logInformation(_logger, "The team %s has no tTeams. Searching in map", team->name);

		// Lo busco en la lista
		struct teamMap * current = teamMapHead;
		while (current != NULL) {
			if (strcmp(current->key, team->name) == 0) {
				logInformation(_logger, "The team %s was found in the team map", team->name);

				fprintf(f, "%s<div class=\"container text-center\">\n", _indentation(indentationLevel + 1));
				fprintf(f, "%s<div class=\"row row-cols-4 gap-4 pb-4\">\n", _indentation(indentationLevel + 2));

				_generateTTeams(indentationLevel + 1, current->team->tTeams);

				fprintf(f, "%s</div>\n", _indentation(indentationLevel + 2));
				fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

				break;
			}
			current = current->next;
		}
		if (current == NULL) {
			logError(_logger, "The team %s was not found in the team map", team->name);
		}
	}

	/* // imprimo los equipos y jugadores
	for (struct teamMap * current = teamMapHead; current != NULL; current = current->next) {
		_generateTeam(indentationLevel + 1, current->team);
	}
	fprintf(f, "%s<div class=\"container text-center\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<div class=\"row row-cols-4\">\n", _indentation(indentationLevel + 2));

	for (struct playerMap * current = playerMapHead; current != NULL; current = current->next) {
		fprintf(f, "%s<div class=\"col\">\n", _indentation(indentationLevel + 3));
		_generatePlayer(indentationLevel + 4, current->player);
		fprintf(f, "%s</div>\n", _indentation(indentationLevel + 3));
	}

	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 2));
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1)); */

	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generateTTeams(const unsigned int indentationLevel, TTeams * tTeams) {
	switch (tTeams->type) {
		case SINGLE:
			_generateTTeam(indentationLevel, tTeams->tTeam);
			break;
		case MULTIPLE:
			_generateTTeam(indentationLevel, tTeams->leftTTeam);
			_generateTTeams(indentationLevel, tTeams->tTeams);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", tTeams->type);
			break;
	}
}

static void _generateTTeam(const unsigned int indentationLevel, TTeam * tTeam) {
	switch (tTeam->type) {
		case BADGE_TTEAM_TYPE:
			_generateBadge(indentationLevel, tTeam->badge);
			break;
		case LINEUP_TTEAM_TYPE:
			_generateLineup(indentationLevel, tTeam->lineup);
			break;
		case HOMEKIT_TTEAM_TYPE:
			_generateHomeKit(indentationLevel, tTeam->homeKit);
			break;
		case PLAYER_TTEAM_TYPE:
			// _addPlayer(tTeam->player);
			_generatePlayer(indentationLevel, tTeam->player);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", tTeam->type);
			break;
	}
}

static void _generateLineup(const unsigned int indentationLevel, Lineup * lineup) {
	_generateCard(indentationLevel, lineup->photo->url, lineup->name);
}

static void _generateHomeKit(const unsigned int indentationLevel, HomeKit * homeKit) {
	_generateCard(indentationLevel, homeKit->photo->url, homeKit->name);
}

static void _generateTournament(const unsigned int indentationLevel, Tournament * tournament) {
	fprintf(f, "%s<div class=\"card\">\n", _indentation(indentationLevel));
	fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), tournament->name);
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

	fprintf(f, "%s<div class=\"container text-center\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<div class=\"row row-cols-4 gap-4 pb-4\">\n", _indentation(indentationLevel + 2));

	_generateTElementsExtras(indentationLevel + 1, tournament->tElements);

	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 2));
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

	_generateTElements(indentationLevel + 1, tournament->tElements);

	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generateTElementsExtras(const unsigned int indentationLevel, TElements * tElements) {
	switch (tElements->type) {
		case SINGLE:
			_generateTElementExtra(indentationLevel, tElements->tElement);
			break;
		case MULTIPLE:
			_generateTElementExtra(indentationLevel, tElements->leftTElement);
			_generateTElementsExtras(indentationLevel, tElements->tElements);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", tElements->type);
			break;
	}
}

static void _generateTElementExtra(const unsigned int indentationLevel, TElement * tElement) {
	switch (tElement->type) {
		case TROPHY_TELEMENT_TYPE:
			_generateTrophy(indentationLevel, tElement->trophy);
			break;
		case TEAM_TELEMENT_TYPE:
			// _generateTeam(indentationLevel, tElement->team);
			break;
		case GROUP_TELEMENT_TYPE:
			// _generateGroup(indentationLevel, tElement->group);
			break;
		case STADIUM_TELEMENT_TYPE:
			_generateStadium(indentationLevel, tElement->stadium);
			break;
		case BALL_TELEMENT_TYPE:
			_generateBall(indentationLevel, tElement->ball);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", tElement->type);
			break;
	}
}

static void _generateTElements(const unsigned int indentationLevel, TElements * tElements) {
	switch (tElements->type) {
		case SINGLE:
			_generateTElement(indentationLevel, tElements->tElement);
			break;
		case MULTIPLE:
			_generateTElement(indentationLevel, tElements->leftTElement);
			_generateTElements(indentationLevel, tElements->tElements);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", tElements->type);
			break;
	}
}

static void _generateTElement(const unsigned int indentationLevel, TElement * tElement) {
	switch (tElement->type) {
		case TROPHY_TELEMENT_TYPE:
			// _generateTrophy(indentationLevel, tElement->trophy);
			break;
		case TEAM_TELEMENT_TYPE:
			_generateTeam(indentationLevel, tElement->team);
			break;
		case GROUP_TELEMENT_TYPE:
			_generateGroup(indentationLevel, tElement->group);
			break;
		case STADIUM_TELEMENT_TYPE:
			// _generateStadium(indentationLevel, tElement->stadium);
			break;
		case BALL_TELEMENT_TYPE:
			// _generateBall(indentationLevel, tElement->ball);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", tElement->type);
			break;
	}
}

static void _generateGroup(const unsigned int indentationLevel, Group * group) {
	fprintf(f, "%s<div class=\"card\">\n", _indentation(indentationLevel));
	fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));
	fprintf(f, "%s<h5 class=\"card-title\">Grupo %s</h5>\n", _indentation(indentationLevel + 2), group->name);
	fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));

	_generateTeams(indentationLevel + 1, group->teams);

	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}

static void _generateTeams(const unsigned int indentationLevel, Teams * teams) {
	switch (teams->type) {
		case SINGLE:
			_generateTeam(indentationLevel, teams->team);
			break;
		case MULTIPLE:
			_generateTeam(indentationLevel, teams->leftTeam);
			_generateTeams(indentationLevel, teams->teams);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", teams->type);
			break;
	}
}

static void _printURL(const unsigned int indentationLevel, char * url) {
	/*
	si url es null imprimir una default
	*/
	logDebugging(_logger, "Printing URL");
	fprintf(f, "%s<img src=\"%s\" class=\"card-img-top\" style=\"width: 16rem; height: 21rem; margin: 1rem auto 0rem auto;\">\n", _indentation(indentationLevel), url ? url : "https://placehold.co/400?text=No%20image");
	logDebugging(_logger, "Ended Printing URL");
	return;
}

//Ball, Badge, Trophy, Special, Homekit, Lineup
static void _generateCard(const unsigned int indentationLevel, char * url, char * name) {
	fprintf(f, "%s<div class=\"card mb-4\" style=\"width: 18rem;\">\n", _indentation(indentationLevel));
	_printURL(indentationLevel + 1, url);
	if (name != NULL) {
		fprintf(f, "%s<div class=\"card-body\">\n", _indentation(indentationLevel + 1));	
		fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", _indentation(indentationLevel + 2), name);
		fprintf(f, "%s</div>\n", _indentation(indentationLevel + 1));
	}
	fprintf(f, "%s</div>\n", _indentation(indentationLevel));
}