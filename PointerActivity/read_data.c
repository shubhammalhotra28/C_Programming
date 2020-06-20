/*
 * Implementation of the read_data module.
 *
 * See read_data.h for a description of the read_data function's
 * specification.
 *
 * Note that the parameter declarations in this module must be
 * compatible with those in the read_data.h header file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_data.h"
/*struct return_type{

	char *ch;
	int *i;
	double *d
};*/

// Reads the three fields from lines such as W$1349$1.414$ into
// local variables using getchar().
// Converts the two numeric fields to numbers using atoi for the
// integer fields and atof for the double.
// Using a correctly defined set of parameters (use pointers) pass
// those values back to the program that called this function.
return_type read_data(char *character,int *integer, double *doub){
	
	/* your declarations and statements REPLACE this comment */
	char ch; // initialising the character
	ch = getchar(); // getting the data from console one by one
	char cha = ch; // storing the character from ch to another variable
	char b[25]; // initialising the char array of size 25
	char c[25]; // initialising the char array of size 25
	int i; // initialising the integer
	double d; // initialising the double
	return_type r1; // initialising r1 as return_type object of struct
	int z = 0; // declaring and initialising integer
	int w = 0; // declaring and initialising integer
	ch = getchar(); // getting the character from console
	ch = getchar(); // getting the character from console
	while(ch!='\0') // loop 
	{
		b[z] = ch; // storing the integer in the array
		if(ch=='$')
		{
			ch = getchar(); // incrementing to get next char from $
			while(ch!='$')
			{
				c[w] = ch; // storing the double in the array
				ch = getchar();
				w++; // incrementing
				
			}
			break; // exiting

		}
		ch = getchar(); // incrementing
		z++; // incrementing
	}
	b[z] = '\0'; // setting the last char of array as null
	c[w] = '\0'; // setting the last char of array as null
	i  = atoi(b);	// string to integer
	d = atof(c); 	// string to double

	r1.i = &i; // pointing towards the address
	r1.d = &d; // pointing towards the address
	r1.ch = &cha; // pointing towards the address
	

	return r1; // return
}
