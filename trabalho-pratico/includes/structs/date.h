#ifndef _DATE_H_
#define _DATE_H_

typedef struct _DATE_ Date;

Date * createDate(short* date, void* key, char type);
void destroyDate(Date * date);
void date_Date(short * dest, Date * date);
void * date_Key(Date * date);
char date_Type(Date * date);

#endif
