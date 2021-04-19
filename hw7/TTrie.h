
#ifndef TTRIE_H
#define TTRIE_H

#include <map>
#include <vector>
#include <string>

template<typename DataType>
class TTrie {
public:
  /**
   * Default Constructor.
   */
  TTrie();

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
  TTrie(const TTrie<DataType>& rhs);  

  /**
   * Destructor.
   */
  ~TTrie();

  /**
   * Assignment operator.
   */
  TTrie<DataType>& operator=(const TTrie<DataType> &rhs);

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */
  TTrie<DataType>& operator+=(const std::vector<DataType> &vec);

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */
  bool operator^(const std::vector<DataType> &vec) const;

  /**
   * Overloaded equality operator to check whether two Trie objects are equal.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   *         false otherwise
   */
  bool operator==(const TTrie<DataType>& rhs) const;

  /**
   * \brief Overloaded output stream operator<< to print the CTrie in 
   * this format a word by line in alphabetical order
   *   e.g. if we have a CTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CTrie object
   * \return A reference to the output stream object
  */
  friend std::ostream& operator<<(std::ostream& os, const TTrie<DataType>& ct);

  /**
   * \return the number of children
   */
  unsigned numChildren() const;

  /**
   * \return true if there are any children, false otherwise
   */
  bool hasChild() const;

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
  bool hasChild(DataType character) const;

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified character.
   * \param character a character
   * \return pointer to child node, or nullptr if there is no such child
   */
  const TTrie<DataType>* getChild(DataType character) const;

  /**
   * \return true if this node is an endpoint, false otherwise
   */
  bool isEndpoint() const;
 
private:
  bool endPoint;
  std::map<DataType, TTrie<DataType>*> children;
  
  void clearMe();
  void addEquals(const std::vector<DataType> &vec);
  void setTTrieEqual(const TTrie<DataType> &rhs);
  TTrie<DataType>* giveChild(DataType c);
  bool carrot(const std::vecot<DataType> &vec) const;
  std::vector<DataType> output_trie(std::vector<DataType> &base, std::vector<DataType> &fullWord) const;
};
#include "TTrie.inc"
#endif // TTRIE_H
