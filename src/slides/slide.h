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

void free_slide_normal(Slide* s){
    if(s->file) free(s->file);
    if(s->slide.intro.title) free(s->slide.intro.title);
    if(s->slide.intro.subtitle) free(s->slide.intro.subtitle);
    if(s->slide.intro.authors) free(s->slide.intro.authors);

    free(s);
}


#endif
