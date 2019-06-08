%{
%}
%union {
    int i;
    char* s;
    char* colour:
}
%token BGI SUBT VSORC ASORC ISORC
%token<colour> BGCOLOUR
%token<s> STR
%token<i> TIME
%%
Presentation: '%' TIME '%' Intro '%' Elements '%' Outro '%'
            ;

Elements: Element
       | Elements Element
       ;

Element: STR Media ';' /* filename */
       | STR Normal ';' /* filename */
       ;

Intro: BGI STR STR SUBT STR STR /* img title subtitle authors */
     | BGI STR STR STR /* img title authors*/
     | BGI BGCOLOUR STR SUBT STR STR /* title subtitle authors */
     | BGI BGCOLOUR STR STR /* title  authors */
     | BGI STR STR SUBT STR STR Image /* img title subtitle authors*/
     | BGI STR STR STR Image /* img title authors */
     | BGI BGCOLOUR STR SUBT STR STR Image /* title subtitle authors */
     | BGI BGCOLOUR STR STR Image /* title authors */
     ;

Outro: Points STR Points
     | Points Points STR
     | Points STR
     | Points
     ;

Points: Point
      | Points Point
      ;

Point: '~' STR
     ;

Media: Video
     | Audio
     | Image
     ;

Video: '(' VSORC STR ')'
     ;

Audio: '(' ASORC STR ')'
     ;

Image: '(' ISORC STR ')'
     ;

Normal: STR STR /* title */
      | STR Media
      | STR Points
%%

#include "lex.yy.c"

void yyerror(char* s) {
    printf("%s", s);
}

int main() {
    yyparse();
    return 0;
}
