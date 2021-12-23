/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Sort
 *
 * @file: sort.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
/**
 * this function takes in an array and the index of the last element. it declares 2 
 * vsriables to keep track of the front and back portions of the array and populates
 * an empty array in ascending order
 *
 * @param[in] last the index of the last element in the array
 * @param[in] array the array to sort
 *
 * @return returns an array with its elements sorted in ascending order
 */
long *sort(size_t last, long *array) {
  
  long front = 0;
  long back = (long) last;
  long *output = calloc(last + 1, sizeof(long));
  long pos = 0;

  while(front <= back) {
    if(array[front] < array[back]) {
      output[pos] = array[front];
      front += 1;
    } else {
      output[pos] = array[back];
      back -= 1;
    }
    pos += 1;
  }
  return output;
}

int main()
{
  size_t length = cs1010_read_size_t();
  long* array = cs1010_read_long_array(length);
  if(array == NULL) {
    cs1010_print_string("memory allocation error!");
    return -1;
  }
  
  long *sorted = sort(length - 1, array);
  for(long i = 0; i < (long) length; i += 1) {
    cs1010_print_long(sorted[i]);
    cs1010_print_string(" ");
  }

  free(array);
  free(sorted);
}
