/*DeMarcus Campbell dec0013 903885028
  Written and compiled in Ubuntu Terminal
  Project1.h
*/

#ifndef PROJECT1_H
#define PROJECT1_H


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Character {
 private:
  int stepsLeft;
  int intelligence;
  int money;
  int score;
 public:
  Character();
  void getAttributes();
  int getSteps();
  int getScore();
  bool gameOver();
  bool addSteps(int steps);
  bool addIntelligence(int intel);
  bool addMoney(int mon);
};

struct HighScore {
 string name;
 int score;
 HighScore(string line);
 void toString();
 int compareTo(HighScore* pointer);
};

struct QuestionNode {
 string question;
 string answer;
 int value;
 QuestionNode* next;
 QuestionNode(string q, string a, int v, QuestionNode* n);
};

class Puzzle {
 private:
  QuestionNode* last;
 public:
  QuestionNode* first;
  Puzzle();
  void askQuestion();
  int checkAnswer(string input);
};

class Menu {
 private:
  int choice;
  string answer;
  Character* player;
  int time;
  ifstream inScores;
  ofstream outScores;
  int chance;
  int score;
  int placeHolder;
  int index;
  Puzzle* puzzle;
  HighScore* array[10];
 public:
  Menu();
  void displayMenu();
  int getChoice();
  void addScore(string name);
  int getScore();
  bool isHighScore();
  void implementChoice(int choice);
  bool isRandomEvent();
  void event();
  void getHighScores();
  bool gameOver();
};

HighScore::HighScore(string line) {
 istringstream iss(line);
 string placeHolder;
 getline(iss, name, ';');
 getline(iss, placeHolder);
 score = stoi(placeHolder);
}

void HighScore::toString() {
 cout << name << "\t" << score << endl;
}

int HighScore::compareTo(HighScore* pointer) {
 return this->score - pointer->score;
}

Menu::Menu() {
 choice = 0;
 player = new Character();
 puzzle = new Puzzle();
 time = 30;
 index = 0;
 chance = rand();
 placeHolder = 0;
}

bool Menu::isHighScore() {
 if ( index < 9 || array == nullptr || array == NULL )
  return true;
 return abs(getScore()) > abs(array[index]->score);
}

bool Menu::gameOver() {
 return time <= 0 || player->gameOver();
}

void Menu::addScore(string name) {
 HighScore* newScore = new HighScore(name + ";" + to_string(getScore()));
 if ( index == 0 )
  array[index] = newScore;
 if ( index < 9 && index != 0 ) { 
  array[index + 1] = newScore;
  index++;
 }
 else if ( array[index]->compareTo(newScore) < 0 )
  array[index] = newScore;
 for ( int i = 1 ; i <= index ; i++ ) {
  HighScore* k = array[i];
  int j = i - 1;
  while ( j >= 0 && array[j]->compareTo(k) < 0 ) {
   array[j + 1] = array[j];
   j -= 1;
  }
  array[j + 1] = k;
 }
 int x = 0;
 outScores.open("HighScores.txt");
 if ( outScores.fail() ) {
  cout << "Failed to open file.\n";
  return;
 }
 while ( x <= index ) {
  outScores << array[x]->name + ";" + to_string(array[x]->score) << endl;
  x++;
 }
 outScores.close();
}

void Menu::displayMenu() {
 cout << endl;
 cout << "Steps Left: " << player->getSteps();
 cout << "\tTime Left: " << time << endl;
 cout << "*********************************************\n";
 cout << "1)Take a step forward\n";
 cout << "2)Read research papers\n";
 cout << "3)Search for dropped money\n";
 cout << "4)View Character Stats\n";
 cout << "5)Quit Game\n";
}

int Menu::getChoice() {
 string placeHolder;
 getline(cin, placeHolder);
 if ( placeHolder == "" || placeHolder == "\n")
  placeHolder = "-1";
 choice = stoi(placeHolder);
 return choice;
}

int Menu::getScore() {
 if ( time > 0 )
  score = player->getScore() * time;
 if ( time <= 0 ) 
  score = player->getScore();
 return abs(score);
}

void Menu::getHighScores() {
 string data;
 inScores.open("HighScores.txt");
 if ( inScores.fail() ) {
  cout << "Failed to open file.\n";
  system("touch HighScores.txt");
  return;
 }
 if ( inScores.eof() ) {
  cout << "There are no recorded HighScores!\n";
  return;
 }
 inScores >> data;
 while ( !inScores.eof() ) {
  if ( index >= 10 ) {
   break;
  }
  array[index] = new HighScore(data);
  index++;
  inScores >> data;
 }
 inScores.close();
 index--;
 for ( int i = 1 ; i <= index ; i++ ) {
  HighScore* k = array[i];
  int j = i - 1;
  while ( j >= 0  && array[j]->compareTo(k) < 0 ) {
   array[j + 1] = array[j];
   j = j - 1;
  }
  array[j + 1] = k;
 }
 for ( int i = 0 ; i <= index ; i++ ) {
  array[i]->toString();
 }
}

