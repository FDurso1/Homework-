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


bool isSame(const string &left, const string &right) {
  //std::cout << "Info: Checking if " << left << " and " << right << " are the same" << std::endl;
  
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

string toLow(string &str) {
  std::stringstream ssLow;
  for (int i = 0; i < (int) str.length(); i++) {
    //std::cout << "adding " << (char) std::tolower(str[i]) << " to the output" << std::endl;
    ssLow << (char) std::tolower(str[i]);
  }
  std::string lowStr = ssLow.str();
  //std::cout << "final result: " << lowStr << std::endl;
  return lowStr;
}


int newContact(std::map<string, person> &map,
	       std::map<string, person> &lowMap) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  //std::cout << "Info: First Name: " << firstName << std::endl;
  //std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  std::string lowFull = toLow(fullName);
  //std::cout << "Info: Lower case: " << lowFull << std::endl;
  if (lowMap.find(lowFull) == lowMap.end()) {
    person a {"", "", "", "", ""};
    map.insert(std::pair<string, person>(fullName,a));
    lowMap.insert(std::pair<string, person>(lowFull, a));    
    std::cout << "Result: Contact created" << std::endl;
  }
  else {
    std::cout << "Error: Contact already exists" << std::endl;
    return 1;
  }
  return 0;
}

int listNames(std::map<string, person> const &map,
	      std::map<string, person> const &lowMap) {

  for (std::map<string,person>::const_iterator lit = lowMap.cbegin();
       lit != lowMap.cend(); lit++) {
    std::string name = lit->first;
    //std::cout << "first name case insensitive is " << name << std::endl;
    
     for (std::map<string,person>::const_iterator it = map.cbegin();
       it != map.cend(); it++) {

       // std::cout << "first name case sensitive is " << it->first << std::endl;

       if (isSame(it->first, name)) {
	  cout << "Result: " << it->first << std::endl;
	  //it = map.cend()-1;
       }
     }
  }
  return 0;
}

int deleteContact(std::map<string, person> &map,
		  std::map<string, person> &lowMap) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  //std::cout << "Info: First Name: " << firstName << std::endl;
  //std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  
  std::string lowFull = toLow(fullName);

  if (lowMap.find(lowFull) != lowMap.end()) {
    for (std::map<string,person>::iterator it = map.begin();
	 it != map.end(); it++) {
      if (isSame(lowFull, it->first)) {
	map.erase(fullName);
	lowMap.erase(lowFull);
	std::cout << "Result: Contact deleted" << std::endl;
	return 0;
      }
    }
  }
  else {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  return 0;
}

int listNumsOfContact(person contact) {
  std::cout << "Info: Listing results" << std::endl;
  std::cout << "Info: Work: " << contact.WORK << std::endl;
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
  
  if(map.find(fullName) == map.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  
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
    // std::cout << "Info: analyzing " << cur << std::endl;
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

int addNumber(std::map<string, person> &map,
	      std::map<string, person> &lowMap) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  std::string lowFull = toLow(fullName);
  
  if (lowMap.find(lowFull) == lowMap.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }
  person *curContact = &(map.find(fullName)->second);
  for (std::map<string,person>::iterator it = map.begin(); it != map.end(); it++) {
    if (isSame(lowFull, it->first)) {
      *curContact = it->second;
    }
  }
  //person *curContact = &(lowMap.find(lowFull)->second);
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
    //std::cout << "Work contact now " << curContact->WORK << std::endl;
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

int delNumber(std::map<string, person> &map,
	      std::map<string, person> &lowMap) {

  std::string lastName;
  cin >> lastName;
  std::string firstName;
  cin >> firstName;
  std::cout << "Info: First Name: " << firstName << std::endl;
  std::cout << "Info: Last Name: " << lastName << std::endl;

  std::stringstream ss;
  ss << lastName << ',' << firstName;
  std::string fullName = ss.str();
  std::string lowFull = toLow(fullName);
  
  if (lowMap.find(lowFull) == lowMap.end()) {
    std::cout << "Error: Contact not found" << std::endl;
    return 1;
  }

  person *curContact = &(map.find(fullName)->second);
  for (std::map<string,person>::iterator it = map.begin(); it != map.end(); it++) {
    if (isSame(lowFull, it->first)) {
      *curContact = it->second;
    }
  }
  
  //person *curContact = &(lowMap.find(lowFull)->second);

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

int loadList(std::map<string, person> &map,
	     std::map<string, person> &lowMap) {
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
    lowMap.erase(it->first);
  }
  
  char comm = ' ';
  //for the whole file
  bool later = false;
  while (later || ifile >> comm) {
    later = false;
    //if it's a P, create a new person and add any numbers present
    if (comm == 'P') {
      std::cout << "creating contact" << std::endl;
      //get their name
      std::string fullName;
      ifile >> fullName;
      std::string lowFull = toLow(fullName);
      //make the person (cannot initialize blank)
      person curContact{"", "", "", "", ""};

      //add them to the map
      map.insert(std::pair<string, person>(fullName,curContact));
      lowMap.insert(std::pair<string, person>(lowFull,curContact));
      
      person *hold = &(map.find(fullName)->second);
      //for that person add any numbers present
      while (later == false && ifile >> comm) {
	std::cout << "For " << fullName << " adding numbers" << std::endl;
        if (comm == 'W') {
  	  string numb;
	  ifile >> numb;
	  hold->WORK = numb;
	  std::cout << "Work phone created for " << fullName << ": " << hold->WORK << std::endl;
        }
        else if (comm == 'H') {
	  string numb;
	  ifile >> numb;
	  hold->HOME = numb;
	  std::cout << "Home phone created for " << fullName << ": " << hold->HOME << std::endl;

        }
        else if (comm == 'C') {
	  string numb;
	  ifile >> numb;
	  hold->CELL = numb;
	  std::cout << "Cell phone created for " << fullName << ": " << hold->CELL << std::endl;
        }
        else if (comm == 'F') {
	  string numb;
	  ifile >> numb;
	  hold->FAX = numb;
	  std::cout << "Fax phone created for " << fullName << ": " << hold->FAX << std::endl;
        }
        else if (comm == 'V') {
	  string numb;
	  ifile >> numb;
	  hold->VOIP = numb;
	  std::cout << "VOIP phone created for " << fullName << ": " << hold->VOIP << std::endl;
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
  std::map<string, person> lowerList;
  char c  = ' ';
  //c = getchar();
  while ((c=getchar()) != EOF && c != 'Q') {
  //command = getchar();
    //std::cout << "Info: command entered =  " << c << std::endl;
    switch(c) {
    case 'C':
      newContact(list, lowerList);
      break;
    case 'D':
      deleteContact(list, lowerList);
      break;
    case 'L':
      listNames(list, lowerList);
      break;
    case 'P':
      listNums(list);
      break;
    case 'N':
      addNumber(list, lowerList);
      break;
    case 'X':
      delNumber(list, lowerList);
      break;
    case 'S':
      saveList(list);
      break;
    case 'R':
      loadList(list, lowerList);
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
      std::cout << c <<  "is not a valid command" << std::endl;
      return 1;
    break;
  }
  }
  return 0;
}
