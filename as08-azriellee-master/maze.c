/**
 * @file: maze.c
 * @author: Azriel (Group E09)
 *
 */
#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * Print one row of the maze to the screen (with colors)
 * 
 * @param[in] maze_row The 1D array representing a row of maze.
 */
void print_maze_row_with_color(char *maze_row) {
  long l = (long)strlen(maze_row); 
  for (long j = 0; j < l; j++) {
    if (maze_row[j] == EMPTY) {
      cs1010_print_string(BLUE);
    } else if (maze_row[j] == USER) {
      cs1010_print_string(RED);
    } else {
      cs1010_print_string(YELLOW);
    }
    putchar(maze_row[j]);
  }
  cs1010_println_string("");
  cs1010_print_string(RESET);
}

/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, size_t nrows, long steps) {
  if (isatty(fileno(stdout))) {
    cs1010_clear_screen();
  }
  for (long i = 0; i < (long) nrows; i += 1) {
    if (!isatty(fileno(stdout))) {
      cs1010_println_string(maze[i]);
    } else {
      print_maze_row_with_color(maze[i]);
    }
  }
  cs1010_println_long(steps);
  if (isatty(fileno(stdout))) {
    usleep(100*1000);
  }
}

/**
 ** create_array takes in an input of how many rows and creates the number of rows 
 ** within the array accordingly. each row within the array will be populated by a string input by
 ** the usur
 **
 ** @pre num_of_rows > 1
 ** @param[in] num_of_rows the number of arrays within the array
 ** @return returns NULL if there is a memeory allocation error, otherwise it will
 ** return a 2D array.
 **
 **/

char **create_array(size_t num_of_rows) {

  char **array;
  array = calloc(num_of_rows, sizeof(char *));
  if(array == NULL) {
    cs1010_println_string("unable to allocate array");
    return NULL;
  }
  for (size_t row = 0; row < num_of_rows; row += 1) {
    array[row] = cs1010_read_word();
    if (array[row] == NULL) {
      cs1010_println_string("unable to allocate array");
      for (size_t j = 0; j < row; j += 1) {
        free(array[j]);
      }
      free(array);
      return NULL;
    }
  }
  return array;
}
/**
 * this function creates a 2D array of boolean, initialising every element
 * to false initially
 *
 * @param[in] num_of_rows the number of rows in the array
 * @param[in] num_of_col the number of columns within each row
 *
 * @return returns NULL if there is a memeory allocation error, otherwise it will
 * return a 2D boolean array.
 */
bool **bool_array(size_t num_of_rows, size_t num_of_col) {

  bool **array;
  array = calloc(num_of_rows, sizeof(char *));
  if(array == NULL) {
    cs1010_println_string("unable to allocate array");
    return NULL;
  }
  for (size_t row = 0; row < num_of_rows; row += 1) {
    array[row] = calloc(num_of_col, sizeof(bool *));
    if(array[row] == NULL) {
      cs1010_println_string("unable to allocate array");
      for (size_t j = 0; j < row; j += 1) {
        free(array[j]);
      }
      free(array);
      return NULL;
    }
    for(size_t i = 0; i < num_of_col; i += 1) {
      array[row][i] = false;
    }
  }
  return array;
}
/**
 * this function checks if an element can be visited, by checking if its parameters are within
 * the bounds of the array and whether the element has been visited before
 *
 * @param[in] array the 2D array of elements
 * @param[in] visited 2D array of boolean to indicate whether an element has been visited
 * @param[in] num_of_rows number of rows in the array
 * @param[in] num_of_col the number of columns within each row
 * @param[in] exp_row the row of the element to check
 * @param[in] exp_col the column of the element to check
 *
 * @return true if the element can be visited else false
 *
 */
