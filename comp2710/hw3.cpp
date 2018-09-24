/*
DeMarcus Campbell dec0013 903885028
hw3.cpp
compiled using g++ in ubuntu terminal
tested in ubuntu terminal
*/

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <ctype.h>
#include <cassert>
#include <unistd.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int Awins1,Bwins1,Cwins1 = 0;
int Awins2,Bwins2,Cwins2 = 0;
const int NUMTRIALS = 10000;
const int NORMALIZER = 100;
const int AARON_PROBABILITY = 33;
const int BOB_PROBABILITY = 50;

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
 return ( (A_alive && B_alive) || (A_alive && C_alive) || (B_alive && C_alive) );
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
 if ( (rand() % NORMALIZER) < AARON_PROBABILITY ) {
  if ( C_alive )
   C_alive = false;
  else
   B_alive = false;
 }
}

void Bob_shoots(bool& A_alive, bool& C_alive) { 
 if ( (rand() % NORMALIZER) < BOB_PROBABILITY ) {
  if ( C_alive )
   C_alive = false;
  else
   A_alive = false;
 }
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {
 if ( B_alive )
  B_alive = false;
 else
  A_alive = false;
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
 Aaron_shoots1(B_alive, C_alive);
}

void test_at_least_two_alive() {
 cout << "Function Testing #1: at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)\n";
 cout << "Case 1: Aaron, Bob, and Charlie alive. \n";
  assert ( true == at_least_two_alive(true, true, true));
  cout << "Case 1 passed.\n";
 cout << "Case 2: Aaron and Bob alive, Charlie dead. \n";
  assert ( true == at_least_two_alive(true, true, false));
  cout << "Case 2 passed.\n";
 cout << "Case 3: Aaron and Charlie alive, Bob dead. \n";
  assert ( true == at_least_two_alive(true, false, true));
  cout << "Case 3 passed.\n";
 cout << "Case 4: Bob and Charlie alive, Aaron dead. \n";
  assert ( true == at_least_two_alive(false, true, true));
  cout << "Case 4 passed.\n";
 cout << "Case 5: Aaron alive, Bob and Charlie dead. \n";
  assert ( false == at_least_two_alive(true, false, false));
  cout << "Case 5 passed. \n";
 cout << "Case 6: Bob alive, Aaron and Charlie dead. \n";
  assert ( false == at_least_two_alive(false, true, false));
  cout << "Case 6 passed. \n";
 cout << "Case 7: Charlie alive, Aaron and Bob dead. \n";
  assert ( false == at_least_two_alive(false, false, true));
  cout << "Case 7 passed.\n";
 cout << "Case 8: Aaron, Bob, and Charlie dead. \n";
  assert( false == at_least_two_alive(false, false, false));
  cout << "Case 8 passed. \n";
}

void test_Aaron_shoots1() {
 bool Btest, Ctest = true;
 //cout << "Function Testing #2: Aaron_shoots1(Bob_alive, Charlie_alive)\n";
 cout << "Case 1: Charlie and Bob alive.\n";
 Aaron_shoots1(Btest,Ctest);
 if ( Btest && Ctest )
  cout << "Aaron missed.\n";
 else
  cout << "Charlie was hit. \n";
 Btest = true;
 Ctest = false;
 cout<< "Case 2: Bob alive Charlie dead.\n";
 Aaron_shoots1(Btest, Ctest);
 if ( Btest )
  cout << "Aaron missed.\n";
 else
  cout << "Bob was hit.\n";
 Btest = false;
 Ctest = true;
 cout << "Case 3: Charlie alive and Bob dead.\n";
 Aaron_shoots1(Btest, Ctest);
 if ( Ctest )
  cout << "Aaron missed.\n";
 else 
  cout << "Charlie was hit.\n";
} 

void test_Bob_shoots() {
 bool Atest, Ctest = true;
 cout << "Function Testing #3: Bob_shoots(bool A_alive, bool C_alive)\n"; 
 cout << "Case 1: Aaron and Charlie alive.\n";
 Bob_shoots(Atest, Ctest);
 if ( Atest && Ctest )
  cout << "Bob missed.\n";
 else
  cout << "Charlie was hit.\n";
 Atest = true;
 Ctest = false;
 cout << "Case 2: Aaron alive and Charlie dead.\n";
 Bob_shoots(Atest, Ctest);
 if ( Atest )
  cout << "Bob missed.\n";
 else
  cout << "Aaron was hit.\n";
 Atest = false;
 Ctest = true;
 cout << "Case 3: Charlie alive and Aaron dead.\n";
 Bob_shoots(Atest,Ctest);
 if ( Ctest )
  cout << "Bob missed.\n";
 else 
  cout << "Charlie was hit.\n";
}

void test_Charlie_shoots() {
 bool Atest,Btest = true;
 cout << "Function Testing #4: Charlie_shoots(bool A_alive, bool B_alive)\n";
 cout << "Case 1: Aaron and Bob alive.\n";
 Charlie_shoots(Atest,Btest);
 if ( Btest && Atest ) 
  cout << "Charlie missed. \n";
 else 
  cout << "Bob was hit.\n";
 cout << "Case 2: Aaron alive and Bob dead.\n";
 Atest = true;
 Btest = false;
 Charlie_shoots(Atest, Btest);
 if ( Atest )
  cout << "Charlie missed.\n";
 else
  cout << "Aaron was hit.\n";
 cout << "Case 3: Bob alive and Aaron dead.\n";
 Atest = false;
 Btest  = true;
 Charlie_shoots(Atest, Btest);
 if ( Btest )
  cout << "Charlie missed.\n";
 else
  cout << "Bob was hit.\n";
}

void test_Aaron_shoots2() {
 //cout << "Function Testing #5: Aaron_shooots2(bool B_alive, bool C_alive)\n";
 test_Aaron_shoots1();
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

void press_any_key() {
 char ch;
 ch = mygetch();
 if (ch == 0 || ch == 224)
  mygetch();
}

int main() {
 srand(time(0));
 int x = 0;
 cout << "********Welcome to DeMarcus's Duel Simulator********\n";
 test_at_least_two_alive();
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 cout << "Function Testing #2: Aaron_shoots1(bool& B_alive, bool& C_alive) \n";
 test_Aaron_shoots1();
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 test_Bob_shoots();
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 test_Charlie_shoots();
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 cout << "Function Testing #5: Aaron_shoots2(bool& B_alive, bool& C_alive)\n";
 test_Aaron_shoots2();
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 cout << "\t\tTesting Strategy 1\n";
 while ( x < NUMTRIALS ) {
  bool Aaron = true;
  bool Bob = true; 
  bool Charlie = true;
  while ( at_least_two_alive(Aaron, Bob, Charlie) ) { 
   if ( Aaron ) 
    Aaron_shoots1(Bob, Charlie);
   if ( Bob ) 
    Bob_shoots(Aaron, Charlie);
   if ( Charlie )
    Charlie_shoots(Aaron, Bob);
  }
  if ( Aaron )
   Awins1++;
  if ( Bob ) 
   Bwins1++;
  if ( Charlie )
   Cwins1++;
  x++;
 }
 cout << "The results of the 10,000 trials are as follows.: \n";
 cout << "Aaron wins: " << Awins1 << "/10000\n";
 cout << "Bob wins: " << Bwins1 << "/10000\n";
 cout << "Charlie wins: " << Cwins1 << "/10000\n";
 cout << "\t\t End Trial One \n";
 cout << "***********************************************\n";
 cout << "Press any key to continue...\n";
 press_any_key();
 cout << endl;
 cout << "***********************************************\n";
 cout << "\t\tTesting Strategy 2\n";
 x = 0;
 while ( x < NUMTRIALS ) {
  bool Aaron = true;
  bool Bob = true; 
  bool Charlie = true;
  while ( at_least_two_alive(Aaron, Bob, Charlie) ) {
   if ( Bob )
    Bob_shoots(Aaron, Charlie);
   if ( Charlie )
    Charlie_shoots(Aaron, Bob);
   if ( Aaron )
    Aaron_shoots2(Bob, Charlie);
  }
  if ( Aaron )
   Awins2++;
  if ( Bob )
   Bwins2++;
  if ( Charlie )
   Cwins2++;
  x++;
 }
 cout << "The results of the 10,000 trials are as follows.:\n";
 cout << "Aaron wins #2: " << Awins2 << "/10000\n";
 cout << "Bob wins #2: " << Bwins2 << "/10000\n";
 cout << "Charlie wins #2: " << Cwins2 << "/10000\n";
 cout << "\t\tEnd Trial Two \n";
 cout << "***********************************************\n";
 cout << endl;
 if ( Awins2 > Awins1 )
  cout << "Strategy 2 is better for Aaron to follow.\n";
 else
  cout << "Strategy 1 is better for Aaron to follow.\n";
 return 0;
}
