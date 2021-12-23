/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Social
 *
 * @file: social.c
 * @author: Azriel (Group E09)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
/**
 * this function creates a 2D dynamically allocated jagged array by taking in 
 * the number of rows of the array
 * 
 * @param[in] num_of_rows the number of rows in the array
 * @return returns a 2D jagged array
 *
 */
char **create_array(size_t num_of_rows) {

  char **contacts;
  contacts = calloc(num_of_rows, sizeof(char *));
  if(contacts == NULL) {
    cs1010_println_string("unable to allocate array");
    return NULL;
  }
  for (size_t row = 0; row < num_of_rows; row += 1) {
    contacts[row] = cs1010_read_word();
    if (contacts[row] == NULL) {
      cs1010_println_string("unable to allocate array");
      for (size_t j = 0; j < row; j += 1) {
        free(contacts[j]);
      }
      free(contacts);
      return NULL;
    }
  }
  return contacts;
}
/**
 * this function takes in a 2D jagged array and its number of rows.
 * it copies each row of the 2D array and outputs the array.
 *
 * @param[in] array the 2D jagged array passed in
 * @param[in] n the number of rows in the array
 * @return returns an array with the same contents as the array passed in
 *
 */
char **copy(char **array, size_t n) {
  
  char **output;
  output = calloc(n, sizeof(char *));
  if(output == NULL) {
    cs1010_println_string("unable to allocate memory");
    free(output);
    return NULL;
  }
  for (size_t row = 0; row < n; row += 1) {
    output[row] = calloc(row + 2, sizeof(char));
    if (output[row] == NULL) {
      cs1010_println_string("unable to allocate array");
      for (size_t j = 0; j < row; j += 1) {
        free(output[j]);
      }
      free(output);
      return NULL;
    }
    memcpy(output[row], array[row], row + 2);
  }
  return output;
}
/**
 * this function checks whether there is a direct connection between 2 nodes in the original array
 * and returns true or false accordingly. it disregards a connection if the two nodes were both
 * not connected in the initial_array
 *
 * @param[in] n the number of rows in array
 * @param[in] row the row of the array in consideration
 * @param[in] col the col of the row in the array 
 * @param[in] array the array we are considering
 * @param[in] initial_array the initial_state of the array before updating
 * @return returns a boolean value
 *
 */
bool connected(size_t n, long row, long col, char **array, char **initial_array) {

  for(long r = (long) n - 1; r >= col; r -= 1) {
    if(r > row) {
      if(array[r][row] == '1' && array[r][col] == '1' && 
          (initial_array[r][row] == '1' || initial_array[r][col] == '1')) {
        return true;
      }
    } else if (r < row) {
      if(array[r][col] == '1') {
        if(col < r) {
          if(array[r][r] == '1' && array[row][r] == '1' && 
              (initial_array[r][r] == '1' || initial_array[row][r] == '1')) {
            return true;
          }
        } else {
          for(long i =  0; i < col; i += 1) {
            if(array[r][i] == '1' && array[row][i] == '1' && 
                (initial_array[r][i] == '1' || initial_array[row][i] == '1')) {
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}
/**
 * this function traverses through all the '0's in array, and updates to 1 if there is a connection. The function
 * then recurses with the updated array as input
 *  
 * @param[in] n the number of rows in the array
 * @param[in] order the degree of seperation 
 * @param[in] array the array we compare with
 * @param[in] copied_array copy of array and the array we update to
 * @param[in] initial the initial state of the array
 *
 * @return returns the final state of array after "order" degrees of seperation
 *
 */
char **seperation(size_t n, size_t order, char **array, char **copied_array, char **initial) {
  
  if(order == 1) {
    return array;
  }
  
  for(long row = (long) n - 1; row >= 0; row -= 1) {
    for(long col = 0; col <= row; col += 1) {
      if(array[row][col] == '1') {
        copied_array[row][col] = '1';
      } else if(connected(n, row, col, array, initial)) {
        copied_array[row][col] = '1';
      }
    }
  }
  return seperation(n, order - 1, copied_array, array, initial);
}

int main()
{
  size_t n = cs1010_read_size_t();
  size_t order = cs1010_read_size_t();
  char **array = create_array(n);
  char **copied_array = copy(array, n);
  char **initial = copy(array, n);
  char **sep_array = seperation(n, order, array, copied_array, initial);

  for(size_t r = 0; r < n; r += 1) {
    cs1010_println_string(sep_array[r]);
  }

  for(size_t row = 0; row < n; row += 1) {
    free(array[row]);
    free(copied_array[row]);
    free(initial[row]);
  }
  free(array);
  free(copied_array);
  free(initial);
}
