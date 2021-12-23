/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Padovan
 *
 * @file: padovan.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
void print_padovan(long padovan[150], long n) {
  if(n > 2) {
    for(long i = 3; i <= n; i += 1) {
      long pad_num = (padovan[i-2] + padovan[i-3]);
      padovan[i] = pad_num;
    }
  }
  for(long j = n; j >= 0; j -= 1) {
    cs1010_println_long(padovan[j]);
  }
}

int main()
{
  long n = cs1010_read_long();
  long padovan[150] = {1,0,0};
  print_padovan(padovan,n);
}
