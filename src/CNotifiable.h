/* 
 * File:   CNotifiable.h
 * Author: kurian
 *
 * Created on November 23, 2013, 9:40 PM
 */

#ifndef CNOTIFIABLE_H
#define	CNOTIFIABLE_H

#include <cstdlib>
#include <string>

namespace spellcheck
{
  
  /*
   * The Notifiable class.
   * Provides basic mechanism for inter-thread communication.
   * Inherit this class so that the inheriting class can notify the calling
   * thread the progress of tasks.
   */
  
  using std::string;
  
  class CNotifiable {
  private:
    
    /* The percentage of operation completed. */
    uint completed;
    
    string message;
    
    /* Are we done, or not? */
    bool done;
    
    /* Did we encounter an error? */
    bool error;
    
  public:
    CNotifiable();
    
    void set_progress (uint progress);
    virtual uint get_progress ();
    
    void init_progress ();
    
    void set_error ();
    bool is_error ();
    
    void set_completed ();
    bool is_complete ();
    
    void set_message (const string& msg);
    const string& get_message ();
  
    virtual ~CNotifiable();
  private:
  };
} /* namespace */

#endif	/* CNOTIFIABLE_H */

