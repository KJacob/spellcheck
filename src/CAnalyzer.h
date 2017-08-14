/* 
 * File:   CAnalyzer.h
 * Author: kurian
 *
 * Created on November 22, 2013, 7:57 PM
 */

#ifndef CANALYZER_H
#define	CANALYZER_H

#include <mutex>
#include <string>
#include <list>
#include <cctype>

#include "CDictionary.h"

/* We assume that the longest word is no longer than MAX_WORDLEN. */
#define MAX_WORDLEN 70

#define INFINITY 0xFF

/*
 * Since we consider spell checking to be a time consuming job,
 * to equalize the load on every processor, we will spawn a previously
 * determined number of threads, each one of which shall have an associated
 * Analyzer object, which will find out possible matches to the misspelled word.
 * To get this done, we will maintain a primary list of misspelled words shared
 * by each Analyzer object. Each one of the Analyzer object shall pull one of
 * these words and delete it from the list, and this delete operation will be
 * protected by a global mutex object.
 * 
 * Foundations of Programming course requires its students to answer with
 * at most two sentences, but it failed to specify how long the two sentences
 * could be.
 */

namespace spellcheck {
  
  using std::list;
  using std::string;
  using std::mutex;

  class CAnalyzer {
  private:
    mutex* excluder;
    DICTTREE dictionary;
    
    string dfsword;
    
    /* The Damerau-Levenshtein distance table. */
    uint *lev_matrix[MAX_WORDLEN], lev_i;
    
    /* The minimum Damerau-Lavenshtein distance in the current row. */
    uint *prev_min_dist;
    
    uint currmindist;
    
  public:
    CAnalyzer(mutex* excluder, const DICTTREE dictionary);
    
    void run (const string& input, list<word>& words, list<match>& matches);
    void find_matches (string& wword, match& currmatch);
    
    void guess (string& wword, match& currmatch, DICTTREE dict);
    
    virtual ~CAnalyzer();
  };
  
} /* namespace */

#endif	/* CANALYZER_H */

