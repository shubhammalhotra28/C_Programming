/*
 * Skeleton implementation for the activity to parse and print
 * CSV formatted files read from standard input.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "unit_tests.h"


/*
 * Returns true iff the character 'ch' ends a field. That is, ch is end of file,
 * a comma, or a newline.
 */

bool is_end_of_field(int ch) {
	return ((ch == ',') || (ch == '\n') || (ch == EOF)) ;
}

/*
 * Return the minimum of two integers.
 */

int min(int x, int y) {
	return x < y ? x : y ;
}

/*
 * Read the next field from standard input. Returns the value of getchar() that
 * stopped (terminated) the field.
 */

int get_field(f_string field) {
	/* FILL THIS IN */

	int i = 0; // declaring and initialising the variable
	int ch = getchar(); // getting the first char
	while(ch!=EOF)
	{
		field[i++]=(char)ch; // updating the character
		ch = getchar(); // incrementing the character
		if(is_end_of_field(ch))
		{
			field[i] = '\0'; // if there is any termination condition-> helper function returns true
			break; // break
			
		}
	}
	return ch; // return the value with which we hit the condition


}

/*
 * Read in a CSV line. No error checking is done on the number of fields or
 * the size of any one field.
 * On return, the fields have been filled in (and properly NUL-terminated), and
 * nfields is the count of the number of valid fields.
 * nfields == 0 means end of file was encountered.
 */

csv_line get_line() {
	/* FILL THIS IN */
	char ch; // initialising the variable
	csv_line c_ref; // creating a ref top the structure type
	int i =0; // declaring and initialising the variable i
	while(ch!=EOF) // loop
	{
		int k = get_field(c_ref.field[i]); // getting the return value from the function in k
		if(k==-1) // if end of file
		{
			c_ref.nfields = 0; // set nfields == 0
			return c_ref; // return;

		}
		else if(k=='\n') // if new line
		{
			break; // exit the loop
		}
		else	
		{
			i++;	// incrementing the value of i
		}

	}
	i++; // increment i including the space for null character
	c_ref.nfields = i; // setting nfields as i
	return c_ref; // return the variable of struct type
}

/*
 * Print a CSV line, associating the header fields with the
 * data line fields.
 * The minimum of the number of fields in the header and the data
 * determines how many fields are printed.
 */

void print_csv(csv_line header, csv_line data) {
	/* FILL THIS IN */
	// header files -> print idk
	int a = min(header.nfields,data.nfields); // getting th emin of the nfields from header and data

	int i; // declaring a variable
	for(i=0;i<a;i++) // loop
	{
		printf("%s = %s\n",header.field[i],data.field[i]); // priniting in required manner

	}


}

/*
 * Driver - read a CSV line for the header then read and print data lines
 * until end of file.
 */

int main( int argc, char *argv[] ) {
	csv_line header ;
	csv_line current ;

	// LLK additional if statement to execute unit tests if program
	// name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;

	header = get_line() ;
	current = get_line() ;

	while ( current.nfields > 0 ) {
		print_csv(header, current) ;
		current = get_line() ;
	}

	return 0 ;
}
