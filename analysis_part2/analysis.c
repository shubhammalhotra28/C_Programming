// Document Analysis project functions for Part 2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "analysis.h"
#include "unit_tests.h"

// First checks that p_list is not NULL. Returns 0 if p_list is a NULL pointer.
// Then checks that word pointer is not NULL and word is not any empty string.
// Returns 0 if either of the above tests on the passed word fails.
//
// Creates the list if starting a fresh list.
// Searches existing list for a match on the word. Increments word count
// if found. If not found adds the word in alphabetic order.
// Returns 1 if the word was added successfully.
// Returns 0 on failure.
// NOTE -- this function makes no assumption on upper or lower case. That is handled by read_file.
// For simplicity all words passed from the unit tests are all lower case only.
int process_word ( struct linked_list *p_list, char *word )
{

	if(p_list==NULL || word==NULL || *word=='\0')
	{

		// if the conditions are not satisfied
    		return 0;
  	}
	else
	{
   		 if(p_list->p_head==NULL)
		 {		// if the list is empty initially
      				add_node_at_head(p_list,word); // adding it to the first ptr at head
      				return 1;// success code of adding the word
   		 }
    	int x=0;
    	x=find_word(p_list,word);// finding the word if it already exists in the list
    	if(x==1)
	{
      		p_list->p_current->one_word.word_count++;// if found then increasing the count
       		return 1;
    	}
    	else if(x==0)
	{
      		int a=add_node_after_current(p_list,word);// adding the word after the current node
      		return a;// if the word was added or not
    	}
    	else
	{	
      		return 0;// if the word could not be found and added
    	}
  	}
}

// Helper function for read_file to validate inputs.
static FILE *validate_read_file_parameters( struct linked_list *p_list, char *file_name )
{
        if ( p_list == NULL || file_name == NULL || *file_name == '\0' ) // if NULL list or if a bad or empty file name string return 0
                return 0 ;

        return fopen( file_name, "r" ) ;
}

// First checks that the passed string with the file name is not a NULL pointer and is not an empty string.
// Also checks that the passed pointer to the linked_list struct is not a NULL pointer.
// Returns 0 if any of the above tests fail.
// returns 0 if the file cannot be read or if the file does not contain any words as defined for this project.
// returns the number of words if the file was found, opened successfully, and it contained at least one valid word.
// NOTE -- this function MUST convert all words read to lower case only! e.g "First" becomes "first"
int read_file( struct linked_list *p_list, char *file_name )
{


	FILE *input_file = validate_read_file_parameters( p_list, file_name ) ;
        if ( input_file == NULL )
	  return 0 ;
          // Now read and process the entire file.
        char one_char ;// storing the char in the files
        char buffer[ MAX_WORD + 1 ] ;// storing each word in the array
        int index = 0 ;// the index of the array
        int word_count = 0 ;// counting the number of words
	int count=0;
	int xtra=0;
	int prev;
        for ( one_char = fgetc( input_file ) ; one_char != EOF ; one_char = fgetc( input_file ) )// going over all the characters in the loop
        {
	  if(one_char==' ' || one_char=='\n' || one_char=='\t'){// if the character is a space, tab or a newline
	    count++;
	  }
	  if((prev==' ' || prev== '\n' || prev=='\t') && (one_char==' ' || one_char=='\t' || one_char=='\n')){
	    xtra++;
	  }
	  if(one_char>=65 && one_char<=90){// if it is an Upper case letter
	    buffer[index]=one_char+32;
	    index++;
	  }
	  else if(one_char>=97 && one_char<=122){// if it a lower case letter
	    buffer[index]=one_char;
	    index++;
	  }
	  if(count-xtra>0){// if the word is complete
	    count=0;
	    xtra=0;
	    word_count++;// increasing the word count
	    buffer[index]='\0';// terminating character of the word
	    process_word(p_list,buffer);// adding the word in the list
	    index=0;
	  }
	  prev=one_char;
	}
        // Process all of the characters in the file one at a time.
        fclose( input_file ) ;
        return word_count ;

}

// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no first word meaning p_head == NULL (empty list).
// Otherwise, returns a struct with the first unique word and its number of occurrences in the text file.
struct word_entry get_first_word( struct linked_list *p_list )
{
	struct word_entry entry ;
	
	if(p_list==NULL || p_list->p_head==NULL || p_list->p_current == NULL)
	{	
		entry.word_count = 0 ;		// so set word count to be 0
		entry.unique_word = NULL;
	}
	else
	{
		entry = p_list->p_head->one_word; // storing the data from thew head of the list
	}
	return entry ;
}

