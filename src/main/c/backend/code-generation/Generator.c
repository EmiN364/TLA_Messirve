#include "Generator.h"
#include <string.h>

FILE * f;

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
static void _generateStadium(const unsigned int indentationLevel, Stadium * stadium);
static void _generateBadge(const unsigned int indentationLevel, Badge * badge);
static void _generatePlayer(const unsigned int indentationLevel, Player * player);
static void _generateBall(const unsigned int indentationLevel, Ball * ball);
static void _generateSpecial(const unsigned int indentationLevel, Special * special);
static void _generateTournament(const unsigned int indentationLevel, Tournament * tournament);
static char * _indentation(const unsigned int indentationLevel);

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
	fprintf(f, "%s<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n", _indentation(3));
	fprintf(f, "%s<link href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\">\n", _indentation(3));
	fprintf(f, "%s<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js\"></script>\n", _indentation(3));
	fprintf(f, "%s</head>\n", _indentation(2));
	fprintf(f, "%s<body>\n", _indentation(2));
}

/**
 * Generates the output of the program.
 */
static void _generateProgram(Program * program) {
	_generateElements(3, program->elements);
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
	fprintf(f, "%s<div class=\"card\" style=\"width: 18rem;\">\n", indentation(' ', indentationLevel, 4));
	switch (elements->type) {
		case SINGLE:
			_generateElement(1 + indentationLevel, elements->element);
			break;
		case MULTIPLE:
			_generateElement(1 + indentationLevel, elements->leftElement);
			_generateElements(1 + indentationLevel, elements->elements);
			break;
		default:
			logError(_logger, "The specified elements type is unknown: %d", elements->type);
			break;
	}
	fprintf(f, "%s</div>\n", indentation(' ', indentationLevel, 4));
}

/**
 * Generates the output of an element.
 */
static void _generateElement(const unsigned int indentationLevel, Element * element) {
	switch (element->type) {
		case TROPHY_ELEMENT_TYPE:
			_generateTrophy(1 + indentationLevel, element->trophy);
			break;
		case TEAM_ELEMENT_TYPE:
			//_generateTeam(1 + indentationLevel, element->team);
			break;
		case STADIUM_ELEMENT_TYPE:
			//_generateStadium(1 + indentationLevel, element->stadium);
			break;
		case BADGE_ELEMENT_TYPE:
			//_generateBadge(1 + indentationLevel, element->badge);
			break;
		case PLAYER_ELEMENT_TYPE:
			//_generatePlayer(1 + indentationLevel, element->player);
			break;
		case BALL_ELEMENT_TYPE:
			//_generateBall(1 + indentationLevel, element->ball);
			break;
		case SPECIAL_ELEMENT_TYPE:
			//_generateSpecial(1 + indentationLevel, element->special);
			break;
		case TOURNAMENT_ELEMENT_TYPE:
			//_generateTournament(1 + indentationLevel, element->tournament);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", element->type);
			break;
	}
}

static void _generateTrophy(const unsigned int indentationLevel, Trophy * trophy){
	//fprintf(f, "%s<img src=\"%s\" class=\"card-img-top\">\n", indentation(' ', indentationLevel, 4), trophy->photo->url);
	fprintf(f, "%s<div class=\"card-body\">\n", indentation(' ', indentationLevel, 4));
	fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", indentation(' ', indentationLevel+1, 4), trophy->name);
	fprintf(f, "%s</div>\n", indentation(' ', indentationLevel, 4));
}

static void _generateTeam(const unsigned int indentationLevel, Team * team){
	//fprintf(f, "%s<img src=\"%s\" style=\"margin-left:%dpx\" class=\"card-img-top\">\n", indentation(' ', indentationLevel, 4), trophy->photo->url, indentationLevel*20);
	//fprintf(f, "%s<div class=\"card-body\">\n", indentation(' ', indentationLevel, 4));
	//fprintf(f, "%s<h5 class=\"card-title\">%s</h5>\n", indentation(' ', indentationLevel, 4), trophy->name);
}

/**
 * Ejemplo de la salida generada:
 */
/*
<!-- Ball, Badge, Trophy, Special -->
<head>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://getbootstrap.com/docs/5.2/assets/css/docs.css" rel="stylesheet">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js"></script>

</head>
<body>
    <div class="row">
        <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://i.pinimg.com/736x/b5/e1/d4/b5e1d4ad4df90b85586a351d7bd39159.jpg" class="card-img-top" alt="...">
                <div class="card-body">
                <h5 class="card-title">Argentina</h5>
                </div>
            </div>
        </div>
        <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://www.lavoz.com.ar/resizer/U3Ia_Y1YqUPbDwmtG-XQawJ5Yu4=/0x0:0x0/980x640/filters:quality(80):format(webp)/cloudfront-us-east-1.images.arcpublishing.com/grupoclarin/IZEFTQH7LFAZRCUHJCREERY5C4.jpg" class="card-img-top" alt="...">
            </div>
        </div>
        <div class="col">
           <h1>Argentina</h1>
        </div>
    </div>
    <div class="container text-center">
        <div class="row row-cols-4">
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>  
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
        <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
          <div class="col">
            <div class="card" style="width: 18rem;">
                <img src="https://fmdataba.com/images/p/1165.png" class="card-img-top" alt="...">
                <div class="card-body">
                  <h5 class="card-title">Lionel Messi</h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Pais: Argentina</li>
                  <li class="list-group-item">Nacimiento: 24/06/1987</li>
                  <li class="list-group-item">Equipo: Inter Miami CF</li>
                  <li class="list-group-item">Altura: 1.69</li>
                  <li class="list-group-item">Peso: 67kg</li>
                </ul>
            </div>
          </div>
        </div>
      </div>
</body>
*/