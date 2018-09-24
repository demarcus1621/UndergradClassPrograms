/*
 * Author: DeMarcus Campbell
 * COMP 3350-002
 * Programming Exercise 2
 * Module 2 Exercise 2
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
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
 
 unsigned int hexStringToValue(char* input){
	 int total = 0;
	 int counter = 0;
	 int i = strlen(input) - 1;
	for ( i ; i >= 0 ; i-- ){
		 int value = hexToValue(input[i]);
		 if ( value == -1 ){
			 total = -1;
			 break;
		 }
		 else if( value == 0 )
			 continue;
		 else
			 total += value << (counter << 2);
		 counter++;
	 }
	 return total;
 }
 
 int main(){
	 char* in = malloc(17);
	 printf("Please input hexadecimal(base-16) string: ");
	 scanf("%s", in);
	 if( hexStringToValue(in) == -1)
		 printf("The string %s is invalid: %s is not a hexadecimal string", in, in);
	 else
		 printf("%d\n", hexStringToValue(in));
 }