// Returns 0 in the word_count field if p_list is NULL.
// Returns 0 in the word_count field if no next word (previously reached end of list or it is an empty list).
// Otherwise, returns a struct with the next unique word and its number of occurrences in the text file.
struct word_entry get_next_word( struct linked_list *p_list )
{
	struct word_entry entry ;
	
	if(p_list == NULL || p_list->p_head == NULL)
	{
		// if list is empty
		entry.word_count = 0; // setting word count to be 0
		entry.unique_word = NULL; // setting the unique word to be NULL
	}
	else if (p_list->p_current == NULL)
	{
		// if the next node is NULL
			
		entry.word_count = 0; // word count  = 0;
		p_list->p_current = p_list->p_tail; // current should point to the tail
	}

	else
	{
		// otherwise store the value of current pointer
		entry = p_list->p_current->one_word;
		p_list->p_current = p_list->p_current->p_next; // incrementing to the next 

	}
	//entry.word_count = 0 ;		// cover end of list case.
	
	return entry ; // return the updated value of entry
}

// Returns 0 in the word_count field if no previous word (was already at beginning of the list or it is an empty list).
// Otherwise, returns a struct with the previous unique word and its number of occurrences in the text file.
struct word_entry get_prev_word( struct linked_list *p_list )
{

	struct word_entry entry ; //declarijng the variable
	entry.unique_word = ""; // declaring and intialisation with empty string
	if(p_list==NULL || p_list->p_current == p_list->p_head)
	{
		// if the p_list is NULL or the head and current are pointing at the same location
		entry.word_count = 0 ;		// cover end of list case.
	}

	else
	{
		p_list->p_current = p_list->p_current->p_previous; // point to the prev
		entry = p_list->p_current->one_word; // store the one_word
	}
	return entry ; // return entry
}

// Returns 0 in the word_count field if the p_list pointer is NULL.
// Returns 0 in the word_count field if no last word meaning p_tail == NULL (empty list).
// Otherwise, returns a struct with the last unique word and its number of occurrences in the text file.
struct word_entry get_last_word( struct linked_list *p_list )
{
	struct word_entry entry ;
	
	if(p_list==NULL || p_list->p_tail == NULL)
	{	// checking if the list or tail is null
		entry.word_count = 0; // set the owrd count to be 0
	}
	else
	{
		// update entry with the value
		
		entry = p_list->p_tail->one_word; // storing the value of last word	
	}
	return entry ; // return the updated entry value
}

// First check the p_list is not NULL. Return 0 if it is NULL.
// Return 0 if the list is empty (e.g. p_head is NULL).
// Writes the sorted unique word list to a csv file.
// Receives the linked list pointer and the name of the file to be created.
// Returns 1 on a successful write of the file.
// Returns 0 on any failure.
// Test for a NULL or empty string in the file_name. Return 0 for failure if NULL or empty.
// Be sure to test for failure to open the file, failure to write to the file, and failure to close.
// You must have a header row exactly like this (without the quotes): "word,count"
// You must have one row for each unique word and its count (e.g. without quotes "student,5").
// It must be in sorted order and must be the complete list.
int write_unique_word_list_to_csv_file(  struct linked_list *p_list, char *file_name )
{
	int status = 0 ; // declaring and initialising 
	int total=0; // declaring and intialising
	if ( p_list == NULL || p_list->p_head == NULL )
		return status ;
	if ( file_name == NULL || *file_name == '\0' )
		return status ;
	FILE *out_file = fopen( file_name, "w" ) ;
	if ( out_file )// if the file is not valid
	{
	  struct word_entry entry; // initialisation
	  p_list->p_current=p_list->p_head;// currently the first element is the head
	  while(p_list->p_current!=NULL){// till the end of the list
	    if(p_list->p_current->p_next!=NULL){// NULL
	      entry=get_next_word(p_list);// next word is being updated
	      fprintf(out_file,"%s,%d\n",entry.unique_word,entry.word_count);// writing into the file
	      total+=entry.word_count; // incrementing the total
	    }else{// if it is the end of the list
	      entry=get_last_word(p_list); // updating the entry
	      fprintf(out_file,"%s,%d\n",entry.unique_word,entry.word_count);// adding the last word to the list
	      total+=entry.word_count; // incrementing
	    }
	    p_list->p_current=p_list->current->p_next;// incrementing
	  }
	  status=1;// setting sattus = 1;
	  fclose( out_file ) ; // closing the file
	}
	return status ; // return
}
