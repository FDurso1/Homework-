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
  std::string name;
  std::string HOME;
  std::string CELL;
  std::string WORK;
  std::string FAX;
  std::string VOIP;  
};

//return the user-inputted full name in proper format last,first
string getFullName() {
  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  return fullName;
}

//returns true if two strings are the same when converted to lowercase
bool isSame(const string &left, const string &right) {
  
  std::stringstream ssLeft;
  for (int i = 0; i < (int) left.length(); i++) {
    ssLeft << std::tolower(left[i]);
  }
  std::string lowLeft = ssLeft.str();
  
  std::stringstream ssRight;
  for (int i = 0; i < (int) right.length(); i++) {
    ssRight << std::tolower(right[i]);
  }
  std::string lowRight = ssRight.str();

  if (lowLeft.compare(lowRight) == 0) {
    return true;
  }
  return false;
}

//returns the string parameter but lowercase
string toLow(string &str) {
  std::stringstream ssLow;
  for (int i = 0; i < (int) str.length(); i++) {
    ssLow << (char) std::tolower(str[i]);
  }
  std::string lowStr = ssLow.str();
  return lowStr;
}

//makes a new contact if one does not exist with that name already
int newContact(std::map<string, person> &map) {
  
  std::string fullName = getFullName();
  std::string lowFull = toLow(fullName);
  
  if (map.find(lowFull) == map.end()) {
    person a {fullName, "", "", "", "", ""};
    map.insert(std::pair<string, person>(lowFull,a));
    std::cout << "Result: Contact created" << std::endl;
    return 0;
  }
  else {
    std::cout << "Error: Contact already exists" << std::endl;
    return 1;
  }
}

//list the names of all contacts
int listNames(std::map<string, person> const &map) {

    for (std::map<string,person>::const_iterator it = map.cbegin(); it != map.cend(); it++) {
       cout << "Result: " << it->second.name << std::endl;
    }
  return 0;
}

