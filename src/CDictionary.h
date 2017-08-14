/* 
 * File:   CDictionary.h
 * Author: kurian
 *
 * Created on November 22, 2013, 9:29 AM
 */

#ifndef CDICTIONARY_H
#define	CDICTIONARY_H

#include <string>
#include <fstream>
#include <cstdlib>

#include "typedefs.h"
#include "CNotifiable.h"

namespace spellcheck{
  
  /* When we say string, we mean std::string. */
  using std::string;
  using std::ifstream;

  class CDictionary : public CNotifiable{
  private:
    
    /* We own this dictionary. */
    DICTTREE dictionary;
    ifstream dictfile;
    uint file_size;
    
  public:
      CDictionary();
      
      void init (const string& file);
      void populate ();
      void insert (string& word);
      
      static LPDICTNODE getchild (DICTTREE wordtree, char ch);
      bool query (string& word);
      
      DICTTREE get_tree ();
      
      virtual ~CDictionary();
      
  private:
    void delete_tree (DICTTREE dictionary);
  };
  
} /* namespace spellcheck*/

#endif	/* CDICTIONARY_H */

