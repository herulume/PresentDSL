#ifndef _NOMAL_H_
#define _NOMAL_H_

#include "media.h"

enum Type {Text_T, Media_T, Points_T};

union Content_Type {
    char* text;
    Media media;
    char* points;
};

typedef struct {
    char* title;
    enum Type type;
    union Content_Type content;
}Normal;

#endif
