// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

// Implement this function first to create an initialized linked list node.
// It must allocate space for the passed string in the one_word structure.
// It must copy the passed string into that structure and sets its word count to 1.
// Assume that the passed word points is not NULL and is not an empty string.
// The calling function is responsible for passing a valid string.
// This function returns a pointer to the allocated node.
struct node *create_node( char *word )
{
	struct node *data = malloc(sizeof(struct node)); //creating a node and allocating memory to it	
	data->one_word.unique_word = malloc(strlen(word)+1);
	strlcpy(data->one_word.unique_word,word,strlen(word)+1);
	//struct word_entry hi; // creating a object for word_entry
	data->one_word.word_count = 1;
	//hi.unique_word = word; // setting the word
	//hi.word_count = 1; // setting the count
	//data->one_word = hi; // setting the word to the pointer(node)
	data->p_previous = NULL; // setting node prev = NULL
	data->p_next = NULL; // setting node next = NULL
	 
	return data; // return on sucessful creation of node
}

// Inserts a node at the beginning of the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the passed p_head and p_current members of p_list.
// p_head and p_current will always point to the newly added node.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
int add_node_at_head( struct linked_list *p_list, char *word )
{

	/*
	 *return 0 if the list is NULL or the word is null
	 * or if the word passed is empty or empty string
	 */

	if(p_list==NULL || word=='\0')
	{
		return 0; 
	}
	if(strlen(word)<1)
	{
		return 0;
	}

	struct node *data; // create a node pointer
	data = create_node(word); // filling data pointer while using the above function
	data->p_next = p_list->p_head;
	if(p_list->p_head==NULL) // if head in the list is NULL
	{
		p_list->p_head = data;// current
		p_list->p_current = p_list->p_head;// same as head
		p_list->p_tail = p_list->p_head;// same point 
	}
	else
	{
		data->p_next = p_list->p_head;
		p_list->p_head->p_previous = data; // setting the head of list = data
		p_list->p_head = data; // setting the current of list = data
		//p_list->p_tail = p_list->p_tail;
		p_list->p_current = p_list->p_head; // setting the tail previous to be list head
		//p_list->p_head->p_next = p_list->p_tail; // setting the head next of the list = tail of the list
	}


	return 1 ;	// Return 1 if successful
}

// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).
int clear_linked_list( struct linked_list *p_list )
{
	struct node* iterator=malloc(sizeof(struct node));
	iterator=p_list->p_head;
	int number_freed=0;
	while (iterator!=NULL){

		p_list->p_head=p_list->p_head->p_next;
		free(iterator->one_word.unique_word);
		free(iterator);
		number_freed++;
		iterator=p_list->p_head;
	}
	p_list->p_tail=NULL;
	p_list->p_current=NULL;
	return number_freed;
}


// Inserts a node after the current pointer in the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Returns 0 for failure if either word test fails.
// Also on failure no change is made to the pointers in p_list.
// On success it returns a 1 and updates at least the p_current member of p_list. p_current points to the newly added node.
// p_head is updated only if p_current is NULL (an empty list).
// p_tail is updated only if the new node is at the end of the list.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
// Hint: if this function is called with a p_current that is NULL (meaning the list is empty)
//       use the add_node_at_head function to create the new node.
int add_node_after_current( struct linked_list *p_list, char *word )
{
	
	if(word==NULL) // if word == NULL
	{
		return 0; // return 0
	}
	
	if(strlen(word)<1) // if word passed is empty string
	{
		return 0; // return 0
	}
	
	if(p_list==NULL) // if p_list == NULL
	{
		return 0; // return 0
	}
	
	struct node *new_node = create_node(word);
  if (p_list->p_current == NULL){
    add_node_at_head(p_list, word);
  }
  else{
    // New Node next, previous
    new_node->p_previous = p_list->p_current;
    new_node->p_next = p_list->p_current->p_next;

    // Next node's previous will be new node
    if (p_list->p_current->p_next != NULL){
      p_list->p_current->p_next->p_previous = new_node;
    }
    // Current node next will be new node
    p_list->p_current->p_next = new_node;

    p_list->p_current = new_node;
    if (p_list->p_current->p_next == NULL){
      p_list->p_tail = p_list->p_current;
    }
  }

	return 1 ;

}


// Searches the linked list for the passed word.
// NOTE -- this function REQUIRES that the linked list has been maintained in English language alphabetical order.
// Definition of match: every letter must match exactly including by case.
// e.g. "A" does NOT match "a". "a " does NOT match "a"
//
// If found it sets the current pointer to the matching node.
// If not found it returns a failure and sets the current pointer to the node just before the
// insertion point (by alphabetic order). Note the special case for a new word that goes at the
// beginning of the list. See the examples below.
//
// Hint: use strcmp to determine sorting order.
//
// If it is found the current pointer is set to the node containing the matching word.
// If it is found this function returns a 1 to indicate success.
//
// If it is not found the current pointer is set to the node just before the insertion point.
// If it is not found the function returns a 0 to indicate failure.
// e.g. the list contains the words "apple", "buy", "cat".
//      Searching for "baby" would set current to the node containing "apple".
//      Searching for "acid" would set current to NULL to indicate that "acid" belongs at the head.
//      searching for "zebra" would set current to the node containing "cat".
//
// Tests on p_list and word: p_list, p_list->head, and word must all not be NULL.
// In addition, word must not be an empty string.
// We must have a valid list with at least one node and we must a valid word to match.
// If any of these conditions are violated this function returns a -1 to indicate invalid input.
int find_word( struct linked_list *p_list, char *word )
{
	if (p_list!=NULL && p_list->p_head!=NULL && word!=NULL && strlen(word)!=0){
		int found=0;
		struct node *iter=malloc(sizeof(struct node));
		iter= p_list->p_head;
		while (iter!=NULL){
			if (strcmp(iter->one_word.unique_word, word)==0){
				found=1;
				p_list->p_current=iter;
				break;
		
			}else if(strcmp(iter->one_word.unique_word,word) > 0){
				if (iter->p_previous== NULL){
					p_list->p_current=NULL;
					break;

				} else{
					p_list->p_current=iter->p_previous;
					break;
				}

			}else{
				p_list->p_current=iter;
				
			}

			iter=iter->p_next;

		}	
		return found;
	}else{
			return -1;

	}
}

