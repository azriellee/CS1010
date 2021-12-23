/**
 * CS1010 Semester 1 AY21/22
 * Assignment 5: CountingSort
 *
 * Read in a series of numbers between 0 and 10000 
 * and sort them using counting sort.
 *
 * @file: countingsort.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
/**
 * Takes in a list and prints out the number corresponding to the position of 
 * the list as many times as the value stored at that particular position
 *
 * param[in,out] checklist the list that contains the number of times to print
 * out each number
 * 
 * @post all the values in checklist will be equals to 0
 */
void print_sorted(long checklist[10001]) {

  for(long i = 0; i < 10001; i += 1) {
    while(checklist[i] > 0) {
      cs1010_println_long(i);
      checklist[i] -= 1;
    }
  }
}
/**
 * takes in 2 lists, checklist and numbers, and the size of the array "numbers"
 * each the position in checklist that corresponds to each element in numbers will
 * be incremented to note down the number of times each number occurs
 *
 * param[in,out] checklist to populate how many times each element occurs in 
 * "numbers" list
 * param[in] numbers the list of numbers to sort
 * param[in] size the size of the "numbers" list
 *
 */
void sort(long checklist[10001], long *numbers, size_t size) {

  for(size_t i = 0; i < size; i += 1) {
    long element = numbers[i];
    checklist[element] += 1;
  }
  print_sorted(checklist);
}
/**
 * Takes in user input for the size of the list and to populate the list "numbers"
 * 
 * -1 is returned if there is a memory allocation error. The memory is freed at
 *  the end of the code by calling free()
 *
 *  the main function initialises the "checklist" to size 10001 and sets every
 *  element to 0
 *
 */
int main()
{
  size_t size = cs1010_read_size_t();
  long *numbers;
  numbers = cs1010_read_long_array(size);
  if(numbers == NULL) {
    cs1010_println_string("array not initialised!");
    return -1;
  }
  
  long checklist[10001] = {0};
  sort(checklist, numbers, size);

  free(numbers);
}
