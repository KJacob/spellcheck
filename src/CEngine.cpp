/* 
 * File:   CEngine.cpp
 * Author: kurian
 * 
 * Created on November 28, 2013, 1:16 PM
 */

#include "CEngine.h"

namespace spellcheck {
  
  CEngine::CEngine(const string& strinfile, const string& strdict,
                   const string& stroutfile) {
    string message ("Analyzing..");
    
    this->strdict = strdict;
    this->strinfile = strinfile;
    this->stroutfile = stroutfile;
    
    this->init_progress();
    this->set_message(message);
    total_words = 0;
    total_threads = 0;
  }
  
  bool
  CEngine::start() throw (string)
  {
    CProgressBar *progressbar;
    bool result;
    
    dictionary = new CDictionary();
    progressbar = new CProgressBar(TERM_ROWS, TERM_COL, dictionary);
    
    /* 
     * Load the dictionary into memory..
     */
    progressbar->start();
    dictionary->init(strdict);
    progressbar->wait_for();
    delete progressbar;
    
    /* 
     * Try to set up the input file.. 
     */
    infile = new CInFile();
    infile->init(strinfile);
    
    /* Go! */
    result = this->run();
    
    return result;
  }
  
  bool
  CEngine::run() throw (string)
  {
    CProgressBar *progressbar;
    mutex *excluder = new mutex ();
    thread *all_threads[MAX_THREADS];
    CAnalyzer *analyzers[MAX_THREADS];
    
    word currword;
    string strword;
    
    int i;
    
    /* 
     * I am the one to be monitored. If you haven't noticed, I copied
     * CNotifiable onto me, and now I have notifying powers.
     */
    progressbar = new CProgressBar(TERM_ROWS, TERM_COL, this);
    
    /* Now start monitoring. */
    progressbar->start();
    
    /* 
     * On your arms.. 
     */
    while (infile->readword(currword))
    {
      strword = infile->get_buffer().substr(currword.first,
                                            currword.second - currword.first);
      
      /* Covert to lowercase. */
      for (i = 0; i < strword.length(); ++i)
        strword[i] = tolower (strword[i]);
      
      /* Ah, that is not in the dictionary. */
      if (!dictionary->query(strword))
        words.push_back (currword);
    }
    
    total_words = words.size();
    
    /*
     * "The weird sisters, hand in hand,
     * posters of sea and land, 
     * thus do go about, about
     * thrice to mine, and thrice to thine,
     * thrice again, to make up nine.
     * Peace! The charm's wound up."
     * 
     * ~ The Witches, Macbeth by Shakespeare.
     */
    try {
      for (i = 0; i < MAX_THREADS; ++i)
      {
        /* Fire! Fire All!! */
        analyzers[i] = new CAnalyzer(excluder, dictionary->get_tree());
        all_threads[i] = new thread ([&](CAnalyzer* analyzer) -> void
        {
          analyzer->run(infile->get_buffer(), words, matches);
        }, analyzers[i]);
      }
    }
    catch (system_error& error)
    {
      if (!i)
      {
        /* Notify the progress bar that something went wrong. */
        this->set_error();
        throw string ("The Scheduler is refusing to spawn threads.");
      }
    }
    
    total_threads = i;
    
    /* Wait for the threads to complete. */
    for (i = 0; i < total_threads; ++i)
      all_threads[i]->join();
    
    /* Clean up. */
    for (i = 0; i < total_threads; ++i)
    {
      delete all_threads[i];
      delete analyzers[i];
    }
    
    /* We have one more object to kill. */
    //delete analyzers[i];
    
    this->set_completed();
    progressbar->wait_for();
    
    delete progressbar;
    delete excluder;
    
    return save_corrections ();
  }
  
  /* 
   * @Override get_progress
   */
  uint
  CEngine::get_progress()
  {
    int progress;
    
    if (!this->total_words)
      return 0;
    
    if (this->is_complete())
      return 100;
    
    progress = total_words - words.size();
    
    return progress * 100 / total_words;
  }
  
  bool
  CEngine::save_corrections() throw (string)
  {
    COutFile *outfile = new COutFile();
    
    outfile->init (stroutfile);
    outfile->save(infile->get_buffer(), matches);
    
    delete outfile;
  }

  CEngine::~CEngine() {
    delete infile;
    delete dictionary;
  }
  
} /* namespace */

