/*
  DeMarcus Campbell 903885028 dec0013
  hw4.c
  compiled and tested using Ubuntu Terminal
  RUN THIS FILE BEFORE hw4.cpp
  THIS FILE CREATES ALL TEST FILES OPENED IN C++ PROGRAM
*/

#include <stdio.h>
#include <stdlib.h>


int main() {
 int x = 0;
 FILE *fp;
 fp = fopen("long.txt", "w+");
 while ( x != 101 ) {
  fprintf(fp,"%d\n",x); 
  x++;
 }
 fclose(fp);
 fp = fopen("empty.txt","w+");
 fclose(fp);
 fp = fopen("input.txt", "w+");
 for ( int i = 0 ; i < 5 ; i++ ) 
  fprintf(fp, "%d\n", i); 
 fclose(fp);
 int array1[] = {4,13,14,17,23,89};
 int array2[] = {3,7,9,14,15};
 fp = fopen("input1.txt", "w+");
 for( int i = 0 ; i < 6 ; i++ )
  fprintf(fp, "%d\n", array1[i]);
 fclose(fp);
 fp = fopen("input2.txt","w+");
 for ( int i = 0 ; i < 5 ; i++ ) 
  fprintf(fp, "%d\n", array2[i]);
 fclose(fp);
 system("cat empty.txt");
 system("cat long.txt");
 system("echo");
 system("cat input.txt");
 system("echo");
 system("cat input1.txt");
 system("echo");
 system("cat input2.txt");
 system("clear");
 return 0;
}
