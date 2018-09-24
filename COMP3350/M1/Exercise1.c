/*
 * Author: DeMarcus Campbell
 * COMP3350-002
 * Programming Assignment 1
 * Module 1 Exercise 1
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 
 /* 
  * This method converts a character representing a binary digit into
  * its integer equivalent.
  * Input: (char) binary digit
  * Output: (unsigned int) value of binary digit
  */
 unsigned int binaryToValue(char input){
	 int x = input - 48;
	 if( x != 1 && x != 0 )
		 return -1;
	 else 
		 return x;
 }
 
 /* 
  * Main function
  * Input: No command line arguments 
  * Output: Standard Out
  */
 int main() {
	 char in;
	 printf("Input desired binary digit(bit): "); 
	 scanf("%s", &in);
	 if( binaryToValue(in) == -1 )
		 printf("The character %s is invalid: %s is not a bit\n", &in, &in);
	 else
		 printf("%d \n", binaryToValue(in));
 }