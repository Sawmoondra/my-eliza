#ifndef CONCERN_H
#define CONCERN_H

#include <string>

using namespace std;

// Handles user input containing sensitive or distressing keywords
// such as hate, kill, suicide, hurt, depressed, angry, etc.
string handleConcern(const string& input);

#endif // CONCERN_H