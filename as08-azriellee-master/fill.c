/**
 * @file: fill.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <stdbool.h>
/**
 *  this function creates a 3D array with "rows" number of rows and "col" number of
 *  columns. each element in the column will be a fixed sized list of 3 long values
 *
 *  @param[in] rows the number of rows of the array
 *  @param[in] col the number of columns within each row
 *  
 *  @return returns a 3D array of long values or NULL if there is a memory allocation
 *  error
 */
long ***create_array(size_t rows, size_t col) {

  long ***array;
  array = calloc(rows, sizeof(long **));
  if(array == NULL) {
    cs1010_print_string("mem allocation error!");
    return NULL;
  }

  for(size_t r = 0; r < rows; r += 1) {
    array[r] = calloc(col, sizeof(long *));
    if(array[r] == NULL) {
      cs1010_print_string("mem allocation error!");
      for(size_t j = 0; j < r; j += 1) {
        free(array[j]);
      }
      free(array);
      return NULL;
    }

    for(size_t c = 0; c < col; c += 1) {
      array[r][c] = cs1010_read_long_array(3);
      if(array[r][c] == NULL) {
        cs1010_print_string("mem allocation error!");
        return NULL;
      }
    }
  }
  return array;
}

void paint(long row, long col, long ***array, long *colour) {
  for(long i = 0; i < 3; i += 1) {
    array[row][col][i] = colour[i];
  }
}
/**
 *  this function compares an element within the array and checks if they have the
 *  same colour as the original element, by checking if all the numbers within 
 *  the element are the same.
 *
 *  @param[in] row the current row the element is in
 *  @param[in] col the current col of the element
 *  @param[in] array the 3D array 
 *  @param[in] cur_val the original element
 *  @param[in] num_of_rows the number of rows in the 3D array
 *  @param[in] num_of_col the number of columns within each row
 *
 *  @return returns true if they are the same colour else return false
 */
bool same_seg(long row, long col, long ***array, long *cur_val, 
    size_t num_of_rows, size_t num_of_col) {

  if(row < 0 || row >= (long) num_of_rows || col < 0 || col >= (long) num_of_col) {
    return false;
  }

  for(long i = 0; i < 3; i += 1) {
    if(array[row][col][i] != cur_val[i]) {
      return false;
    }
  }
  return true;
}
/**
 *  this function will recursively run through and update all the elements in 
 *  the same segment as the current element, by checking all adjacent elements
 *
 *  @param[in] row the current row the element is in
 *  @param[in] col the current col of the element
 *  @param[in, out] array the 3D array 
 *  @param[in] cur_val the original element
 *  @param[in] num_of_rows the number of rows in the 3D array
 *  @param[in] num_of_col the number of columns within each row
 *  @param[in] colour the value to update for each element in the segment
 *
 */
void fill_region(long row, long col, long *cur_val, size_t num_of_rows, 
    size_t num_of_col, long ***array, long *colour) {

  paint(row, col, array, colour);

  if(same_seg(row + 1, col, array, cur_val, num_of_rows, num_of_col)) {
    fill_region(row + 1, col, cur_val, num_of_rows, num_of_col, array, colour);
  }
  if(same_seg(row - 1, col, array, cur_val, num_of_rows, num_of_col)) {
    fill_region(row - 1, col, cur_val, num_of_rows, num_of_col, array, colour);
  }
  if(same_seg(row, col + 1, array, cur_val, num_of_rows, num_of_col)) {
    fill_region(row, col + 1, cur_val, num_of_rows, num_of_col, array, colour);
  }
  if(same_seg(row, col - 1, array, cur_val, num_of_rows, num_of_col)) {
    fill_region(row, col - 1, cur_val, num_of_rows, num_of_col, array, colour);
  }
}
/**
 *  this function gets user input on the current element to fill, and calls another
 *  function to fill the current element and all the elements in the same segment
 *
 *  @param[in] num_of_rows the number of rows in the array
 *  @param[in] num_of_col the number of col within each row
 *  @param[in, out] array the 3D array
 *
 */
void fill(size_t num_of_rows, size_t num_of_col, long ***array) {

  long row = cs1010_read_long();
  long col = cs1010_read_long();
  long cur_val[3];

  for(long ele = 0; ele < 3; ele += 1) {
    cur_val[ele] = array[row][col][ele];
  }

  long *colour = cs1010_read_long_array(3);
  if(colour == NULL) {
    cs1010_print_string("mem allocation error!");
    return;
  }

  fill_region(row, col, cur_val, num_of_rows, num_of_col, array, colour);

  free(colour);
}
/**
 *  this function prints each the colour of each element in the 3D array
 *  
 *  @param[in] i the current row in the array
 *  @param[in] j the current column within the row
 *  @param[in] array the 3D array
 */
void print_line(size_t i, size_t j, long ***array) {

  for(size_t k = 0; k < 3; k += 1) {
    if(k == 2) {
      cs1010_println_long(array[i][j][k]);
    } else {
      cs1010_print_long(array[i][j][k]);
      cs1010_print_string(" ");
    }
  }
}
/**
 *  this function prints each element of each column within each row in the 3D array
 *
 *  @param[in] num_of_rows the number of rows in the array
 *  @param[in] num_of_col the number of columns within each row
 *  @param[in] array the 3D array to print
 *
 */
void print_canvas(size_t num_of_rows, size_t num_of_col, long ***array) {

  cs1010_print_string("P3 ");
  cs1010_print_long((long) num_of_col);
  cs1010_print_string(" ");
  cs1010_print_long((long) num_of_rows);
  cs1010_print_string(" ");
  cs1010_println_long(255);

  for(size_t i = 0; i < num_of_rows; i += 1) {
    for(size_t j = 0; j < num_of_col; j += 1) {
      print_line(i, j, array);
    }
  }
}

int main() {

  size_t num_of_rows = cs1010_read_size_t();
  size_t num_of_col = cs1010_read_size_t();

  long ***array = create_array(num_of_rows, num_of_col);
  if(array == NULL) {
    cs1010_print_string("mem allocation error!");
    return -1;
  }

  size_t fill_operations = cs1010_read_size_t();

  for(size_t f = 0; f < fill_operations; f += 1) {
    fill(num_of_rows, num_of_col, array);
  }

  print_canvas(num_of_rows, num_of_col, array);

  for(size_t row = 0; row < num_of_rows; row += 1) {
    for(size_t col = 0; col < num_of_col; col += 1) {
      free(array[row][col]);
    }
    free(array[row]);
  }
  free(array);

}
