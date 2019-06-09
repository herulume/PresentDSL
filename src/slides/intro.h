#ifndef _INTRO_H_
#define _INTRO_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/utils.h"

typedef struct {
    char* title;
    char* subtitle;
    char* authors;
}Intro;

void free_intro(Intro i) {
    free(i.title);
    if(i.subtitle) free(i.subtitle);
    if(i.authors) free(i.authors);
}

char* intro_html(Intro i) {
    char* html;
    char* html0;
    char* html1;
    char* html2;

    asprintf(&html0, "<div align=\"center\"><h1>%s</h1></div><hr/>\n", clean(i.title));

    if(i.subtitle && !i.authors) {
        asprintf(&html1, "<div align=\"right\"><h2>%s</h2></div><hr/>", clean(i.subtitle));
        html = concat(2, html0, html1);
        free(html0);
        free(html1);
    }

    if(i.authors && !i.subtitle) {
        asprintf(&html2, "<div align=\"left\"><h4>%s</h4></div><hr/>", clean(i.authors));
        html = concat(2, html0, html2);
        free(html0);
        free(html2);
    }

    if(i.authors && i.subtitle) {
        asprintf(&html1, "<div align=\"right\"><h2>%s</h2></div><hr/>", clean(i.subtitle));
        asprintf(&html2, "<div align=\"left\"><h4>%s</h4></div><hr/>", clean(i.authors));
        html = concat(3, html0, html1, html2);
        free(html0);
        free(html1);
        free(html2);
    }

    if(!i.authors && !i.subtitle) {
        html = concat(1, html0);
        free(html0);
    }

    return html;
}
#endif
