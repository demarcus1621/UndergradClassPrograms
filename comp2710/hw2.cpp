/*
 * DeMarcus Campbell dec0013 903885028
 * hw2.cpp
 * Compiled using G++ on TUX machines "$g++ hw2.cpp"
 * Tested using command "$./a.out" on TUX machine
 */

#include <iostream>

using namespace std;

int main(){
 cout.setf(ios::fixed);
 cout.setf(ios::showpoint);
 cout.precision(2);

 double loanAmount;
 double interestRate;
 double monthlyInterest;
 double paymentRate;
 double principle;
 double placeHolder;
 int monthCounter = 0;

 cout << "Enter the loan amount: ";
 cin >> loanAmount;
 cout << endl;
 cout << "Enter the yearly interest rate: ";
 cin >> monthlyInterest;
 cout << endl;
 cout << "Enter the amount paid per month: ";
 cin >> paymentRate;
 cout << endl;

 monthlyInterest = monthlyInterest / 1200;

 if ( paymentRate <= loanAmount * monthlyInterest ) {
  cout << "This payment rate is too small to pay off the loan \n";
  return 0;
 }

 cout << "\v \n";
 cout << "************************************************\n";
 cout << "\t \t Amoritization Table\n";
 cout << "************************************************\n";
 cout << "Month  Balance   Rate  Payment  Interest  Principle\n";

 while ( loanAmount * monthlyInterest >= 0 ) {
  if ( monthCounter == 0 ) {
   cout << monthCounter << "\t" << loanAmount << "\t N/A \t N/A \t N/A \t N/A \n";
  }
  else if ( loanAmount - principle <= 0 ) {
   placeHolder = loanAmount;
   cout << monthCounter << "\t 0 \t" << monthlyInterest * 100 << "\t" << placeHolder + (loanAmount * monthlyInterest) << "\t"
    << placeHolder * monthlyInterest << "\t" << placeHolder << endl;
   loanAmount -= principle;
   interestRate += (placeHolder * monthlyInterest);
   break;
  }
  else {
   principle = paymentRate - (loanAmount * monthlyInterest);
   placeHolder = loanAmount;
   loanAmount -= principle;
   cout << monthCounter << "\t" << loanAmount << "\t" << monthlyInterest * 100 << "\t" << paymentRate << "\t"
    << placeHolder * monthlyInterest << "\t" << principle << endl;
   interestRate += (placeHolder * monthlyInterest);
  }
  monthCounter++;
 }

 cout << "*************************************************\n";
 cout <<endl;
 cout << "It will take "<< monthCounter << " months to pay off the loan.\n";
 cout << "Total Interest Paid: $" << interestRate << endl;

 return 0;
}
