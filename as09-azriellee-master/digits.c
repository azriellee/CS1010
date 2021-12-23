/**
 * CS1010 Semester 1 AY21/22
 * Assignment 9: Digits
 *
 * @file: digits.c
 * @author: Azriel (Group E09)
 */

#include "cs1010.h"
#include <stdbool.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5
#define MAX 28 * 28

typedef struct digit {
  char **array;
  long label;
} digit;

typedef struct neighbor {
  long label;
  long distance;
} neighbor;

/**
 *  creates a 2D array of n number of rows and n number of cols
 *
 *  @pre n > 0
 *  @param[in] n the number of rows of the 2D array
 *  @return returns a 2D char array or NULL if memory allocation fails
 *
 */
char **create_array(size_t n) {

  char **array = calloc(n, sizeof(char *));
  if(array == NULL) {
    cs1010_print_string("mem alloc error");
    free(array);
    return NULL;
  }
  for(size_t j = 0; j < n; j += 1) {
    array[j] = cs1010_read_word();
    if(array[j] == NULL) {
      cs1010_print_string("mem alloc error");
      for(size_t m = 0; m < j; m += 1) {
        free(array[m]);
      }
      free(array);
      return NULL;
    }
  }
  return array;
}
/**
 *  takes in 2 2D arrays of char and finds the number of different char between the arrays
 *  calculation of distance will be cut when the distance is greater than the current max distance
 *  after we have at least K values of distances
 *  
 *  @param[in] test_sample the test_sample to check
 *  @param[in] training_sample the training sample being compared to
 *  @param[in] iteration the number of distance values we already have
 *  @param[in] max_so_far the current max of K values of distance data
 *
 *  @return returns a long value of the number of different char between 2 arrays
 *
 */
long distance(char **test_sample, char **training_sample, size_t iteration, long max_so_far) {

  long dist = 0;
  for(size_t i = 0; i < NROWS; i += 1) {
    for(size_t j = 0; j < NCOLS; j += 1) {
      if(test_sample[i][j] != training_sample[i][j]) {
        dist += 1;
      }
      if(dist > max_so_far && iteration > K) {
        return dist;
      }
    }
  }
  return dist;
}
/**
 *  finds the digit with the lowest distance, should there be 2 most common occurrence of a digit
 *  
 *  @param[in, out] num the pointer to the digit with lowest distance
 *  @param[in] k_nearest the array of K-nearest digits and distances
 *  @param[in] i the digit to update
 *
 */
void find_num(long *num, neighbor *k_nearest, long i) {

  for(long j = 0; j < K; j += 1) {
    if(k_nearest[j].label == i) {
      *num = i;
      break;
    }
    if(k_nearest[j].label == *num) {
      break;
    }
  }
}
/**
 *  finds the most occurring digit, and breaks ties by choosing the digit with lower distance
 *
 *  param[in] k_nearest the array of K-nearest digits and distances
 *  @return returns the most commonly occurring digit
 *
 */
long highest_occurrence(neighbor *k_nearest) {

  long digit[10] = {0};
  
  for(size_t i = 0; i < K; i += 1) {
    digit[k_nearest[i].label] += 1;
  }

  long occurrence = 0;
  long num = 0;
  
  for(long i = 0; i < 10; i += 1) {
    if(digit[i] > occurrence) {
      occurrence = digit[i];
      num = i;
    } else if (digit[i] == occurrence) {
        find_num(&num, k_nearest, i);
    }
  }
  
  free(k_nearest);
  return num;
}

/**
 * function finds the K-nearest digits from the training sample, and returns the digit it is recognised as
 *  
 *  @pre num_training > 0
 *
 *  @param[in] dist_truth the array of neighbor containing the distance between the test sample and all the training samples
 *  and the label of the training sample
 *  @param[in] num_training the number of training samples
 *  @return returns the digit that the test sample is recognised as, 
 *
 */
long recognised_as(neighbor *dist_truth, size_t num_training) {

  neighbor *k_nearest = calloc(K, sizeof(neighbor));
  if(k_nearest == NULL) {
    cs1010_print_string("mem alloc error");
    return -1;
  }

  for(size_t i = 0; i < K; i += 1) {

    long min = MAX;
    long ele = 0;

    for(long j = 0; j < (long) num_training; j += 1) {
      if(dist_truth[j].distance < min) {
        min = dist_truth[j].distance;
        ele = j;
      } else if (dist_truth[j].distance == min && dist_truth[j].label < dist_truth[ele].label) {
        min = dist_truth[j].distance;
        ele = j;
      }
    }
    
    k_nearest[i].distance = min;
    k_nearest[i].label = dist_truth[ele].label;
    dist_truth[ele].distance = MAX;
    ele = 0;

  }
  return highest_occurrence(k_nearest);
}
/**
 *  function creates an array of neighbor to store the distance and label of the test_sample to each training sample
 *  then recognises the test sample as the most commonly occurring digit in the array of neighbor, and returns that
 *  value 
 *
 *  @param[in] test_sample the 2D array to test
 *  @param[in] training_samples the array of digit containing all the training samples and their corresponding labels
 *  @param[in] num_training the number of training samples
 *
 *  @return returns a long value of the digit that the test sample is recognised as
 */
long compare_distance(char **test_sample, digit *training_samples, size_t num_training) {

  neighbor *dist_truth = calloc(num_training, sizeof(neighbor));

  if(dist_truth == NULL) {
    cs1010_print_string("mem alloc error");
    return -1;
  }

  long max = 0;

  for(size_t i = 0; i < num_training; i += 1) {
    char **training_sample = training_samples[i].array;
    dist_truth[i].label = training_samples[i].label;
    long dist = distance(test_sample, training_sample, i, max);
    dist_truth[i].distance = dist;
    if(dist > max) {
      max = dist;
    } 
  }

  long rec_digit = recognised_as(dist_truth, num_training);
  free(dist_truth);

  return rec_digit;
}

int main()
{
  size_t num_training = cs1010_read_size_t();
  digit *training_samples = calloc(num_training, sizeof(digit));
  if(training_samples == NULL) {
    cs1010_print_string("mem alloc error");
    return -1;
  }
  for(size_t i = 0; i < num_training; i += 1) {
    training_samples[i].label = cs1010_read_long();
    training_samples[i].array = create_array(NROWS);
  }
  
  size_t num_test = cs1010_read_size_t();
  double correct = 0.0;

  for(size_t i = 0; i < num_test; i += 1) {
    long label = cs1010_read_long();
    char **test_sample = create_array(NROWS);

    cs1010_print_long(label);
    cs1010_print_string(" ");
    long recognised_as = compare_distance(test_sample, training_samples, num_training);
    cs1010_println_long(recognised_as);

    if(recognised_as == label) {
      correct += 1;
    }

    for(size_t j = 0; j < NROWS; j += 1) {
      free(test_sample[j]);
    }
    free(test_sample);
  }
  
  cs1010_print_double((correct / num_test) * 100);
  
  for(size_t i = 0; i < num_training; i += 1) {
    for(size_t j = 0; j < NROWS; j += 1) {
      free(training_samples[i].array[j]);    
    }
    free(training_samples[i].array);
  }
  free(training_samples);


}
