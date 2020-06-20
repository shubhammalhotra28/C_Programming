/*
 * Home Security System
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "hs_config.h"
#include "hs_util.h"

/*
 * An event node on the linked list of events for
 * a room. Consists of an event as gathered from a
 * reading and a link to the next node on the list
 * (if any).
 */
struct evnode_t {
	struct event_t event ;
	struct evnode_t *next ;
} ;

/*
 * Room event information
 * 	The room number.
 * 	Total number of events that have been logged.
 * 	Pointer to the most recent reading's node (if any).
 * 	Pointer to the next room (if any).
 */
struct room_t {
	int room ;
	int ecount ;
	struct evnode_t *event_list_head ;
	struct room_t *next_room ;
} ;

/*
 * Head of the list of rooms being monitored.
 */
static struct room_t *room_list = NULL ;

/*
 * Local support functions (static).
 * You have to fill in the details.
 * Feel free to add more to make your work easier!
 */
static void process_a_reading(struct reading_t reading) ;

static struct room_t *find_room(int room) ;
static struct room_t *add_new_room(int room) ;
static void trim_list(int room, int keep, char timestamp[]) ;

static struct evnode_t *make_event_node() ;
void printing(int j);


/*
 * Main driver function.
 *
 * First, initialize global data structures (rooms array).
 *
 * Next, read lines of text representing readings, parse these, and if there
 * are no syntax errors, record the associated events. Syntactically incorrect
 * input reading lines are silently discarded.
 * 
 * When the program ends, make sure all memory is cleaned up!!
 */
int main() {
	char next_line[MAX_LINELENGTH+1] ;
	struct reading_t reading ;

	/*
	 * Read a line of text into next_line, then attempt to parse
	 * it as a <reading> line. If the line is parsable, get the
	 * last reading structure and process it according to the
	 * specification for the appropriate level.
	 * See hs_util.h for useful utility functions.
	 * 
	 * At the end of the program, clean up any dynamically allocated memory
	 */


	// FILL IN THE BODY
	room_list = (struct room_t *)malloc(sizeof(struct room_t)); // allocating memory
	
	while(read_line(next_line,MAX_LINELENGTH)!=0)	//loop
	{
		parse_string(next_line,&reading); //parsing string
		if(reading.event.event_id == T_PRINT) // if equals 9
		{
			/*
			 * required set of print statements which are required for the result(output).
			*/
			printf("*****\n");
			printf("Home Security System: Room %d @ %s\n",reading.room_id,reading.event.time_stamp);
			printf("Triggered by sensor %d\n",reading.event.sensor);
			struct room_t *found_room = find_room(reading.room_id);
			printf("%d total room events\n",found_room?found_room->ecount:0);
		}
		process_a_reading(reading); // function calling
		
	}



	return 0 ;
}

/*
 * Given a reading, process the included event for the room in the reading.
 * T_PRINT and T_TRIM readings are really commands; once executed they are
 * discarded.
 * For all other readings check to see whether an alert should be printed,
 * then add the event to as the newest event in the room's event list.
 */

