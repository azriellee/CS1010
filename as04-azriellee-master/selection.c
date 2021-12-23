/**
 * CS1010 Semester 1 AY21/22
 * Assignment 4: SelectionSort
 *
 * @file: selection.c
 * @author: Azriel (Group E09)
 */

#include "cs1010.h"
void print_list(long length, long list[1000]) {
  for(long i = 0; i < length - 1; i += 1) {
    cs1010_print_long(list[i]);
    cs1010_print_string(" ");
  }
  cs1010_println_long(list[length - 1]);
}

void output_list(long n, long list[1000]) {
  
  for(long i = n-1; i >= 1; i -= 1) {

    long max = list[i];
    long pos = i;
    long og_num = list[i];

    for(long j = i-1; j >= 0; j -= 1) {
      if(list[j] > max) {
        max = list[j];
        pos = j;
      }
    }
    
    list[i] = max;
    list[pos] = og_num;
    print_list(n,list);
  }
  
}

int main() 
{
  long n = cs1010_read_long();
  long list[1000];
  for(int i = 0; i < n; i += 1) {
    list[i] = cs1010_read_long();
  }
  output_list(n,list);
}
