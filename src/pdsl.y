%{
#include <string.h>
#include <stdio.h>

#include "src/slides/slide.h"
#include "src/darray/vector.h"

int yylex();
void yyerror(const char *s);

Slide** v = NULL; /* array of *Slide */
Slide*  s = NULL; /* tmp *Slide*/

int n_media = 0;
int n_intro = 0;
int n_total = 0;
%}
%union {
    int i;
    char* s;
    Media media;
    char* p;
}
%token SUBT VSORC ASORC ISORC
%token<s> STR
%token<p> POINT
%token<i> TIME
%type<p> Point Points
%type<media> Video Image Audio Media
%%

Presentation: '%' TIME '%' Elements '%' { if(v) {
                                            size_t i; size_t size = vector_size(v);
                                            for(i = 0; i < size; ++i) {
                                                if (i == size-1) slide_end_html(v[i], $2);
                                                else slide_html(v[i], $2, v[i+1]->file);
                                                free_slide(v[i]); v[i] = NULL;
                                            }
                                            vector_free(v); v = NULL;
                                          }
                                        }
            ;

Elements: Element { ++n_total; }
        | Elements Element { ++n_total; }
        ;

Element: '[' STR Media ']'  { s = malloc_slide_media(); s->slide.media = $3; s->file = strdup($2); vector_push_back(v, s); s = NULL; ++n_media; }
       | '[' STR Normal ']' { s->file = strdup($2); vector_push_back(v, s); s = NULL; }
       | '[' STR Intro ']'  { s->file = strdup($2); vector_push_back(v, s); s = NULL; ++n_intro; }
       ;

Intro: 'I' STR SUBT STR STR '*' { s = malloc_slide_intro(); s->slide.intro.title = strdup($2); s->slide.intro.subtitle = strdup($4); s->slide.intro.authors = strdup($5); }
     | 'I' STR STR '*'          { s = malloc_slide_intro(); s->slide.intro.title = strdup($2); s->slide.intro.authors = strdup($3); }
     | 'I' STR SUBT STR '*'     { s = malloc_slide_intro(); s->slide.intro.title = strdup($2); s->slide.intro.subtitle = strdup($4); }
     | 'I' STR '*'              { s = malloc_slide_intro(); s->slide.intro.title = strdup($2); }
     ;

Points: Point { asprintf(&$$, "%s\n", $1); }
      | Points Point { asprintf(&$$, "%s%s\n", $1, $2); }
      ;

Point: '~' POINT { $$ = $2; }
     ;

Media: 'M' Video '>' { $$ = $2; }
     | 'M' Audio '>' { $$ = $2; }
     | 'M' Image '>' { $$ = $2; }
     ;

Video: '(' VSORC STR ')' { $$ = (Media){ .type = Video, .src = strdup($3) }; }
     ;

Audio: '(' ASORC STR ')' { $$ = (Media){ .type = Audio, .src = strdup($3) }; }
     ;

Image: '(' ISORC STR ')' { $$ = (Media){ .type = Image, .src = strdup($3) }; }
     ;

Normal: 'N' STR STR '>'    { s = malloc_slide_normal(); s->slide.normal.title = strdup($2); s->slide.normal.type = Text_T; s->slide.normal.content.text = strdup($3); }
      | 'N' STR Media '>'  { s = malloc_slide_normal(); s->slide.normal.title = strdup($2); s->slide.normal.type = Media_T; s->slide.normal.content.media = $3;       }
      | 'N' STR Points '>' { s = malloc_slide_normal(); s->slide.normal.title = strdup($2); s->slide.normal.type = Points_T; s->slide.normal.content.points = strdup($3); }

%%

#include "lex.yy.c"

void yyerror(const char* s) {
    printf("%s", s);
}

int main() {
    yyparse();
    return 0;
}
