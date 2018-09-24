/*
 DeMarcus Campbell 903885028 dec0013
 hw5.cpp
 Tested using Ubuntu terminal 
*/

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

struct TriviaNode {
 string question;
 string answer;
 int value;
 TriviaNode *next;

 TriviaNode() {
  question = "";
  answer = "";
  value = 0;
  next = NULL;
 }

 TriviaNode( string q, string a, int v, TriviaNode* x) {
  question = q;
  answer = a;
  value = v;
  next = x;
 }
};


class QuestionList {
 private:
  string question;
  string answer;
  int value;
  int counter;
 public:
  TriviaNode* first;
  TriviaNode* last;
  QuestionList();
  bool addNode(string, string, int);
  int checkAnswer(string, string);
  int countCompare(int);
};

QuestionList::QuestionList() {
 counter = 3;
 string q = "How long was the shortest war on record?(Hint: Less than an hour.)";
 int value = 100;
 string a = "38";
 first = new TriviaNode(q, a, value, new TriviaNode());
 first->next->question = "What was the Bank of America's original name?(Hint: Pizza)";
 first->next->answer = "Bank of Italy";
 first->next->value = 50;
 q = "What is the best-selling video game of all time?(Hint: Building)";
 a = "Tetris";
 value = 20;
 last = new TriviaNode(q, a, value, NULL);
 first->next->next = last;
}

bool QuestionList::addNode(string ques, string ans, int val) {
 TriviaNode* temp = new TriviaNode(ques, ans, val, NULL);
 last->next = temp;
 last = last->next;
 counter++;
 return last->question == temp->question;
}

int QuestionList::checkAnswer(string input, string answer) {
 if ( input == answer )
  return 0;
 else 
  return 1;
}
int QuestionList::countCompare(int comp) {
 return comp - counter;
}

#ifdef UNIT_TESTING
 int main() {
  cout << "************Test Driver************" << endl;
  cout << "Unit Testing Function #1: bool addNode(string ques, string ans, int val)\n";
  QuestionList* test = new QuestionList();
  assert(true == test->addNode("How long was the shortest war on record?(Hint: Less than an hour.)", "38", 100));
  cout << "This checks that all values within the first and last node are equal.\n";
  assert(test->first->question == test->last->question);
  assert(test->first->answer == test->last->answer);
  assert(test->first->value == test->last->value);
  cout << "Case 1 passed.\n";
  delete test;
  cout << "Unit Testing Function #2: int checkAnswer(string input, string answer)\n";
  test = new QuestionList();
  cout << "Case 1: Correct Answer" << endl;
  assert(0 == test->checkAnswer("38",test->first->answer));
  cout << "Case 1 passed.\n";
  cout << "Case 2: Incorrect Answer\n";
  assert( 1 == test->checkAnswer("Nope", test->first->answer));
  cout << "Case 2 passed.\n";
  cout << "Case 3: No Answer(Empty string)\n";
  assert( 1 == test->checkAnswer("", test->first->answer));
  cout << "Case 3 passed.\n";
  cout << "\t\tUnit Testing Complete\n";
  cout << "***********************************************\n";
  return 0;
 }
#else 
int main() {
 int totalScore = 0;
 string ques, ans, input, cont, place;
 int val, count;
 QuestionList* qList = new QuestionList();
 do {
  cout << "Input a question to be added to the list: ";
  getline(cin, ques);
  cout << "Input the answer to your given question: ";
  getline(cin, ans);
  cout << "Input the amount of points for the question: ";
  getline(cin, place);
  val = stoi(place);
  if(qList->addNode(ques, ans, val))
   cout << "Question successfully created.\n";
  else
   cout << "Question could not be added to the list.\n";
  cout << "Would you like to continue?(Yes,No): ";
  getline(cin, cont);
 } while ( cont != "No" );
 cout << "How many questions would you like to answer?: ";
 getline(cin, place);
 count = stoi(place);
 if ( count == 0 ) {
  cout << "Warning: You must answer at least one question.\n";
  count++;
 }
 TriviaNode* temp = qList->first;
 for ( int i = 1 ; i <= count ; i++) {
  if ( qList->countCompare(i) > 0 )
   break;
  cout << "Question: " << temp->question << endl;
  cout << "Input your answer: ";
  getline(cin, input);
  if ( qList->checkAnswer(input, temp->answer) != 0 ) {
   cout << "That is not the right answer. The correct answer is: " << temp->answer << endl;
  }
  else {
   cout << "That is correct!";
   totalScore += temp->value;
  }
  temp = temp->next;
 }
 cout << "Your final score is: " << totalScore << endl;
 return 0;
}
#endif
