/**  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 *  2nd Authors)
 *  Authors: Mohamed Sheikh: A11012063
 *  Authors: Rodrigo Efraim: A13334006
 */
#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/** Insert a word into the dictionary. 
 *  
 *  @param word The string that will be added to the BSTDictionary.
 *  @return Truw if the word was successfully inserted. False otherwise.
 */
bool DictionaryBST::insert(std::string word)
{
  //If the word is empty then return false.
  if(word.length() == 0)
  {
    return false;
  }

  //If it is already in the setBST then return false.
  if(this->find(word) == true)
  {
    return false;
  }

  //Insert into the setBST.
  setBST.insert(word);  
  return true;
}

/**
 *  Return true if word is in the dictionary, and false otherwise.
 *
 *  @param word The string that we are searching for in the dictionary.
 *  @return true if the string was found. False othersise.
 */
bool DictionaryBST::find(std::string word) const
{

  auto foundIT = setBST.find(word);

  if(foundIT != setBST.end())
  {
    return true;
  }

  return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
