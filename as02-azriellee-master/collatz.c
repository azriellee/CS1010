/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Collatz 
 *
 * Read in a positive integer n from the standard input,
 * then, for each number k between number 1 .. n, transform
 * it into 1 based on the steps below:
 * - if k is even, k = k/2
 * - else, k = 3k + 1
 * Find the number k that requires the most number of steps
 * between 1 and n, and print both k and the number of steps
 * to standard output. If there are multiple numbers with
 * the same number of steps, we prefer to output the smaller
 * among these numbers.
 *
 * @file: collatz.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <math.h>

long total_stopping_time(long num){

  long stopping_time = 0;
  while(num > 1){
    if(num % 2 == 0){
      num /= 2;
    } else{ 
      num = (num * 3) + 1;
    }
    stopping_time += 1;
  }
   return stopping_time;
}

void largest_num(long input){

  long max_num = 1;
  long max_stopping_time = 0;

  for(long i = 1;i <= input;i += 1){
    long cur_stopping_time = total_stopping_time(i);
    if(cur_stopping_time > max_stopping_time){
      max_num = i;
      max_stopping_time = cur_stopping_time;
    }
  }
  cs1010_println_long(max_num);
  cs1010_print_long(max_stopping_time);
}

int main() 
{
  long input = cs1010_read_long();
  largest_num(input);

}
