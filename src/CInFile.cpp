/* 
 * File:   CInFile.cpp
 * Author: kurian
 * 
 * Created on November 28, 2013, 12:18 PM
 */

#include "CInFile.h"

namespace spellcheck {

  CInFile::CInFile() {
    /* Nothing to do. */
  }
  
  bool
  CInFile::init(const string& strfile)
  {
    infile.open(strfile, ifstream::in);
    
    if (!infile.good())
    {
      infile.close();
      return false;
    }
    
    /* Ah, we're good. */
    return true;
  }
  
  /*
   * Returns true if a word was successfully read.
   * 
   * Warning: This function is impure - That means I will destroy of its
   * arguments the original content.
   */
  
  bool
  CInFile::readword(word& receive)
  {
    char ch, peekch;
    uint wordbegin(0), wordend(0);
    
    /* 
     * Wade through the file character by character, until we find a word.
     */
    
    while (infile.good())
    {
      peekch = infile.peek();
      
      if (isalnum(peekch))
      {
        wordbegin = currpointer;
        break;
      }
      
      if (peekch == char_traits<char>::eof())
      {
        return false;
      }
      
      ch = infile.get();
      buffer.push_back(ch);
      currpointer++;
    }
    
    /* 
     * Now get the word.
     */
    
    while (infile.good())
    {
      peekch = infile.peek();
      
      if (!isalnum (peekch) || peekch == char_traits<char>::eof())
      {
        wordend = currpointer;
        break;
      }
      
      ch = infile.get();
      buffer.push_back(ch);
      currpointer++;
    }
    
    /* Give them what we have found. */
    receive.first = wordbegin;
    receive.second = wordend;
    return true;
  }
  
  const
  string&
  CInFile::get_buffer()
  {
    return this->buffer;
  }
  
  void
  CInFile::cleanup()
  {
    infile.close();
  }

  CInFile::~CInFile() {
  }
}