static void process_a_reading(struct reading_t reading) {

	
	// FILL IN THE BODY
	if(reading.event.event_id == T_PRINT) // || reading.event.event_id == T_TRIM)
	{
		// prinnt and return
		printing(reading.room_id);
		return;
	
	}

	if(reading.event.event_id == T_TRIM) // || reading.event.event_id == T_TRIM)
	{
		// prinnt and return
		
		struct room_t * room = find_room(reading.room_id);
		trim_list(reading.room_id,reading.event.event_info,reading.event.time_stamp);	
		//room_list->event_list_head = 
		
		static struct room_t *temp = find_room(reading.room_id);       
	
		struct evnode_t * event = temp->event_list_head;
		room_list->event_list_head = event;
		
		
		return;
	
	}


	struct evnode_t *evnode = make_event_node(reading.event); // intialising the pointer of typer evnode_t and making event

	struct room_t * room = find_room(reading.room_id); // initialising pointer of type room_t and finding
	if(!room){ // if check
	room = add_new_room(reading.room_id); // add rom
	struct room_t * temp_room = room_list; // new pointer assigned with room_list
	while(temp_room->next_room){ // loop

		temp_room = temp_room->next_room; // increment
	}

	temp_room->next_room = room; // setting value of next_room
	}
	if(room->event_list_head == NULL){ // if NULL
		room->event_list_head = (struct evnode_t *)malloc(sizeof(struct evnode_t)); // memory creating
		room->event_list_head = evnode; // setting the value
	}
	else{
		
		evnode->next = room->event_list_head; // setting the value 
		room->event_list_head = evnode;

	}

	room->room = reading.room_id; // setting the value

	room->ecount++; // increment the counter
	




	if(reading.event.event_id==T_INTRUDER) // if event_id == 3
	{

		printf("Intruder alert @ %s: room %d / sensor %d.\n",reading.event.time_stamp,reading.room_id,reading.event.sensor);
		
	}
	else if(reading.event.event_id == T_TEMPERATURE && ((reading.event.event_info)>110 || (reading.event.event_info)<50))
	{
		printf("Temperature alert @ %s: room %d / sensor %d / %d degrees.\n",reading.event.time_stamp,reading.room_id,reading.event.sensor,reading.event.event_info);
		
	}

	else if(reading.event.event_id == T_CO && (reading.event.event_info) > 3000)
	{
		printf("Carbon monoxide alert @ %s: room %d / sensor %d / %d PPB.\n",reading.event.time_stamp,reading.room_id,reading.event.sensor,reading.event.event_info);
		
	}




	return ;
}

/*
 * ************ HELPER FUNCTION *****************************************
 * This is the main funtion called to get the required result
 * in an appropraiate form.
 * It is having the value of int within the argument.
 * room id is passed for the specifc output. 
 */

void printing(int j)
{
	int i = 0; // intialising the int
	int size = room_list->ecount;  //sizeof(rooms)/sizeof(rooms[0]); // getting the size
	struct room_t * room = find_room(j);
	if(!room)
	room = add_new_room(j);
	struct evnode_t *temp = room->event_list_head;// assigning the value
	// loop to get the required print statements printed
	while(temp){// loop
			if(temp->event.event_id == T_TEMPERATURE)
			{
				printf("Sensor %d @ %s temperature reading %d degrees\n",temp->event.sensor,temp->event.time_stamp,temp->event.event_info);
			}
			else if(temp->event.event_id == T_CO)
			{
				printf("Sensor %d @ %s carbon monoxide reading %d PPB\n",temp->event.sensor,temp->event.time_stamp,temp->event.event_info);
			}
			else if(temp->event.event_id== T_INTRUDER)
			{
				printf("Sensor %d @ %s intruder alert\n",temp->event.sensor,temp->event.time_stamp);
			}
		
		temp = temp->next; // increment
		i++; // increment
	}
	
}




/*
 * Find the specified <room> in the <room_list>, returning a pointer to the
 * found room_t structure or NULL if there is no such <room> in the list.
 */
static struct room_t *find_room(int room)
{
	struct room_t *the_room ;

	// FILL IN THE BODY
	
	the_room = room_list; // assigning room_list

	while(the_room!=NULL) // loop
	{
		if(the_room->room == room)
		{
			return the_room; // return
		}
		the_room = the_room->next_room; // increment
	}
	return NULL; // return NULL

	//return the_room ;
}

/*
 * Create a new room_t node for <room>, initialize its fields, and append
 * the node to the end of the <room_list>.
 * Returns a pointer to the new room's structure.
 */
static struct room_t *add_new_room(int room) 
{


	struct room_t *new_room = (struct room_t*)malloc(sizeof(struct room_t)); // ptr. to new room structure

	// FILL IN THE BODY
	// all the values are being assigned
	new_room->room = room;
	new_room->ecount = 0;
	new_room->event_list_head = NULL;
	new_room->next_room = NULL;	

//	printf("hello working\n");
//	printf("new_room->room = %d\n",new_room->room);
	
	return new_room ;
}

/*
 * If the <room> is in the <room_list>, trim the room's event node list
 * to at most <keep> entries. As the list is ordered from newest to
 * oldest, the oldest entries are discarded.
 *
 * Whether the room exists or not, and whether or not the list holds
 * anything, the specified "Trim log" message must be printed. Obviously,
 * for a non-existent room nothing is actually trimmed (removed).
 *
 * Note - dynamically allocated space for event nodes removed from
 *        the list must be freed.
 */
