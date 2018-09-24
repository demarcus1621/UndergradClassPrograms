/*
 * Author: Demarcus Campbell
 * COMP3350-002
 * Programming Assignment 1 
 * Module 1 Exercise 2
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 
 /*
  * This function takes in a hexadecimal digit and
  * converts it into its integer equivalent
  * Input: (char) hexadecimal digit
  * Output: (unsigned int) value of hexadecimal digit
  */
 unsigned int hexToValue(char input){
	 int x = input - 0x30;
	 if( x > 9 && x < 17 || x > 22 )
		 return -1;
	 else if( x <= 9 )
		 return x;
	 else {
		 x >> 4;
		 return x - 7;
	 }
 }
 
 /*
  * Main function
  * Input: No command line arguments
  * Output: Standard Out
  */
 int main() {
	 char in;
	 printf("Input hexadecimal(base-16) digit: ");
	 scanf("%s", &in);
	 if( hexToValue(in) == -1 )
		 printf("The character %s is invalid: %s is not a hexadecimal digit.\n", &in, &in);
	 else
		 printf("%d\n", hexToValue(in));
 }