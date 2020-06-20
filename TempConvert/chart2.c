#include<stdio.h>
#include<stdlib.h>

int main()
{
 // initialising the variable
 int i;

 float cel,fah; // initialising the variable
 printf("Fahrenheit-Celsius\n"); // prinitng the statement
 for(i=0;i<=300;i=i+20)
 {
 /* for loop further printing the cel value along with fahrenheit values */
  fah = i;
  cel = (5.0*(fah-32))/9.0;
  printf("%d\t%.1f\n",i,cel);
  
 }
 return 0; // returning integer 0 ->terminating the program 
}

