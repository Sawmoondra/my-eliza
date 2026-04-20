#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "genericVerbs.h"
#include "responseTracker.h"

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Helper: trim leading/trailing whitespace from a string
// ─────────────────────────────────────────────────────────────────────────────
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

// ─────────────────────────────────────────────────────────────────────────────
// main: drives the ELIZA conversation loop.
// Reads user input, checks for repetition, routes to the appropriate
// component handler, and prints a response.
// Exits when the user types "bye".
// ─────────────────────────────────────────────────────────────────────────────
int main() {

    ResponseTracker tracker;
    string userInput;

    // Greeting
    cout << "=========================================\n";
    cout << "  Welcome to myELIZA - Your AI Therapist \n";
    cout << "=========================================\n";
    cout << "Hello. I am Dr. ELIZA, your psychiatrist. Please share what is on your mind today.\n";
    cout << "(Type 'bye' at any time to end the session.)\n\n";

    // Main conversation loop
    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        // Trim whitespace
        userInput = trim(userInput);

        // Skip empty input
        if (userInput.empty()) {
            cout << "ELIZA: Please, go on.\n\n";
            continue;
        }

        // Exit condition
        string lowerInput = userInput;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        if (lowerInput == "bye") {
            cout << "ELIZA: Goodbye. I hope our session was helpful. Take care.\n";
            break;
        }

        // ── Repeated response check ───────────────────────────────────────────
        // Record the input and check if it has been seen before
        tracker.recordInput(lowerInput);
        if (tracker.isRepeated(lowerInput)) {
            cout << "ELIZA: " << tracker.getNudgeMessage() << "\n\n";
            continue;
        }

        // ── Route to component handlers ───────────────────────────────────────
        // Milestone 1: only the generic verbs component is active.
        // Future milestones will add more handlers here (love, concern, etc.)
        string response = handleGenericVerbs(userInput);

        cout << "ELIZA: " << response << "\n\n";
    }

    return 0;
}