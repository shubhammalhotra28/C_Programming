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
 * Room event information
 * 	Total number of events that have been logged
 * 	Index of the newest event (if any)
 * 	Index of the oldest event (if any)
 * 	Buffer of (up to) MAX_EVENTS most recent events
 */
struct room_t {
	int event_count ;
	int newest ;
	int oldest ;
	struct event_t buffer[MAX_EVENTS] ;

} ;

/*
 * Rooms being monitored.
 */
#define MAX_ROOMS (5)
static struct room_t rooms[MAX_ROOMS] ;

/*
 * Local support functions (static).
 * Feel free to add more to make your work easier!
 */
static void process_a_reading(struct reading_t reading,int i) ;
static void init_rooms() ; 
void read_level1(struct reading_t reading);
void level_2(struct reading_t reading);

void print_level_2(struct room_t rooms[MAX_ROOMS]);
void printing(int i);
//void printing(struct room_t* rooms,int i);
/*
 * Main driver function.
 *
 * First, initialize global data structures (rooms array).
 *
 * Next, read lines of text representing readings, parse these, and if there
 * are no syntax errors, record the associated events. Syntactically incorrect
 * input reading lines are silently discarded.
 */

int j = 0; // declaring and intialising a gloabl variable

int main()
{
	char next_line[MAX_LINELENGTH+1] ;
	struct reading_t reading ;

	init_rooms() ;
	/*
	 * Read a line of text into next_line, then attempt to parse
	 * it as a reading line. If the line is parsable, process it according to the
	 * specification for the appropriate level.
	 * See hs_util.h for useful utility functions
	 */
	/* Your code here*/
	
	int i = 0; // initialising int
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
			printf("%d total room events\n",rooms[reading.room_id].event_count);
		}
		process_a_reading(reading,reading.room_id); // function calling
		i++;	// increment i
	}
	return 0 ;
}

/*
 * Given a reading, process the included event for the room in the reading.
 * T_PRINT readings are really commands; once executed they are discarded.
 * For all other readings check to see whether an alert should be printed,
 * then add the event as the newest event in the room's circular buffer.
 */


static void process_a_reading(struct reading_t reading,int i)
{
	/* Your code here */
	if(reading.event.event_id == T_PRINT) // if it has a 9
	{
		
		printing(i); // calling the helper function
	 
		return; // return 
	}
	
	struct event_t buffer_ref; // creating instance of type event_t

	rooms[i].event_count++; // incrementing the count
       		
	rooms[i].newest = rooms[i].event_count%(MAX_EVENTS); // setting the newest

	// check condition for oldest to be updated

	if(rooms[i].newest%MAX_EVENTS==0)
	{
		rooms[i].oldest = 0;
	}
	else
	{
		rooms[i].oldest = rooms[i].newest+1;
	}
	
	buffer_ref.sensor = reading.event.sensor; // updating the values	
	strcpy(buffer_ref.time_stamp,reading.event.time_stamp);		// updating the values

	buffer_ref.event_id = reading.event.event_id; // updating the values
	buffer_ref.event_info = reading.event.event_info; // updating the values
	rooms[i].buffer[rooms[i].newest] = buffer_ref; // updating the values

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
}
/*
 * ************ HELPER FUNCTION *****************************************
 * This is the main funtion called to get the required result
 * in an appropraiate form.
 * It is using the help of the oldest and the newest 
 * to get thr corret output
 */
