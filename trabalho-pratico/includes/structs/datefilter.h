#ifndef _DATEFILTER_H_
#define _DATEFILTER_H_

typedef struct _DATE_FILTER_ DateFilter;
typedef short Date;

DateFilter * createDateFilter(Date date, void* key, char type);
void destroyDateFilter(DateFilter * filter);
void filter_Date(Date dest, DateFilter * filter);
void * filter_Key(DateFilter * filter);
char filter_Type(DateFilter * filter);

#endif
