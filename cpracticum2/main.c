// C pointers Practicum with malloc and free
// SWEN-250
// Larry Kiser Nov. 29, 2015
// Larry Kiser updated to summer version July 11, 2017

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unit_tests.h"

extern char *malloc_options ;

// Run the unit tests or as a "normal program".
int main( int argc, char *argv[] ) {

	malloc_options = "CFGSU" ;		// DO NOT TOUCH THIS LINE

	return test() ;
}
