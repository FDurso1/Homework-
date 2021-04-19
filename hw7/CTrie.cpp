#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
// TODO: add other #includes as needed
#include <stdbool.h>

#include "CTrie.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::string;

// TODO: implement the CTrie member functions and friend function


 /**
   * Default Constructor.
   */
CTrie::CTrie() {
  std::map<char, CTrie*> children;
  endPoint = false;
}

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
CTrie::CTrie(const CTrie& rhs){
  *this = rhs; //using overloaded opperator  
}


  /**
   * Destructor.
   */

void CTrie::clearMe() {
  //cout << "Clearing started" << endl;
  std::map<char, CTrie*>::iterator it = this->children.begin();
  std::vector<CTrie*> pointers;
  while (it != this->children.end()) {
    pointers.push_back(it->second);
    //std::cout << "Storing " << it->second << std::endl;
    it++;
  }
  for (std::vector<CTrie*>::iterator it = pointers.begin(); it != pointers.end(); it++) {
    //std::cout << "Deleting " << &it << std::endl;
    delete *it;
  }

  this->children.clear();
  //std::cout << "Clear concluded" << std::endl;
}

CTrie::~CTrie() {
  // std::cout << "Destructor called for " << this << std::endl;
  clearMe();
  //std::cout << "Destructor concluded" << std::endl;
}

  /**
   * Assignment operators
   */

void CTrie::setCTrieEqual(const CTrie &rhs) {
  std::cout << "Setting equals" << std::endl;
  endPoint = rhs.endPoint;
  std::cout << "End point set to " << rhs.endPoint << std::endl;

  std::map<char, CTrie*>::const_iterator cit = rhs.children.cbegin();
  while (cit != rhs.children.cend()) {
    std::cout << "rhs child detecte with the letter " << cit->first << endl;
    CTrie *nextLevel = new CTrie;
    std::cout << "Recurring with a new CTrie" << std::endl;
    *nextLevel = *(cit->second);

    children[cit->first] = nextLevel;
    std::cout << "word finished, possibly more" << std::endl;
    cit++;
  }
  
}

CTrie & CTrie::operator=(const CTrie &rhs) {
  std::cout << "= operator" << std::endl;
  if (this != &rhs) {
    std::cout << "Deep copying" << std::endl;
    //remove all of *this recursively
    clearMe();
    cout << "Cleared of original values" << endl;
    //then recursively copy all of rhs
    setCTrieEqual(rhs);
    std::cout << "Deep copy done" << std::endl;
  }
  
  cout << "Copy constructor now returning a value" << endl;
  return *this;
}

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */

void CTrie::addEquals(const std::string& word) {

  char c = word.at(0);
  std::cout << "working with character: " << c << " out of word: " << word
	    << std::endl;
  
  if (!hasChild(c)) {
    // no such child
    std::cout << "That character does not already exist" <<std::endl;
    CTrie* nextLevel = new CTrie;
    cout << "Next level made" << endl;
    children[c] = nextLevel;
    std::cout << "It has been inserted into the map" << std::endl;
  }
  
  if (word.length() > 1) { //word not done yet
    std::string wordCopy = word.substr(1,word.size()-1);

    std::cout << "Recurring with a shorter word: " << wordCopy << std::endl;
    *giveChild(c) += wordCopy;
  }
  else { //last character in word
    std::cout << "word done, setting endpoint to TRUE" << std::endl;
    endPoint = true;
  }
}

CTrie& CTrie::operator+=(const std::string& word) {
  addEquals(word);
  return *this;
}

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */

bool CTrie::carrot(const std::string &word) const {
  char c = word.at(0);
  cout << "carrot called with c = " << c << endl;
 
  if (hasChild(c) == false) {
    cout << "Child not found for character: " << c << ", returning false" << endl;
    return false;
  }
  
  if (word.length() > 1) { //word not done yet
    const std::string wordCopy = word.substr(1, word.size() -1);
    cout << "recurring with " << wordCopy << " and newest child" << endl;
    //removes the first letter in word
    return *getChild(c) ^ wordCopy;
  } //else, last character in the word
  else if (isEndpoint() == false) {
    cout << "End of word reached, but not an endpoint" << endl;
    //but the last character is not an endpoint
    return false;
  }
  cout << "Word found in carrot, returning true" << endl;
  return true;
}

