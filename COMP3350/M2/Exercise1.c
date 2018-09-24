/*
 * Author: DeMarcus Campbell
 * COMP 3350-002
 * Programming Exercise 2
 * Module 2 Exercise 1
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 unsigned int binaryToValue(char input){
	 int x = input - 0x30;
	 if ( x != 0 && x != 1 )
		 return -1;
	 else 
		 return x;
 }
 
 unsigned int binaryStringToValue(char* input){
	 int total = 0;
	 int counter = 0;
	 int i = strlen(input) - 1;
	for ( i ; i >= 0 ; i-- ){
		 int value = binaryToValue(input[i]);
		 if ( value == -1 ){
			 total = -1;
			 break;
		 }
		 else if( value == 0 )
			 continue;
		 else
			 total += value << counter;
		 counter++;
	 }
	 return total;
 }
 
 int main(){
	 char* in = malloc(17);
	 printf("Please input a 16-bit binary string: ");
	 scanf("%s", in);
	 if( binaryStringToValue(in) == -1 )
		 printf("The string %s is invalid: %s is not a binary string\n", in, in);
	 else 
		 printf("%d\n", binaryStringToValue(in) );
 }