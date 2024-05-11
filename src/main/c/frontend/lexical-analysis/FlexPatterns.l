%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

%x MULTILINE_COMMENT
%x ONELINE_COMMENT

/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

%%

integer [[:digit:]]+
float integer"."integer
string ([[:alnum:][:space:][:punct:]])+
date digitdigit/digitdigit/digitdigitdigitdigit
url "http(s)?://"string"(.png|.jpg|.jpeg)"

url                                 { return URLLexemeAction(createLexicalAnalyzerContext()); }

"//".*                              { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"//"        						{ BEGIN(ONELINE_COMMENT); BeginSingleLineCommentLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>"\n"				{ EndSingleLineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<ONELINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>[^\n]+     		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<ONELINE_COMMENT>.				    { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"player"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"tournament"                        { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"stadium"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"badge"                             { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"trophy"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"country"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"team"                              { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"group"                             { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"lineup"                            { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"homekit"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"ball"                              { return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"special"                           { return KeywordLexemeAction(createLexicalAnalyzerContext()); }

"{"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }

";"                                 { return SemicolonLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return SemicolonLexemeAction(createLexicalAnalyzerContext()); }
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

string                              { return StringLexemeAction(createLexicalAnalyzerContext()); }
float                               { return FloatLexemeAction(createLexicalAnalyzerContext()); }
date                                { return DateLexemeAction(createLexicalAnalyzerContext()); }
integer       						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
