#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
// TODO: add other #includes as needed
#include <stdbool.h>

#include "CTrie.h"


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

void deleteMe(CTrie* lhs) {
  std::cout << "DeleteMe called" << std::endl;
  std::map<char, CTrie*>::iterator it = lhs->children.begin();
  while (it != lhs->children.end()) {
    std::cout << "There was a child found, recurring for that child" << std::endl; 
    deleteMe(it->second); //every time it finds a new child it recurrs
    //and it loops this process for every child on the current level
    it++;
  }
  delete it->second;
  std::cout << "No child detected at this level, deleting current CTrie" << std::endl;
  //every time it does not find a child it deletes the current CTrie
}

CTrie::~CTrie() {
  std::cout << "Destructor called" << std::endl;
  
  std::map<char, CTrie*>::iterator it = this->children.begin();
  while (it != this->children.end()) {
    delete it->second;
  }


  //deleteMe(this); //calls the recursive function
  std::cout << "Destructor concluded" << std::endl;
}

  /**
   * Assignment operators
   */

CTrie setCTrieEqual(CTrie* lhs, const CTrie &rhs) {
  std::cout << "Setting equals" << std::endl;
  lhs->endPoint = rhs.endPoint;
  std::cout << "End point set to " << rhs.endPoint << std::endl;
  std::map<char, CTrie*>::const_iterator cit = rhs.children.cbegin();
  while (cit != rhs.children.cend()) {
    std::cout << "rhs child detected" << std::endl;
    CTrie* nextLevel = new CTrie;
    std::cout << "Recurring with a new CTrie" << std::endl;
    setCTrieEqual(nextLevel, *(cit->second));
    lhs->children.insert(std::pair<char, CTrie*>((char)cit->first, nextLevel));
    std::cout << "adding a blank to lhs's map, then recurring it" << std::endl;
    cit++;
  }
  return *lhs;
}

CTrie & CTrie::operator=(const CTrie &rhs) {

  if (this != &rhs) {
    std::cout << "Deep copying" << std::endl;
    //remove all of *this recursively
    deleteMe(this);
    //then recursively copy all of rhs
    *this = setCTrieEqual(this, rhs);
    std::cout << "Deep copy done" << std::endl;
  }
  return *this;
}

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */

void addEquals(const std::string& word, CTrie* rhs) {

  char c = word.at(0);
  std::cout << "working with character: " << c << " out of word: " << word
	    << std::endl;
  //This iterator and if/else structures are based on those found in hw7 hints.
  std::map<char, CTrie *>::const_iterator cit = rhs->children.find(c);
  if (cit == rhs->children.end()) {
    // no such child
    std::cout << "That character does not already exist" <<std::endl;
    CTrie* nextLevel = new CTrie;
    rhs->children.insert(std::pair<char, CTrie*>(c, nextLevel));
    std::cout << "It has been inserted into the map" << std::endl;
  }
  // else, cit->second is the pointer to the child node

  if (word.length() > 1) { //word not done yet
    std::string wordCopy = word.substr(1,word.size()-1);
    //removes the first letter in word
    std::cout << "Recurring with a shorter word: " << wordCopy << std::endl;
    addEquals(wordCopy, cit->second);
  }
  else { //last character in word
    std::cout << "word done, setting endpoint" << std::endl;
    rhs->endPoint = true;
  }
}

CTrie& CTrie::operator+=(const std::string& word) {
  addEquals(word, this);
  return *this;
}

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */

bool carrot(const std::string &word, const CTrie* rhs) {
  char c = word.at(0);

  std::map<char, CTrie *>::const_iterator cit = rhs->children.find(c);
  if (cit == rhs->children.end()) {
    return false;
  }
  
  if (word.length() > 1) { //word not done yet
    std::string wordCopy = word.substr(1, word.size() -2);
    //removes the first letter in word
    return carrot(wordCopy, cit->second);
  } //else, last character in the word
  else if (rhs->endPoint == false) { //but the last character is not an endpoint
    return false;
  }
  return true;
}

bool CTrie::operator^(const std::string &word) const {
  return carrot(word, this);
}

/**
   * Overloaded equality operator to check whether two Trie objects are equal
.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   * false otherwise
   */


bool doubleEqual(const CTrie* lhs, const CTrie* rhs) {
  std::map<char, CTrie*>::const_iterator rcit = rhs->children.cbegin();
  std::map<char, CTrie*>::const_iterator lcit = lhs->children.cbegin();
  while (rcit != rhs->children.cend()) {
    if (lcit == lhs->children.cend()) {
      return false;
    }
    if (lhs->endPoint != rhs->endPoint) {
      return false;
    }
    if (lcit->first != rcit->first) {
      return false;
    }
    lcit++;
    rcit++;
    return doubleEqual(lcit->second, rcit->second);
  }
  return true;
}


bool CTrie::operator==(const CTrie& rhs) const {
  return doubleEqual(this, &rhs);
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

std::ostream& outPut(std::ostream& os, const CTrie& ct) {
  std::map<char, CTrie*>::const_iterator cit = ct.children.cbegin();
  while (cit != ct.children.cend()) {
    os << cit->first;
    if (ct.endPoint) {
      os << '\n';
    }
    else {
      outPut(os, *(cit->second));
    }
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const CTrie& ct) {
  return outPut(os, ct);
}

  /**
   * \return the number of children
   */
unsigned CTrie::numChildren() const {
  unsigned sum = 0;
  std::map<char, CTrie*>::const_iterator cit = this->children.cbegin();
  while (cit != this->children.cend()) {
    sum++;
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
  std::cout << "Testing if " << character << " is a child" << std::endl;
  //Code based on hint for hw7
  std::map<char, CTrie *>::const_iterator cit = this->children.find(character);
  std::cout << "cit created" << std::endl;
  if (cit == this->children.end()) {
    std::cout << "Returning false" << std::endl;
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
  if (cit == children.end()) {
    return nullptr;
  }
  else {
    return cit->second;
  }

}

  /**
   * \return true if this node is an endpoint, false otherwise
   */
bool CTrie::isEndpoint() const {
  return this->endPoint;
}