bool CTrie::operator^(const std::string &word) const {
  return carrot(word);
}

/**
   * Overloaded equality operator to check whether two Trie objects are equal
.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   * false otherwise
   */


bool CTrie::doubleEqual(const CTrie* rhs) const {
  string a = "";
  return rhs->output_trie(a, a) == this->output_trie(a, a);
}


bool CTrie::operator==(const CTrie& rhs) const {
  cout << "Beginning == operator in CTrie" << endl;
  return doubleEqual(&rhs);
} 

  /**
   * \brief Overloaded output stream operator<< to print the CTrie in
   * this format a word by line in alphabetical order
   *   e.g. if we have a CTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CTrie object
   * \return A reference to the output stream object
  */

void outAllKids(const CTrie* ct) {
  std::map<char, CTrie*>::const_iterator cit = ct->children.cbegin();
  cout << "Listing all the kids of this CTrie: " << endl;
   while (cit != ct->children.cend()) {
     cout << cit->first << endl;
     cit++;
   }
}

//have a base that holds the stem, and word which holds everything.
string CTrie::output_trie(string& curBase, string& word) const {
  //outAllKids(this);
  
  std::map<char, CTrie*>::const_iterator cit = children.cbegin();
  //cout << "Starting output trie with CTrie" << this << endl;
  //  std::cin.ignore();
  string saveCurBase = curBase;
  
  while (cit != children.cend()) {
    //for each letter in the map at this level

    //cout << "child detected with letter " << cit->first << endl;
    curBase += cit->first;
    //cout << "Curbase is: " << curBase << endl;
    //change this to curBase += cit->first;?
    //std::cin.ignore();
    
    if (isEndpoint()) {
      word += curBase;
      word += '\n';
    }
    if (hasChild()) {
      //cout << "Recursive call" << endl;
      //std::cin.ignore();
      (cit->second)->output_trie(curBase, word);
      curBase = saveCurBase;
      //cout << "after recursive call, word: " << word << ", curBase: " << curBase << endl;
    }
    
    cit++;
  }
  //cout << "Going back a level" << endl;
  //std::cin.ignore();
  return word;
}

std::ostream& operator<<(std::ostream& os, const CTrie& ct) {
  cout << "beginning << operator" << endl;
  // std::cin.ignore();
  string str = "";
  string base = "";
  os << ct.output_trie(base, str);
  //  cout << "Return from output_trie: " << ct.output_trie(base, str) << endl;
  cout << "ending << operator" << endl;
  return os;
}

  /**
   * \return the number of children
   */
unsigned CTrie::numChildren() const {
  unsigned sum = 0;
  std::map<char, CTrie*>::const_iterator cit = this->children.cbegin();
  while (cit != this->children.cend()) {
    sum++;
    cit++;
  }
  return sum;
}

  /**
   * \return true if there are any children, false otherwise
   */
bool CTrie::hasChild() const {
  std::map<char, CTrie*>::const_iterator cit = this->children.cbegin();
  return !(cit == this->children.cend());
}

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
bool CTrie::hasChild(char character) const {
  //std::cout << "Testing if " << character << " is a child" << std::endl;
  //Code based on hint for hw7
  std::map<char, CTrie *>::const_iterator cit = this->children.find(character);
  //std::cout << "cit created" << std::endl;
  if (cit == this->children.cend()) {
    //std::cout << "Returning false" << std::endl;
    return false;
  }
  return true;

}

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified character.
   * \param character a character
   * \return pointer to child node, or nullptr if there is no such child
   */
const CTrie* CTrie::getChild(char character) const {

  //Code based on hint for hw7
  std::map<char, CTrie *>::const_iterator cit = this->children.find(character);
  if (cit == children.cend()) {
    return nullptr;
  }
  else {
    return cit->second;
  }

}

CTrie* CTrie::giveChild(char c) {
    
  if (children.find(c) == children.end()) {
    return nullptr;
  }
  else {
    return (children.find(c))->second;
  }

}

  /**
   * \return true if this node is an endpoint, false otherwise
   */
bool CTrie::isEndpoint() const {
  return this->endPoint;
}
