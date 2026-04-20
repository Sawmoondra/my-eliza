#include "responseTracker.h"
#include <string>
#include <map>
#include <vector>

using namespace std;

// Record a user input and return the total count for that input
int ResponseTracker::recordInput(const string& input) {
    // Increment the count for this input (inserts with 0 if not present, then adds 1)
    inputHistory[input]++;
    return inputHistory[input];
}

// Returns true if the user has typed this exact input more than once
bool ResponseTracker::isRepeated(const string& input) {
    // Check if key exists and has been seen more than once
    if (inputHistory.find(input) != inputHistory.end()) {
        return inputHistory[input] > 1;
    }
    return false;
}

// Returns a nudge message encouraging the user to elaborate or try something different
string ResponseTracker::getNudgeMessage() {
    // A small set of varied nudge responses so we don't repeat ourselves either
    static vector<string> nudges = {
        "You've mentioned that before. Can you tell me more about it?",
        "We've touched on that already. Is there something deeper you'd like to explore?",
        "I notice you keep coming back to that. What does it really mean to you?",
        "You seem focused on that topic. Let's try approaching it from a different angle.",
        "That's come up before. Perhaps there's something else on your mind?",
        "That thought keeps coming up. What do you think it means?",
        "You've said that a few times now. Let's dig deeper into that."
    };

    // Rotate through nudges so they don't repeat either
    static int nudgeIndex = 0;
    string msg = nudges[nudgeIndex % nudges.size()];
    nudgeIndex++;
    return msg;
}