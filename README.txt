================================================================
  myELIZA - Primitive AI Chatbot (ELIZA Simulation)
  CSCE Project 2 - Milestone 1
================================================================

GROUP MEMBERS:
    Aryal, Samundra     
    Ghimire, Simran
    Pokhrel, Bijaya
    Byre ,Steven
    Nguyen, Aaron 
  

----------------------------------------------------------------
HOW TO COMPILE
----------------------------------------------------------------
On the UNT CSE CELL machines (or any Linux machine with g++):

  g++ -std=c++17 -o myEliza main.cpp genericVerbs.cpp responseTracker.cpp

If you are using a Makefile:
  make

----------------------------------------------------------------
HOW TO RUN
----------------------------------------------------------------
After compiling, run:

  ./myEliza

The program will greet you and wait for your input.
Type your message and press Enter to receive a response.
Type "bye" (without quotes) to end the session.

----------------------------------------------------------------
NOTES
----------------------------------------------------------------
- This is Milestone 1. The following component is implemented:
    * Generic Verbs (have, want, need, know, learn, travel, buy,
      do, make, get, try, think, feel, believe, like, remember)
- Repeated input detection is also implemented. If you type the
  same message more than once, ELIZA will prompt you to elaborate.
- All source files must be compiled together as shown above.
- Requires C++17 or later (for full regex support).

----------------------------------------------------------------
FILES INCLUDED
----------------------------------------------------------------
  main.cpp              - Main conversation loop (int main)
  genericVerbs.h        - Header for generic verbs component
  genericVerbs.cpp      - Implementation of generic verbs component
  responseTracker.h     - Header for repeated response tracker
  responseTracker.cpp   - Implementation of repeated response tracker
  README.txt            - This file
================================================================
