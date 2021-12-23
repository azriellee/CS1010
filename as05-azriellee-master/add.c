/**
 * CS1010 Semester 1 AY21/22
 * Assignment 5: Add
 *
 * @file: add.c
 * @author: Azriel (Group E09)
 */

#include "cs1010.h"
#include <stdbool.h>
/**
 *  This function takes in a list of characters num, and adds the value of each digit in num
 *  to their respective place in the array "list". This function can be used to add multiple 
 *  numbers into the same list, to find the sum of the numbers
 *
 *  param[in,out] list storing the sum of the all the digits in their respective places
 *  param[in] num the string of numbers to add each digit in the number into the list
 *  param[in] len_num the length of the string of numbers
 *  param[in] len_list the length of the list to store the sum of the digits
 */
void populate_array(long *list, char* num, size_t len_num, size_t len_list) {

  size_t cur_pos = 0;

  for(long i = (long) len_num - 1; i >= 0; i -= 1) {
    long value = num[i] - 48;
    list[cur_pos] += value;

    if(list[cur_pos] >= 10) {
      list[cur_pos] -= 10;
      list[cur_pos + 1] += 1;

      /**
       * if any digit in the array "list" >= 10, add 1 to the following position, 
       * then decrement the current value by 10. continue this loop if the subsequent
       * values are also >= 10 
       */

      size_t next = 1;
      while(list[cur_pos + next] + 1 >= 10 && (cur_pos + next) < len_list) {
        list[cur_pos + next] -= 10;
        list[cur_pos + next + 1] += 1;
        next += 1;
      }
    }
    cur_pos += 1;
  }

}
/**
 *  this function prints the finalised digits in the list as a string of characters 
 *  it ignores the first character if the first character is '0'.
 *  
 *  param[in] list storing the sum of digits in their respective places 
 *  param[in] longer the length of the list storing the sum of digits
 */
void print_list(long *list, size_t longer) {

  long cur_pos = 0;
  
  for(long i = (long) longer - 1; i >= 0; i -= 1) {
    char digit = (char) (list[i]  + 48);
      
    if(digit == '0' && i == (long) (longer - 1)) {
      continue;
    }
    putchar(digit);
    cur_pos += 1;
  }

}
/**
 *  this function takes in 2 numbers as a string, creates an array = length or longer string + 1
 *  the digits of each string are added into the array and are the printed out
 *
 *  param[in] num1 the string containing the first number
 *  param[in] num2 the string containing the second number
 *
 */
void add(char* num1, char* num2) {

  size_t len_num1 = strlen(num1);
  size_t len_num2 = strlen(num2);
  size_t longer = (len_num1 > len_num2) ? len_num1 : len_num2;
  long *list = calloc(longer + 1, sizeof(long));

  populate_array(list, num1, len_num1, longer + 1);
  populate_array(list, num2, len_num2, longer + 1);

  print_list(list, longer + 1);

  free(list);
}
/**
 *  Main function takes in 2 inputs from user as a string and calls the add function
 *  that adds both numbers together as if they are long values
 *
 *  @pre input for num1 & num2 only contains digit char
 *
 */
int main()
{ 
  char* num1 = cs1010_read_word();
  char* num2 = cs1010_read_word();

  add(num1, num2);

  free(num1);
  free(num2);

}
