/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Prime
 *
 * Reads in an integer n from standard input and print 
 * the smallest prime larger or equal to n.
 *
 * @file: prime.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime(long num){
  
  for(long i = 2;i <= sqrt(num);i += 1){
    if(num % i == 0){
      return false;
    }
  }
  return true;
}

long next_prime(long number){

  long num = number;
  while(!is_prime(num)){
    num += 1;
  }
  return num;
}

int main()
{
  long input = cs1010_read_long();
  cs1010_print_long(next_prime(input));

}
