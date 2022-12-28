#ifndef _DATE_H_
#define _DATE_H_

typedef struct _DATE_FILTER_ DateFilter;

DateFilter * createDateFilter(short* date, void* key, char type);
void destroyDateFilter(DateFilter * filter);
void filter_Date(short * dest, DateFilter * filter);
void * filter_Key(DateFilter * filter);
char filter_Type(DateFilter * filter);

#endif
