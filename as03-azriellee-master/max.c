/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"

long max(const long list[], long start, long end)
{
  if(start >= end) {
    return list[end]; 
  }
  long rem_list = max(list, start + 1, end);
  if(list[start] > rem_list) {
    return list[start];
  }
  return rem_list;
}

int main()
{
  long n = cs1010_read_long();
  long list[n];

  for(long i = 0; i < n; i += 1) {
    list[i] = cs1010_read_long();
  }

  long first_half = max(list, 0, (n/2) - 1);
  long second_half = max(list, n/2, n-1);
  long max = first_half > second_half ? first_half : second_half;
  cs1010_print_long(max);
}
