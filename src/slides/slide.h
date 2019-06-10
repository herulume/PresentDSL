#ifndef _SLIDE_H_
#define _SLIDE_H_

#include <stdlib.h>

#include "media.h"
#include "normal.h"
#include "intro.h"

enum Slide_Type {Media_S, Normal_S, Intro_S};

union slide {
    Media media;
    Normal normal;
    Intro intro;
};

typedef struct {
    char* file;
    enum Slide_Type type;
    union slide slide;
}Slide;


Slide* malloc_slide_normal() {
    Slide* s = (Slide*)malloc(sizeof(Slide));
    s->type = Normal_S;
    s->slide.normal = (Normal) { };

    return s;
}

Slide* malloc_slide_media() {
    Slide* s = (Slide*)malloc(sizeof(Slide));
    s->type = Media_S;
    s->slide.media = (Media) { };

    return s;
}

Slide* malloc_slide_intro() {
    Slide* s = (Slide*)malloc(sizeof(Slide));
    s->type = Intro_S;
    s->slide.intro = (Intro) { };

    return s;
}

void free_slide(Slide* s) {
    if(s->type == Media_S)  free_media(s->slide.media);
    if(s->type == Normal_S) free_normal(s->slide.normal);
    if(s->type == Intro_S)  free_intro(s->slide.intro);

    free(s->file);
    free(s);
}

void slide_html(Slide* s, int time, char* next) {
    FILE *f;
    f = fopen(clean(s->file), "w");
    char time_s[12];
    sprintf(time_s, "%d", time);
    char* html;
    char* pre_time = "<!DOCTYPE html><html>\n<head>\n<meta charset=\"UTF-8\"/>\n<meta http-equiv=\"REFRESH\" content=\"";
    char* after_time = " ;URL=";
    char* after_next = " \">\n</head>\n<body>\n";
    char* end = "\n</body>\n</html>\n";
    char* body;

    if(s->type == Media_S)  body = media_html(s->slide.media);
    else if(s->type == Normal_S) body = normal_html(s->slide.normal);
    else body = intro_html(s->slide.intro);

    html = concat(7, pre_time, time_s, after_time, next, after_next, body, end);
    fprintf(f, "%s", html);
    fclose(f);
    free(html);
    free(body);
}

void slide_end_html(Slide* s, int time) {
    FILE *f;
    f = fopen(clean(s->file), "w");
    char time_s[12];
    sprintf(time_s, "%d", time);
    char* html;
    char* pre_time = "<html>\n<head>\n<meta charset=\"UTF-8\"/>\n";
    char* after_next = "</head>\n<body>\n";
    char* end = "\n</body>\n</html>\n";
    char* body;

    if(s->type == Media_S)  body = media_html(s->slide.media);
    else if(s->type == Normal_S) body = normal_html(s->slide.normal);
    else body = intro_html(s->slide.intro);

    html = concat(4, pre_time, after_next, body, end);
    fprintf(f, "%s", html);
    fclose(f);
    free(html);
    free(body);
}
#endif
