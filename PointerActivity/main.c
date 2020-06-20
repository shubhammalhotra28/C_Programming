/*
 * Driver program for the activity.
 * 	1. Declares local variables for the character, integer, and
 * 	   double precision values returned by read_data.
 * 	2. Calls read_data with pointers to the variables so that
 * 	   the values read can be returned.
 * 	3. On return, prints the character, integer, and double
 * 	   precision number using the following format string for
 * 	   printf:
 * 	   	"Character %c Integer %d Floating point %.4f\n"
 * 	   Note: you must also, of course, provide the values to
 * 	   be printed.
 *      4. Return a 0 to the operating system.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_data.h"
#include "read_data.c"
int main() {
	/* your declarations and statements REPLACE this comment */
	
	char *ch; // initialising the pointer
	int *i; // initialising the pointer
	double *d; // initialising the pointer
	return_type r; // initialising struct object 
	r = read_data(ch,i,d); // getting the values in r returned by the funct
	ch = r.ch; // pointing to the values
	i = r.i; // pointing to the  values
	d = r.d; // pointing to  the values

	// printing the desired statement
	printf("Character %c Integer %d Floating point %.4f\n",*ch,*i,*d);
	

	return 0 ;
}
