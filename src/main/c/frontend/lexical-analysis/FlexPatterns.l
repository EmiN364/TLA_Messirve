%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

%x MULTILINE_COMMENT
%x ONELINE_COMMENT
%x STRING
%x NAME

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

/**
 * "//"        						{ BEGIN(ONELINE_COMMENT); BeginSingleLineCommentLexemeAction(createLexicalAnalyzerContext()); }
 * <ONELINE_COMMENT>"\n"				{ EndSingleLineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
 * <ONELINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
 * <ONELINE_COMMENT>[^\n]+     		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
 * <ONELINE_COMMENT>.				    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }
 */

digit     [[:digit:]]
integer   {digit}+
float     {integer}\.{integer}
alnum     [[:alnum:]]
space     [[:space:]]
string    {alnum}({alnum}|{space}|\.\/)*{alnum}
date      {digit}{digit}\/{digit}{digit}\/{digit}{digit}{digit}{digit}
url       http(s)?:\/\/[[:alnum:]\/](\.png|\.jpg|\.jpeg)

%%

{url}                                 { return URLLexemeAction(createLexicalAnalyzerContext()); }

"//".*                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"player"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"tournament"                        { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"stadium"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"badge"                             { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"trophy"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"country"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"team"                              { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"group"                             { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"lineup"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"homekit"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"ball"                              { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }
"special"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); BEGIN(NAME); }

"{"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }

<STRING>";"                         { BEGIN(INITIAL); return SemiColonLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return ColonLexemeAction(createLexicalAnalyzerContext()); BEGIN(STRING); }
","                                 { return CommaLexemeAction(createLexicalAnalyzerContext()); }

"Country"                           { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Birthdate"                         { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Team"                              { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Height"                            { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Weight"                            { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Photo"                             { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Capacity"                          { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Name"                              { return AttributeLexemeAction(createLexicalAnalyzerContext()); }
"Brand"                             { return AttributeLexemeAction(createLexicalAnalyzerContext()); }

<STRING>{float}                     { return FloatLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{integer}       		    { return IntegerLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{date}                      { return DateLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{string}                    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<NAME>{string}                      { return StringLexemeAction(createLexicalAnalyzerContext()); }
<NAME>"{"                           { BEGIN(INITIAL); return BraceLexemeAction(createLexicalAnalyzerContext()); }
<NAME>[[:space:]]+                 { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
