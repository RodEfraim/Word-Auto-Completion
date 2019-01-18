/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Mohamed Sheikh: A11012063
 *  Authors: Rod Efraim:  A13334006
 */
#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>


/**
 *  The class for a TST Node. Each node will contain a single
 *  letter of keys in dictionary.
 */
class TSTNode
{
public:

  TSTNode* left = nullptr;
  TSTNode* middle = nullptr;
  TSTNode* right = nullptr;
  TSTNode* parent = nullptr;

  //Const data in node.
  char data;  

  //Identifies whether node is considered word in dictionary
  //Only node corresponding to last letter of dictionary word/  bool isWord = false;

  //Frequency of the key.
  unsigned int frequency = 0;


  //Constructor
  TSTNode();
};


/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /** Insert a word with its frequency into the dictionary.
  *  Return true if the word was inserted, and false if it
  *  was not (i.e. it was already in the dictionary or it was
  *  invalid (empty string).
  *
  *  @param word The new word to be inserted into the dictionary.
  *  @param freq The frequency this new word contains.
  *  @return true if it is a successful insert. False otherswise.
  */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */

  /** Return true if word is in the dictionary, and false otherwise.
   *
   *  @param word The string we are searching for in the TST dictionary.  
   *  @return true if word was found. False otherwise.
   */
  bool find(std::string word) const;

  /** Return up to num_completions of the most frequent completions
  *  of the prefix, such that the completions are words in the dictionary.
  *  These completions should be listed from most frequent to least.
  *  If there are fewer than num_completions legal completions, this
  *  function returns a vector with as many completions as possible.
  *  If no completions exist, then the function returns a vector of size 0.
  *  The prefix itself might be included in the returned words if the prefix
  *  is a word (and is among the num_completions most frequent completions
  *  of the prefix)
  *
  *  @param prefix From this string, further prediction completions will be
  *  exposed.
  *  @prefix num_completions 
  */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here

  TSTNode* root = nullptr;

  /**
   *  Helper function used in insert to add new nodes straight down the middle.
   *  This occurs when the TST wants to add a node into a null location.
   *
   *  @param wordCount The counter that controls the iterations.
   *  @param word The word that the insert function wants to insert.
   *  @param The node is passed down representing a index of the word we want to
   *  insert.
   */
  void addingNewMiddleNodes(unsigned int & wordCount, 
                            const std::string & word, 
                            TSTNode* & current);

  /** 
   *  Helper function that Deletes node in a postoder traversal.
   *
   *  @param is called recursively to remove everynode.
   */
  void deleteAll(TSTNode*);

  /**
   * Comparator function used in sort algorithm.
   * Sorts elements by frequency in descending order.
   */
  static bool freqSort(const std::pair<std::string, unsigned int> one,
                       const std::pair<std::string, unsigned int> two);

};
#endif // DICTIONARY_TRIE_H
