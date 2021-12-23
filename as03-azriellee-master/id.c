/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: ID
 *
 * @file: id.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
long get_remainder(long id){

  long sum = 0;

  while(id > 0) {
    sum += (id % 10);
    id /= 10;
  }
  
  return sum % 13;
}


int main()
{
  long id = cs1010_read_long();
  char code[13] = {'Y', 'X', 'W', 'U', 'R', 'N', 'M', 'L',
    'J', 'H', 'E', 'A', 'B'};

  long remainder = get_remainder(id);
  putchar(code[remainder]);
}
