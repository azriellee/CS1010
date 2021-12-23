/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Inversion
 *
 * @file: inversion.c
 * @author: Azriel (Group E09)
 */

#include "cs1010.h"
/**
 * this function takes in a the index of the last element of an array and the array
 * in consideration. it assumes that the first k elements are increasing order & the 
 * remaining n-k elements are in decreasing order, and no elements are equal.
 *
 * the function will calculate the number of inverted pairs whenever a front element
 * is larger than the back element. Since every element in between the front and back 
 * element will be larger than the back element, the number of inverted pairs can be
 * calculated in constant time.
 *
 * @pre array is strictly increasing up til k elements and strictly decreasing thereafter
 *
 * @param[in] last_pos the index of the alst element of the array
 * @param[in] array the array of long given by user input
 *
 * @return returns the number of pairs of inversions within the array
 */
long inversion(size_t last_pos, long *array) {
  
  long front = 0;
  long back = (long) last_pos;
  long inversions = 0;

  if(last_pos == 0) {
    return inversions;
  }

  while(front < back) {
    if(array[front] > array[back]) {
      inversions += (back - front);
      back -= 1;
    } else {
      front += 1;
    }
  }
  return inversions;
}

int main()
{
  size_t n = cs1010_read_size_t();
  long* array = cs1010_read_long_array(n);
  if(array == NULL) {
    cs1010_print_string("memory allocation error");
    return -1;
  }
  
  cs1010_print_long(inversion(n - 1, array));

  free(array);
}
