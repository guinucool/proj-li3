#ifndef _PAGE_H_
#define _PAGE_H_

#define MAX_LINE 200

void page(List list, void (*printer)(void*,void*,int*,FILE*), int pos, int N, void * second);

#endif