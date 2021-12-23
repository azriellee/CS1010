/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Pattern
 *
 * Read in two positive integers: an interval n (n >= 1) 
 * and the height of the triangle h.  Then draw a triangle
 * according to a given pattern.  
 *
 * @file: pattern.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>
// define function is_prime
// if leading even and increment by even, just return space 
// if leading even and increment odd, skip every even number jump
// if leading odd and increment odd, skip every odd number jump
// control ^ in for loop

bool is_prime(long n){
  
  if(n == 2 || n == 3){
    return true;
  }
  for(long i = 2;i <= sqrt(n);i += 1){
   if(n % i == 0){
    return false;
   }
  }
  return true;
}

//checking each cell for prime numbers
bool contains_prime(long cell_length,long increment,long cell_starting_num){
  
  bool has_prime = false;

  if(cell_starting_num % 2 == 0 && increment % 2 == 0){
    return has_prime;
  }
  for(long i = 1;i <= cell_length;i += 1){
    if(is_prime(cell_starting_num)){
      return true;
    }
    cell_starting_num += increment;
  }
  return has_prime;
}

//drawing each row
void draw_row(long cell_length,long height,long row,long first_num){

  long num_of_cells = (2*row) -1;
  long total_cells = (2*height)-1;
  long empty_space = (total_cells - num_of_cells)/2;
  long cell_starting_num = first_num;

  for(long col = 1;col <= total_cells;col += 1){
    if(col <= empty_space || col > empty_space+num_of_cells){
      if(col == total_cells){
        cs1010_println_string(" ");
      }else{
        cs1010_print_string(" ");
      }
    }else{
      if(contains_prime(cell_length,row,cell_starting_num)){
        cs1010_print_string("#");
      }else{
        cs1010_print_string(" ");
      }
      cell_starting_num += 1;
    }
  }
}

//draw all the rows in the triangle
void draw_triangle(long cell_length,long height){

  long first_num = 1; 

  for(long row = 1;row <= height;row += 1){
    draw_row(cell_length,height,row,first_num);
    first_num += row * cell_length; 
  }

}

int main()
{
  long cell_length = cs1010_read_long();
  long height = cs1010_read_long();
  
  draw_triangle(cell_length,height);
}
