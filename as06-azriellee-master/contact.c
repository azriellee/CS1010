/**
 * CS1010 Semester 1 AY21/22
 * Assignment 6: Contact
 *
 * @file: contact.c
 * @author: Azriel (Group E09)
 */
#include "cs1010.h"
#include <stdbool.h>
/**
 * create_array takes in an input of how many lists and creates the number of lists 
 * within the array accordingly, with each list having a size corresponding to its
 * row number. each list within the array will be populated by a string input by
 * the usuer
 *
 * @pre num_of_rows > 1
 * @param[in] num_of_rows the number of arrays within the array
 * @return returns NULL if there is a memeory allocation error, otherwise it will
 * return a 2D array.
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
    }
  }
  return contacts;
}
/**
 * contact takes in a size_t variable corresponding to person1, person2 & a 2D
 * array. it checks whether the people that person2 came in contact with also came
 * in contact with person1
 *
 * @param[in] person1 a size_t variable corresponding to the first person input by
 * user
 * @param[in] person2 a size_t variable corresponding to second person input by 
 * user
 * @param[in] array a 2D jagged array
 * @return true if one of the person who came into contact with person2 also came in
 * contact with person1, if not false will be returned
 *
 */
bool contact(size_t person1, size_t person2, char **array) {
  
  char *array_taken = array[person2];
  for(size_t i = 0; i < person2; i += 1) {
    if(array_taken[i] == '1') {
      if(array[i][person1] == '1') {
        cs1010_print_string("contact through ");
        cs1010_print_long((long) i);
        return true;
      }
    }
  }
  return false;
}

int main()
{
  size_t n = cs1010_read_size_t();
  char **array = create_array(n);
  
  size_t person1 = cs1010_read_size_t();
  size_t person2 = cs1010_read_size_t();
  
  if(array[person2][0] == '1') {
    cs1010_print_string("direct contact");
  }
  else {
    if(!contact(person1, person2, array)) {
      cs1010_print_string("no contact"); 
    }
  }
  
  for(size_t row = 0; row < n; row += 1) {
    free(array[row]);
  }
  free(array);
}
