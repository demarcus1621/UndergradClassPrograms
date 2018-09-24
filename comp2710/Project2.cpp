/*
  DeMarcus Campbell dec0013 903885028
  Written and compiled in Ubuntu Terminal
  Project2.cpp
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include "Project2.h"

using namespace std;

int main() {
 srand(time(0));
 UserInterface ui;
 string emp = "EmployeeData.txt";
 ifstream f(emp.c_str());
 ui = UserInterface(f.good());
 while ( true ) {
  //if ( ui.checkLog() ) 
  // ui.displayActive();
  //else 
   ui.displayIdle();
 }
 return 0;
}
