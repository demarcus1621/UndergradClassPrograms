/*
 DeMarcus Campbell 903885028 dec0013
 hw4.cpp
 compiled and tested in Ubuntu Terminal
 compilation "$g++ hw4.cpp"
 testing "$./a.out"
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <stdio.h>
#include <termios.h>
#include <ctype.h>
#include <unistd.h>

using namespace std;

ifstream inStream;
ifstream inTestStream; 
ofstream outStream;
ofstream outTestStream;
const int MAX_SIZE = 100;

//READS FILE INPUT AND STORES IN ARRAY DISPLAYS TO STDOUT
int readFile( int inputArray[], ifstream& instream ) {
 int data;
 int index = 0;
 if( instream.eof() )
  return 0;
 instream >> data;
 while ( !instream.eof() ) {
  if ( index >= MAX_SIZE ) {
   cout << "File exceeds max inputs. " << MAX_SIZE <<" lines read from file.\n";
   break;
  }
  inputArray[index] = data;
  cout << inputArray[index] << endl;
  index++;
  instream >> data;
 }
 instream.close();
 return index;
}

//SORTS GIVEN ARRAYS INTO THIRD ARRAY
int sort( int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[] ) {
 int x = 0;
 int outSize = inputArray1_size + inputArray2_size;
 while ( x < inputArray1_size ) {
  outputArray[x] = inputArray1[x];
  x++;
 }
 x = 0;
 while ( x < inputArray2_size ) {
  outputArray[x + inputArray1_size] = inputArray2[x];
  x++;
 }
 for ( int i = 1 ; i < outSize ; i++ ) {
  int k = outputArray[i];
  int j = i - 1;
  while ( j >= 0 && outputArray[j] > k ) {
   outputArray[j + 1] = outputArray[j];
   j = j - 1;
  }
  outputArray[j+1] = k;
 }
}

//WRITES GIVEN ARRAY INTO OUTPUT STREAM FILE
void writeFile( int outputArray[], int outputArray_size, ofstream& outstream ) {
 int x = 0;
 while ( x < outputArray_size ) {
  outstream << outputArray[x] << endl;
  cout << outputArray[x] << endl;
  x++;
 }
 outstream.close();
}

void readFileTestDriver() {
 inTestStream.open("input.txt");
 cout << "Function Testing #1: readFile( int inputArray[]. ifstream& instream )\n";
 cout << "Case 1: Open 5 line file with one input per line.\n"; 
 assert( 5 == readFile( new int[10] , inTestStream ));
 cout << "Case 1 passed.\n";
 inTestStream.close();
 cout << "Case 2: Open empty file.\n";
 inTestStream.open("empty.txt");
 assert(0 == readFile( new int[10], inTestStream ));
 cout << "Case 2 passed.\n";
 inTestStream.close();
 cout << "Case 3: Open file with more inputs than MAX_SIZE constant.\n";
 inTestStream.open("long.txt");
 assert( MAX_SIZE == readFile( new int[MAX_SIZE], inTestStream ));
 cout << "Case 3 passed.\n";
 inTestStream.close();
}

void sortTestDriver() {
 int a[5] = {5,6,7,3,9};
 int b[7] = {7,8,9,4,5,6,3};
 int e[0];
 int testOut[25];
 cout << "Function Testing #2: int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[])\n";
 cout << "Case 1: Two randomly arranged arrays.\n";
 cout << "Array 1: ";
 for (int i = 0 ; i < 5 ; i++) {
  cout << a[i] <<" ";
 }
 cout << "\nArray 2: ";
 for (int i = 0 ; i < 7 ; i++) {
  cout << b[i] <<" ";
 }
 cout << endl;
 assert( 12 == sort(a, 5, b, 7, testOut) );
 cout << "Sorted Array: ";
 for (int i = 0 ; i < 12 ; i++) {
  cout << testOut[i] << " ";
 }
 cout << endl;
 cout << "Case 1 passed. \n";
 int a1[] = {1,2,3,4,5};
 int b1[] = {20,30,45,60,70,95,130};
 int testOut1[25];
 cout << "Case 2: Two respectively sorted arrays.\n";
 cout << "Array 1: ";
 for (int i = 0 ; i < 5 ; i++) {
  cout << a1[i] << " ";
 }
 cout << "\nArray 2: ";
 for ( int i = 0 ; i < 7 ; i++ ) {
  cout << b1[i] << " ";
 }
 cout << endl;
 assert( 12 == sort(a1, 5, b1, 7, testOut1) );
 cout << "Sorted Array: ";
 for ( int i = 0 ; i < 12 ; i++ ) {
  cout << testOut1[i] << " ";
 }
 cout << "\nCase 2 passed.\n";
 int testOut2[25];
 cout << "Case 3: Non-sorted array and empty array.\n";
 cout << "Array 1: ";
 for ( int i = 0 ; i < 5 ; i++ ) {
  cout << a[i] << " ";
 }
 cout << "\nArray 2: Empty\n";
 assert( 5 == sort(a, 5, e, 0, testOut2) );
 cout << "Sorted Array: ";
 for( int i = 0 ; i < 5 ; i++ ) {
  cout << testOut2[i] << " ";
 }
 cout << "\nCase 3 passed.\n";
}

void writeFileTestDriver() {
 cout << "Function Testing #3: writeFile( int outputArray[], int outputArray_size)\n";
 cout << "void writeFile(int outputArray[], int outputArray_size) cannot be unit tested. Must be integration tested.\n";
}

void integrationTestDriver() {
 cout << "Integration Test Functions: void writeFile(int outputArray[], int outputArray_size) and int readFile(int inputArray[], ifstream& inputstream)\n";
 cout << "Case 1: Output an normal array of ints, {2,4,6,47,3} to file \"outTest.txt\" and read the file.\n";
 outTestStream.open("outTest.txt");
 int a[5] = {2,4,6,47,3};
 writeFile(a,  5, outTestStream);
 inTestStream.open("outTest.txt");
 assert( 5 == readFile(new int[5], inTestStream) );
 cout << "Integration Test Case 1 passed\n";
 cout << "Case 2: Output empty file into file \"outTest1.txt\" and read the file.\n";
 outTestStream.open("outTest1.txt");
 writeFile( new int[0], 0, outTestStream);
 inTestStream.open("outTest1.txt");
 assert( 0 == readFile(a, inTestStream) );
 inTestStream.close();
 cout << "Integration Test 2 passed.\n";
}

int mygetch() {
 int ch;
 struct termios oldt, newt;

 tcgetattr( STDIN_FILENO, &oldt);
 newt = oldt;
 newt.c_lflag &= ~(ICANON|ECHO);
 tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 ch = getchar();
 tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
 return ch;
}

void keyPress() {
 char ch;
 ch = mygetch();
 if ( ch == 0 || ch == 224 ) 
  mygetch();
}

int main() {
 string filename;
 int iArray[MAX_SIZE];
 int iArray2[MAX_SIZE];
 int oArray[2 * MAX_SIZE];
 int iArraySize;
 int iArraySize2;
 int oArraySize;
 cout << "********Welcome Demarcus's Sorting Program********\n";
 readFileTestDriver();
 cout << "Press any key to continue...\n";
 keyPress();
 cout << endl;
 sortTestDriver();
 cout << "Press any key to continue...\n";
 keyPress();
 cout << endl;
 writeFileTestDriver();
 cout << "Press any key to continue...\n";
 keyPress();
 cout << endl;
 integrationTestDriver();
 cout << "Press any key to continue...\n";
 keyPress();
 cout << endl;
 cout << "\t\tSorting Algorithm\n";
 cout << "Enter first input file name: ";
 cin >> filename;
 cout << "Attempting to open file: " << filename << endl;
 inStream.open((char*)filename.c_str());
 if ( inStream.fail() ) {
  cout << "Failed to open spcified file." << endl;
  exit(1);
 }
 iArraySize = readFile( iArray, inStream );
 cout << "Enter the second input file name: ";
 cin >> filename;
 inStream.open((char*)filename.c_str());
 cout << "Attempting to open file: " << filename << endl;
 if ( inStream.fail() ) {
  cout << "Failed to open specified file." << endl;
  exit(1);
 }
 iArraySize2 = readFile( iArray2, inStream );
 oArraySize = sort( iArray, iArraySize, iArray2, iArraySize2, oArray );
 cout << "Enter the desired output file name: ";
 cin >> filename;
 outStream.open((char*)filename.c_str());
 if ( outStream.fail() ) {
  cout << "Failed to create specified output file: ";
  exit(1);
 }
 writeFile( oArray, oArraySize, outStream);
 cout << "The sorted list of " << oArraySize << " is:\n";
 for ( int i = 0 ; i < oArraySize ; i++ ) {
  cout << oArray[i] << " ";
 }
 cout << endl;
 cout << "Please check that " << filename << " was successfully created.\n";
 cout << "***************Thank You***************\n";
 return 0;
}