static void trim_list(int room, int keep, char timestamp[]) {
//
	// FILL IN THE BODY
	/*
	int count = 0;
	int entry = 0;
	static struct room_t *temp;
	temp = find_room(room);       	
	//= room_list;
	 struct evnode_t * event = temp->event_list_head;
	int i=0;
	////////////////////////
	while(event)
	{
		printf("before trim = %d\n",event->event);
		event = event->next;
	}
	event = temp->event_list_head;
	////////////////////////
	struct evnode_t *temp_evt = event;

	while(i<keep && event)
	{
		temp_evt = event;
		event = event->next;
		i++;
		//temp_evt = event;
	}

//	struct evnode_t *temp_evt = event;
	
	//event->next = NULL;
	//printf("temp->next = %d\n",event->next);
	//printf("temp->next = %d\n",temp_evt->next);
	//struct evnode_t  *h = event;
	temp_evt->next = NULL;
	while(event){
		struct evnode_t * temp_evt_1 = event;
		//(struct evnode_t*)malloc(sizeof(struct evnode_t));	
		//temp_evt = event;
		//printf("temp_evt val of sensor %d\n",temp_evt->event.sensor);
		//temp_evt->event.sensor = event.event.sensor;
		event = event->next;
		//temp_evt_1 = NULL;
		//temp_evt->event.event_id = event->event.event_id;
		//temp_evt->event.sensor = event->event.sensor;
		//temp_evt->event.event_info = event->event.event_info;
		//temp_evt->event.sensor = event->event.sensor;
		//strcpy(temp_evt->event.time_stamp,event->event.time_stamp);
		
		
	//	et number
	//	f(	temp_evt->next == NULL)
	//	{
	//		printf("NULL\n");
	//	}
		//free(temp_evt->event);
		temp_evt_1->next = NULL;
		
		free(temp_evt_1);
		
		
		count++;
	}
	printf("Trim log @ %s: room %d log trimmed to length %d (%d entries removed).\n",timestamp,room,i,count);
	//////////////////
	
	// required print statement
	 struct evnode_t * event_h = temp->event_list_head;

	while(event_h)
	{
		printf("After trim = %d\n",event_h->event);
		event_h = event_h->next;
	}

	*/
	
	/*
	 * ************************************************************************************************
	 * Correct code according to me but if i am doing so then i am getting the segmentation fault
	 * and i dont know what is creating that error.
	 * whereas this should be the final code and be written in this manner.
	 * I had reverted back the changes made as that atleast made my code compiled and run.
	****************************************************************************************************
	*/
		
	
	int count = 0;
	int entry = 0;
	static struct room_t *temp;
	temp = find_room(room);       
	
	struct evnode_t * event = temp->event_list_head;
	
	
	int i=0;
	while(i<keep && event)
	{
		event = event->next;
		i++;
	}

	struct evnode_t * temp_evt; 
	while(event){
		
		temp_evt = event;
		
		event = event->next;
		
		free(temp_evt);
		
	
		count++;
	}
	
	event = NULL;

	
	/*
	int count = 0;
	int entry = 0;
	static struct room_t *temp;
	temp = find_room(room);       	
	//= room_list;
	 struct evnode_t * event = temp->event_list_head;
	int i=0;
	while(i<keep && event)
	{
		event = event->next;
		i++;
	}
	while(event){
		struct evnode_t * temp_evt = event;
		event = event->next;
		temp_evt = NULL;
		free(temp_evt);
		count++;
	}
	*/

	printf("Trim log @ %s: room %d log trimmed to length %d (%d entries removed).\n",timestamp,room,i,count);
	return ;
}

/*
 * Create a new evnode_t node, initialize it using the provided
 * event and a NULL link, and return the pointer to the node.
 */
static struct evnode_t *make_event_node(struct event_t event) {
	struct evnode_t *new_evnode ;

	// FILL IN THE BODY

	struct evnode_t *node = (struct evnode_t*)malloc(sizeof(struct evnode_t));
	// initialise
	//assigning the values
	node->event.sensor = event.sensor;
	node->event.event_id = event.event_id;
	node->event.event_info = event.event_info;
	strcpy(node->event.time_stamp,event.time_stamp);

	node->next = NULL;// setting next to NULL
		

	return node ;//return
}





