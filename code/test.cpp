#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cerrno>

#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

using namespace std;

int main(int argc, char* argv[])
{

  //Using Utils
  //File I/O logic
  ifstream dictStream;
  string prefix = "";
  unsigned int numCompletions = 0;
  
  DictionaryBST d_bst;
  DictionaryTrie d_tt;
  DictionaryHashtable d_ht;

  vector<std::string> words;

  bool hasPassed; 
  unsigned int fileLength = 0;
  unsigned int HUGE_FILE_BYTES = 1000000;

  int t_bst, t_ht, tt;
  
  try
  {
    if(argc != 4)
    {
      throw std::invalid_argument("Incorrect number of parameters");
    }

    dictStream.open(argv[1]);
    prefix = argv[2];
    numCompletions = stoi(argv[3]);
    
    if(dictStream.fail())
    {
      throw ios_base::failure("Unable to open file.");
    }
    
    //Get size of file 
    dictStream.seekg(0, dictStream.end);
    fileLength = dictStream.tellg();
    dictStream.seekg(0, dictStream.beg);
    
    if(fileLength > HUGE_FILE_BYTES || numCompletions > 5000)
    {
      cout << endl << "WARNING: Huge file detected, tests may take time!" << endl;
    }

    /*
    //Load into dict directly 
    d_bst = new DictionaryBST();
    d_tt = new DictionaryTrie();
    d_ht = new DictionaryHashtable();
    

    Utils::load_dict(d_tt, dictStream);
    Utils::load_dict(d_bst, dictStream);
    Utils::load_dict(d_ht, dictStream);
    */

    //Load into vector to test inserts
    cout << "Initializing vector with data from " << argv[1] << "... ";
    Utils::load_vector(words, dictStream, numCompletions);
    cout << "SUCCESS!" << endl;
    
    
    /** 
     * Test Insert 
     */
    cout << "\n\nTEST: Inserting into Dictionaries." << endl;
    
    for(auto & e: words)
    {
      t_bst = 0;
      t_ht = 0;
      tt = 0;
      hasPassed = false;

      
      //cout << "Inserting: \"" << e << "\"... ";
      t_bst = d_bst.insert(e);
      t_ht = d_ht.insert(e);
      tt = d_tt.insert(e, 0);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
      {
        cout << "Inserting: \"" << e << "\"... ";
        cout << "failed for DictionaryBST! " << endl;
        
      }
      if(!t_ht)
      {
        cout << "Inserting: \"" << e << "\"... ";
        cout << "failed for DictionaryHashset! " << endl;
        
      }
      if(!tt)
      {
        cout << "Inserting: \"" << e << "\"... ";
        cout << "failed for DictionaryTrie! " << endl;
        
      }

      if(!t_ht || !t_bst || !tt)
      {
        break;
      }
      hasPassed = true;
     
      

    }

    if(hasPassed)
    {
      cout << "All insert tests... PASSED! :D " << endl;
    }

    /** 
     * Test Reinsert 
     */
    cout << "\n\nTEST: Reinserting into Dictionaries." << endl;
    
    for(auto & e: words)
    {
      tt = 0;
      hasPassed = false;

      tt = d_tt.insert(e, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(tt)
      {
        cout << "Inserting: \"" << e << "\"... ";
        cout << "failed for DictionaryTrie! " << endl;
        
      }

      if(tt)
      {
        break;
      }
      hasPassed = true;
    }

    if(hasPassed)
    {
      cout << "All reinsert tests... PASSED! :D " << endl;
    }


    /** 
     * Test Find on existing elements.
     */
    cout << "\n\nTEST: Finding existing words in Dictionaries..." << endl;
    for(auto & e: words)
    {
      t_bst = 0;
      t_ht = 0;
      tt = 0;
      hasPassed = false;

      //cout << "Finding: \"" << e << "\"... ";
      t_bst = d_bst.find(e);
      t_ht = d_ht.find(e);
      tt = d_tt.find(e);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
      {
        cout << "Finding: \"" << e << "\"... ";
        cout << "failed for DictionaryBST! " << endl;
        break;
      }
      if(!t_ht)
      {
        cout << "Finding: \"" << e << "\"... ";
        cout << "failed for DictionaryHashset! " << endl;
        break;
      }
      if(!tt)
      {
        cout << "Finding: \"" << e << "\"... ";
        cout << "failed for DictionaryTrie! " << endl;
        break;
      }
      
      if(!t_ht || !t_bst || !tt)
      {
        break;
      }

      hasPassed = true;
    }
    
    if(hasPassed)
    {
      cout << "All find tests... PASSED! :D " << endl;
    }


    //DOES THIS EVEN WORK???~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for(string e : d_tt.predictCompletions("bi", 10))
    {
      cout << e << endl;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  }
 /* catch(std::out_of_range & e)
  {
    cout << "Error: " << e.what() << endl;
    return -1;
  }*/
  catch(std::exception & e)
  {
    if(errno) 
    {
      perror("The following error occured");
    }
    
    cout << "Error: " << e.what() << endl;
    
    cout << "\nPlease provide the following:" << endl;
    cout << "dict_file.txt   - A dictionary file name to insert into TST.\n";
    cout << "required_prefix - Prefix to search for within dictionary.\n";
    cout << "num_comp        - Number of completions to return statisfying prefix.\n";
    cout << "\nUsage: ./test dict_file.txt required_prefix num_comp" << endl;

    return -1;
  }
  

  return 0;
}

