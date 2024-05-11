#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void BeginSingleLineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndSingleLineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token BraceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '{': token = OPEN_BRACE; break;
		case '}': token = CLOSE_BRACE; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

Token KeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "player") == 0) {
		token = PLAYER;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "tournament") == 0) {
		token = TOURNAMENT;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "stadium") == 0) {
		token = STADIUM;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "badge") == 0) {
		token = BADGE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "trophy") == 0) {
		token = TROPHY;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "team") == 0) {
		token = TEAM;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "group") == 0) {
		token = GROUP;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "lineup") == 0) {
		token = LINEUP;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "homekit") == 0) {
		token = HOMEKIT;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "ball") == 0) {
		token = BALL;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "special") == 0) {
		token = SPECIAL;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token SemiColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return SEMICOLON;
}

Token ColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return COLON;
}

Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return COMMA;
}

Token URLLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return URL;
}

Token AttributeLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	if (strcmp(lexicalAnalyzerContext->lexeme, "Country") == 0) {
		token = iCOUNTRY;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Birthdate") == 0) {
		token = iBIRTHDATE;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Team") == 0) {
		token = iTEAM;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Height") == 0) {
		token = iHEIGHT;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Weight") == 0) {
		token = iWEIGHT;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Photo") == 0) {
		token = iPHOTO;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Capacity") == 0) {
		token = iCAPACITY;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Name") == 0) {
		token = iNAME;
	} else if (strcmp(lexicalAnalyzerContext->lexeme, "Brand") == 0) {
		token = iBRAND;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token StringLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
	return STRING;
}

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

Token FloatLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->floatNumber = atof(lexicalAnalyzerContext->lexeme);
	return FLOAT;
}

Token DateLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->string = strdup(lexicalAnalyzerContext->lexeme);
	return DATE;
}
