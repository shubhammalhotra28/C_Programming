// Longest Line activity with limited unit tests
// Based on prior work by SE dept. faculty
// L. Kiser
// Oct. 18, 2015
// LLK updated Feb. 10, 2016 to make arrays MAXLINE + 1 for EOS.
//
// Adds a simple test function and a boolean assert function to
// allow basic unit test. This is intended as a starting point
// for more sophisticated unit testing in C in later activities
// and projects.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>		// LLK addition to support strstr function

#define MAXLINE 80   /* maximum input line size */

/* function declarations */
extern int readline( char line[], int max );
extern void copy( char to[], char from[] );
extern int test( void) ;		// LLK addition for unit testing

/*
 * main:
 *     Print longest input line
 * Note: You may have to declare additional variables.
 */

int main( int argc, char *argv[] ) {		// LLK addition for unit testing
	int len;	       /* current line length */
	char line[MAXLINE + 1];    /* current input line */
	int max_length = 1000;	   //predefined variable used to initialise the array
	char copy_arr[max_length]; // char array-> initialisation
	int max_length_till_now = 0; // variable initialisation

	// LLK additional if statement to execute unit tests if program
	// name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;

	while ( (len = readline( line, MAXLINE )) > 0 ) 
	{
			
		//printf("%d\n", len);
	
		/*Fill in with code to save the longest line using your copy function */
	/* condition to get the output for the highest length string -> copied */
		if(len > max_length_till_now){
			max_length_till_now = len;
			copy(copy_arr,line);
			//printf("%d",len);
			//printf("copied %s",copy_arr);
		}
				

		
	}
	//printf("Length is %d",len);	
			//printf("I am exiting");
			printf("%s",copy_arr);
	


	return 0; // return success code

}
/*
 * readline:
 *   Read a line into array <s> and return its length.
 *      * The string in <s> must be properly terminated.
 *      * At most <max_chars> are read; excessive characters are
 *        discarded.
 *      * The length returned is the length of the entire
 *        line, not just the piece that is copied.
 *      * A terminating newline ('\n') is *not* copied over.
 *      * If EOF is encountered, return (-1).
 * Note: You may have to declare additional variables.
 */
int readline( char s[], int max_chars ) {
	/* your code here */
	int i=0;
	int sum = 0;
	char ch = getchar(); // getting input one by one

	if(ch == EOF)
	{		
		return -1; // returning -1 if it hits end of file
	}
	while(ch!=EOF)
	{
	// loop
		if(i<=max_chars)
		{
			//printf("i=%d",i);
			s[i] = ch; // getting the data store one by one
			if(s[i]=='\n')
			{
				//printf("enter is executed\n");
				s[i+1] = '\0';
				break;
			}

		}
		else
		{
			//printf("sum is incrementing %d\n",sum);
			sum++;
		}
		i++; // incrementing i
		ch = getchar(); // incrementing ch
	}
	
	return i+sum ; // placeholder for the real return value.
}

/* copy:
 *    Copy proper C string <from> into <to>
 *    Assume <to> has enough space to hold a copy of <from>.
 * Note: You may have to declare additional variables.
 */
void copy( char to[], char from[] ) {
	//	Your code here: (LLK updated)
	//	You CANNOT use any of the string
	//	functions to implement this function.
	//	You MUST use the passed parameters as array.
	//	Do NOT use pointers.
	
	int  i = 0;
	for(i = 0;from[i]!='\0';i++)
	{
		to[i] = from[i]; // copying from -> to
	}
	to[i] = '\0'; // adding null charactuer to terminate the string
}
// LLK added simple boolean assert function for unit testing
int assert( int testresult, char error_message[] ) {
	static int test_number = 1 ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! testresult ) {
		printf( "%d test failed: %s\n", test_number, error_message ) ;
		result = 0 ;
	}
	return result ;
}

// LLK added unit tests.
int test()
{
	char output_array[MAXLINE + 1] = "" ;	// initialize to empty line to be safe
	char testline1[] = "A" ;	// test single char line
	char testline2[] = "" ;		// test empty line
	char testline3[] = "Typical line to be copied." ;
	char testline4[] = "\n\n\n" ;
	int passcount = 0 ;
	int failcount = 0 ;
	int result ;
	
	printf("\nExecuting unit tests\n") ;
	// first unit test
	copy( output_array, testline1 ) ;
	if ( assert( !strcmp( output_array, testline1 ), "Unit test for one character string" ) )
		passcount++ ;
	else
		failcount++ ;
	
	copy( output_array, testline2 ) ;
	if ( assert( !strcmp( output_array, testline2 ), "Unit test for copying empty string" ) )
		passcount++ ;
	else
		failcount++ ;
	
	copy( output_array, testline3 ) ;
	if ( assert( !strcmp( output_array, testline3 ), "Unit test for typical string" ) )
		passcount++ ;
	else
		failcount++ ;

	copy( output_array, testline4 ) ;
	if ( assert( !strcmp( output_array, testline4 ), "Unit test for string with only newlines" ) )
		passcount++ ;
	else
		failcount++ ;

	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}

