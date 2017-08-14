/* 
 * File:   CDictionary.cpp
 * Author: kurian
 * 
 * Created on November 22, 2013, 9:29 AM
 */

#include "CDictionary.h"

namespace spellcheck {
  
  CDictionary::CDictionary() {
    string message ("Loading dictionary onto memory..");
    
    /* Starting.. */
    this->init_progress();
    this->set_message(message);
  }
  
  void
  CDictionary::init(const string& file)
  {    
    dictfile.open(file, ifstream::in);
    
    if (dictfile.bad())
    {
      /* Kill the progress monitor, and then die. */
      this->set_error();
      throw string ("Could not open dictionary. ");
    }
    
    dictfile.seekg(0, ifstream::end);
    
    file_size = dictfile.tellg();
    
    /* Now go back. */
    dictfile.seekg(0, ifstream::beg);
    
    dictionary = new DICTNODE();
    
    populate ();
    
    this->set_progress(100);
    
    /* Done loading the dictionary. */
    this->set_completed();
  }
  
  /* Reads all words into memory, and sets up the dictionary tree. */
  void
  CDictionary::populate()
  {
    string word;
    
    while (dictfile.good())
    {
      dictfile >> word;
      insert (word);
      
      this->set_progress(dictfile.tellg() * 100 / file_size);
    }
  }
  
  /*
   * Inserts a word into the dictionary tree.
   * On error, throws string describing the message.
   */
  void
  CDictionary::insert(string& word)
  {
    int i, len(word.length());
    LPDICTNODE node(this->dictionary), newnode;
    
    for (i = 0; i < len; i++)
    {
      newnode = getchild (node, word[i]);
      
      if (!newnode)
      {
        /* Now we have to create a new node and add. */
        newnode = new DICTNODE ();
        newnode->letter = word[i];
        
        node->children.push_back(newnode);
      }
      
      node = newnode;
    }
    
    /* And now our special character indicating end of word. */
    newnode = getchild (node, '$');
    if (!newnode)
    {
      newnode = new DICTNODE ();
      newnode->letter = '$';
      
      node->children.push_back(newnode);
    }
    
    /* Okay. */
  }
  
  LPDICTNODE
  CDictionary::getchild(DICTTREE wordtree, char ch)
  {
    list<LPDICTNODE>::iterator it;
    
    for (it = wordtree->children.begin(); it != wordtree->children.end(); ++it)
    {
      if ((*it)->letter == ch)
        return *it;
    }
    
    return NULL;
  }
  
  void
  CDictionary::delete_tree(DICTTREE dictionary)
  {
    list<LPDICTNODE>::iterator it;
    
    /* Leaf. */
    if (!dictionary->children.size())
    {
      delete dictionary;
      return;
    }
    
    for (it = dictionary->children.begin(); it != dictionary->children.end(); ++it)
    {
      delete_tree (*it);
    }
    
    /* Now this node has become a zombie. */
    delete dictionary;
  }
  
  /*
   * This is the benefit of what we have done.
   * Contrary to popular belief, we can now check the existence of a 
   * particular word in the dictionary in O(p) time, where p denotes the
   * length of the word, as opposed to O(n), where n is the length of the
   * dictionary.
   * 
   ********************************************************************** 
   * "Beneath this mask, there is more than flesh.                      *
   *  Beneath this mask there is an idea, Mr. Creedy.                   *
   *  And ideas are bulletproof."                                       *
   *  ~ Hugo Weaving, V for Vendetta                                    *
   * ********************************************************************
   */
  
  bool
  CDictionary::query (string& word)
  {
    LPDICTNODE node(dictionary);
    int i;
    
    for (i = 0; i < word.length(); ++i)
    {
      node = getchild (node, word[i]);
      
      if (!node)
        return false;
    }
    
    if (getchild (node, '$'))
      return true;
    
    return false;
  }
  
  DICTTREE
  CDictionary::get_tree()
  {
    return this->dictionary;
  }
  
  CDictionary::~CDictionary() {
    
    dictfile.close();
    
    /*
     * Now we have to do a little housekeeping.
     * Perform a DFS, and destroy every node.
     */
    
    delete_tree (dictionary);
  }
}

