#ifndef GENERICVERBS_H
#define GENERICVERBS_H

#include <string>

using namespace std;


// genericVerbs: handles user input that contains common generic action verbs
// such as have, purchase, travel, know, learn, get, want, need, do, make, etc.
// Uses C++ regex (regex_search, regex_match, regex_replace) to detect patterns
// and generate contextually appropriate psychiatrist-style responses.

// Main function: takes the user's input string, checks it against all
// generic-verb patterns, and returns a response string.
// Returns an empty string if no pattern matched (so main can try other components).
string handleGenericVerbs(const string& input);

#endif // GENERICVERBS_H