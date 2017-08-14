/* 
 * File:   CProgram.cpp
 * Author: kurian
 * 
 * Created on November 28, 2013, 8:18 PM
 */

#include "CProgram.h"

namespace spellcheck {
  CProgram::CProgram(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
    engine = NULL;
  }
  
  bool
  CProgram::init()
  {
    /* 
     * Try to decipher the arguments.  
     */
    try {
      parse_arguments ();
    }
    catch (string& error)
    {
      cerr << "Error: " << error << endl;
      display_help ();
      return false;
    }
    
    return true;
  }
  
  void
  CProgram::parse_arguments()
  {
    progname = string (*argv++);
    argc --;
    
    if (argc != 6)
      throw string ("Incorrect number of arguments.");
    
    while (argc)
    {
      if (**argv == '-')
      {
        switch (*(*argv + 1))
        {
          case 'd':
            strdict = string (*++argv);
            break;
            
          case 'i':
            strinfile = string (*++argv);
            break;
            
          case 'o':
            stroutfile = string (*++argv);
            break;
            
          default:
            throw string ("Unknown option: ") + string (*argv + 1);
        }
        
        argv ++;
        argc -= 2;
      }
      else
        throw string ("Command without a switch.");
    }
  }
  
  void
  CProgram::display_help()
  {
    cout << "Spellcheck by Kurian Jacob.\n"
            "Copyleft (cc) Kurian Jacob. Zero rights reserved. \n\n"
            "Usage: " << progname << " -d <dictionary> -o <output file> "
            "-i <input file>" << endl;
  }
  
  int
  CProgram::run()
  {
    engine = new CEngine (strinfile, strdict, stroutfile);
    
    try {
      engine->start();
    }
    catch (string &error)
    {
      cerr << "Unexpected error: " << error << endl;
      return EXIT_FAILURE;
    }
    catch (...)
    {
      cerr << "FATAL: Unknown error." << endl;
      return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
  }

  CProgram::~CProgram() {
    if (engine)
      delete engine;
  }
} /* namespace */

