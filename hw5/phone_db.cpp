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
  std::string fullName = ss.str();

  if (map.find(fullName) == map.end()) {
    person a {"", "", "", "", ""};
    map.insert(std::pair<string, person>(fullName,a));
  }
  else {
    std::cout << "Error: Contact already exists" << std::endl;
  }
  return 0;
}

int listNames(std::map<string, person> const &map) {
  //Does not work when: map<string,person>::iterator it
  //replace auto
  for (std::map<string,person>::const_iterator it = map.cbegin();
       it != map.cend(); it++) {
    cout << "Result: " << it->first << std::endl;
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
  
  if (map.erase(fullName) == 1) {
    std::cout << "Contact deleted" << std::endl;
  }
  else {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
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

int isValidType(string type) {
  if (type.compare("WORK") == 0 || type.compare("HOME") == 0 ||
    type.compare("CELL") == 0 || type.compare("FAX") == 0 ||
      type.compare("VOIP") == 0) {
    return 0;
  }
  return 1;
}

int isValidNum(string num) {
  std::string valids = "0123456789";
  //std::string cur = "";
  char curc = ' ';
  for (int i = 0; i < (int) num.length(); i++) {
    //cur = num.substr(i,i);
    curc = num.at(i);
    string cur(1, curc);
    std::cout << "Info: analyzing " << cur << std::endl;
    if (i == 0 || i == (int) num.length()-1) {
      if (valids.find(cur) == std::string::npos) {
	std::cout << "Info: Error found at bounds" << std::endl;
	return 1;
      }
    }
    else if (valids.find(cur) == std::string::npos && (cur.compare("-") != 0)) {
      std::cout << "Info: Error in middle" << std::endl;
      return 1;
    }
  }
  std::cout << "Info: Succesful read" << std::endl;
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

  if (map.find(fullName) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }

  person *curContact = &(map.find(fullName)->second);
  std::string type;
  cin >> type;

  if (isValidType(type) != 0) {
    std::cout << "Error: Invalid phone number type" << std::endl;
    return 1;
  }

  std::string num;
  cin >> num;

  if (isValidNum(num) != 0) {
    std::cout << "Error: Not a valid phone number" << std::endl;
    return 1;
  }
  
  if (type.compare("WORK") == 0) {
    if (curContact->WORK == "") {
      std::cout << "Result: Phone number added" << std::endl;
    }
    else {
      std::cout << "Result: Phone number replaced" << std::endl;
    }
    curContact->WORK = num;
  }
  else if (type.compare("HOME") == 0) {
    if (curContact->HOME == "") {
      std::cout << "Result: Phone number added" << std::endl;
    }
    else {
      std::cout << "Result: Phone number replaced" << std::endl;
    }
    curContact->HOME = num;
  }
  else if (type.compare("CELL") == 0) {
    if (curContact->CELL == "") {
      std::cout << "Result: Phone number added" << std::endl;
    }
    else {
      std::cout << "Result: Phone number replaced" << std::endl;
    }
    curContact->CELL = num;
  }
  else if (type.compare("FAX") == 0) {
    if (curContact->FAX == "") {
      std::cout << "Result: Phone number added" << std::endl;
    }
    else {
      std::cout << "Result: Phone number replaced" << std::endl;
    }
    curContact->FAX = num;
  }
  else if (type.compare("VOIP") == 0) {
    if (curContact->VOIP == "") {
      std::cout << "Result: Phone number added" << std::endl;
    }
    else {
      std::cout << "Result: Phone number replaced" << std::endl;
    }
    curContact->VOIP = num;
  }
  else {
    std::cout << "Info: Error assigning number type" << std::endl;
    std::cout << "Error: Invalid phone number type" << std::endl;
    return 1;
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
  if (map.find(fullName) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  person *curContact = &(map.find(fullName)->second);

  std::string type;
  cin >> type;
  
  if (type.compare("WORK") == 0 && curContact->WORK != "") {
    curContact->WORK = ""; 
  }
  else if (type.compare("HOME") == 0 && curContact->HOME != "") {
    curContact->HOME = "";
  }
  else if (type.compare("CELL") == 0 && curContact->CELL != "") {
    curContact->CELL = "";
  }
  else if (type.compare("FAX") == 0 && curContact->FAX != "") {
   curContact->FAX = "";
  }
  else if (type.compare("VOIP") == 0 && curContact->VOIP != "") {
    curContact->VOIP = "";
  }
  else {
    std::cout << "Info: Error deleting number type" << std::endl;
    std::cout << "Error: No phone number of that type" << std::endl;
    return 1;
  }
  return 0;

}

int saveList(std::map<string, person> const &map) {

  string name;
  cin >> name;
  std::ofstream outFile(name);
  if (outFile.is_open() == false) {
    std::cout << "Error: Could not open output file" << std::endl;
  }
  
  
  for (auto it = map.begin();it != map.end(); it++) {
    outFile << "P " << it->first << std::endl;
    if (it->second.WORK != "") {
      outFile << "W " << it->second.WORK << std::endl;
    }
    if (it->second.HOME != "") {
      outFile << "H " << it->second.HOME << std::endl;
    }
    if (it->second.CELL != "") {
      outFile << "C " << it->second.CELL << std::endl;
    }
    if (it->second.FAX != "") {
      outFile << "F " << it->second.FAX << std::endl;
    }
    if (it->second.VOIP != "") {
      outFile << "V " << it->second.VOIP << std::endl;
    }


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
  
  //Clear current map
  for (auto it = map.begin();it != map.end(); it++) {
    map.erase(it->first);
  }
  
  char comm = ' ';
  //for the whole file
  while (ifile >> comm) {
    bool later = false;
    //if it's a P, create a new person and add any numbers present
    if (comm == 'P' || later) {
      later = false;
      std::cout << "creating contact" << std::endl;
      //get their name
      string fullName;
      ifile >> fullName;

      //make the person (cannot initialize blank)
      person *hold{"e", "e", "e", "e", "e"};
      hold->HOME = "";
      hold->WORK = "";
      hold->CELL = "";
      hold->FAX = "";
      hold->VOIP = "";
      //add them to the map
      map.insert(std::pair<string, person>(fullName,hold));

      //for that person add any numbers present
      while (ifile >> comm) {
	std::cout << "For " << fullName << " adding numbers" << std::endl;
        if (comm == 'W') {
  	  string numb;
	  ifile >> numb;
	  hold->WORK = numb;
        }
        else if (comm == 'H') {
	  string numb;
	  ifile >> numb;
	  hold->HOME = numb;
        }
        else if (comm == 'C') {
	  string numb;
	  ifile >> numb;
	  hold->CELL = numb;
        }
        else if (comm == 'F') {
	  string numb;
	  ifile >> numb;
	  hold->FAX = numb;
        }
        else if (comm == 'V') {
	  string numb;
	  ifile >> numb;
	  hold->VOIP = numb;
        }
	else if (comm == 'P') {
	  later = true;
	}
	else {
	  std::cout << "Error: Invalid database file" << std::endl;
	  return 1;
	}
      }
      std::cout << "Ending numbers for that contact" << std::endl;
    } //end of inner while loop
    else { //if the command is not a P
      std::cout << "Error: Invalid database file (2)" << std::endl;
      return 1;
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