void Menu::implementChoice(int choice) {
 switch ( choice ) {
  case 1:
   if(isRandomEvent())
    event();
   else {
    time -= 1;
    cout << "You safely took a step forward towards the end of the hallway.\n";
   }
   player->addSteps(1);
   break;
  case 2:
   cout << "Hmm, a very interesting paper in your major sounds nice!\n Intelligence +2\n";
   player->addIntelligence(2); 
   time -= 2;
   break;
  case 3:
   placeHolder = rand() % 20;
   cout << "It must be your lucky day!\n Money +" << placeHolder << endl;
   player->addMoney(placeHolder);
   time -= 1;
   break;
  case 4:
   player->getAttributes();
   break;
  case 5:
   cout << "GAME OVER\n";
   exit(0);
   break;
  default:
   cout << "Invalid Choice!\n";
 }
}

bool Menu::isRandomEvent() {
 return rand() % 100 < 75;
}

void Menu::event() {
 switch ( rand() % 75 ) {
  case 0 ... 24:
   cout << "You have encountered a puzzle!!\n";
   puzzle->askQuestion();
   cout << "Answer: ";
   getline(cin,answer);
   time -= puzzle->checkAnswer(answer);
   break;
  case 25 ... 34:
   cout << "You have an appointment with one of your professors.\n";
   cout << "Time -1\n";
   cout << "Intelligence +3\n";
   player->addIntelligence(3);
   time -= 1;
   break;
  case 35 ... 44:
   cout << "You met up with a friend to grab lunch.\n";
   cout << "Time -2\n";
   time -= 2;
   break;
  case 45 ... 64: 
   cout << "GRUNT WORK!!!\n";
   cout << "Intelligence -20\n";
   cout << "Time -5\n";
   player->addIntelligence(-20);
   time -= 5;
   break;
  case 65 ... 74:
   cout << "Busy work... You are tasked to grade some students' homework.\n";
   cout << "Time -3\n";
   time -= 3;
   break;
 }
}

Character::Character() {
 stepsLeft = 20;
 intelligence = 100;
 money = 25;
}

void Character::getAttributes() {
 cout << "You have " << stepsLeft << " steps left.\n";
 cout << "You have " << intelligence << " intelligence.\n";
 cout << "You have " << money << " money.\n";
}

int Character::getSteps() {
 return stepsLeft;
}

int Character::getScore() {
 return intelligence * money;
}

bool Character::gameOver() {
 return stepsLeft <= 0 || intelligence <= 0 || money <= 0;
}

bool Character::addSteps(int steps) {
 return stepsLeft -= steps;
}

bool Character::addIntelligence(int intel) {
  return intelligence += intel;
}

bool Character::addMoney(int mon) {
 return money += mon;
}

QuestionNode::QuestionNode(string q, string a, int v, QuestionNode* n) {
 question = q;
 answer = a;
 value = v;
 next = n;
}

Puzzle::Puzzle() {
 first = new QuestionNode("What is 1 + 2 + 3 + 4?", "10", 1, nullptr);
 QuestionNode* temp = new QuestionNode("Who performmed the first ever debugging of a computer?","Grace Hopper", 2, nullptr);
 first->next = temp;
 last = temp;
 temp = temp->next;
 temp = new QuestionNode("What number system is used by computers?","Binary",1, nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("What is the integral of cosine?","Sine",3, nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("What movie are some of today's most popular games based on?", "Battle Royale",5,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Xbox or PlayStation","PlayStation",1,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("What year did America decalare independance?","1776",1,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("\"I love you, you love me\" comes from what children's TV show?","barney",3,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("The Buddha is a native of what country?","India",2,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Leggo my?","Eggo",4,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Game where you collect money and buy property.","Monopoly",2,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("A favorite snack at movie theaters.","Popcorn",3,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Tabletop RPG.","Dungeons and Dragons",4,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Brand of canned spaghetti and ravioli.","Chef Boyardee",4,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("A popular Japanese snack.","Pokki",2,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Atomic makeup of water.","H2O",1,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Newton discovered physics from?","Apple", 5,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp ->next;
 temp = new QuestionNode("The original keyboard layout.","DVORAK", 5,nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("The capital of the United States.","Washington DC", 4, nullptr);
 last->next = temp;
 last = last->next;
 temp = temp->next;
 temp = new QuestionNode("Auburn University's spirit chant.", "War Eagle", 5, nullptr);
 last->next = temp;
 last = last->next;
}

void Puzzle::askQuestion() {
 cout << first->question << endl;
}

int Puzzle::checkAnswer(string input) {
 bool temp = input == first->answer;
 int placeHolder = first->value;
 if ( temp )
  cout << "Hmm, I guess you're smart after all.\n";
 else
  cout << "As I thougt, you're an idiot!\n";
 first = first->next;
 return placeHolder;
}


#endif
