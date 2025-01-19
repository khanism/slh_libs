#ifndef SLH_CHARS_TO_INTS_H
#define SLH_CHARS_TO_INTS_H

#include <ctype.h>

/*
* This function takes an char array as an input and returns, a struct that contains the parsed integers and the number of integers read.
* The input char array contains a comma seperated list of integers that are read as is from a file.
* Example for this kind of array: {'1', ',', '-', '3'}, which would translate to the integer array  {1, -3} and the number of integers would be 2.
* Returns NULL on error.
*/

typedef struct integer_arr {
	int num_integers;
	int* stored_integers;
} integer_arr;

integer_arr* chars_to_ints(unsigned char input_arr[], int size_of_array) {
	// TODO: Handle illegal characters
	// Determine the number of integers in this map file
	integer_arr* integers = NULL;
	integers = (integer_arr*) malloc(sizeof(integer_arr));
	integers->num_integers = 0;
	// TODO: Currently we would run into problems if we have more than 100 integers in the file input
	integers->stored_integers = (int*) malloc(100 * sizeof(int));
	bool is_signed = false;

	for (unsigned int idx = 0; idx < size_of_array; ++idx) {

		int num_digits = 0;

		if (input_arr[idx] == '-' || isdigit(input_arr[idx]) || input_arr[idx] == ' ') {

			if (input_arr[idx] == ' ') {
				continue;
			}
			else if (input_arr[idx] == '-') {
				idx++;
				is_signed = true;
			}

			for (; isdigit(input_arr[idx]); idx++) {
				num_digits++;
			}

			if (input_arr[idx] == ',' || input_arr[idx] == EOF || input_arr[idx] == '\0') {
				if (num_digits > 0) {
					integers->num_integers += 1;
					// Store these in an integer
					int result_integer = 0;
					int current_decimal = 1;
					for (int decimal_place = idx-1; isdigit(input_arr[decimal_place]); --decimal_place, current_decimal *= 10) {
						int tmp_integer = input_arr[decimal_place] - 48;
						tmp_integer *= current_decimal;
						result_integer += tmp_integer;
					}

					if (is_signed) {
						result_integer *= -1;
					}

					integers->stored_integers[integers->num_integers - 1] = result_integer;
					is_signed = false;
				}
			}
			else {
				printf("Expected a \',\',  \'#\', \'0\' or \'EOF\', but \'%c\' was given", input_arr);
				return NULL;
			}

		} else {
			printf("Expected a negative or non-negative digit, but \'%c\' was given", input_arr);
			return NULL;
		}
	}

	return integers;
}

#endif

