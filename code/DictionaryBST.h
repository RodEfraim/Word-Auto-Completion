/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 *  2nd Authors)
 *  Authors: Mohamed Sheikh: A11012063
 *  Authors: Rodrigo Efraim: A13334006
 */
#ifndef DICTIONARY_BST_H
#define DICTIONARY_BST_H

#include <string>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//TODO: NEW ROD
#include <set>


/**
 *  The class for a dictionary ADT, implemented as a BST
 * When you implement this class, you MUST use a balanced binary
 * search tree in its implementation.  The C++ set implements 
 * a balanced BST, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryBST
{
public:

  /* Create a new Dictionary that uses a BST back end */
  DictionaryBST();

  /** Insert a word into the dictionary. 
  *  
  *  @param word The string that will be added to the BSTDictionary.
  *  @return Truw if the word was successfully inserted. False otherwise.
  */
  bool insert(std::string word);

  /**
  *  Return true if word is in the dictionary, and false otherwise.
  *
  *  @param word The string that we are searching for in the dictionary.
  *  @return true if the string was found. False othersise.
  */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryBST();

private:
  // Add your own data members and methods here

  //Note that C++ STL set uses a balanced BST (red black tree) to store
  //elements.
  //Empty set of strings.
  
  std::set<std::string> setBST;  
};

#endif // DICTIONARY_BST_H
