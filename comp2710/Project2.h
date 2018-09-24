/*
  DeMarcus Campbell dec0013 903885028
  Written and compiled in Ubuntu Terminal
  Project2.h
*/

#ifndef PROJECT2_H
#define PROJECT2_H

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Employee;
class Client;

class UserInterface{
 private:
  vector<Employee> employee;
  vector<Client> clients;
  bool isActive;
  bool isLogin;
 public:
  UserInterface();
  UserInterface(bool);
  void displayIdle();
  void displayActive();
  Employee getLogin();
  bool checkLog();
  void implementChoice(int, Employee&);
};

class Employee {
 private:
  string username;
  string password;
  bool isSysAdmin;
 public:
  Employee();
  Employee(string, string, bool);
  Employee(string);
  friend class UserInterface;
  friend bool operator ==( const Employee&, const Employee&);
  bool changePassword();
  Employee addEmployee();
  Client addClient();
  void addAccount(Client);
  void toString();
  string toFile();
};

class Account {
 private:
  int balance;
  int number;
  string type;
 public:
  Account();
  friend class Client;
  Account(int, int, string);
  Account(string);
  int getBalance();
  friend bool operator ==(const Account&, const Account&);
  void toString();
  string toFile();
};

class Client {
 private:
  vector<Account> accounts;
  int social;
  string name;
 public:
  friend class Employee;
  friend class UserInterface;
  friend bool operator ==(const Client&, const Client&);
  Client();
  Client(string, int);
  Client(string);
  int getTotalBalance();
  void makeDeposit(int);
  void addAccount(Account);
  void toString();
  string toFile();
};

UserInterface::UserInterface() {
 isActive = false;
 isLogin = false;
 Employee root("root","toor",true);
 employee.push_back(root);
}

UserInterface::UserInterface(bool x) {
 isActive = false;
 isLogin = false;
 ifstream inStream;
 string data;
 inStream.open("EmployeeData.txt");
 if ( inStream.fail() ) {
  system("touch EmployeeData.txt");
  UserInterface();
 }
 inStream >> data;
 while ( !inStream.eof() ) {
  employee.push_back(Employee(data));
  inStream >> data;
 }
 inStream.close();
 inStream.open ("ClientData.txt");
 if ( inStream.fail() ) {
  system(" touch ClientData.txt");
  return;
 }
 inStream >> data;
 while ( !inStream.eof() ) {
  clients.push_back(Client(data));
  inStream >> data;
 }
 inStream.close();
}

void UserInterface::displayIdle() {
 system("clear");
 cout << "\n\n\t\tPress ENTER to open terminal...\n";
 cout <<endl<<endl;
 string temp;
 cout << "Enter Option: ";
 getline(cin, temp);
 displayActive();
}

void UserInterface::displayActive() {
 system("clear");
 string choice;
 Employee loggedIn;
 while ( !isLogin )
  loggedIn = getLogin();
 if ( loggedIn.isSysAdmin ) {
  cout << endl;
  cout << "1) Modify Password\n";
  cout << "2) Add Client\n";
  cout << "3) Modify Client Information\n";
  cout << "4) Modify Branch Staff\n";
  cout << "5) Log Out\n";
  cout<<endl;
  getline(cin, choice);
 }
 else {
  cout << endl;
  cout << "1) Modify Password\n";
  cout << "2) Add Client\n";
  cout << "3) Modify Client Informaiton\n";
  cout << "4) Log Out\n";
  cout<<endl;
  getline(cin, choice);
 }
 implementChoice(stoi(choice), loggedIn);
}

Employee UserInterface::getLogin() {
 string tempu, tempp;
 cout << "Username: ";
 getline(cin, tempu);
 cout << "Password: ";
 getline(cin, tempp);
 Employee temp(tempu, tempp, false);
 if ( find(employee.begin(), employee.end(), temp) != employee.end() ) {
  isLogin = true;
  temp = *find(employee.begin(), employee.end(), temp);
  return temp;
 }
 isLogin = false;
 return temp; 
}

