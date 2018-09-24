/*
 * Author: DeMarcus Campbell
 * COMP3350-002
 * Programming Assignment 1
 * Module 1 Exercise 3
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 
 /*
  * This function converts the integer that is input into a 
  * 32-bit binary integer string
  * Input: (unsigned int) number to be converted to binary
  * Output: (char*) binary string equivalent of input
  */
 char* binaryConvert(unsigned int var){
	 unsigned int x = var;
	 int val;
	 int i = 32;
	 int j;
	 char* array;
	 array = malloc(33);
	 for( j = 0 ; j < 33 ; j++) 
		 array[j] = '0';
	 while( x > 0 && i >= 0 ) {
		 val = x & 1;
		 array[i] = val + 0x30;
		 i--;
		 x = x >> 1;
	 }
	 return(array);
 }
 
 /*
  * Main function
  * Input: No command line arguments
  * Output: Standard Out
  */
 int main() {
	 printf("Enter desired value: ");
	 unsigned int x;
	 scanf("%d", &x);
	 printf("%s\n", binaryConvert(x));
 }