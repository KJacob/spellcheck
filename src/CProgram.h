/* 
 * File:   CProgram.h
 * Author: kurian
 *
 * Created on November 28, 2013, 8:18 PM
 */

#ifndef CPROGRAM_H
#define	CPROGRAM_H

#include <string>
#include <cstdlib>
#include <iostream>

#include "CEngine.h"

namespace spellcheck {
  using std::string;
  using std::cerr;
  
  class CProgram {
  private:
    int argc;
    char **argv;
    string progname, strinfile, strdict, stroutfile;
    CEngine *engine;
    
  public:
    CProgram(int argc, char **argv);
    
    bool init ();
    
    void parse_arguments ();
    void display_help ();
    
    int run ();
    
    virtual ~CProgram();
  };
} /* namespace */
#endif	/* CPROGRAM_H */

