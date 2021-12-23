/**
 * CS1010 Semester 1 AY21/22
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the taxi fare for the trip.
 *
 * @file: taxi.c
 * @author: Azriel lee (Group E09)
 */

#include "cs1010.h"
#include <stdbool.h>
#include <math.h>
double first_10(long distance_left){
  double i = ceil(distance_left/400.0);
  return i*0.22;
}
double subsequent(long rem_dist){
  double j = ceil(rem_dist/350.0);
  return j*0.22;
}

double basic_fare(long distance){
  double price = 3.7;
  if(distance > 1000 && distance <= 10000){
    price += first_10(distance-1000);
  } else if(distance >10000){
    price += 23*0.22;
    price += subsequent(distance-10000);
  }
  return price;
}

double surcharge(long day, long time){
  double s = 1.0;
  if(day>=1 && day<=5 && time>=600 && time<=929){
    s = 1.25;
  } else if(time>=1800 && time <=2359){
    s = 1.25;
  } else if(time>=0 && time <=559){
    s = 1.5;
  }
  return s;
}

int main()
{
  long day = cs1010_read_long();
  long hour = cs1010_read_long();
  long minute = cs1010_read_long();
  long distance = cs1010_read_long();
  long time = hour*100 + minute;
  double fare = basic_fare(distance);
  double total_price = fare * surcharge(day,time);
  cs1010_println_double(total_price);

}
