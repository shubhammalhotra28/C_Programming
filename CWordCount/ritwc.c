#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define FALSE (0)
#define TRUE  (1)

int main() {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */
	bool lastWasEmpty = false;

	/* REPLACE WITH ADDITIONAL VARIABLE DECLARATIONS YOU NEED */
	char mychar;	
	int ch;  	
	int j = 0;
	/* REPLACE WITH THE CODE FOR WORD COUNT */
	for(ch=getchar();ch!=EOF;ch=getchar()){

	if(ch=='\n'||ch=='\0'){
	tot_lines++;
}
	if(ch==' '|| ch=='\n'){
		mychar = ch;
		if((ch == ' ' || ch == '\0' || ch == '\n') && lastWasEmpty){
					
		}else{
			tot_words++;
			lastWasEmpty = true;
		}
       	       j++; 
	}
       else{
	       lastWasEmpty=false;
       }
	tot_chars++;

}
	printf(" %d	 %d	 %d\n",tot_lines,tot_words,tot_chars);
	return 0 ;
}
