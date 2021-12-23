/**
 * CS1010 Semester 1 AY21/22
 * Assignment 7: Peak
 *
 * @file: peak.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
/**
 * this function updates the left & right pointers according to where
 * the peak may be located at. it first checks the right side of the array
 * and will only check the left side if there is a decrement on the right
 * or when the array has been exhausted. 
 *
 * @param[in] mid the mid point of the array
 * @param[in] array the array with the elevation data
 * @param[in, out] left which points to the memory address of the left bound of the array
 * @param[in, out] right which points to the memory address of the right bound of the array
 */
void check(long mid, long* array, long *left, long *right) {

  for(long i = mid + 1; i < *right; i += 1) {
    if(array[i] < array[mid]) {
      break;
    } 
    if(array[i] > array[mid]) {
      *left = i - 1;
      return;
    }
  }

  *right = mid;

  for(long j = mid - 1; j > *left; j -= 1) {
    if(array[j] < array[mid]) {
      break;
    } 
    if(array[j] > array[mid]) {
      *right = j + 1;
      return;
    }
  }
  *left = mid;
}
/**
 * this function takes in the array of elevation data and the index of the
 * last element. it returns the position of a peak if it exists or -1 if 
 * no peak exists
 *
 * @pre last >= 2
 *
 * @param[in] last the index of the last element
 * @param[in] array the elevation data
 * 
 * @return long value of the index of the peak or -1 if no peak
 */
long search(size_t last, long* array) {
  
  long left = 0;
  long right = (long) last;

  while(left <= (right - 2)) {
    long mid = (left + right) / 2;
    if(array[mid] > array[mid - 1] && array[mid] > array[mid + 1]) {
      return mid;
    }
    check(mid, array, &left, &right);
  }
  return -1;
}

int main()
{
  size_t n = cs1010_read_size_t();
  long* elevation = cs1010_read_long_array(n);
  if(elevation == NULL) {
    cs1010_print_string("memory allocation error");
    return -1;
  }
  
  long pos = search(n - 1, elevation);

  if(pos > 0) {
    cs1010_print_long(pos);
  } else {
    cs1010_print_string("no peak");
  }

  free(elevation);
}
