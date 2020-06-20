/* prime-number finding program
Originally by Norman Matloff, UC Davis
http://wwwcsif.cs.ucdavis.edu/~davis/40/gdb_Tutorial.htm
Modified by Mark Ardis, RIT, 11/1/2006

Will report a list of all primes which are less than
or equal to the user-supplied upper bound.
WARNING: There are bugs in this program! */

#include <stdio.h>

int prime[15];  // prime[i] will be 1 if i is prime, 0 otherwise 
int upper_bound; // check all numbers up through this one for primeness

void checkPrime(int k, int prime[]) {

  /* the plan:  see if j divides k, for all values J which are
  themselves prime (no need to try J if it is nonprime), and
  less than or equal to sqrt(K) (if K has a divisor larger
  than this square root, it must also have a smaller one,
  so no need to check for larger ones) */
 
  int j = 2; // declaring and initialising the variable j = 2
  while (j*j<=k)  // looop till j<=(k)^(1/2)
  { 
    if (prime[j] == 1)
    { 
      if (k % j == 0)  
      {
        prime[k] = 0;
        return;
      } // if (k % j == 0) 
    } // if (prime[j] == 1) 
    j++; // incrementing j
  } // while (1) 

  // if we get here, then there were no divisors of k, so it is prime 
  prime[k] = 1;

} // CheckPrime() 

int main() {
  int i; // initialising integer i
  int upper_bound; // initialising the variable
  printf("Enter upper bound:\n"); // displaying the command 
  scanf("%d", &upper_bound);// getting the value from the user
 // upper_bound = 50 ; // As we could not hard code the number 
  prime[1] = 1; 
  prime[2] = 1;
   /* loop to check what all numbers are
   * prime. This is further calling a defined function 
   * called checkPrime.
   */
  for (i = 3; i <= upper_bound; i += 2) {
    checkPrime(i, prime);
    if (prime[i]) // if = true
    {  
      printf("%d is a prime\n", i); // number will be printed
    } // if (prime[i]) 
  } // for (i = 3; i <= upper_bound; i += 2) 
  return 0;// terminating the program with 0
} // main() 
