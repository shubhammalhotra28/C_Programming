#include<stdio.h>
#include<stdlib.h>

int main()
{
 int i; // initialising the variable

 int cel; // initialising the variable
 printf("Fahrenheit-Celsius\n"); // prinitng the statement
 for(i=0;i<=300;i=i+20)
 {
 /* for loop further printing the cel value along with fahrenheit values */
  cel = (5*(i-32))/9;
  printf("%d\t%d\n",i,cel);
  
 }
 return 0; // returning integer 0 ->terminating the program 
}

