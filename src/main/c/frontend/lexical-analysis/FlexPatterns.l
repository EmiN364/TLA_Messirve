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
string    {alnum}(({alnum}|{space}|\.)*{alnum})?
date      {digit}?{digit}\/{digit}?{digit}\/{digit}{digit}{digit}{digit}
url       https?:\/\/[[:alnum:][:punct:]]*\.(jpg|png|jpeg|gif|svg)

%%


<*>"//".*                            { IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"player"                            {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"tournament"                        {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"stadium"                           {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"badge"                             {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"trophy"                            {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"country"                           {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"team"                              {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"group"                             {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"lineup"                            {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"homekit"                           {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"ball"                              {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }
"special"                           {  BEGIN(NAME); return KeywordLexemeAction(createLexicalAnalyzerContext()); }

"{"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }
"}"                                 { return BraceLexemeAction(createLexicalAnalyzerContext()); }

<STRING>";"                         { BEGIN(INITIAL); return SemiColonLexemeAction(createLexicalAnalyzerContext()); }
";"                                 { return SemiColonLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { BEGIN(STRING); return ColonLexemeAction(createLexicalAnalyzerContext()); }
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

<STRING>{url}                       { return URLLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{date}                      { return DateLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{float}                     { return FloatLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{integer}       		    { return IntegerLexemeAction(createLexicalAnalyzerContext()); }
<STRING>{string}                    { return StringLexemeAction(createLexicalAnalyzerContext()); }

<NAME>{string}                      { BEGIN(INITIAL); return StringLexemeAction(createLexicalAnalyzerContext()); }
<NAME>"{"                           { BEGIN(INITIAL); return BraceLexemeAction(createLexicalAnalyzerContext()); }
<NAME>[[:space:]]+					{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
