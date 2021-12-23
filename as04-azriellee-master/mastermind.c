/**
 * CS1010 Semester 1 AY21/22
 * Assignment 4: Mastermind
 *
 * @file: mastermind.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <stdbool.h>
long correct_digits(long master[4], long guess[4]) {

  long check_list[10] = {0};
  long num_digits = 0;

  for(long n = 0; n < 4; n += 1) {
    check_list[master[n]] += 1;
  }
  
  for(long j = 0; j < 4; j += 1) {
    if(check_list[guess[j]] != 0) {
      num_digits += 1;
      check_list[guess[j]] -= 1;
    }
  }

 return num_digits;
}

bool get_result(long master[4], long guess[4]) {
  
  long col = 0;
  long correct = 0;

  for(long i = 0; i < 4; i += 1) {
    if(master[i] == guess[i]){
      correct += 1;
    } 
  }
  
  col = correct_digits(master, guess) - correct;

  cs1010_print_long(correct);
  cs1010_print_string(" ");
  cs1010_println_long(col);

  if(correct == 4){
    return true;
  }
  return false;
}
int main()
{
  long master[4];
  bool is_correct = false;
  for(long i = 0; i < 4; i += 1) {
    master[i] = cs1010_read_long();
  }
  while(!is_correct) {
    long guess[4];
    for(long j = 0; j < 4; j += 1) {
      guess[j] = cs1010_read_long();
    }
    is_correct = get_result(master, guess);  
  }
}
