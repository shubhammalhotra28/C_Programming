// C (no pointers) Practicum
// SWEN-250
// Larry Kiser Feb. 13, 2018
//             New no pointers practicum without structs

#include <stdlib.h>
#include <stdio.h>
#include "cpracticum.h"
#include "unit_tests.h"

// Create a loop that goes to the end of the passed string that
// counts the number of numeric characters in that string.
// Return that count from this function.
// Numeric characters are all of the characters from 0 through 9.
//
// Return 0 if there are no numeric characters in the string.
// Return 0 if the passed string is an empty string.
// Otherwise, return the number of numeric characters in the string.
//
// You are NOT allowed to use any library functions. You must write
// C code that determines whether or not each character is a numeric character.
// If you wish you can create your own function that determines whether
// or not a character is a numeric character. You could then call that function
// in your loop that searches the string.
int count_number_of_numeric_characters( char mystring[] )
{


	int i = 0; // declaring and initialising the variable
	int j = 0; // declaring and initialising the variable
	int count = 0; // declaring and initialising the variable
	char digits[]={0,1,2,3,4,5,6,7,8,9}; // array of digits o to 9
	for(i=0;mystring[i]!='\0';i++) // for loop
	{ // taking single entry of the array
		for(j=0;j<9;j++) // for loop
		{
			// comparing the entry of the array with digits array
			if(mystring[i]!=digits[j] && mystring[i]>=48 && mystring[i]<=57)
			{
				// found
				count++; // increment count
				break; // break
			}
		}
	}

	return count;		// return count;
}

// For the passed string you must convert all lower case letters to upper case letters.
// Do no change make any other changes to the array.
// For example a string "ab132 CD==" would become "AB123 CD==".
// The string may be an empty string. If it is empty do nothing.
// Note that this means you are directly changing the characters in the passed string.
// Hint -- per the ASCII code chart an 'a' is 97 decimal and an 'A' is 65 decimal.
//         You can use that difference to convert from lower case to upper case.
void convert_to_upper_case( char mystring[] )
{

	int i; // declaring the variable
	for(i=0;mystring[i]!=EOF;i++) // for loop
	{
		if(mystring[i]>=97 && mystring[i]<=122) // checking if its in the lower range of ascii values
		{
			mystring[i] -= 32; // if yes then decrementing the value by 32
		}
	}
}

// This function returns the letter 'L' if the value is < the lower_limit.
// It returns the letter 'M' if the value is >= the lower limit and <= the upper_limit.
// It returns 'H' if the value is > the upper limit.
// You can assume that upper_limit is always > lower_limit.
//NOTE: THIS FUNCTION HAS BEEN COMPLETED FOR YOU.  DO !!NOT!! CHANGE THIS CODE!
char range_test( int value, int lower_limit, int upper_limit )
{
	
	if(value < lower_limit) // if value is less than lower_limit
	{
		return 'L'; // returning char L
	}
	if ( value >= lower_limit && value <= upper_limit) // if value is greater or equal to lower_limit and less than or equal to upper_limit
	{
		return 'M' ; // return char M
	}
	else // otherwise the higher value will be th only feasible option
	{ 
		return 'H'; // return char H
	}
}

// This function is implemented incorrectly. You need to correct it.
// It is supposed to total up the integers in the array.
// The number of entries to add up is the second parameter.
// It returns that sum.
// NOTE -- you are required to correct this code. You are not allowed to completely rewrite it.
//         There are 5 errors in this routine. You must fix all errors. It is possible that the
//         unit tests may pass without all errors being corrected. Be sure that your corrected
//         code does not produce any warnings.
int fix_bad_code( int numbers[], int number_to_add )
{
	int i;
	int total = 0;
	for ( i = 0 ; i < number_to_add ; i++ ) ;
	{
		total += numbers[i];
	}
	return total;
		

}


// Only runs the unit tests.
int main( int argc, char *argv[] ) {

	// Execute unit tests
	return test() ;
}
