/* 
 * File:   COutFile.h
 * Author: kurian
 *
 * Created on November 28, 2013, 4:46 PM
 */

#ifndef COUTFILE_H
#define	COUTFILE_H

#include <string>
#include <fstream>
#include <list>

#include "typedefs.h"
#include "CInterrogator.h"

namespace spellcheck {
  
  using std::ofstream;
  using std::list;
  using std::string;
  
  class COutFile {
  private:
    ofstream outfile;
    CInterrogator *interrogator;
    
  public:
    COutFile();
    
    bool init (const string& strfile);
    bool save (const string& buffer, list<match>& matches);
    
    virtual ~COutFile();
  };
} /* namespace */

#endif	/* COUTFILE_H */

