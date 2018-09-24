#include <iostream>
#include "Project1.h"

using namespace std;

int main() {
 Puzzle* x = new Puzzle();
 QuestionNode* temp = x->first;
 while ( temp != nullptr ) {
  cout << temp->question << endl;
  temp = temp->next;
 }
 return 0;
}
