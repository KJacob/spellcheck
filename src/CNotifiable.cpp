/* 
 * File:   CNotifiable.cpp
 * Author: kurian
 * 
 * Created on November 23, 2013, 9:40 PM
 */

#include "CNotifiable.h"

namespace spellcheck {
 
  CNotifiable::CNotifiable() {
  }
  
  void
  CNotifiable::set_progress(uint progress)
  {
    this->completed = progress;
  }
  
  void
  CNotifiable::init_progress()
  {
    /* Initial settings. */
    this->completed = 0;
    this->error = false;
    this->done = false;
    this->message.clear();
  }
  
  uint
  CNotifiable::get_progress()
  {
    return this->completed;
  }
  
  void
  CNotifiable::set_error()
  {
    error = true;
  }
  
  bool
  CNotifiable::is_error()
  {
    return this->error;
  }
  
  void
  CNotifiable::set_completed()
  {
    this->done = true;
  }
  
  bool
  CNotifiable::is_complete()
  {
    return this->done;
  }
  
  void
  CNotifiable::set_message(const string& msg)
  {
    this->message = msg;
  }
  
  const
  string&
  CNotifiable::get_message()
  {
    return this->message;
  }

  CNotifiable::~CNotifiable() {
    /* No. Nothing to do. */
  }
}

