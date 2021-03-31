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
  //Does not work when: map<string,person>::iterator it
  //replace auto
  for (std::map<string,person>::const_iterator it = map.cbegin();
       it != map.cend(); it++) {
    cout << "Result: " << it->first << std::endl;
    cout << "Info: Work phone: " << it->second.WORK << std::endl;
  }
  return 0;
}

int deleteContact(std::map<string, person> &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  /*
  for (std::map<string,person>::iterator it = map.begin(); it != map.end(); it++) {

  } */
  map.erase(fullName);
  return 0;
}

int listNumsOfContact(person contact) {
  std::cout << "Info: Listing results" << std::endl;

  //.compare did not work, neither did != ""
  if (contact.HOME.compare("") != 0) {
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

int addNumber(std::map<string, person> &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();

  person curContact = map.find(fullName)->second;
  
  std::string type;
  cin >> type;
  
  if (type.compare("WORK") == 0) {
    cin >> curContact.WORK;
    std::cout << "Work Phone: " << curContact.WORK << std::endl;
  }
  else if (type.compare("HOME") == 0) {
    cin >> curContact.HOME;
  }
  else if (type.compare("CELL") == 0) {
    cin >> curContact.CELL;
  }
  else if (type.compare("FAX") == 0) {
    cin >> curContact.FAX;
  }
  else if (type.compare("VOIP") == 0) {
    cin >> curContact.VOIP;
  }
  else {
    std::cout << "Info: Error assigning number type" << std::endl;
  }
  return 0;
}

int delNumber(std::map<string, person> &map) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();

  person curContact = map.find(fullName)->second;

  std::string type;
  cin >> type;
  
  if (type.compare("WORK") == 0) {
    curContact.WORK = ""; 
  }
  else if (type.compare("HOME") == 0) {
    curContact.HOME = "";
  }
  else if (type.compare("CELL") == 0) {
    curContact.CELL = "";
  }
  else if (type.compare("FAX") == 0) {
   curContact.FAX = "";
  }
  else if (type.compare("VOIP") == 0) {
    curContact.VOIP = "";
  }
  else {
    std::cout << "Info: Error deleting number type" << std::endl;
  }
  return 0;

}

int saveList(std::map<string, person> const &map) {

  string name;
  cin >> name;
  std::ofstream outFile(name);
  for (auto it = map.begin();it != map.end(); it++) {
    outFile << "P " << it->first << std::endl;
    outFile << "W " << it->second.WORK << std::endl;
    outFile << "H " << it->second.HOME << std::endl;
    outFile << "C " << it->second.CELL << std::endl;
    outFile << "F " << it->second.FAX << std::endl;
    outFile << "V " << it->second.VOIP << std::endl;
  }
  return 0;
}

int loadList(std::map<string, person> &map) {
  string name;
  cin >> name;
  std::ifstream ifile(name);
  if (!ifile.is_open()) {
    std::cout << "failed to open file" << std::endl;
    return 1;
  }
  //TODO: clear current map
  for (auto it = map.begin();it != map.end(); it++) {
    //code from delNumber once that works
  }
  
  char comm = ' ';
  //for the whole file
  while (ifile >> comm) {
    //if it's a P, create a new person and add any numbers present
    if (comm == 'P') {
      //get their name
      string fullName;
      ifile >> fullName;

      //make the person
      person hold{"", "", "", "", ""};

      //add them to the map
      map.insert(std::pair<string, person>(fullName,hold));

      //for that person add any numbers present
      while (ifile >> comm) {
        if (comm == 'W') {
  	  string numb;
	  ifile >> numb;
	  hold.WORK = numb;
        }
        else if (comm == 'H') {
	  string numb;
	  ifile >> numb;
	  hold.HOME = numb;
        }
        else if (comm == 'C') {
	  string numb;
	  ifile >> numb;
	  hold.CELL = numb;
        }
        else if (comm == 'F') {
	  string numb;
	  ifile >> numb;
	  hold.FAX = numb;
        }
        else if (comm == 'V') {
	  string numb;
	  ifile >> numb;
	  hold.VOIP = numb;
        }
      }
    } //end of inner while loop
    else { //if the command is not a P
      std::cout << "Error reading in data from file" << std::endl;
    }
 }
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
      deleteContact(list);
      break;
    case 'L':
      listNames(list);
      break;
    case 'P':
      listNums(list);
      break;
    case 'N':
      addNumber(list);
      break;
    case 'X':
      delNumber(list);
      break;
    case 'S':
      saveList(list);
      break;
    case 'R':
      loadList(list);
      break; 
    default:

    break;
  }
  }
  return 0;
}
