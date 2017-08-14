/* 
 * File:   CProgressBar.h
 * Author: kurian
 *
 * Created on November 27, 2013, 7:46 PM
 */

#ifndef CPROGRESSBAR_H
#define	CPROGRESSBAR_H

#include <thread>
#include <system_error>
#include <chrono>
#include <iostream>
#include <string>

#include "CNotifiable.h"

/* Color schemes */
#define BG_GREEN "\e[0;42m"
#define BG_RED "\e[0;41m"
#define BG_BLUE "\e[0;44m"

/* ANSI Terminal Operations. */
#define TERM_SAVE_POS "\e[s"
#define TERM_LOAD_POS "\e[u"

/* Reset operation. */
#define TERM_RESET "\e[m"

namespace spellcheck {
  using std::thread;
  using std::system_error;
  using std::chrono::milliseconds;
  using std::cout;
  using std::string;
  using std::endl;
  
  class CProgressBar {
  private:
    int n_rows, n_coloumns;
    thread *this_thread;
    CNotifiable *subject;
    string animate_char;
    int curr_char;
    
  public:
    CProgressBar(int rows, int columns, CNotifiable *subject);
    
    bool start ();
    void run ();
    
    void draw_error ();
    void draw_done ();
    void draw_progress ();
    
    /* Actual drawing. */
    void draw_bar (const string colour);
    
    /* Wait for completion. */
    void wait_for ();
    
    virtual ~CProgressBar();
  private:
  };

} /* namespace */

#endif	/* CPROGRESSBAR_H */

