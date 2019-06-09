#ifndef _MEDIA_H_
#define _MEDIA_H_

enum Media_Type {Video, Audio, Image};

typedef struct {
    enum Media_Type type;
    char* src;
}Media;

#endif
