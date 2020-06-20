/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>

#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
	int i = 0;
	for(i=0;string[i]!='\0';i++){
		
		if(ch==string[i]){
			return i;
		}
	
	}
	return NOT_FOUND ;	// placeholder
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
		int i = 0;
		for(i=0;string[i]!='\0';i++)
		{
			if(ch==string[i]){
				return string+i;
			}
		}
		return NULL ;	// placeholder
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
	
	int i = 0;
	int j = 0;

	for(i=0;string[i]!='\0';i++){
		for(j=0;stop[j]!='\0';j++){
			
			if(stop[j]==string[i]){
				return i;
			}

		}
	}
	
	
	
	return NOT_FOUND ;	// placeholder
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
	
	int i = 0;
	int j =0;
	for(i=0;string[i]!='\0';i++)
	{
		for(j=0;stop[j]!='\0';j++)
		{
			if(string[i]==stop[j]){
				return string+i;
			}
		}
	}
	return NULL ;	// placeholder
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
	
	if(substr==" "){
		return string+0;
	}
	int i,j;
	return strstr(string,substr);
	return NULL;	// placeholder
} 
