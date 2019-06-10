#ifndef _NOMAL_H_
#define _NOMAL_H_

#include "media.h"
#include "../utils/utils.h"

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

void free_normal(Normal n) {
    free(n.title);
    if(n.type == Text_T) free(n.content.text);
    if(n.type == Media_T) free_media(n.content.media);
    if(n.type == Points_T) free(n.content.points);
}

char* normal_text_html(Normal n) {
    char* html;
    char* token;
    char* rest = clean(n.content.text);
    char* html0;
    asprintf(&html0, "%s", "<div align=\"center\" style=\"position:absolute;top:50\%;left:50\%;margin-right:-50\%;transform:translate(-50\%,-50\%) \"><p style=\"font-size: 30px \">\n");

    token = strtok_r(rest, "\n", &rest);
    if(!token) {
        html = concat(3, html0, clean(n.content.text), "</p></div>");
        free(html0);
        return html;
    }

    while (token) {
        html = concat(2, html0, token);
        free(html0);
        asprintf(&html0, "%s</p><p style=\"font-size: 30px \">", html);
        token = strtok_r(rest, "\n", &rest);
        if (!token) asprintf(&html0, "%s</p>\n", html);
    }
    asprintf(&html, "%s</div>", html0);
    free(html0);

    return html;
}

char* normal_points_html(Normal n) {
    char* html;
    char* token;
    char* rest = n.content.points;
    char* html0;
    asprintf(&html0, "%s", "<div style=\"text-align:center;\"><ul style=\"display:inline-table;\">\n");

    token = strtok_r(rest, "\n", &rest);
    if(!token) {
        html = concat(3, html0, n.content.points, "</ul></div>");
        free(html0);
        return html;
    }

    while (token) {
        html = concat(4, html0,"<li style=\"font-size: 30px \">", token, "</li>\n");
        free(html0);
        asprintf(&html0, "%s", html);
        token = strtok_r(rest, "\n", &rest);
    }
    asprintf(&html, "%s</ul></div>", html0);
    free(html0);

    return html;
}

char* normal_html(Normal n) {
    char* html0;
    char* html1;
    char* html;


    asprintf(&html1, "<div align=\"center\"><h1>%s</h1></div><hr/>\n", clean(n.title));

    if(n.type == Text_T) html0 = normal_text_html(n);
    else if(n.type == Media_T) html0 = media_html(n.content.media);
    else html0 = normal_points_html(n);

    html = concat(2, html1, html0);
    free(html0);
    free(html1);

    return html;
}

#endif
