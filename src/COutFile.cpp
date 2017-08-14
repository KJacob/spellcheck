/* 
 * File:   COutFile.cpp
 * Author: kurian
 * 
 * Created on November 28, 2013, 4:46 PM
 */

#include "COutFile.h"

namespace spellcheck {

  COutFile::COutFile() {
    interrogator = new CInterrogator();
  }
  
  bool
  COutFile::init(const string& strfile)
  {
    outfile.open(strfile);
    
    if (!outfile.good())
    {
      outfile.close();
      throw string ("Could not open output file. ");
    }
    
    return true;
  }
  
  bool
  COutFile::save(const string& buffer, list<match>& matches)
  {
    int left(0);
    string result;
    
    /* Sort. O(nlog(n))*/
    matches.sort([](match a, match b) -> bool
    {
      return a.first < b.first;
    });
    
    while (matches.size())
    {
      interrogator->query(buffer, matches.front(), result);
      
      outfile << buffer.substr(left, matches.front().first.first - left);
      outfile << result;
      
      left = matches.front().first.second;
      
      matches.pop_front();
    }
    
    outfile << buffer.substr(left);
    outfile.close();
    
    return true;
  }

  COutFile::~COutFile() {
    delete interrogator;
  }
} /* namespace */

