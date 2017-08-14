/* 
 * File:   main.cpp
 * Author: kurian
 *
 * Created on November 21, 2013, 7:28 PM
 */
#include "CProgram.h"

int main(int argc, char** argv) {
  using namespace spellcheck;
  
  CProgram *app = new CProgram(argc, argv);
  int status;
  
  /* Starting.. */
  if (!app->init())
    return EXIT_FAILURE;
  
  /* Go, now! */
  status = app->run();
  
  delete app;
  return status;
}

