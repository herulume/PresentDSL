%{
int yylex();
void yyerror(const char *s);
%}
%union {
    int i;
    char* s;
}
%token SUBT VSORC ASORC ISORC
%token<s> STR
%token<i> TIME
%%
Presentation: '%' TIME '%' Elements '%'
            ;

Elements: Element
        | Elements Element
        ;

Element: '[' STR Media ']' /* filename */
       | '[' STR Normal ']'
       | '[' STR Intro ']'
       ;

Intro: 'I' STR SUBT STR STR '*' /* title subtitle authors */
     | 'I' STR STR '*' /* title authors */
     | 'I' STR SUBT STR '*' /* title subtitle */
     ;

Points: Point
      | Points Point
      ;

Point: '~' STR
     ;

Media: 'M' Video '>'
     | 'M' Audio '>'
     | 'M' Image '>'
     ;

Video: '(' VSORC STR ')'
     ;

Audio: '(' ASORC STR ')'
     ;

Image: '(' ISORC STR ')'
     ;

Normal: 'N' STR '>' /* title */
      | 'N' STR Media '>'
      | 'N' STR Points '>'
%%

#include "lex.yy.c"

void yyerror(const char* s) {
    printf("%s", s);
}

int main() {
    yyparse();
    return 0;
}
