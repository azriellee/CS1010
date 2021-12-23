/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Suffix
 *
 * Read in a number and prints out the number with the appropriate suffix.
 *
 * @file: suffix.c
 * @author: Azriel Lee (Group E09)
 */
#include "cs1010.h"
void print_with_suffix(long num){
  cs1010_print_long(num);
  if(num%10==1 && num%100!=11){
    cs1010_println_string("st");
  } else if(num%10==2 && num%100!=12){
    cs1010_println_string("nd");
  } else if(num%10==3 && num%100!=13){
    cs1010_println_string("rd");
  } else{ 
    cs1010_println_string("th");
  }
}
int main() 
{
  long num = cs1010_read_long();
  print_with_suffix(num);
}