bool can_explore(char **array, bool **visited, size_t num_of_rows, size_t num_of_col
    , long exp_row, long exp_col) {

  if(exp_row < 0 || exp_row >= (long) num_of_rows || exp_col < 0 || exp_col >= (long) num_of_col) {
    return false;
  }
  if(array[exp_row][exp_col] == WALL || visited[exp_row][exp_col]) {
    return false;
  }
  return true;
}
/**
 * this function updates the current position
 *
 * @param[in, out] array the 2D array
 * @param[in] exp_row the new row of Scully
 * @param[in] exp_col the new col of Scully
 * @param[in] ini_row the original row of Scully
 * @param[in] ini_col the original col of Scully
 *
 */
void update(char **array, long exp_row, long exp_col, long ini_row, long ini_col) {
  
  array[exp_row][exp_col] = USER;
  array[ini_row][ini_col] = EMPTY;

}
/**
 * this function recursively finds the possible path of Scully and backtracks if a dead end is reached
 *
 * @param[in, out] array the array containing the maze
 * @param[in, out] visited the array to check if a cell has been visited before
 * @param[in] num_of_rows the number of rows in the array
 * @param[in] num_of_col the number of columns within the row
 * @param[in] cur_row the current row position of Scully
 * @param[in] cur_col the current column containing Scully's position
 * @param[in, out] steps the total steps taken by Scully
 * @param[in] correct to check if scully has already reached the edge
 *
 */
void explore_maze(char **array, bool **visited, size_t num_of_rows, size_t num_of_col,
    long cur_row, long cur_col, long *steps, long *correct) {
  
  print_maze(array, num_of_rows, *steps);
  visited[cur_row][cur_col] = true;
  *steps += 1;

  if(cur_row == 0 || cur_row == (long) num_of_rows - 1 || cur_col == 0 || cur_col == (long) num_of_col - 1) {
    *correct = 1;
    return;
  }

  if(can_explore(array, visited, num_of_rows, num_of_col, cur_row - 1, cur_col)) {
    update(array, cur_row - 1, cur_col, cur_row, cur_col);
    explore_maze(array, visited, num_of_rows, num_of_col, cur_row - 1, cur_col, steps, correct);
    if(*correct == 1) {
      return;
    }
  } else if(can_explore(array, visited, num_of_rows, num_of_col, cur_row, cur_col + 1)) {
    update(array, cur_row, cur_col + 1, cur_row, cur_col);
    explore_maze(array, visited, num_of_rows, num_of_col, cur_row, cur_col + 1, steps, correct);
    if(*correct == 1) {
      return;
    }
  } else if(can_explore(array, visited, num_of_rows, num_of_col, cur_row + 1, cur_col)) {
    update(array, cur_row + 1, cur_col, cur_row, cur_col);
    explore_maze(array, visited, num_of_rows, num_of_col, cur_row + 1, cur_col, steps, correct);
    if(*correct == 1) {
      return;
    }
  } else if(can_explore(array, visited, num_of_rows, num_of_col, cur_row, cur_col - 1)) {
    update(array, cur_row, cur_col - 1, cur_row, cur_col);
    explore_maze(array, visited, num_of_rows, num_of_col, cur_row, cur_col - 1, steps, correct);
    if(*correct == 1) {
      return;
    }
  } else {
    array[cur_row][cur_col] = EMPTY;
    return;
  }

  array[cur_row][cur_col] = USER;
  explore_maze(array, visited, num_of_rows, num_of_col, cur_row, cur_col, steps, correct);;
}

int main() {

  size_t num_of_rows = cs1010_read_size_t();
  size_t num_of_col = cs1010_read_size_t();
  char **array = create_array(num_of_rows);
  bool **visited = bool_array(num_of_rows, num_of_col);
  long cur_row;
  long cur_col;
  long steps = 0;
  long correct = 0;

  for(long i = 0; i < (long) num_of_rows; i += 1) {
    for(long j = 0; j < (long) num_of_col; j += 1) {
      if(array[i][j] == USER) {
        cur_row = i;
        cur_col = j;
      }
    }
  }

  explore_maze(array, visited, num_of_rows, num_of_col, cur_row, cur_col, &steps, &correct);

  for(size_t row = 0; row < num_of_rows; row += 1) {
    free(array[row]);
    free(visited[row]);
  }
  free(array);
  free(visited);
}
