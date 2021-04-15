#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
// TODO: add other #includes as needed
#include <stdbool.h>

#include "CTrie.h"
using namespace std;

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
CTrie::~CTrie() {

}

  /**
   * Assignment operator.

   person a {fullName, "", "", "", "", ""};
    map.insert(std::pair<string, person>(lowFull,a));


    (char)cit->first, nextLevel)
<char, CTrie*>
   */

CTrie& setCTrieEqual(CTrie lhs, const CTrie &rhs) {
  std::cout << "Setting equals" << std::endl;
  lhs.endPoint = rhs.endPoint;
  std::cout << "End point set to " << rhs.endPoint << std::endl;
  std::map<char, CTrie*>::const_iterator cit = rhs.children.cbegin();
  while (cit != rhs.children.cend()) {
    std::cout << "rhs child detected" << std::endl;
    CTrie nextLevel();
    std::cout << "Recurring with a new CTrie" << std::endl;
    setCTrieEqual(nextLevel, cit->second);
    lhs.children.insert(std::pair<char, CTrie*>());
    std::cout << "adding a blank to lhs's map, then recurring it" << std::endl;
  }
  return lhs;
}

CTrie & CTrie:: operator=(const CTrie &rhs) {
  std::cout << "Deep copying" << std::endl;
  *this = setCTrieEqual(*this, rhs);
  std::cout << "Deep copy done" << std::endl;
  return *this;
}

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */

CTrie& operator+=(const std::string& word) {

  //TODO
  return *this;
}

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */

bool operator^(const std::string &word) const {

  //TODO
  return false;
}

/**
   * Overloaded equality operator to check whether two Trie objects are equal
.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   * false otherwise
   */

bool operator==(const CTrie& rhs) const {

  //TODO
  return false;
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

friend std::ostream& operator<<(std::ostream& os, const CTrie& ct) {

}

  /**
   * \return the number of children
   */
CTtrie::unsigned numChildren() const {
  //TODO
  return 0;
}

  /**
   * \return true if there are any children, false otherwise
   */
CTrie::bool hasChild() const {
  return *this.endPoint;
}

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
CTrie::bool hasChild(char character) const {
  //TODO
  return false;
}

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified character.
   * \param character a character
   * \return pointer to child node, or nullptr if there is no such child
   */
const CTrie* getChild(char character) const {

}

  /**
   * \return true if this node is an endpoint, false otherwise
   */
bool isEndpoint() const {

}
