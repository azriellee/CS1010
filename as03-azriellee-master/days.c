/**
 * CS1010 Semester 1 AY21/22
 * Assignment 3: Days
 *
 * @file: days.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
long get_day(long months[12], long month, long day){
  
  long day_of_year = day;

  for(long i = 0; i < (month-1); i += 1){
    day_of_year += months[i];
  }
  return day_of_year;
}


int main() 
{

  long month = cs1010_read_long();
  long day = cs1010_read_long();
  long months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  cs1010_print_long(get_day(months, month, day));
}
