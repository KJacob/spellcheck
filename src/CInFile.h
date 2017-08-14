/* 
 * File:   CInFile.h
 * Author: kurian
 *
 * Created on November 28, 2013, 12:18 PM
 */

#ifndef CINFILE_H
#define	CINFILE_H

#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

#include "typedefs.h"

namespace spellcheck {
  
  using std::string;
  using std::ifstream;
  using std::char_traits;

  class CInFile {
  private:
    ifstream infile;
    string buffer;
    uint currpointer;
    
  public:
    CInFile();
    
    bool init (const string& strfile);
    bool readword (word& receive);
    
    const string& get_buffer ();
    void cleanup ();
    
    virtual ~CInFile();
  };
} /* namespace */

#endif	/* CINFILE_H */

