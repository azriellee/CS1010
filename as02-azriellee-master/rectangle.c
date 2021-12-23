/**
 * CS1010 Semester 1 AY21/22
 * Assignment 2: Rectangle
 *
 * Reads in two integer numbers corresponding to the width and the 
 * height of a rectangle.   Draw the rectangle with the given characters
 * to the standard output.
 *
 * @file: rectangle.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_RIGHT "╝"
#define BOTTOM_LEFT "╚"
#define HORIZONTAL "═"
#define VERTICAL "║"
void print_horizontal(long w,long v,long length){

  for(long j = 1; j <= w ; j += 1){
    if(v == 1 || v == length){
      cs1010_print_string(HORIZONTAL);
    }else{
      cs1010_print_string(" ");
    }
  }
}

void print_rectangle(long width, long length){
  
  for(long i = 1;i <= length;i += 1){
    if(i == 1){

      cs1010_print_string(TOP_LEFT);
      print_horizontal(width-2,i,length);
      cs1010_println_string(TOP_RIGHT);

    }else if(i == length){

      cs1010_print_string(BOTTOM_LEFT);
      print_horizontal(width-2,i,length);
      cs1010_print_string(BOTTOM_RIGHT);

    }else{
      
      cs1010_print_string(VERTICAL);
      print_horizontal(width-2,i,length);
      cs1010_println_string(VERTICAL);
    }
  }
}


int main()
{
  long width = cs1010_read_long();
  long height = cs1010_read_long();
  if(width >= 2 && height >= 2){
    print_rectangle(width,height);
  }
  
}

