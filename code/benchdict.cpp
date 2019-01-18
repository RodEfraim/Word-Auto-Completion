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
  unsigned int min_size = 0;
  unsigned int step_size = 0;
  unsigned int num_iterations = 0;
  ifstream dictFile;

  
  DictionaryBST* d_bst = nullptr;
  DictionaryTrie* d_tt = nullptr;
  DictionaryHashtable* d_ht = nullptr;

  Timer timer;
  long long searchTime = 0;
  long long sumAllSearch = 0;
  long long averageRuntime = 0;
  unsigned int count = 0;
  unsigned int totalIncs = 0;
  int NUM_OF_READS = 100;
  int NUM_OF_RUNS = 100;
  
  vector<string> searchLines;
  string line;

  try
  {
    if(argc != 5)
    {
      throw std::invalid_argument("Incorrect number of parameters");
    }

    min_size = stoi(argv[1]);
    step_size = stoi(argv[2]);
    num_iterations = stoi(argv[3]);
    
    dictFile.open(argv[4]);
    if(dictFile.fail())
    {
      throw ios_base::failure("Unable to open file.");
    }

    //Get size of file to determine if user is attempting to read
    //more elements than exist in the input file.
    dictFile.seekg(0, dictFile.end);
    unsigned int fileLength = dictFile.tellg();
    

    if(min_size > fileLength)
    {
      throw std::out_of_range("Please use a file with more elements than min_size");
    }


    
    /**
    * DictionaryTrie Benchmark
    */
    cout << endl << "DictionaryTrie" << endl;
    for(unsigned int i = 0; i < num_iterations; ++i)
    {
      //reset stream to start of dictionary
      dictFile.seekg(0, dictFile.beg);
   
      //reset find time counter for each iteration
      searchTime = 0;

      //New 100 elements needed after ith adjustment
      //to number of elemnts inserted into trees.
      searchLines.clear();

      //create new dictionary object & load min_size + (i * step_size)
      //elements from begining of dictionary.
      d_tt = new DictionaryTrie();
      
      totalIncs = min_size + (i * step_size);
      
      Utils::load_dict(*d_tt, dictFile, totalIncs);
      
      //Read next 100 words from dictionary
      for(int j = 0; j < NUM_OF_READS; ++j)
      {
        count = 0;
        getline(dictFile, line);
    
        //strip off frequency information.
        for(auto & e: line)
        {
          count++;
          if(e == ' ')
          {
            break;
          }
        }
        line.erase(0, count);
        
        searchLines.push_back(line);
      }

      //Compute average runtime for each iteration
      for(int k = 0; k < NUM_OF_RUNS; ++k)
      {
       
        searchTime = 0;
        for(auto & e: searchLines)
        {
          timer.begin_timer();
          d_tt->find(e);
          searchTime += timer.end_timer();
        }
        sumAllSearch += searchTime;
      }

      averageRuntime = sumAllSearch / NUM_OF_RUNS;
      
      cout << totalIncs << "\t" << averageRuntime << endl;
      
      //dictionary files are huge, need to delete asap so as to not 
      //run out of memory when testing other trees.
      delete d_tt;
    }
    


    /**
     * DictionaryBST Benchmark
     */
    cout << endl << "DictionaryBST" << endl;
    for(unsigned int i = 0; i < num_iterations; ++i)
    {
      //reset stream to start of dictionary
      dictFile.seekg(0, dictFile.beg);
   
      //reset find time counter for each iteration
      searchTime = 0;

      //New 100 elements needed after ith adjustment
      //to number of elemnts inserted into trees.
      searchLines.clear();

      //create new dictionary object & load min_size + (i * step_size)
      //elements from begining of dictionary.
      d_bst = new DictionaryBST();
      
      totalIncs = min_size + (i * step_size);
      
      Utils::load_dict(*d_bst, dictFile, totalIncs);
      
      //Read next 100 words from dictionary
      for(int j = 0; j < NUM_OF_READS; ++j)
      {
        count = 0;
        getline(dictFile, line);
    
        //strip off frequency information.
        for(auto & e: line)
        {
          count++;
          if(e == ' ')
          {
            break;
          }
        }
        line.erase(0, count);
        
        searchLines.push_back(line);
      }

      //Compute average runtime for each iteration
      for(int k = 0; k < NUM_OF_RUNS; ++k)
      {
       
        for(auto & e: searchLines)
        {
          timer.begin_timer();
          d_bst->find(e);
          searchTime += timer.end_timer();
        }
        
        averageRuntime = searchTime / NUM_OF_RUNS;
      }

      cout << totalIncs << "\t" << averageRuntime << endl;
      
      //dictionary files are huge, need to delete asap so as to not 
      //run out of memory when testing other trees.
      delete d_bst;
    }


    


    /**
     * DictionaryHashtable Benchmark
     */
    cout << endl << "DictionaryHashtable" << endl;
    for(unsigned int i = 0; i < num_iterations; ++i)
    {
      //reset stream to start of dictionary
      dictFile.seekg(0, dictFile.beg);
   
      //reset find time counter for each iteration
      searchTime = 0;

      //New 100 elements needed after ith adjustment
      //to number of elemnts inserted into trees.
      searchLines.clear();

      //create new dictionary object & load min_size + (i * step_size)
      //elements from begining of dictionary.
      d_ht = new DictionaryHashtable();
      
      totalIncs = min_size + (i * step_size);
      
      Utils::load_dict(*d_ht, dictFile, totalIncs);
      
      //Read next 100 words from dictionary
      for(int j = 0; j < NUM_OF_READS; ++j)
      {
        count = 0;
        getline(dictFile, line);
    
        //strip off frequency information.
        for(auto & e: line)
        {
          count++;
          if(e == ' ')
          {
            break;
          }
        }
        line.erase(0, count);
        
        searchLines.push_back(line);
      }

      //Compute average runtime for each iteration
      for(int k = 0; k < NUM_OF_RUNS; ++k)
      {
       
        for(auto & e: searchLines)
        {
          timer.begin_timer();
          d_ht->find(e);
          searchTime += timer.end_timer();
        }
        
        averageRuntime = searchTime / NUM_OF_RUNS;
      }

      cout << totalIncs << "\t" << averageRuntime << endl;
      
      //dictionary files are huge, need to delete asap so as to not 
      //run out of memory when testing other trees.
      delete d_ht;
    }

    

  }
  catch(std::out_of_range & e)
  {
    cout << "Error: " << e.what() << endl;
    return -1;
  }
  catch(std::exception & e)
  {
    if(errno) 
    {
      perror("The following error occured");
    }
    
    cout << "Error: " << e.what() << endl;
    
    cout << "\nPlease provide the following:" << endl;
    
    cout << "min_size       - The minimum size of the dictionary you want to" 
         << " test" << endl;
    
    cout << "step_size      - The step size (how much to increase the"  
         << " dictionary size for each iteration)" << endl;
    
    cout << "num_iterations - The number of iterations (e.g how many times do you"
         << " want to increase your dictionary size)" << endl;
    
    cout << "dictfile       - The name of a dictionary file to use" << endl;
    
    cout << "\nUsage: ./benchdict min_size step_size num_iterations dictfile" << endl;

    return -1;
  }
  

  return 0;
}