bool UserInterface::checkLog() {
 return isLogin;
}

void UserInterface::implementChoice(int option, Employee& x) {
 string ch, tempu, tempp; 
 switch (option) {
  case 1: 
   x.changePassword();
   break;
  case 2:
   x.addClient();
   break;
  case 3:
   if (true) {
    cout << "Client Name: ";
    getline(cin, tempu);
    cout << "Client SSN: ";
    getline(cin, tempp);
    Client pH(tempu, stoi(tempp));
    if ( find(clients.begin(), clients.end(), pH) != clients.end() ) {
     pH = *find(clients.begin(), clients.end(), pH);
     cout << "1) Make Deposit\n";
     cout << "2) Withdrawal\n";
     cout << "3) View Account(s) Status\n";
     getline(cin, ch);
     if ( stoi(ch) == 1 || stoi(ch) == 2 ) 
      pH.makeDeposit(stoi(ch));
     else if ( stoi(ch) == 3 ) {
      pH.toString();
     }
     else {
      cout << "Invalid choice\n";
     }
    }
    else {
     cout << "Entered information does not match a current client.\n";
    }
   }
   break;
  case 4:
   if ( x.isSysAdmin ) {
    cout << "Add or Delete Branch Staff: ";
    getline(cin, ch);
    if ( ch == "add" || ch == "Add" )
     x.addEmployee();
    if ( ch == "delete" || ch == "del" || ch == "Del" ) {
     cout << "Employee Username: ";
     getline(cin, tempu);
     cout << "Employee Password: ";
     getline(cin, tempp);
     Employee temp(tempu,tempp, false);
     if ( find(employee.begin(), employee.end(), temp) != employee.end() ) 
      employee.erase(find(employee.begin(), employee.end(), temp));
     else
      cout << "Employee not found.\n";
    }
   }
   else {
    isLogin = false;
    displayIdle();
   }
   break;
  case 5:
   if ( x.isSysAdmin ) {
    isLogin = false;
    displayIdle();
    break;
   }
  default:
   cout << "Invalid option try again.\n";
 }
}

Account::Account() {
 balance = 0;
 number = rand() % 100000000;
 type = "Checking";
}

Account::Account(int bal, int num, string typ) {
 balance = bal;
 number = num;
 type = typ;
}

Account::Account(string line) {
 istringstream iss(line);
 string pH;
 getline(iss, pH, ';');
 balance = stoi(pH);
 getline(iss, pH, ';');
 number = stoi(pH);
 getline(iss, type);
}

int Account::getBalance() {
 return balance;
}

bool operator ==(const Account& x, const Account& y) {
  return x.number == y.number && x.type == y.type;
}

void Account::toString() {
 cout << "Balance: " << balance << endl << "Type: " << type << endl;
}

string Account::toFile() {
 string x = to_string(balance)  + ";" + to_string(number) + ";" + type;
 return x;
}

Client::Client() {
 name = "default";
 social = 000000000;
}

Client::Client(string nam, int soc) {
 name = nam;
 social = soc;
}

Client::Client(string line) {
 istringstream iss(line);
 string ph;
 getline(iss, name, ';');
 getline(iss, ph, ';');
 social = stoi(ph);
 getline(iss, ph);
 int x = stoi(ph);
 ifstream fs;
 fs.open("AccountData.txt");
 if ( fs.fail() )
  return;
 fs >> ph;
 for( int i = 0 ; i < x ; i++ ) {
  accounts.push_back(Account(ph));
  fs >> ph;
 }
 fs.close();
}

bool operator ==(const Client& x, const Client& y) {
 return x.name == y.name && x.social == y.social;
}

int Client::getTotalBalance() {
 int totalTemp = 0;
 for ( int i = 0 ; i < accounts.size() ; i++ ) {
  totalTemp += accounts[i].getBalance();
 }
 return totalTemp;
}

