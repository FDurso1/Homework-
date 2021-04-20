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
using std::cin;
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
  std::map<char, CTrie*>::iterator it = this->children.begin();
  std::vector<CTrie*> pointers;
  
  //store all the pointers in a vector
  while (it != this->children.end()) {
    pointers.push_back(it->second);
    it++;
  }
  for (std::vector<CTrie*>::iterator it = pointers.begin();
       it != pointers.end(); it++) {
    delete *it;
  }

  this->children.clear();
}

CTrie::~CTrie() {
  clearMe();
}

  /**
   * Assignment operators
   */

void CTrie::setCTrieEqual(const CTrie &rhs) {
  endPoint = rhs.endPoint;
  
  std::map<char, CTrie*>::const_iterator cit = rhs.children.cbegin();
  while (cit != rhs.children.cend()) {
    //for each child at this layer, create a CTrie that will be a copy
    //of it, and then recur this function on the new CTrie.
    CTrie *nextLevel = new CTrie;
    *nextLevel = *(cit->second);
    children[cit->first] = nextLevel;
    cit++;
  }
  
}

CTrie & CTrie::operator=(const CTrie &rhs) {
  if (this != &rhs) {
    //remove all of *this recursively
    clearMe();
        
    //then recursively copy all of rhs
    setCTrieEqual(rhs);
  }
  return *this;
}

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */

//Word will always be at least 1 letter
void CTrie::addEquals(const std::string& word) {
    char c = word.at(0);
       
    //if the child does not exist with that letter yet, make it
    if (!hasChild(c)) {
      CTrie* nextLevel = new CTrie;
      children[c] = nextLevel;
    }
    //else, the child already exists and can be called with giveChild()

    if (word.length() > 1) {
      std::string wordCopy = word.substr(1,word.size()-1);
      *giveChild(c) += wordCopy;
    }
    if (word.length() == 1) {
      this->endPoint = true;
      return;
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
 
  if (hasChild(c) == false) {
    //the CTrie does not have the next character in the word
    return false;
  }
  
  if (word.length() > 1) { //word not done yet
    const std::string wordCopy = word.substr(1, word.size() -1);
    //make a copy of word with the first letter removed
    return *getChild(c) ^ wordCopy;
  }
  //else, last character in the word
  else if (isEndpoint() == false) {
    //but the last character is not an endpoint
    return false;
  }
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

bool CTrie::operator==(const CTrie& rhs) const {
  //using the output of this and rhs to determine if they are equal.
  string lBase, lFull, rBase, rFull = "";
  return rhs.output_trie(lBase, lFull) == (*this).output_trie(rBase, rFull);

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


string CTrie::output_trie(string& curBase, string& fullWord) const {
  
  std::map<char, CTrie*>::const_iterator cit = children.cbegin();
  //save the current base 
  string saveCurBase = curBase;
  
  while (cit != children.cend()) { //for every child
    
    curBase += cit->first; //the base gets incremented by that letter
    if (isEndpoint()) {
      //if it's an endpoint, the fullWord final output gains the current base
      fullWord += curBase;
      fullWord += '\n';
    }
    if (hasChild()) { //recursive call if the current CTrie has a child
      (cit->second)->output_trie(curBase, fullWord);
      curBase = saveCurBase; //but, the curBase must be reset afterwards
    } 
    cit++;
  }
  return fullWord;
}

std::ostream& operator<<(std::ostream& os, const CTrie& ct) {
  string str = "";
  string base = "";
  os << ct.output_trie(base, str);
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
  
  //Code based on hint for hw7
  std::map<char, CTrie *>::const_iterator cit = this->children.find(character);
  if (cit == this->children.cend()) {
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

/**
This function is similar to getChild(), except it is not constant, which
means that its output can then be modified.
 */
CTrie* CTrie::giveChild(char c) {

  std::map<char, CTrie *>::iterator it = children.find(c);
  if (it == children.end()) {
    return nullptr;
  }
  else {
    return it->second;
  }

}

  /**
   * \return true if this node is an endpoint, false otherwise
   */
bool CTrie::isEndpoint() const {
  return this->endPoint;
}
