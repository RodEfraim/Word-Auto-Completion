/**  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 *  2nd Authors)
 *  Authors: Mohamed Sheikh: A11012063
 *  Authors: Rodrigo Efraim: A13334006
 */
#ifndef DICTIONARY_HASHTABLE_H
#define DICTIONARY_HASHTABLE_H

#include <string>
#include <unordered_set>

/**
 *  The class for a dictionary ADT, implemented as a Hashtable
 * When you implement this class, you MUST use a Hashtable
 * in its implementation.  The C++ unordered_set implements 
 * a Hashtable, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryHashtable
{
public:

  /* Create a new Dictionary that uses a Hashset back end */
  DictionaryHashtable();

  /*  Insert a word into the dictionary. 
  *
  *  @param word The string that will be added to the BSTDictionary.
  *  @return Truw if the word was successfully inserted. False otherwise.
  */
  bool insert(std::string& word);

  /* 
   *  Return true if word is in the dictionary, and false otherwise 
   *
   *  @param word The string that we are searching for in the dictionary.
   *  @return true if the string was found. False othersise.
   * */
  bool find(std::string& word) const;

  /* Destructor */
  ~DictionaryHashtable();

private:
  // Add your own data members and methods here
  
  std::unordered_set<std::string*> unorderedSetBST;

};

#endif // DICTIONARY_HASHTABLE_H