void Client::addAccount(Account a) {
 accounts.push_back(a);
}

void Client::makeDeposit(int option) {
 string tempt, tempnum;
 cout << "Account Type (Checking, Saving, etc.): ";
 getline(cin, tempt);
 cout << "Account Number: ";
 getline(cin, tempnum);
 Account temporary(0, stoi(tempnum), tempt);
 if ( find(accounts.begin(), accounts.end(), temporary) != accounts.end() ) {
  temporary = *find(accounts.begin(), accounts.end(), temporary);
  if ( option == 1 ) {
   cout << "Deposit Amount: ";
   getline(cin, tempnum);
   temporary.balance += abs(stoi(tempnum));
  }
  else if ( option == 2 ) {
   cout << "Witdrawal Amount: ";
   getline(cin, tempnum);
   if ( abs(stoi(tempnum)) >  temporary.balance )
    cout << "Entered amount will cause overdraft! Withdrawal cancelled.\n";
   else
    temporary.balance -= abs(stoi(tempnum));
  }
 }
 else 
  cout << "Provided account does not match any account owned by this client.\n";  
}

void Client::toString() {
 cout << "Name: " << name << endl;
 cout << "SSN: " << social << endl;
 cout << "Account(s): " << endl;
 for ( int i = 0 ; i < accounts.size() ; i++ ) {
  accounts[i].toString();
 }
}

string Client::toFile() {
 string x = name + ";" + to_string(social) + ";" + to_string(accounts.size());
 return x;
}

Employee::Employee() {
 username = "username";
 password = "password";
 isSysAdmin = false;
}

Employee::Employee(string user, string pass, bool status) {
 username = user;
 password = pass;
 isSysAdmin = status;
}

Employee::Employee(string line) {
 istringstream iss(line);
 string temp;
 getline(iss, username, ';');
 getline(iss, password, ';');
 getline(iss, temp);
 if ( temp == "true" || temp == "1")
  isSysAdmin = true;
 else 
  isSysAdmin = false;
}

Employee Employee::addEmployee() {
 if ( !isSysAdmin ) {
  cout << "Only System Administrators have access to this protocol!\n";
  return *this;
 }
 string us, temp;
 bool isSysAdmin;
 cout << "Input Employee Username: ";
 getline(cin, us);
 cout << "Password is set to default \"password\"\n";
 cout << "Is employee a system administrator? Y/N: ";
 getline(cin, temp);
 if ( temp == "Y" || temp == "y" )
  return Employee(us, "password", true);
 return Employee(us, "password", false);
}

bool Employee::changePassword() {
 string temp, ren;
 cout << "Enter your current password: ";
 getline(cin, temp); 
 if ( temp != password ) {
  cout << "Password Incorrect\n";
  return false;
 }
 while ( ren != temp ) {
  cout << "Enter your desired password: ";
  getline(cin, temp);
  cout << "Re-enter your new password: ";
  getline(cin, ren);
 }
 password = temp;
 return true;
}

Client Employee::addClient() {
 string nam, temp;
 int soc;
 cout << "New Client Name: ";
 getline(cin,nam);
 cout << "Client SSN (xxxxxxxxx): ";
 getline(cin, temp);
 soc = stoi(temp);
 return Client(nam, soc);
}

void Employee::addAccount(Client c) {
 string atyp, temp;
 int bal;
 cout << "Account Type: ";
 getline(cin, atyp);
 cout << "Deposit: ";
 getline(cin, temp);
 bal = stoi(temp);
 c.addAccount( Account(bal, rand() % 100000000, atyp) );
 c.toString();
}

bool operator ==(const Employee& x, const Employee& y) {
 return x.username == y.username && x.password == y.password;
}

void Employee::toString() {
 cout << username << endl;
 cout << password << endl;
 cout << isSysAdmin << endl;
}

string Employee::toFile() {
 string x = username + ";" + password + ";" + to_string(isSysAdmin);
 return x;
}

#endif
