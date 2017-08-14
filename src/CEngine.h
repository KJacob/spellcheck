/* 
 * File:   CEngine.h
 * Author: kurian
 *
 * Created on November 28, 2013, 1:16 PM
 */

#ifndef CENGINE_H
#define	CENGINE_H

#include <string>
#include <thread>
#include <mutex>
#include <list>
#include <system_error>
#include <cctype>

#include "CDictionary.h"
#include "typedefs.h"
#include "CAnalyzer.h"
#include "CInFile.h"
#include "CNotifiable.h"
#include "COutFile.h"
#include "CProgressBar.h"

#define TERM_ROWS 120
#define TERM_COL 70

/* The maximum number of threads. */
#define MAX_THREADS 9

namespace spellcheck {
  
  using std::thread;
  using std::mutex;
  using std::string;
  using std::list;

  class CEngine : public CNotifiable{
  private:
    string strinfile, strdict, stroutfile;
    CDictionary *dictionary;
    CInFile *infile;
    list<word> words;
    list<match> matches;
    uint total_words, total_threads;
    
  public:
    CEngine(const string& strinfile, const string& strdict, const string& stroutfile);
    
    /* start() is the function to be called from outside. */
    bool start () throw(string);
    bool run () throw (string);
    bool save_corrections () throw (string);
    
    virtual uint get_progress ();
    
    virtual ~CEngine();
  };
} /* namespace */

#endif	/* CENGINE_H */

