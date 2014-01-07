#include "uobject.h"




void SwapEntries(int pos1, int pos2, ANEWentry *tab) {
  ANEWentry temp;
  temp=tab[pos1];
  tab[pos1]=tab[pos2];
  tab[pos2]=temp;
}




int Quicksort_2(ANEWentry *tab, int bottom, int top, int middle) {
  int i,temp=bottom;
  SwapEntries(middle,top,tab); // reference element gets moved to the end
  for (i=bottom;i<top;++i) if (tab[i].entry<=tab[top].entry) {
      SwapEntries(i,temp,tab);
      temp++;
    }
  SwapEntries(top,temp,tab); // reference element gets moved to the proper place in this iteration
  return temp;  
}




void Quicksort(ANEWentry *tab, int bottom, int top) {
  int temp,middle;
  if (bottom<top) {
    middle=bottom+(top-bottom)/2;
    temp=Quicksort_2(tab,bottom,top,middle);
    Quicksort(tab,bottom,temp-1);
    Quicksort(tab,temp+1,top);
  }
}




void SortQuicksort(ANEWentry *tab, int size) {
  int bottom=0,top=size-1;
  Quicksort(tab,bottom,top);  
}
