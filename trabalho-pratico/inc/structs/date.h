#ifndef _DATE_H_
#define _DATE_H_

typedef struct _DATE_{
    short date[3];
    void* key;
    char type;
}Date;

Date * createDate(short* date, void* key, char type);
void destroyDate(Date * date);

#endif
