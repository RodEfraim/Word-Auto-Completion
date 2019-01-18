/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Mohamed Sheikh: A11012063
 *  Authors: Rod Efraim:  A13334006
 */
#include<queue>
#include<stack>
#include<algorithm> /* sort */
#include<utility> /* pair(), make_pair() */

#include "util.h"
#include "DictionaryTrie.h"

/**
 *  TSTNodew constructor creates new TSTNodes.
 */
TSTNode::TSTNode(){}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}

/** Insert a word with its frequency into the dictionary.
 *  Return true if the word was inserted, and false if it
 *  was not (i.e. it was already in the dictionary or it was
 *  invalid (empty string).
 *
 *  @param word The new word to be inserted into the dictionary.
 *  @param freq The frequency this new word contains.
 *  @return true if it is a successful insert. False otherswise.
 * */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{

  TSTNode* current = root;
  unsigned int wordCount = 0;

  if(root == nullptr)
  {
    //Insert first letter
    TSTNode* newNode = new TSTNode();
    newNode->data = word.at(wordCount);
    root = newNode;

    //std::cout << "Inserting " << word.at(wordCount) << std::endl;

    current = root;

    wordCount++;

    //Insert rest of the letters
    addingNewMiddleNodes(wordCount, word, current);

    //TODO: Make this into a void helper function.
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Label last node as "word node" and update its frequency.
    current->isWord = true;
    if(current->frequency < freq)
    {
      current->frequency = freq;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    return true;
  }

  //unsigned int wordCount = 0;
  while(wordCount < word.length())
  {
    //std::cout << "\nFrom word (" << word.at(wordCount) << ") VS (" 
      //<< current->data << ") from current's data" << std::endl;

    if(word.at(wordCount) < current->data)
    {
      if(current->left != nullptr)
      {
        //Since node has left child, traverse down to node's left child.
        current = current->left;
      }
      else
      {
        //Reached null as going left.

        //std::cout << "Inserting (" << word.at(wordCount) << ") AS LEFT" << std::endl;

        //Creates a new node.
        TSTNode* newNodeLeft = new TSTNode();
        newNodeLeft->data = word.at(wordCount);

        //Make the new node be the current's left child.
        current->left = newNodeLeft;

        //Link new node's parent to the current.
        newNodeLeft->parent = current; 
        
        //The current will now point 
        current = current->left;

        //NEW: Is this needed?
        wordCount++;

        addingNewMiddleNodes(wordCount, word, current);

        //TODO: Make this into a void helper function.
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //Label last node as "word node" and update its frequency.
        current->isWord = true;
        if(current->frequency < freq)
        {
          current->frequency = freq;
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        return true;
      }
    }
    else if(word.at(wordCount) > current->data)
    {
      if(current->right != nullptr)
      {
        //Since node has right child, traverse down to node's right child.
        current = current->right;
      }
      else
      {
        //std::cout << "Inserting (" << word.at(wordCount) << ") AS RIGHT" << std::endl;

        //Creates a new node. 
        TSTNode* newNodeRight = new TSTNode();
        newNodeRight->data = word.at(wordCount);

        //Make the new node be the current's right child.
        current->right = newNodeRight;

        //Link new node's parent to the current.
        newNodeRight->parent = current; 

        //The current will now point to the new node.
        current = current->right;

        //NEW: Is this needed?
        wordCount++;

        addingNewMiddleNodes(wordCount, word, current);

        //TODO: Make this into a void helper function.
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //Label last node as "word node" and update its frequency.
        current->isWord = true;
        if(current->frequency < freq)
        {
          current->frequency = freq;
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        return true;
      }
    }
    else if(word.at(wordCount) == current->data)
    { 
      if((current->data == word.at(word.length() - 1)) 
          && current->isWord == false /*true*/
          && wordCount == word.length() - 1)
      {
        //Handles the PREFIX insertion case.

        //TODO: Make this into a void helper function.
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //Label last node as "word node" and update its frequency.
        current->isWord = true;
        if(current->frequency < freq)
        {
          current->frequency = freq;
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //std::cout << "Returning true, successful PREFIX insert" << std::endl;

        return true;
      }
      else if((current->data == word.at(word.length() - 1)) 
          && current->isWord == true
          && wordCount == word.length() - 1)
      {
        //Handles the RE-INSERTION case..
        //Update frequency to highest value, then return false.

        if(current->frequency < freq)
        {
          current->frequency = freq;
        }
        //std::cout << "Returning false, WORD ALREADY INSERTED" << std::endl;

        return false;
      }


      if(current->middle != nullptr)
      {
        current = current->middle;

        //This will increment if it matches and the next node is not null.
        wordCount++;
      }
      else
      {
        //Handles the POSTFIX insertion case.

        wordCount++;

        addingNewMiddleNodes(wordCount, word, current);

        //TODO: Make this into a void helper function.
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        //Label last node as "word node" and update its frequency.
        current->isWord = true;
        if(current->frequency < freq)
        {
          current->frequency = freq;
        }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        return true;        
      }
    }//End of primal if-else if-else if chain.

  }//End of while

  return false;
}

/** Return true if word is in the dictionary, and false otherwise.
 *
 *  @param word The string we are searching for in the TST dictionary.  
 *  @return true if word was found. False otherwise.
 */
bool DictionaryTrie::find(std::string word) const
{
  if(root == nullptr)
  {
    return false;
  }

  TSTNode* current = root;

  //Traverses the chars of the word parameter.
  unsigned int wordCount = 0;
  while(/*word[wordCount] != '\0'*/wordCount < word.length())
  {
    if(word.at(wordCount) < current->data)
    {
      //If node has left child, traverse down to node's left child.
      if(current->left != nullptr)
      {
        current = current->left;
      }
      else
      {
        return false;
      }
    }
    else if(word.at(wordCount) > current->data)
    {
      //If node has right child, traverse down to node's right child.
      if(current->right != nullptr)
      {
        current = current->right;
      }
      else
      {
        return false;
      }
    }
    else if(word.at(wordCount) == current->data)
    {
      //If current equals last letter of key and it is in the TST, return true;
      //TODO: MIGHT NEED MODIFICATION FOR EX: "autocomplete"
      if((current->data == word.at(word.length() - 1)) 
          && current->isWord == true
          && wordCount == word.length() - 1)
      {
        return true;
      }

      if(current->middle != nullptr)
      {
        current = current->middle;
        wordCount++;
      }
      else
      {
        return false;
      }
    }
  }

  //This return is so that the program compiles.
  return false;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  //TODO: Add edge cases at the top.

  std::vector<std::string> words;
  std::vector<std::string> frequencies;

  std::string validWord = "";
  std::queue<TSTNode*> queueBFS;

  std::stack<char> letterStacker;

  std::pair<std::string, unsigned int> pairWordFreq;
  std::vector<std::pair<std::string, unsigned int>> sortedWords;

  unsigned int wordCount = 0;
  unsigned int wordFreq = 0;

  bool isInDict = false;

  TSTNode* parentTracker = nullptr;
  TSTNode* current = nullptr;
  TSTNode* BFSroot = nullptr;
  TSTNode* tempRight = nullptr;
  TSTNode* tempLeft = nullptr;
  
  //If TST does not exist, return empty vector.
  if(root == nullptr)
  {
    words.clear();
    return words;
  }
  
  //If empty string as prefix, return empty vector.
  if(prefix.empty())
  {
    std::cout << "Invalid Input. Please retry with corrent input." << std::endl;
    words.clear();
    return words;
  }

  current = root;

  //FIND PREFIX LOGIC.
  //Traverses the chars of the string prefix parameter.
  while(wordCount < prefix.length())
  {
    if(prefix.at(wordCount) < current->data)
    {
      //If node has left child, traverse down to node's left child.
      if(current->left != nullptr)
      {
        current = current->left;
      }
      else
      {
        //Prefix not found, RETURN EMPTY VECTOR.
        std::cout << "Invalid Input. Please retry with corrent input." << std::endl;
        words.clear();
        return words;
      }
    }
    else if(prefix.at(wordCount) > current->data)
    {
      //If node has right child, traverse down to node's right child.
      if(current->right != nullptr)
      {
        current = current->right;
      }
      else
      { 
        //Prefix not found, RETURN EMPTY VECTOR.
        std::cout << "Invalid Input. Please retry with corrent input." << std::endl;
        words.clear();
        return words;
      }
    }
    else if(prefix.at(wordCount) == current->data)
    {
      //validWord += current->data;

      //If prefix is in dictionary, add to vector.
      //This node indicates begining of BST search AND
      //prefix is in dictionary.
      if((current->data == prefix.at(prefix.length() - 1)) 
          && current->isWord == true
          && wordCount == prefix.length() - 1)
      {

        //pairWordFreq = std::make_pair(validWord, current->frequency);
        //sortedWords.push_back(pairWordFreq);
        //words.push_back(validWord);
        break;
      }
      
      if(current->middle != nullptr)
      {
        //prefix is not in dictionary, break on last
        //letter to set correct root.
        if(wordCount == prefix.length() - 1)
        {
          break;
        }
        current = current->middle;
        wordCount++;
      }
    }
  }

  //The last letter node of the prefix will be considered the root of the
  //BFS because we will perform BFS starting from this last letter node.
  queueBFS.push(current);
  
  BFSroot = current;
 

  //Optimization:
  //The left or right children of the BFSroot (i.e prefix) will
  //never be returned as a valid suffix.
  if(BFSroot->right != nullptr)
  {
    tempRight = BFSroot->right;
    BFSroot->right = nullptr;
  }

  if(BFSroot->left != nullptr)
  {
    tempLeft = BFSroot->left;
    BFSroot->left = nullptr;
  }


  while(!queueBFS.empty())
  {
    current = queueBFS.front();
    
    validWord = prefix; 
    //If reached word node, reverse traverse tree
    //to build valid suffixes
    if(current->isWord == true)
    {     
      parentTracker = current; 
      wordFreq = current->frequency;

      //If prefix is in dictionary, insert word node key.
      if(parentTracker == BFSroot)
      {
        pairWordFreq = std::make_pair(validWord, wordFreq);
        sortedWords.push_back(pairWordFreq);
        isInDict = true;
      }    
      else 
      {
        letterStacker.push(parentTracker->data);       
        isInDict = false;
      }

      //Start from word node, go until we hit last
      //letter of the prefix (i.e BFSroot).
      while(parentTracker->parent != BFSroot 
            && isInDict == false)
      {
        if(parentTracker->parent->middle ==
           parentTracker)
        {
          letterStacker.push(parentTracker->parent->data);
        }

        parentTracker = parentTracker->parent;

      }

      //build word from stack
      while(!letterStacker.empty())
      {
        validWord += letterStacker.top(); 
        letterStacker.pop();
      }

      //push each valid word & frequency into vector.
      if(!isInDict)
      {
        pairWordFreq = std::make_pair(validWord, wordFreq);
        sortedWords.push_back(pairWordFreq);
      }
    }

    //Breadth first search algorithm
    queueBFS.pop();

    if(current->left != nullptr)
    {
      queueBFS.push(current->left);  
    } 
    
    if(current->middle != nullptr)
    {
      queueBFS.push(current->middle);
    }
    
    if(current->right != nullptr)
    {
      queueBFS.push(current->right);
    }    
  }

  //sort valid suffixes by frequency in desc. order
  std::sort(sortedWords.begin(), sortedWords.end(), freqSort);

  //Reattach left & right subtrees that were not needed
  //for provided prefix.
  BFSroot->right = tempRight;
  BFSroot->left = tempLeft;

  //return only requested number of completions
  if(num_completions < sortedWords.size())
  {
    sortedWords.resize(num_completions);
  }
  
  //add sorted words (by freq desc.) into words vector
  for(auto & e : sortedWords)
  {
    words.push_back(e.first);
  }

  return words;
}

/**
 *  Comparator function for sort algorithm used in predictCompletions.
 *  This sorts a pair of (valid word, frequency) by frequency in descending
 *  order.
 */
bool DictionaryTrie::freqSort(const std::pair<std::string, unsigned int> one,
                              const std::pair<std::string, unsigned int> two)
{
  
  if(one.second < two.second)
  {
    return false;
  }
    
  return true;

}

/**
 *  Helper function used in insert to add new nodes straight down the middle.
 *  This occurs when the TST wants to add a node into a null location.
 *
 *  @param wordCount The counter that controls the iterations.
 *  @param word The word that the insert function wants to insert.
 *  @param The node is passed down representing a index of the word we want to
 *  insert.
 */
void DictionaryTrie::addingNewMiddleNodes(unsigned int & wordCount,
                                          const std::string & word, 
                                          TSTNode* & current)
{      
  TSTNode* newNodeMiddle;
  for(; wordCount < word.length(); wordCount++)
  {
    newNodeMiddle = new TSTNode();
    newNodeMiddle->data = word.at(wordCount);
    
    current->middle = newNodeMiddle;
    newNodeMiddle->parent = current; 
    current = current->middle;
  }
}

/** 
 * Destructor.
 */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

/** 
 *  Helper function that Deletes node in a postoder traversal.
 *
 *  @param is called recursively to remove everynode.
 */
void DictionaryTrie::deleteAll(TSTNode* n)
{
  //Base case.
  if(n == nullptr)
  {
    return;
  }

  // Post order traversal delete
  deleteAll(n->left);
  deleteAll(n->middle);
  deleteAll(n->right);
  
  delete(n);
}

