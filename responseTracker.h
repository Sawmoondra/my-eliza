#ifndef RESPONSETRACKER_H
#define RESPONSETRACKER_H

#include <string>
#include <map>

using namespace std;

// ResponseTracker: tracks how many times the user has given the same input
// so we can prompt them to give a different response if they repeat themselves.

class ResponseTracker {
public:
    // Record a user input; returns how many times it has been seen (including this time)
    int recordInput(const string& input);

    // Returns true if the user has said this exact thing more than once
    bool isRepeated(const string& input);

    // Returns a motivational nudge message for repeated inputs
    string getNudgeMessage();

private:
    // Maps each user input string to the number of times it has been seen
    map<string, int> inputHistory;
};

#endif // RESPONSETRACKER_H