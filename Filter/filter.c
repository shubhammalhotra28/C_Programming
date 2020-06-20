/*
 * Implementation of functions that filter values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h> OTHER THAN
 * strcpy() and strlen()
 *****
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "filter.h"

#define NUL ('\0')

/*
 * YOU MAY FIND THIS FUNCTION USEFUL.
 * Return true if and only if character <c> is in string <s>.
 */
static bool includes(char c, char *s) {
	while( *s && c != *s ) {
		s++ ;
	}
	return c == *s ;
}

/*
 * YOU MAY ALSO FIND THIS FUNCTION USEFUL.
 * Return true if and only if string <pre> is a prefix of string <s>.
 */
static bool prefix(char *s, char *pre) {
	while( *pre && *s == *pre ) 
	{
		s++ ;
		pre++ ;
	}
	return *pre == NUL ;
}

/*
 * Copy <string> to <result> while removing all occurrences of <ch>.
 */
void filter_ch_index(char string[], char result[], char ch) {

	int i = 0; // declaring and initialising the variable with 0
	int j = 0; // declaring and initialising the variable with 0
	for(i=0;string[i]!=NUL;i++) // loop
	{
		if(string[i]!=ch) // if ith element is not equal
		{
			result[j++] = string[i]; // then append and increment k
		}
	}
	result[j] = NUL; // add null to the last ith index
}

/*
 * Return a pointer to a string that is a copy of <string> with
 * all occurrences of <ch> removed. The returned string must occupy
 * the least possible dynamically allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_ch_ptr(char *string, char ch) {
	
	int i = 0; // declaring and initialising the variable with 0
	int cnt = 0; // declaring and initialising the variable with 0
	char *prev_string = string; // copying the string
	for(i=*string;i!='\0';i=*string) // loop
	{
		if(i!=ch) // if i is not equal to ch
		{
			cnt++; // increment the cnt
		}
		*string++; // increment the string
	}
	string = prev_string; // initialising the string to be as prev_string
	char *result = malloc(cnt+1); // creating a pointer of space cnt+1
	if(*string==NUL) // if string equals null
	{
		*result = NUL; // setting result to null
		return result; // return
	}
	i = 0; // setting i to 0
	char *prev_result = result;// storing the result in prev_result
	for(i=*string;i!=NUL;i=*string) // loop
	{
		if(ch!=i) // if ch is not equal to i
		{
			*result = *string; // set result to string
			*result++; // increment the result
		} 
		*string++; // increment the string

	}
	result = prev_result; // set result equals prev_result
	return result; // return result

}

/*
 * Copy <string> to <result> while removing all occurrences of
 * any characters in <remove>.
 */
