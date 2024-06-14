#include "Generator.h"

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

// static const char _expressionTypeToCharacter(const ExpressionType type);
// static void _generateConstant(const unsigned int indentationLevel, Constant * constant);
// static void _generateExpression(const unsigned int indentationLevel, Expression * expression);
// static void _generateFactor(const unsigned int indentationLevel, Factor * factor);

static void _generateEpilogue(const int value);
static void _generateProgram(Program * program);
static void _generatePrologue(void);
static void _generateElements(const unsigned int indentationLevel, Elements * elements);
static void _generateElement(const unsigned int indentationLevel, Element * element);
static char * _indentation(const unsigned int indentationLevel);
// static void _output(const unsigned int indentationLevel, const char * const format, ...);

/**
 * Converts and expression type to the proper character of the operation
 * involved, or returns '\0' if that's not possible.
 */
/* static const char _expressionTypeToCharacter(const ExpressionType type) {
	switch (type) {
		case ADDITION: return '+';
		case DIVISION: return '/';
		case MULTIPLICATION: return '*';
		case SUBTRACTION: return '-';
		default:
			logError(_logger, "The specified expression type cannot be converted into character: %d", type);
			return '\0';
	}
} */

/**
 * Generates the output of a constant.
 */
/* static void _generateConstant(const unsigned int indentationLevel, Constant * constant) {
	_output(indentationLevel, "%s", "[ $C$, circle, draw, black!20\n");
	_output(1 + indentationLevel, "%s%d%s", "[ $", constant->value, "$, circle, draw ]\n");
	_output(indentationLevel, "%s", "]\n");
} */

/**
 * Generates the output of a factor.
 */
/* static void _generateFactor(const unsigned int indentationLevel, Factor * factor) {
	_output(indentationLevel, "%s", "[ $F$, circle, draw, black!20\n");
	switch (factor->type) {
		case CONSTANT:
			_generateConstant(1 + indentationLevel, factor->constant);
			break;
		case EXPRESSION:
			_output(1 + indentationLevel, "%s", "[ $($, circle, draw, purple ]\n");
			_generateExpression(1 + indentationLevel, factor->expression);
			_output(1 + indentationLevel, "%s", "[ $)$, circle, draw, purple ]\n");
			break;
		default:
			logError(_logger, "The specified factor type is unknown: %d", factor->type);
			break;
	}
	_output(indentationLevel, "%s", "]\n");
} */

/**
 * Outputs a formatted string to standard output.
 */
/*static void _output(const unsigned int indentationLevel, const char * const format, ...) {
	va_list arguments;
	va_start(arguments, format);
	char * indentation = _indentation(indentationLevel);
	char * effectiveFormat = concatenate(2, indentation, format);
	vfprintf(stdout, effectiveFormat, arguments);
	free(effectiveFormat);
	free(indentation);
	va_end(arguments);
}*/

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
	// genero el archivo html en donde voy a imprimir las figuritas
	f = fopen("Output.html", "w");
	_generatePrologue();
	_generateProgram(compilerState->abstractSyntaxtTree);
	_generateEpilogue(compilerState->value);
	fclose(f);
	logDebugging(_logger, "Generation is done.");
}

/**
 * Creates the prologue of the generated output, a Latex document that renders
 * a tree thanks to the Forest package.
 *
 * @see https://ctan.dcc.uchile.cl/graphics/pgf/contrib/forest/forest-doc.pdf
 */
static void _generatePrologue(void) {
	/*
	_output(0, "%s",
		"\\<!DOCTYPE html>\n"
		"\\<html>\n"
		"\\<head>\n"
		"\\<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n"
		"\\<link href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\">\n"
		"\\<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js\"></script>\n"
		"\\</head>\n"
		"\\<body>\n"
	);
	*/
	fprintf(f, "<!DOCTYPE html>\n");
	fprintf(f, "<html>\n");
	fprintf(f, "<head>\n");
	fprintf(f, "<title>Figuritas</title>\n");
	fprintf(f, "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n");
	fprintf(f, "<link href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\">\n");
	fprintf(f, "<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js\"></script>\n");
	fprintf(f, "</head>\n");
	fprintf(f, "<body>\n");
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
static void _generateEpilogue(const int value) {
	/*_output(0, "%s",
		"\\</body>\n"
		"\\</html>\n"
	);*/
	fprintf(f, "</body>\n");
	fprintf(f, "</html>\n");
}

/**
 * Generates the output of an expression.
 */
/* static void _generateExpression(const unsigned int indentationLevel, Expression * expression) {
	_output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
	switch (expression->type) {
		case ADDITION:
		case DIVISION:
		case MULTIPLICATION:
		case SUBTRACTION:
			_generateExpression(1 + indentationLevel, expression->leftExpression);
			_output(1 + indentationLevel, "%s%c%s", "[ $", _expressionTypeToCharacter(expression->type), "$, circle, draw, purple ]\n");
			_generateExpression(1 + indentationLevel, expression->rightExpression);
			break;
		case FACTOR:
			_generateFactor(1 + indentationLevel, expression->factor);
			break;
		default:
			logError(_logger, "The specified expression type is unknown: %d", expression->type);
			break;
	}
	_output(indentationLevel, "%s", "]\n");
}
 */
/**
 * Generates the output of the elements.
 */
static void _generateElements(const unsigned int indentationLevel, Elements * elements) {
	//_output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
	fprintf(f, "<div class=\"card\" style=\"width: 18rem;\">\n");
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
	//_output(indentationLevel, "%s", "]\n");
}

/**
 * Generates the output of an element.
 */
static void _generateElement(const unsigned int indentationLevel, Element * element) {
	// _output(indentationLevel, "%s", "[ $E$, circle, draw, black!20\n");
	switch (element->type) {
		case TROPHY_ELEMENT_TYPE: // Prev. EXPRESSION
			// _generateTrophy(1 + indentationLevel, element->trophy);
			break;
		case TEAM_ELEMENT_TYPE:
			// _generateTeam(1 + indentationLevel, element->team);
			break;
		case STADIUM_ELEMENT_TYPE:
			// _generateStadium(1 + indentationLevel, element->stadium);
			break;
		case BADGE_ELEMENT_TYPE:
			// _generateBadge(1 + indentationLevel, element->badge);
			break;
		case PLAYER_ELEMENT_TYPE:
			// _generatePlayer(1 + indentationLevel, element->player);
			break;
		case BALL_ELEMENT_TYPE:
			// _generateBall(1 + indentationLevel, element->ball);
			break;
		case SPECIAL_ELEMENT_TYPE:
			// _generateSpecial(1 + indentationLevel, element->special);
			break;
		case TOURNAMENT_ELEMENT_TYPE:
			// _generateTournament(1 + indentationLevel, element->tournament);
			break;
		default:
			logError(_logger, "The specified element type is unknown: %d", element->type);
			break;
	}
	// _output(indentationLevel, "%s", "]\n");
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
    <div class="card" style="width: 18rem;">
        <img src="https://s.rfi.fr/media/display/797a3f40-12b1-11ea-ad06-005056a99247/w:1280/p:1x1/ballon-adidas-jabulani-2.jpg" class="card-img-top" alt="...">
        <div class="card-body">
          <h5 class="card-title">Jabulani</h5>
        </div>
    </div>
</body>
*/