void printing(int j)
{
	int i = 0; // intialising the int
	int size = sizeof(rooms)/sizeof(rooms[0]); // getting the size
	if(rooms[j].newest > rooms[j].oldest) // check
	{
		for(i=size-1;i>=0;i--) // loop
		{
		
			if(rooms[j].buffer[i].event_id == T_TEMPERATURE)
			{
				printf("Sensor %d @ %s temperature reading %d degrees\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
			}
			else if(rooms[j].buffer[i].event_id == T_CO)
			{
				printf("Sensor %d @ %s carbon monoxide reading %d PPB\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
			}
			else if(rooms[j].buffer[i].event_id == T_INTRUDER)
			{
				printf("Sensor %d @ %s intruder alert\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp);
			}
		}
	}
	else // else
	{
		for(i=rooms[j].newest;i>=0;i--) // loop
		{
	
			if(rooms[j].buffer[i].event_id == T_TEMPERATURE)
			{
				printf("Sensor %d @ %s temperature reading %d degrees\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
			}
			else if(rooms[j].buffer[i].event_id == T_CO)
			{
				printf("Sensor %d @ %s carbon monoxide reading %d PPB\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
			}
			else if(rooms[j].buffer[i].event_id == T_INTRUDER)
			{
				printf("Sensor %d @ %s intruder alert\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp);
			}
		}
		
		for(i=size-1;i>=rooms[j].oldest;i--) // loop
		{
	
		if(rooms[j].buffer[i].event_id == T_TEMPERATURE)
		{
			printf("Sensor %d @ %s temperature reading %d degrees\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
		}
		else if(rooms[j].buffer[i].event_id == T_CO)
		{
			printf("Sensor %d @ %s carbon monoxide reading %d PPB\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp,rooms[j].buffer[i].event_info);
		}
		else if(rooms[j].buffer[i].event_id == T_INTRUDER)
		{
			printf("Sensor %d @ %s intruder alert\n",rooms[j].buffer[i].sensor,rooms[j].buffer[i].time_stamp);
		}
	}


}
}
/*
 * Initialize the information on all rooms so that no rooms
 * have any events associated with them.
 */
static void init_rooms()
{
	int room_id ;

	/*
	 * Initialize rooms array so that all rooms have no
	 * events associated with them.
	 */

	for( room_id = 0 ; room_id < MAX_ROOMS ; room_id++ ) {
		rooms[room_id].event_count = 0 ;
		rooms[room_id].newest = 0 ;
		rooms[room_id].oldest = 0 ;
	}
}
void read_level1(struct reading_t reading){

	if(reading.event.event_id == T_TEMPERATURE)
	{
	
		printf("Room %d / Sensor %d: %s: temperature reading %d degrees\n",reading.room_id,reading.event.sensor,reading.event.time_stamp,reading.event.event_id,reading.event.event_info);
	}//printf("reading check %d\n",reading.room_id);	
	else if (reading.event.event_id == T_CO)
	{
		printf("Room %d / Sensor %d: %s: carbon monoxide reading %d PPB \n",reading.room_id,reading.event.sensor,reading.event.time_stamp,reading.event.event_id,reading.event.event_info);
	}
	
	else if (reading.event.event_id == T_INTRUDER)
	{

		printf("Room %d / Sensor %d: %s: intruder alert \n",reading.room_id,reading.event.sensor,reading.event.time_stamp);
	}
	else if (reading.event.event_id== T_PRINT){
		
		printf("Room %d / Sensor %d: %s: print\n",reading.room_id,reading.event.sensor,reading.event.time_stamp);
	}
}
/*
 * print_level_2 -> taking hte array of rooms created globally.
 * it is just accessing the value of very first index and 
 * looping across the buffer which is an array of event_t
 * and printing the required result.
 *
 */

void print_level_2(struct room_t rooms[MAX_ROOMS])
{	
	printf("*****\n");
	printf("Triggered by sensor %d\n",rooms[0].buffer[0].sensor);
	printf("%d total room events\n",rooms[0].event_count);		
		


	int i;	
	for(i = 4;i>=0;i--)
			
	{
		if(rooms[0].buffer[i].event_id==1)
		{
			printf("Sensor %d @ %s temperature reading %d degrees\n",rooms[0].buffer[i].sensor,rooms[0].buffer[i].time_stamp,rooms[0].buffer[i].event_info);
		
		}
		else if(rooms[0].buffer[i].event_id==2)
		{
			printf("Sensor %d @ %s carbon monoxide reading %d PPB\n",rooms[0].buffer[i].sensor,rooms[0].buffer[i].time_stamp,rooms[0].buffer[i].event_info);
		}
			
		else 		
		{	
			printf("Sensor %d @ %s intruder alert\n",rooms[0].buffer[i].sensor,rooms[0].buffer[i].time_stamp);

		}

	}
}

