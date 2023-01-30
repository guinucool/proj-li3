#ifndef _DATEFILTER_H_
#define _DATEFILTER_H_

#define MONTHS 12
#define DAYS 31

// Estrutura
typedef struct _DATE_MAP_ *DateMap;

// Tratamentos
DateMap createDateMap(short year);
void updateDateMap(DateMap map, short day, short month, void * element);
void destroyDateMap(DateMap map, void (*)(void*));
void debugPrintDateMap(DateMap map, void (*)(void*));
void * dateMapGet(DateMap map, short day, short month);
void dateMap(DateMap map, void (*)(void*));
void dateFilter(DateMap map, Date up, Date down, void (*)(void*));
short datemap_year(DateMap map);

#endif
