#ifndef __QUICKSORT_H__
#define __QUICKSORT_H__

#include "uobject.h"

void SwapEntries(int pos1, int pos2, ANEWentry *tab);
int Quicksort_2(ANEWentry *tab, int bottom, int top, int middle);
void Quicksort(ANEWentry *tab, int bottom, int top);
void SortQuicksort(ANEWentry *tab, int size);

#endif
