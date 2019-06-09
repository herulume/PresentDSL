%option noyywrap
%option noinput nounput
%{
#include "y.tab.h"
%}

%%
[>*()%~IMN\[\]] { return yytext[0]; }

SUBT  { return SUBT; }
VSORC { return VSORC; }
ASORC { return ASORC; }
ISORC { return ISORC; }

\'[^']*\' {
    yylval.s = strdup(yytext);
    return STR;
}

[0-9]+ {
    yylval.i = atof(yytext);
    return TIME;
}


.|\n    { ; }

%%
