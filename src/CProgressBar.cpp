/* 
 * File:   CProgressBar.cpp
 * Author: kurian
 * 
 * Created on November 27, 2013, 7:46 PM
 */

#include "CProgressBar.h"

namespace spellcheck {
  
  /*
   * For time consuming operations, it is nice to have a progress bar
   * to make the user think that we are actually doing something.
   * Here, we accept an object that is notifiable(I actually meant monitorable,
   * but my vocabulary was not kind enough.) and periodically check it's
   * progress and report it to the user with some cool animation.
   */
  
  CProgressBar::CProgressBar(int rows, int columns, CNotifiable *subject) {
    this->n_rows = rows;
    this->n_coloumns = columns;
    
    /* The subject to monitor. */
    this->subject = subject;
    
    /* The characters for animation. */
    
    /* Horizontal line. */
    animate_char.push_back('-');
    
    /* Horizontal line, 45 degrees. */
    animate_char.push_back('/');
    animate_char.push_back('|');
    animate_char.push_back('\\');
  }
  
  /*
   * Create a progress monitoring thread, and start monitoring.
   */
  bool
  CProgressBar::start()
  {
    try
    {
      this_thread = new thread ([&](void) -> void
      {
        this->run();
      });
    }
    catch (system_error& err)
    {
      /* Oops! */
      return false;
    }
    
    return true;
  }
  
  /* 
   * The progress bar's main loop.
   */
  void
  CProgressBar::run ()
  {
    milliseconds forty_millisec(40);
    int count(0);
    curr_char = 0;
    
    cout << endl << subject->get_message() << endl << endl;
    
    while (true)
    {
      if (subject->is_error())
      {
        draw_error ();
        break;
      }
      else if (subject->is_complete())
      {
        draw_done ();
        break;
      }
      else {
        /* Still busy. */
        draw_progress ();
      }
      
      if (count & 1)
      {
        /*
         * "Harpier cries, 't's time, 't's time!"
         * ~ The witches, Macbeth by Shakespeare. 
         */
        if (curr_char >= animate_char.length())
        {
          curr_char = 0;
          count = 0;
        }
        else curr_char ++;
      }
      
      /* 
       * The effect of persistence of vision is around 50ms. Therfore, we need
       * to update the bar only 20 times a second.
       */
     
      std::this_thread::sleep_for(forty_millisec);
      count ++;
    }
  }
  
  void
  CProgressBar::draw_done()
  {
    draw_bar (string (BG_GREEN));
  }
  
  void
  CProgressBar::draw_error()
  {
    draw_bar (string (BG_RED));
  }
  
  void
  CProgressBar::draw_progress()
  {
    draw_bar (string (BG_BLUE));
  }
  
  void
  CProgressBar::draw_bar(const string colour)
  {
    int i, blocks, progress;
    
    /* Save the current cursor position. */
    cout << TERM_SAVE_POS;
    
    /* Animation. */
    cout << '[';
    
    progress = subject->get_progress();
    
    blocks = progress * n_coloumns / 100;
    
    /*
     * "Can't rely on anyone these days."
     * ~ The Joker, The Dark Knight
     */
    if (100 == progress)
      blocks = n_coloumns;
    
    /* Set the color. */
    cout << colour;
    
    for (i = 0; i < blocks; ++i)
      cout << ' ';
    
    /* Reset defaults. */
    cout << TERM_RESET;
    for (; i < n_coloumns; ++i)
      cout << ' ';
    
    cout << ']';
    
    /* Progress in percentage. */
    cout << progress << '%';
    
    /* Animation. */
    cout << ' ' << animate_char[curr_char];
    
    /* Return to the initial position. */
    cout << TERM_LOAD_POS;
    
    /* Okay. */
  }
  
  /* 
   * Do NOT call this function from within this_thread.
   * And also, do NOT forget to call this function from the thread that invoked
   * me.
   */
  void
  CProgressBar::wait_for()
  {
    this_thread->join();
    cout << endl << endl;
    /* Okay. */
  }
  
  CProgressBar::~CProgressBar() {
    /* Nothing to do. */
  }
} /* namespace */

