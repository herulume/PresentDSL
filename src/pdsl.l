%option noyywrap

%%
";" return ";";
"(" return "(";
")" return ")";
"%" return "%";
"~" return "~";

BGI return BGI;
SUBT return SUBT;
VSORC return VSORC;
ASORC return ASORC;
ISORC return ISORC;

(red|blue|white) {
    yyval.colour = strdup(yytext);
    return BGCOLOUR;
}

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
