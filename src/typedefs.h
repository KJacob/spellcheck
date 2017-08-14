/* 
 * File:   typedefs.h
 * Author: kurian
 *
 * Created on November 21, 2013, 9:32 PM
 */

#ifndef TYPEDEFS_H
#define	TYPEDEFS_H

#include <list>
#include <cstdlib>
#include <string>

namespace spellcheck {
  
  using std::list;
  using std::pair;
  using std::string;
  
  /*
   * The dictionary tree shall be representing the entire dictionary.
   * We will use a special character '$' to denote a node that marks the end of
   * a word, hoping that the letter '$' will never show up in any word 
   * in the dictionary.
   */
  
  typedef struct _tagDICTNODE
  {
    char letter;
    list<_tagDICTNODE *> children;
  } DICTNODE, *LPDICTNODE;
  
  typedef LPDICTNODE DICTTREE;
  
  /* The first and second elements of the pair points to characters in the 
   * main string.
   */
  typedef pair<uint, uint> word;
  typedef pair<word, list<string> > match;
} /* spellcheck namespace */
#endif	/* TYPEDEFS_H */

