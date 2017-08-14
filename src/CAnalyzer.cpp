/* 
 * File:   CAnalyzer.cpp
 * Author: kurian
 * 
 * Created on November 22, 2013, 7:57 PM
 */

#include "CAnalyzer.h"

namespace spellcheck {

  CAnalyzer::CAnalyzer(mutex* excluder, const DICTTREE dictionary) {
    this->excluder = excluder;
    this->dictionary = dictionary;
    
    int i;
    
    for (i = 0; i < MAX_WORDLEN; ++i)
      lev_matrix[i] = new uint[MAX_WORDLEN];
    
    prev_min_dist = new uint [MAX_WORDLEN];
  }
  
  /*
   * The next most important loop. Retrieves jobs from the list,
   * and processes them one after the other.
   * 
   * @FIXME: In fact, we need two mutex objects for optimal performance.
   * At this moment, such a performance benefit is unnecessary. If the need comes,
   * modify the below functions such that removal of a job and addition
   * of a result excluded by two 'muteces'.
   */
  
  void
  CAnalyzer::run(const string& input, list<word>& words, list<match>& matches)
  {
    /* All matches. */
    match currmatch;
    
    /* The word to be searched. */
    string wword;
    
    /* The current word. */
    word currword;
    
    while (true)
    {
      /* Where is your pass? */
      excluder->lock();
      
      if (words.empty())
      {
        /* And now we're done. */
        excluder->unlock();
        break;
      }
      
      currword = words.front();
      
      /* Now get the word to be compared. */
      wword = input.substr(currword.first, currword.second - currword.first);
      
      /* Delete the word from job list. */
      words.pop_front();
      
      excluder->unlock();
      
      currmatch.first = currword;
      find_matches (wword, currmatch);
      
      excluder->lock();
      matches.push_back(currmatch);
      excluder->unlock();
    }
  }
  
  void
  CAnalyzer::find_matches(string& wword, match& currmatch)
  {
    int j;
    
    /* Set the current search word to empty. */
    dfsword.clear();
    
    /* We are just beginning. */
    lev_i = 1;
    
    /* 256 is infinity for us. */
    currmindist = INFINITY;
    
    /* Preparing the initial table.. */
    for (j = 0; j <= wword.length(); ++j)
    {
      lev_matrix[0][j] = j;
    }
    
    /* Obviously, the minimum distance in the first row is zero. */
    prev_min_dist[0] = 0;
    
    guess (wword, currmatch, this->dictionary);
  }
  
  /*
   * CAnalyzer::guess : Enumerates all the possibilities using the
   * Damerau-Levenshtein algorithm. 
   */
  
  void
  CAnalyzer::guess(string& wword, match& currmatch, DICTTREE dict)
  {
    list<LPDICTNODE>::iterator it;
    int j, mindist, currdist;
    
    if (lev_i > 1)
    {
      /* There's no point in going forward. */
      if (prev_min_dist[lev_i - 2] > currmindist)
        return;
    }
    
    prev_min_dist[lev_i] = lev_i;
    
    for (it = dict->children.begin(); it != dict->children.end(); ++it)
    {
      if ((*it)->letter == '$')
      {
        /* We are now at the end of a word. Check whether we need to add it. */
        int newmindist(lev_matrix[lev_i - 1][wword.length()]);
        
        if (newmindist == currmindist)
        {
          currmatch.second.push_back(dfsword);
        }
        else if (newmindist < currmindist)
        {
          /* Clear everything. */
          currmatch.second.clear();
          currmatch.second.push_back(dfsword);
          
          /* Reset the minimum distance.*/
          currmindist = newmindist;
        }
      }
      else {
        lev_matrix [lev_i][0] = dfsword.length() + 1;
        
        for (j = 1; j <= wword.length(); ++j)
        {
          mindist = 1 + lev_matrix [lev_i - 1][j];
          currdist = 1 + lev_matrix [lev_i] [j - 1];
          
          mindist = mindist > currdist ? currdist : mindist;
          
          currdist = lev_matrix[lev_i - 1][j - 1];
          
          /* We need case insensitive comparison. */
          if (tolower ((*it)->letter) != tolower(wword[j - 1]))
            currdist++;
          
          mindist = mindist > currdist ? currdist : mindist;
          
          if (lev_i > 1
              && j > 1
              && tolower(wword[j - 1]) == tolower(dfsword[lev_i - 2])
              && tolower(wword [j - 2]) == tolower((*it)->letter))
          {
            currdist = lev_matrix[lev_i - 2][j - 2] + 1;
            mindist = mindist > currdist ? currdist : mindist;
          }
          
          lev_matrix [lev_i][j] = mindist; 
          
          if (prev_min_dist[lev_i] > mindist)
            prev_min_dist[lev_i] = mindist;
        }
        
        lev_i++;
        dfsword.push_back((*it)->letter);
        
        guess (wword, currmatch, *it);
        
        /* Step back, and enter the sibling of the current node if possible. */
        lev_i--;
        dfsword.pop_back();
      }
    }
  }

  CAnalyzer::~CAnalyzer() {
    int i;
    
    for (i = 0; i < MAX_WORDLEN; i++)
      delete[] lev_matrix[i];
      
      delete[] prev_min_dist;
  }

} /* namespace */