#ifndef _DATE_H_
#define _DATE_H_

typedef struct _DATE_ {
    int day, month, year;
} Date;

Date createDate(int, int, int);
int calculateAge(Date, Date);

#endif