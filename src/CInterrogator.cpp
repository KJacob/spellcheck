/* 
 * File:   CInterrogator.cpp
 * Author: kurian
 * 
 * Created on November 28, 2013, 4:54 PM
 */

#include "CInterrogator.h"
#include "CProgressBar.h"

namespace spellcheck {
 
  CInterrogator::CInterrogator() {
    /* Nothing to do. */
  }
  
  bool
  CInterrogator::query(const string& buffer, match& choices, string& result)
  {
    int left, right, choice, i;
    word context = choices.first;
    list<string>::iterator it;
    
    for (left = context.first; left > 0; --left)
    {
      if (!isalnum (buffer[left]) && buffer[left] != ' ')
        break;
    }
    
    for (right = context.second; right < buffer.length(); ++right)
    {
      if (!isalnum (buffer[right]) && buffer [right] != ' ')
        break;
    }
    
    print_heading(string("CONTEXT"));
    cout << buffer.substr(left, context.first - left);
    
    /* Change color. That means highlight the incorrect word.*/
    cout << FG_RED;
    cout << buffer.substr(context.first, context.second - context.first);
    cout << TERM_RESET;
    cout << buffer.substr(context.second, right - context.second);
    
    cout << endl << "The highlighted word was not found. Did you mean ?\n"
            "0. No changes" << endl;
    for (i = 1, it = choices.second.begin(); it != choices.second.end(); ++it, ++i)
    {
      cout << i << ". " << *it << endl;
    }
    
    while (true)
    {
      cout << "\nEnter your choice: ";
      cin >> choice;
      
      if (choice > i || choice < 0)
      {
        cout << "Please. ";
      }
      else break;
    }
    
    if (!choice)
      result = buffer.substr(context.first, context.second - context.first);
    else
    {
      for (i = 1, it = choices.second.begin(); it != choices.second.end(); ++it, ++i)
      {
        if(i == choice)
        {
          result = *it;
          
          /* The user badly wants the word to begin with uppercase. */
          if (isupper (buffer[context.first]))
            result[0] = toupper(result[0]);
          break;
        }
      }
    }
      
    return true;
  }
  
  void
  CInterrogator::print_heading(const string str)
  {
    int len = str.length(), i;
    
    cout << endl << str << endl;
    for (i = 0; i < len; ++i)
      cout << "=";
    cout << endl;
  }

  CInterrogator::~CInterrogator() {
    /* No. Nothing to do. */
  }
} /* namespace */

