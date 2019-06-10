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

    if(!i.authors && !i.subtitle) {
        asprintf(&html0, "<div align=\"center\" style=\"position:absolute;top:50%%;left:50%%;margin-right:-50%%;transform:translate(-50%%,-50%%) \" ><h1>%s</h1><hr/></div>\n", clean(i.title));
        html = concat(1, html0);
        free(html0);
        return html;
    } else {
        asprintf(&html0, "<div align=\"center\"><hr/><h1>%s</h1></div><hr/>\n", clean(i.title));
    }

    if(i.subtitle && !i.authors) {
        asprintf(&html1, "<div align=\"center\" style=\"position:absolute;top:50%%;left:50%%;margin-right:-50%%;transform:translate(-50%%,-50%%) \" ><h2>%s</h2></div>", clean(i.subtitle));
        html = concat(2, html0, html1);
        free(html0);
        free(html1);
        return html;
    }

    if(i.authors && !i.subtitle) {
        asprintf(&html2, "<div align=\"left\" style=\"position:absolute; bottom:0; width:100%% height:60px; \"><h4>%s</h4></div>", clean(i.authors));
        html = concat(2, html0, html2);
        free(html0);
        free(html2);
        return html;
    }

    if(i.authors && i.subtitle) {
        asprintf(&html1, "<div align=\"center\" style=\"position:absolute;top:50%%;left:50%%;margin-right:-50%%;transform:translate(-50%%,-50%%) \" ><h2>%s</h2></div>", clean(i.subtitle));
        asprintf(&html2, "<div align=\"left\" style=\"position:absolute; bottom:0; width:100%% height:60px; \"><h4>%s</h4></div>", clean(i.authors));
        html = concat(3, html0, html1, html2);
        free(html0);
        free(html1);
        free(html2);
        return html;
    }
    return NULL;
}
#endif
