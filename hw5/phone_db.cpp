#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <sstream>

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::cin;
using std::endl;

struct person {
  std::string HOME;
  std::string CELL;
  std::string WORK;
  std::string FAX;
  std::string VOIP;  
};

int newContact(std::map<string, person> &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  person a {"", "", "", "", ""};

  std::string fullName = ss.str();
  map.insert(std::pair<string, person>(fullName,a)); 
  return 0;
}

int listNames(std::map<string, person> const &map) {
  for (auto it = map.begin();
       it != map.end(); it++) {
    cout << "Result: " << it->first << endl;
  }
  return 0;
}
/*
int deleteContact(std::map<string, person> const &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
 
  map.erase(fullName);
  return 0;
}
*/
int listNumsOfContact(person contact) {
  if (contact.HOME != "") {
    std::cout << "Result: HOME," + contact.HOME << std::endl;
  }
  if (contact.CELL != "") {
    std::cout << "Result: CELL," + contact.CELL << std::endl;
  }
  if (contact.WORK != "") {
    std::cout << "Result: WORK," + contact.WORK << std::endl;
  }
  if (contact.FAX != "") {
    std::cout << "Result: FAX," + contact.FAX << std::endl;
  }
  if (contact.VOIP != "") {
    std::cout << "Result: VOIP," + contact.VOIP << std::endl;
  }

  return 0;
}

int listNums(std::map<string, person> const &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  //  int itt = map.find(fullName);
  listNumsOfContact(map.find(fullName)->second);
  return 0;
}


int main() {
  
  std::map<string, person> list;
  char c  = ' ';
  //c = getchar();
  while ((c=getchar()) != EOF && c != 'Q' && c != 'q') {
  //command = getchar();
    //std::cout << "Info: command entered =  " << c << std::endl;
    switch(c) {
    case 'C':
      newContact(list);
      break;
    case 'D':
      //      deleteContact(list);
      break;
    case 'L':
      listNames(list);
      break;
    case 'P':
      listNums(list);
      break;

    case 'N':

      break;
    case 'X':

      break;
    case 'R':

      break;
    case 'Q':

      break;
 
    default:

    break;
  }
  }
  return 0;
}