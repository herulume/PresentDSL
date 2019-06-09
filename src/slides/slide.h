#ifndef _SLIDE_H_
#define _SLIDE_H_

#include "media.h"
#include "normal.h"
#include "intro.h"
#include "outro.h"

enum Slide_Type {Media_S, Normal_S, Intro_S, Outro_S};

union slide {
    Media media;
    Normal normal;
    Intro intro;
    Outro outro;
};

typedef struct {
    enum Slide_Type type;
    union slide slide;
}Slide;

#endif
