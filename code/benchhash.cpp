#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cerrno>
#include<cstring>

#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

using namespace std;


unsigned int hash1(string word, int size);

unsigned int hash2(string word, int size);


int main(int argc, char* argv[])
{
  //The name of a dictionary file to use.
  //string dictfile = argv[1];
 
  ifstream dictFile;  
  dictFile.open(argv[1]);

  if(argc != 3)
  {
    cout << "Incorrect number of parameters." << endl;
    return -1;
  }

  if(dictFile.fail())
  {
    cout << "Unable to open file." << endl;
    return -1;
  }


  //The number of words to be inserted from the dictioanry
  //in the hashtable.
  unsigned int num_words = stoi(argv[2]);
  unsigned int size = 2 * num_words;

  //This will keep track of the indexes that have been hit.
  //vector<int> slotHit(size);    
  unsigned int slotHitHash1[size];
  unsigned int slotHitHash2[size];
  unsigned int indexHit;;

  //Makes all values in the arrays 0.
  memset(slotHitHash1, 0, size * sizeof(unsigned int));
  memset(slotHitHash2, 0, size * sizeof(unsigned int));


  //We will store the words into the vector.
  vector<string> searchLines;
  string line;

  int collisionCount = 0;


  Utils::load_vector(searchLines, dictFile, num_words);

  //Insert words into slotHitHash1
  for(string e : searchLines)
  {
    indexHit = hash1(e, size);

    slotHitHash1[indexHit] += 1;
  }

  //Insert words into the slotHitHash2
  for(string e : searchLines)
  {
    indexHit = hash2(e, size);

    slotHitHash2[indexHit] += 1;
  }
      


  cout << "1ST HASH FUNCTION" << endl; 
  for(unsigned int count1 = 0; count1 < size; count1++)
  {
    collisionCount = 0;

    for(unsigned int count2 = 0; count2 < size; count2++)
    {
      if(slotHitHash1[count2] == count1)
      {
        collisionCount++;
      }
    }

    if(collisionCount != 0)
    {
      if(count1 == 0)
      {
        cout << collisionCount << " empty slots." << endl;
      }
      else
      {
        cout << collisionCount << " with " << count1 << " hits." << endl;
      }
    }
  }


  cout << "\n2ND HASH FUNCTION" << endl; 
  for(unsigned int count1 = 0; count1 < size; count1++)
  {
    collisionCount = 0;

    for(unsigned int count2 = 0; count2 < size; count2++)
    {
      if(slotHitHash2[count2] == count1)
      {
        collisionCount++;
      }
    }

    if(collisionCount != 0)
    {
      if(count1 == 0)
      {
        cout << collisionCount << " empty slots." << endl;
      }
      else
      {
        cout << collisionCount << " with " << count1 << " hits." << endl;
      }
    }
  }


  return 0;
}

/**
 *://stackoverflow.com/questions/8317508/hash-function-for-a-string
 *
 *  @param word The word we are storing in the hash table
 *  @return unsigned int between 0 and the table size (not including
 *  table size). 
 */
unsigned int hash1(string word, int size)
{
  unsigned int sum = 0;

  for(unsigned int count = 0; count < word.length(); count++)
  {
    sum = sum + int(word.at(count));
  }

  return sum % size;
}

/**
 *://stackoverflow.com/questions/8317508/hash-function-for-a-string
 *
 *  @return unsigned int between 0 and the table size (not including
 *  table size).
 */
unsigned int hash2(string word, int size)
{
  int seed = 131;
  unsigned long hash = 0;

  for(unsigned int count = 0; count < word.length(); count++)
  {
    hash = (hash * seed) + word.at(count);
  }

  return hash % size;
}
