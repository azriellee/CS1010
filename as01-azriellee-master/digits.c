/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of its digits to the standard output.
 *
 * @file: digits.c
 * @author: Azriel Lee (Group E09)
 */

#include "cs1010.h"
#include <math.h>
long sum_of_digits(long integer){
  if(integer==0){
    return 0;
  }
  return integer%10 + sum_of_digits(integer/10);
}

int main()
{
  long integer = cs1010_read_long();
  cs1010_print_long(sum_of_digits(integer));
}
