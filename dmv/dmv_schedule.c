/***
 * Functions for the DMV customer scheduling and service application.
 * Implementation file.
 ***/

#include <stdlib.h>
#include "dmv_schedule.h"

/*
 * Actual definition of the line array of service lines.
 */
struct service_line line[NLINES] ;

/*
 * Initialize the service lines so that (a) line[0] has priority 'A'
 * through line[2] having priority 'C' and (b) there are no customers
 * in any line.
 * NOTES: As usual, an empty list is signified by a NULL pointer.
 */
void init_service_lines() {
	// Placeholder for your code
	int service_index=0; // declaring and initialising the variable
	for(service_index=0;service_index<NLINES;service_index++) // loop
	{
		line[service_index].priority = (char)((int)'A'+service_index);
		line[service_index].head_of_line = NULL;
	}

}

/*
 * Return the next ticket number.
 * 	The first customer gets ticket number 1.
 *	The number increases by 1 on each call.
 * Local (static) int ticket holds the current ticket value.
 */
static int ticket = 1 ;
int next_ticket() 
{

	return ticket++ ;	// return tickets
}

/*
 * A new customer arrives with the given <priority> and
 * <ticket_number>. The customer is placed at the end of
 * the appropriate service line.
 */
void new_customer(char priority, int ticket_number) 
{


	if(!line[(int)(priority-'A')].head_of_line) //1st 
	{
		line[(int)(priority-'A')].head_of_line=(struct customer *) malloc(sizeof(struct customer)); // malloc memory
		line[(int)(priority-'A')].head_of_line->ticket_number = ticket_number; // assign
	}
	else
	{
		struct customer *temp = line[(int)(priority-'A')].head_of_line; // temp variable
		while(temp->next_customer) // to find the last pos
		{
			temp = temp->next_customer;
		}
		temp->next_customer =(struct customer *) malloc(sizeof(struct customer));
		temp->next_customer->ticket_number = ticket_number; // assign
	}

}

/*
 * Return the ticket number of the first customer in the
 * line for <priority> after removing the customer from the
 * associated service_line.
 *
 * Return NO_CUSTOMER if there are no customers in the indicated line.
 */
int serve_customer(char priority)
{
	struct customer *temp  = line[priority-'A'].head_of_line;

	if(!temp) // if NULL
	{
		return NO_CUSTOMER;
	}
	line[priority-'A'].head_of_line = line[priority-'A'].head_of_line->next_customer; // next
	int ticket_number = temp->ticket_number; // ticket_number
	free(temp); // free 
	return ticket_number; // return ticket_number.
}

/*
 * Return the ticket number of the first customer in the highest
 * priority line that has customers after removing the customer
 * from the line. 'A' is highest priority and 'C' is lowest.
 *
 * Return NO_CUSTOMER if there are no customers in any of the lines.
 *
 * Example: if there are 0 customers in the 'A' line, 3 customers in the 'B'
 *          line and 2 customers in the 'C' line, then the first customer in
 *          the 'B' line would be removed and his/her ticket number returned.
 */
int serve_highest_priority_customer()
{
	int service_index = 0;
	for(service_index=0;service_index<NLINES;service_index++) // loop
	{
		if(line[service_index].head_of_line) // if found not NULL
		{
			return serve_customer((char)('A'+service_index)); // call and return serve_customer
		}

	}
	return NO_CUSTOMER ; // return NO_CUSTOMER
}

/*
 * Return the number of customers in the service line for <priority>
 */
int customer_count(char priority) 
{
	int count =0; // declaring and initialising the variable
	struct customer *temp = line[(int)(priority-'A')].head_of_line; // temp variable
	while(temp) // loop
	{
		temp = temp->next_customer; // increment
		count++; // incement
	}
	return count; // return count
}

/*
 * Return the number of customers in all service lines.
 */
int customer_count_all() 
{
	int count =0;//initialising and declaring the varizble
	int service_index=0; // declaring and initiialsisng the variable
	for(service_index=0;service_index<NLINES;service_index++) // loop
	{
		struct customer *temp = line[service_index].head_of_line;
		while(temp) // loop
		{
			temp = temp->next_customer; // increment
			count++; // increment
		}
	}

	return count; // return count
}

