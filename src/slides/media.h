#ifndef _MEDIA_H_
#define _MEDIA_H_

#include <stdlib.h>
#include <stdio.h>

#include "../utils/utils.h"

enum Media_Type {Video, Audio, Image};

typedef struct {
    enum Media_Type type;
    char* src;
}Media;

void free_media(Media m) {
    free(m.src);
}

char* image_html(Media m) {
    char* html;
    asprintf(&html, "<img src=\"%s\" />", clean(m.src));
    return html;
}

char* audio_html(Media m) {
    char* html;
    asprintf(&html, "<audio controls src=\"%s\" />", clean(m.src));
    return html;
}

char* video_html(Media m) {
    char* html;
    asprintf(&html, "<video width=\"500\" height=\"500\" src=\"%s\" controls />", clean(m.src));
    return html;
}

char* media_html(Media m) {
    if(m.type == Video) return video_html(m);
    if(m.type == Audio) return audio_html(m);
    else return image_html(m);
}

#endif
