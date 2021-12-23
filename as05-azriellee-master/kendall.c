/*
 * CS1010 Semester 1 AY21/22
 * Assignment 5: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance. 
 *
 * @file: kendall.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
/**
 * This function takes in the size of a list and returns the number
 * of possible pairings between each element in the list without repeats.
 * 
 *  @pre num_of_items > 0
 *  @param[in] num_of_items the number of items in the list
 *  @return Returns the number of possible non-repeating pairs in the list
 */
long get_pairs(size_t num_of_items) {
  
  long pairs = 0;

  for(size_t i = num_of_items - 1; i > 0; i -= 1) {
    
    pairs += i;

  }
  
  return pairs;
}
/**
 * The function first finds the number of wrong pairs within the list.
 * A wrong pair is when a number is further down the list compared to another number yet is smaller.
 * 
 * The function then calculates the kendall ratio by dividing the number of wrong
 * pairs to the total number of pairs in the list.
 *
 * @pre num_of_items > 0, num_of_pairs > 0
 * @param[in] numbers the list of numbers 
 * @param[in] num_of_items the size of the list
 * @param[in] num_of_pairs the total number of possible pairs in the list
 *
 * @return returns a double that siginifies the ratio between number of wrong pairs
 * & total number of possible pairs
 */
double kendall(long *numbers, size_t num_of_items, long num_of_pairs) {

  long wrong = 0;

  for(size_t i = 0; i < num_of_items - 1; i += 1) {

    long cur_num = numbers[i];

    for(size_t j = i + 1; j < num_of_items; j += 1) {
      long sub_num = numbers[j];
      if(sub_num < cur_num) {
        wrong += 1;

      }
    }
  }

  double kend = (wrong * 1.0) / num_of_pairs;
  return kend;
}
/**
 * Takes in a user input for the size of the list and populates the list based
 * on the user's input. 
 *
 * -1 is returned if there is a memory allocation error. The memory is freed at
 * at the end of the code by calling free()
 *
 * the main function calls upon other functions to calculate the kendall ratio,
 * and prints out the corresponding double value.
 *
 */
int main()
{
  size_t num_of_items = cs1010_read_size_t();
  long *numbers;
  numbers = cs1010_read_long_array(num_of_items);

  if(numbers == NULL) {
    cs1010_println_string("list not initialised!");
    return -1;
  }
  
  long num_of_pairs = get_pairs(num_of_items);
  cs1010_println_double(kendall(numbers, num_of_items, num_of_pairs));  

  free(numbers);
}
