/*DeMarcus Campbell dec0013 903885028
  Written and compiled in Ubuntu Terminal
  Project1.cpp
*/

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <string>
#include "Project1.h"

using namespace std;


#ifdef UNIT_TESTING
int main() {
 srand(time(0));
 string answer;
 Menu* menuTest = new Menu();
 Character* characterTest = new Character();
 Puzzle* puzzleTest = new Puzzle();
 cout << "This is the test driver for Character methods.\n";
 cout << "Function #1: void getAttributes()\n";
 characterTest->getAttributes();
 cout << "If output was displayed case passed.\n";
 cout << "Function #2: int getSteps()\n";
 assert(20 == characterTest->getSteps());
 cout << "Case passed.\n";
 cout << "Function #3: int getScore()\n";
 assert(2500 == characterTest->getScore());
 cout << "Case passed.\n";
 cout << "Function #4: bool addSteps(int steps)\n";
 assert(true == characterTest->addSteps(10));
 assert(10 == characterTest->getSteps());
 cout << "Case passed.\n";
 cout << "Function #5: bool addIntelligence(int intl)\n";
 assert(true == characterTest->addIntelligence(20));
 cout << "Case passed.\n";
 cout << "Function #6: bool addMoney(int mon)\n";
 assert(true == characterTest->addMoney(20));
 cout << "Case passed.\n";
 cout<<endl;
 cout<<endl;
 cout << "This is the test driver for Puzzle methods.\n";
 cout << "Testing correct answer.\n";
 puzzleTest->askQuestion();
 puzzleTest->checkAnswer("10");
 cout << "Case passed.\n";
 cout << "Testing inccorrect answer.\n";
 puzzleTest->askQuestion();
 puzzleTest->checkAnswer("Hopper Grace");
 cout << "Case passed.\n";
 cout<<endl;
 cout<<endl;
 cout << "This is the test driver for the Menu methods.\n";
 cout << "Function #1: void displayMenu()\n";
 menuTest->displayMenu();
 cout << "Case passed.\n";
 cout << "Function #2: int getChoice()\n";
 cout << "Should output same value that was input.\n";
 cout << menuTest->getChoice() << endl;
 cout << "Case passed.\n";
 cout << "Function #3: void getHighScores()\n";
 cout << "Case #1: The file does not exist => file should be created.\n";
 menuTest->getHighScores();
 cout << "Case passed.\n";
 cout << "Case #2: The file does exist => an array should exist with up to the top 10 high scores.\n";
 assert(true == menuTest->isHighScore());
 cout << "Score is high score.\n";
 menuTest->addScore("TestRun");
 cout << "Score successfully added to list.\n";
 menuTest->getHighScores();
 cout << "Case passed.\n";
 cout << "Function #4: void implementChoice(int choice)\n";
 cout << "Case #1: Input == 1\n";
 menuTest->implementChoice(1);
 cout << "Case passed.\n";
 cout << "Case #2: Input = 2\n";
 menuTest->implementChoice(2);
 cout << "Case pased.\n";
 cout << "Case #3: Input = 3\n";
 menuTest->implementChoice(3);
 cout << "Case passed.\n";
 cout << "Case #4: Input = 4\n";
 menuTest->implementChoice(4);
 cout << "Case passed.\n";
 cout << "Case #5: Non-valid input\n";
 menuTest->implementChoice(-1);
 cout << "Case passd.\n";
 return 0;
}

#else
int main() {
 srand(time(0));
 Menu* menu = new Menu();
 string choice;
 string name;
 cout << "\t\tWelcome to Shelby and Dragons!!!\n";
 cout << "\t\t\tWhat is your name?\n";
 cout << "\n\nName: ";
 getline(cin, name);
 cout<<endl;
 cout<<endl;
 cout << "1: Play Game\n";
 cout << "2: View High Scores\n";
 cout << "3: Quit Games\n";
 cout << "Choice: ";
 getline(cin, choice);
 if (choice == "\n" || choice == ""){
  choice = "0";
  cout << "This is the value.\n";
 }
 switch ( stoi(choice) ) {
 case 1:
  while ( !menu->gameOver() ) {
   menu->displayMenu();
   cout << "Choice: ";
   menu->implementChoice(menu->getChoice());
  }
  cout << "Final Score: " << menu->getScore() <<endl;
  cout<<endl;
  cout<<endl;
  menu->getHighScores();
  cout<<endl;
  cout<<endl;
  if ( menu->isHighScore() ) {
   menu->addScore(name);
   cout << "Congratulations you got a new high score!!!\n";
   cout<<endl;
   cout<<endl;
   menu->getHighScores();
  } 
  cout << "Thank you for playing this game!!\n";
  break;
 case 2:
  menu->getHighScores();
 case 3:
  exit(0);
  break;
 default:
  cout << "Invalid Input!\n";
 }
 delete menu;
 return 0;
} 
#endif
