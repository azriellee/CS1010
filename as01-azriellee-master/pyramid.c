/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Pyramid
 *
 * Read in three positive integer corresponding to the width,
 * length, and height of a pyramid from the standard input, and
 * print the total surface area to the standard output.
 *
 * @file: pyramid.c
 * @author: Azriel Lee (Group E09)
 */

#include "cs1010.h"
#include <math.h>

double hypotenuse_of(double side1,double side2){
  return sqrt(1.0*side1*side1 + 1.0*side2*side2);
}

long area_of_rectangle(long width,long length){
  return width*length;
}

double area_of_triangle(double a,double b,double c){
  double s = (a+b+c)/2;
  return sqrt(s*(s-a)*(s-b)*(s-c));
}

int main() 
{
  long width = cs1010_read_long();
  long length = cs1010_read_long();
  long height = cs1010_read_long();
  
  long rectangle = area_of_rectangle(width,length);
  double diagonal = hypotenuse_of(width,length)/2;
  double triangle_side = hypotenuse_of(diagonal,height);
  double triangle_area1 = area_of_triangle(triangle_side,triangle_side,width);
  double triangle_area2 = area_of_triangle(triangle_side,triangle_side,length);
  double total_area = 2*triangle_area1 + 2*triangle_area2 + rectangle;

  cs1010_println_double(total_area);
}
