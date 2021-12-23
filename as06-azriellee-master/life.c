/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Life
 *
 * @file: life.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
/**
 * This function reads a 2D array and copies the content of the array
 *
 * @param[in] array the array to be copied
 * @param[in] num_of_rows the number of rows in the array
 * @param[in] col the number of columns in each row
 *
 * @retun Returns a 2D array that has the same contents of the array passed in
 *
 */
char **copy(char **array, size_t num_of_rows, size_t col) {

  char **output;
  output = calloc(num_of_rows, sizeof(char *));
  if(output == NULL) {
    cs1010_println_string("unable to allocate memory");
    free(output);
    return NULL;
  }
  for (size_t row = 0; row < num_of_rows; row += 1) {
    output[row] = calloc(col + 1, sizeof(char));
    if (output[row] == NULL) {
      cs1010_println_string("unable to allocate array");
      for (size_t j = 0; j < row; j += 1) {
        free(output[j]);
      }
      free(output);
      return NULL;
    }
    memcpy(output[row], array[row], col + 1);
  }
  return output;
}
/**
 * This function returns a character according to the neighbours surrounding the
 * particular position in the array
 *
 * @param[in] r the row in the array we are considering
 * @param[in] c the col within the row in consideration
 * @param[in] array
 *
 * @return returns a char variable depending on the number of live and dead cells
 * surrounding
 */
char update_char(size_t r, size_t c, char **array) {

  long live = 0;

  if(array[r+1][c] == '#') {
    live += 1;
  }
  if(array[r-1][c] == '#') {
    live += 1;
  }
  if(array[r][c+1] == '#') {
    live += 1;
  }
  if(array[r][c-1] == '#') {
    live += 1;
  }
  if(array[r+1][c+1] == '#') {
    live += 1;
  }
  if(array[r+1][c-1] == '#') {
    live += 1;
  }
  if(array[r-1][c+1] == '#') {
    live += 1;
  }
  if(array[r-1][c-1] == '#') {
    live += 1;
  }
  if(array[r][c] == '.' && live == 3) {
    return '#';
  } 
  if(array[r][c] == '#' && (live == 2 || live == 3) ) {
    return '#';
  }
  return '.';
}
/**
 * This function takes initially takes in 3 of the same arrays, and updates 2 of 
 * the arrays, initial and updated, based on the control_array. the function then
 * prints the updated array by rows, and recurses itself until iterations == 0.
 *
 * @pre iterations > 0
 *
 * @param[in] row the number of rows in the array
 * @param[in] col number of columns in each row
 * @param[in] iterations number of recursions
 * @param[in, out] initial_array the array to update and print
 * @param[in] updated_array copy of initial_array
 * @param[in] control_array copy of initial_array
 * 
 * 
 */
void print_animation(size_t row, size_t col, long iterations, char **initial_array,
    char **updated_array, char **control_array) {
    
    cs1010_clear_screen();

    for(size_t r = 1; r < row - 1; r += 1) {
      for(size_t c = 1; c < col - 1; c += 1) {
        updated_array[r][c] = initial_array[r][c];
      }
    }

    for(size_t r = 1; r < row - 1; r += 1) {
      for(size_t c = 1; c < col - 1; c += 1) {
        initial_array[r][c] = update_char(r, c, control_array);
        updated_array[r][c] = update_char(r, c, control_array);
      }
    }
    for(size_t i = 0; i < row; i += 1) {
      cs1010_println_string(initial_array[i]);
    }
    if(iterations == 1) {
      return;
    }
    
    usleep(250 * 1000);
    print_animation(row, col, iterations - 1, updated_array, control_array, initial_array);

}

int main()
{
    size_t row = cs1010_read_size_t();
    size_t col = cs1010_read_size_t();
    long iterations = cs1010_read_long();

    char **initial_array = cs1010_read_word_array(row);
    if (initial_array == NULL) {
      cs1010_print_string("memory allocation error!");
      return -1;
    }

    char **updated_array = copy(initial_array, row, col);
    char **control_array = copy(initial_array, row, col);

    print_animation(row, col, iterations, initial_array, updated_array, control_array);

    for(size_t i = 0; i < row; i += 1) {
      free(updated_array[i]);
      free(initial_array[i]);
    }
    free(initial_array);
    free(updated_array);
}