//delete a contact if it exists
int deleteContact(std::map<string, person> &map) {
  
  std::string fullName = getFullName();
  std::string lowFull = toLow(fullName);

  if (map.erase(lowFull) == 1) {
    std::cout << "Result: Contact deleted" << std::endl;
    return 0;
  }
  else {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
}

//list all the numbers of a particular contact
int listNums(std::map<string, person> const &map) {

  std::string fullName = getFullName();
  std::string lowFull = toLow(fullName);
  
  if(map.find(lowFull) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  
  person contact = map.find(lowFull)->second;

  if (contact.CELL != "") {
    std::cout << "Result: CELL," + contact.CELL << std::endl;
  }
  if (contact.FAX != "") {
    std::cout << "Result: FAX," + contact.FAX << std::endl;
  }
  if (contact.HOME != "") {
    std::cout << "Result: HOME," + contact.HOME << std::endl;
  }
  if (contact.VOIP != "") {
    std::cout << "Result: VOIP," + contact.VOIP << std::endl;
  }
  if (contact.WORK != "") {
    std::cout << "Result: WORK," + contact.WORK << std::endl;
  }
  return 0;
}

//checks whether a given phone type is valid
int isValidType(string type) {
  if (type.compare("WORK") == 0 || type.compare("HOME") == 0 ||
    type.compare("CELL") == 0 || type.compare("FAX") == 0 ||
      type.compare("VOIP") == 0) {
    return 0;
  }
  return 1;
}

//checks whether a given phone number is valid
int isValidNum(string num) {
  std::string valids = "0123456789";
  char curc = ' ';
  
  for (int i = 0; i < (int) num.length(); i++) {
    curc = num.at(i);
    string cur(1, curc);
    
    if (i == 0 || i == (int) num.length()-1) {
      if (valids.find(cur) == std::string::npos) {
	//if the value at the beginning or end of the number is not a number
	return 1;
      }
    }
    else if (valids.find(cur) == std::string::npos && (cur.compare("-") != 0)) {
      //if the value in the middle of the number is not a number or '-'
      return 1;
    }
  }
  return 0;
}

//adds a number to a contact
int addNumber(std::map<string, person> &map) {
  
  std::string fullName = getFullName();
  std::string lowFull = toLow(fullName);
  
  if (map.find(lowFull) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  person *curContact = &(map.find(lowFull)->second);
  
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
    std::cout << "Error: Invalid phone number type" << std::endl;
    return 1;
  }
  return 0;
}

//deletes a number from a contact
int delNumber(std::map<string, person> &map) {

  std::string fullName = getFullName();
  std::string lowFull = toLow(fullName);
  
  if (map.find(lowFull) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }

  person *curContact = &(map.find(lowFull)->second);
  
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
  std::cout << "Result: Phone number deleted" << std::endl;
  return 0;
}

//saves the list of contacts
int saveList(std::map<string, person> const &map) {

  string name;
  cin >> name;
  std::ofstream outFile(name);
  if (outFile.is_open() == false) {
    std::cout << "Error: Could not open output file" << std::endl;
  }
  
  for (std::map<string,person>::const_iterator cit = map.cbegin(); cit != map.cend(); cit++) {
    outFile << "P " << cit->first << std::endl;

    if (cit->second.name != "") {
      outFile << "N " << cit->second.name << std::endl;
    }
    if (cit->second.WORK != "") {
      outFile << "W " << cit->second.WORK << std::endl;
    }
    if (cit->second.HOME != "") {
      outFile << "H " << cit->second.HOME << std::endl;
    }
    if (cit->second.CELL != "") {
      outFile << "C " << cit->second.CELL << std::endl;
    }
    if (cit->second.FAX != "") {
      outFile << "F " << cit->second.FAX << std::endl;
    }
    if (cit->second.VOIP != "") {
      outFile << "V " << cit->second.VOIP << std::endl;
    }
  }
  return 0;
}

//recovers a list of contacts
int loadList(std::map<string, person> &map) {
  string name;
  cin >> name;
  std::ifstream ifile(name);
  if (!ifile.is_open()) {
    std::cout << "failed to open file" << std::endl;
    return 1;
  }
  
  //Clear current map
  for(std::map<string,person>::iterator it = map.begin();
      it != map.end(); it++) {
    map.erase(it->first);
  }
  
  char comm = ' ';
  //for the whole file
  bool later = false;
  while (later || ifile >> comm) {
    later = false;
    //if it's a P, create a new person and add any numbers present
    if (comm == 'P') {
      
      //get their name
      std::string fullName;
      ifile >> fullName;
      std::string lowFull = toLow(fullName);
      
      //make the person
      person curContact{fullName, "", "", "", "", ""};

      //add them to the map
      map.insert(std::pair<string, person>(lowFull,curContact));

      person *hold = &(map.find(lowFull)->second);
      
      //for that person add any numbers present
      //also, short circuit the loop if the previous contact ended
      while (later == false && ifile >> comm) {
	
	if (comm == 'N') {
	  string nam;
	  ifile >> nam;
	  hold->name = nam;
	}
	else if (comm == 'W') {
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
	  std::cout << "Info: Next contact found" << std::endl;
	  later = true;
	}
	else {
	  std::cout << "Error: Invalid database file" << std::endl;
	  return 1;
	}
      }
      std::cout << "Info: Ending numbers for previuos contact" << std::endl;
    } 
    else { //if the command is not a P
      std::cout << "Info: Odd character detected: " << comm << std::endl;
      std::cout << "Error: Invalid database file" << std::endl;
      return 1;
    }
  }
 return 0;
}

int main() {
  
  std::map<string, person> list;
  char c  = ' ';
  
  while ((c=getchar()) != EOF && c != 'Q') {
    
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
      //all are valid inputs, but should be ignored
    case ' ': //space
      break;
    case '\n': //newline
      break;
    case '\t': //horizontal tab
      break;
    case '\v': //vertical tab
      break;
    default:
      std::cout << "Info: " << c <<  " is not a valid command" << std::endl;
      return 1;
    break;
    }
  }
  return 0;
}
