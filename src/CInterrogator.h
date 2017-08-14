/* 
 * File:   CInterrogator.h
 * Author: kurian
 *
 * Created on November 28, 2013, 4:54 PM
 */

#ifndef CINTERROGATOR_H
#define	CINTERROGATOR_H

#include <iostream>
#include <string>
#include <cctype>
#include <list>

#include "typedefs.h"

#define FG_RED "\e[0;31m"

#ifndef TERM_RESET
  #define TERM_RESET "\e[m"
#endif

namespace spellcheck {
  using std::cout;
  using std::endl;
  using std::string;
  using std::list;
  using std::cin;
  
  class CInterrogator {
  private:
    
  public:
    CInterrogator();
    
    bool query (const string& buffer, match& choices, string& result);
    void print_heading (const string str);
    
    virtual ~CInterrogator();
  };
}

#endif	/* CINTERROGATOR_H */

