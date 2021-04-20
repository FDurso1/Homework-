#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdbool.h>


 /**
   * Default Constructor.
   */
template<typename DataType>
TTrie<DataType>::TTrie() {
  typename std::map<DataType, TTrie<DataType>*> children;
  endPoint = false;
}

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
template<typename DataType>
TTrie<DataType>::TTrie(const TTrie<DataType>& rhs){
  *this = rhs; //using overloaded opperator  
}

  /**
   * Destructor.
   */
template<typename DataType>
void TTrie<DataType>::clearMe() {
  typename std::map<DataType, TTrie<DataType>*>::iterator it = this->children.begin();
  typename std::vector<TTrie<DataType>*> pointers;
  
  //store all the pointers in a vector
  while (it != this->children.end()) {
    pointers.push_back(it->second);
    it++;
  }
  for (typename std::vector<TTrie<DataType>*>::iterator it = pointers.begin();
       it != pointers.end(); it++) {
    delete *it;
  }

  this->children.clear();
}

template<typename DataType>
TTrie<DataType>::~TTrie() {
  clearMe();
}

  /**
   * Assignment operators
   */

template<typename DataType>
void TTrie<DataType>::setTTrieEqual(const TTrie<DataType> &rhs) {
  endPoint = rhs.endPoint;
  
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = rhs.children.cbegin();
  while (cit != rhs.children.cend()) {
    //for each child at this layer, create a TTrie that will be a copy
    //of it, and then recur this function on the new TTrie.
    TTrie<DataType> *nextLevel = new TTrie<DataType>;
    *nextLevel = *(cit->second);
    children[cit->first] = nextLevel;
    cit++;
  }
}

template<typename DataType>
TTrie<DataType> & TTrie<DataType>::operator=(const TTrie<DataType> &rhs) {
  if (this != &rhs) {
    //remove all of *this recursively
    clearMe();
        
    //then recursively copy all of rhs
    setTTrieEqual(rhs);
  }
  return *this;
}

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */

//Word will always be at least 1 letter
template<typename DataType>
void TTrie<DataType>::addEquals(const std::vector<DataType>& vec) {
  DataType c = vec.front();
  std::cout << "DataType: " << c << " out of vector " << vec << std::endl;
    
  //if the child does not exist with that letter yet, make it
  if (!hasChild(c)) {
    TTrie<DataType>* nextLevel = new TTrie<DataType>;
    children[c] = nextLevel;
  }
  //else, the child already exists and can be called with giveChild()
  if (vec.size() > 1) {
    typename std::vector<DataType> sub(vec.begin()+1, vec.end());
    *giveChild(c) += sub;
  }
  if (vec.size() == 1) {
    this->endPoint = true;
    std::cout << "The TTrie: " << giveChild(c) << " with the DataType " << c <<"ow has the endPoint value " << giveChild(c)->isEndpoint() << std::endl;
    return;
  }
}

template<typename DataType>
TTrie<DataType>& TTrie<DataType>::operator+=(const std::vector<DataType> &vec) {
  addEquals(vec);
  return *this;
}

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */

template<typename DataType>
bool TTrie<DataType>::carrot(const typename std::vector<DataType> &vec) const {
  DataType c = vec.front();
 
  if (hasChild(c) == false) {
    //the TTrie does not have the next character in the word
    return false;
  }
  
  if (vec.size() > 1) { //vec not done yet
     typename std::vector<DataType> sub(vec.begin()+1, vec.end());
    //make a copy of vec with the first DataType removed
    return *getChild(c) ^ sub;
  }
  //else, last character in the word
  else if (isEndpoint() == false) {
    //but the last character is not an endpoint
    return false;
  }
  return true;
}


template<typename DataType>
bool TTrie<DataType>::operator^(const std::vector<DataType> &vec) const {
  return carrot(vec);
}

/**
   * Overloaded equality operator to check whether two Trie objects are equal
.
   * \param rhs A const reference to the TTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   * false otherwise
   */
template<typename DataType>
bool TTrie<DataType>::operator==(const TTrie<DataType>& rhs) const {
  //using the output of this and rhs to determine if they are equal.
  DataType a, b, c, d;
  return rhs.output_trie(a, b) == (*this).output_trie(c, d);

} 

  /**
   * \brief Overloaded output stream operator<< to print the TTrie in
   * this format a word by line in alphabetical order
   *   e.g. if we have a TTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input TTrie object
   * \return A reference to the output stream object
  */

template<typename DataType>
typename std::vector<DataType> TTrie<DataType>::output_trie(typename std::vector<DataType> curBase, std::vector<DataType>& fullVec) const {
  
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = children.cbegin();
  //save the current base 
   saveCurBase = curBase;
  
  while (cit != children.cend()) { //for every child
    
    curBase.push_back(cit->first); //the base gets incremented by that letter
    if (isEndpoint()) {
      //if it's an endpoint, the fullWord final output gains the current base
      fullVec.push_back(curBase);
      fullVec.push_back('\n');
    }
    if (hasChild()) { //recursive call if the current TTrie has a child
      (cit->second)->output_trie(curBase, fullVec);
      curBase = saveCurBase; //but, the curBase must be reset afterwards
    } 
    cit++;
  }
  return fullVec;
}
/*
template<typename DataType>
std::ostream& operator<<(std::ostream& os, const TTrie<DataType>& tt) {
  typename std::vector<DataType> base;
  typename std::vector<DataType> full;
  typename std::vector<DataType> oVec = tt.output_trie(base, full);
  for (int i = 0; i < oVec.size(); i++) {
    os << oVec[i];
  }
  return os;
}
*/
  /**
   * \return the number of children
   */
template<typename DataType>
unsigned TTrie<DataType>::numChildren() const {
  unsigned sum = 0;
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = this->children.cbegin();
  while (cit != this->children.cend()) {
    sum++;
    cit++;
  }
  return sum;
}

  /**
   * \return true if there are any children, false otherwise
   */
template<typename DataType>
bool TTrie<DataType>::hasChild() const {
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = this->children.cbegin();
  return !(cit == this->children.cend());
}

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
template<typename DataType>
bool TTrie<DataType>::hasChild(DataType character) const {
  
  //Code based on hint for hw7
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = this->children.find(character);
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
template<typename DataType>
const TTrie<DataType>* TTrie<DataType>::getChild(DataType character) const {

  //Code based on hint for hw7
  typename std::map<DataType, TTrie<DataType>*>::const_iterator cit = this->children.find(character);
  if (cit == children.cend()) {
    return nullptr;
  }
  else {
    return cit->second;
  }

}

/**
This function is similar to getChild, except it is not constant, which
means that its output can then be modified.
 */
template<typename DataType>
TTrie<DataType>* TTrie<DataType>::giveChild(DataType c) {

  typename std::map<DataType, TTrie<DataType>*>::iterator it = children.find(c);
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
template<typename DataType>
bool TTrie<DataType>::isEndpoint() const {
  return this->endPoint;
}
