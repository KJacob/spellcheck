DESIGN OF THE COMPUTER PROGRAM SPELLCHECK
=========================================

By Kurian Jacob

1. main (): main () loads and starts the program.

2. Program object: The front end of the program. Parses the command line and
      starts the engine.
      
3. Engine: The middle end of the program. The engine has notifying capabilities.
      Other threads(threads of execution) can monitor and communicate with engine object.
      It starts the Analyzer (analyzers to be precise, because there are too many of them
      at a given time. Remember that this program is concurrent :)). The engine starts
      and stops the worker threads.
      
4. Dictionary: Loads and manages the dictionary file. It uses trees to represent the dictionary.
      With this approach, dictionary can check for the existence of a word in a fraction of a second.
      I used the dictionary that came with the Linux operating system containing about 0.45 million words.
      
5. Analyzer: The analyzer is responsible for enumerating the alternatives to misspelled words.
      The engine maintains a list of words to be corrected. Each analyzer picks one of them
      and tries to correct them using Damerau-Levenshtein algorithm. In this version, there are
      9 Analyzers working concurrently. That means, if your computer has more processors, this program
      works faster.
      
6. Progress bar: The progress bar tells the user about the progress of operation(obviously).
      It can take a notifiable object as it's argument and draw the progress bar accordingly.
      
7. Notifiable objects: Some objects in this program are notifiable. The Notifiable class
      is an abstract class that defines functions for inter-thread communication.
      
8. Infile: Infile objects represents the input file. It processes the input file.

9. Outfile: Outfile represents the output file.

10. Interrogator: This is a part of user interface. It presents the alternatives to misspelled words to
      the user and asks the user to resolve ambiguities.
      
COMPILATION
===========
If your computer is not a GNU/Linux 64 bit machine, then you may need to recompile the program.
This program will only work on UNIX and UNIX like operating systems such as GNU/Linux.

To compile the program using gcc, go to the src directory and run
   
      $ g++ -pthread -std=c++0x *.cpp -o bin/spellcheck
      
If there were no errors, gcc will create an ELF program in the bin directory. You can now run the program.
The working of the program is illustrated in screenshots.