void filter_any_index(char string[], char result[], char remove[]) {

	//printf("djsdhshdhie");	
	int i = 0; // declaring and initialising the variable to 0
	int j = 0; // declaring and intialising the variable to 0
	int k = 0; // declaring and initialising the variable to 0
	bool flag = true; // declaring and initialising the boolean to be true
	for(i=0;string[i]!=NUL;i++) // loop
	{
		for(j=0;remove[j]!=NUL;j++) // loop
		{
			if(string[i]==remove[j]) // if match
			{
				flag = false; // set flag = false
				break; // break
			}
		}
		if(flag==true) // if flag is true
		{
			result[k++] = string[i]; // store value of string in result and increment k
		}
		flag = true; // set flag to true
		
	}
	result[k] = NUL; // set the last null terminator
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of any characters in <remove>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *filter_any_ptr(char *string, char* remove) {
	
  int length_string=strlen(string);// getting the length
  int i=0;// declaring and intialising the variable to 0
  int cnt=0;// declaring and intialising the variable to 0
  int k=0;// declaring and initialising the variable to 0
  char *final=malloc(length_string+1);// temp pointer created
  char *temp=malloc(length_string+1);// temp pointer creeated
  char *old_final=final;// storing final string
  char *old_string=string;// storing string org value
  char *old_remove=remove;// storing the remove org value
  char *old_temp=temp;// setting the value to temp
  strcpy(temp,string);// ccopying
  for(k=*remove;k!=NUL;k=*remove){ //for loop
    memset(final,0,length_string+1);// setting the values to be null
    old_final=final;// updating the values
    cnt=0;// setting cnt to 0
    for(i=*temp;i!=NUL;i=*temp){ // for loop
      if(k!=i){// to check if chars are equal
	*final=i;// storing the value of i to final
	cnt++;// incrementing the cnt
	*final++;// incrementing the final
      }
      *temp++;// incrementing the temp
    }
    if(*remove++ !=NUL){// if remove is NULL
      final=old_final;// setting final back to the final
      strcpy(temp,final);// copyin
    }
    else if(*remove++==NUL){ 
      *final=NUL;// adding NUL at the end
      final=old_final; // updating
    }
  }
  remove=old_remove;// initialzing the remove back to its original value
  temp=old_temp;// setting the temp to old value
  char *result=malloc(cnt+1);// allocating memory for the result
  if(*string==NUL){
    *result=NUL;
    free(final);// freeing the memory
    free(temp);
    return result; // return result
  }
  if(*remove==NUL){
    strcpy(result,string); // copy of string to be given
    free(final);// freeing the mem
    free(temp);
    return result; // return result
  }
  strcpy(result,final);//copying 
  free(final);// freeing 
  free(temp);
  return result; // return result
	
	//return strcpy(malloc(1), "") ; // placeholder
}

/*
 * Return a pointer to a copy of <string> after removing all
 * occurrrences of the substring <substr>.
 * The returned string must occupy the least possible dynamically
 * allocated space.
 *****
 * YOU MAY *NOT* USE ARRAY INDEXING.
 *****
 */
char *filter_substr(char *string, char* substr) {
  char *prev_substr=substr;// storing the initial value of substring
  int i=0; // declaring and initialising the variable to 0 
  int j=0;// declaring and initialising the variable to 0
  int length=strlen(substr);// storing the length of substring
  int length_string=strlen(string); // storing the length of the string
  int cnt=0;// initialising the cnt with 0
  int n=0;// declaring and initialising the n = 0
  char *old_string=string;// storing the initial value of string
  
  for(i=*string;i!=NUL;i=*string){// for loog
    char *old_string1=string;// initial valiue of stirng is stored
    for(j=0;j<length;j++){// for loop
      if(*string==*substr){// if equal
	*substr++;// incrementing
	*string++;// incrementing
	cnt++;// incrementing
      }
    }
    string=old_string1;// setting the old value
    substr=prev_substr;// setting the old value
    if(cnt==length){// if same length
      n++;// incrementing
    }
    cnt=0;//setting cnt to 0
    *string++;// incrementing
  }
  char *result=malloc(length_string-length*n+1);// allocating the memory
  char *final=malloc(length_string+1);// allocating the mem to pointer
  char *temp=malloc(length_string+1);// alocating the mem to pointer
  char *old_final=final;// storing the old value
  char *old_temp=temp;// storing the old value
  string=old_string;// initializing the initial value
  strcpy(temp,string);// copying
  if(*temp==NUL){// if str is nukk
    *result=NUL;// set result to null
    return result;
  }
  
  for(i=*temp;i!=NUL;i=*temp){// loop
    if(i!=*substr){// if no match of i to substr
      *final=*temp;//updating the final ptr
      *temp++;//incrementing ptr
      *final++;// incrementing ptr
    }else if(strlen(temp)>=length){
      char *old_temp=temp;// storing the starting value of temp
      cnt=0;// set cnt to 0
      for(j=0;j<length;j++){// for loop
	if(*temp==*substr){// if equal
	  *substr++;// incrementing
	  *temp++;// incrementing
	  cnt++;// incrementing
	}
      }
      substr=prev_substr;// reinitializing the substr to its initial value
      if(cnt!=length){// if the cnt is not equal to length
	temp=old_temp;// setting back old value
	*final=*temp;
	*final++;// incrementing
	*temp++;// incrementing
      }
    }
    else{
      *final=*temp;
      *final++; // incrementing
      *temp++; // incrementing
    }
  }
  *final=NUL;// adding NULL
  final=old_final;// set old value
  strcpy(result,final);// copying
  free(final);
  temp=old_temp;// set opld value
  free(temp);// freeing
  return result; // return result
	
	//return strcpy(malloc(1), "") ; // placeholder
}
