#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "genericVerbs.h"
#include "responseTracker.h"
#include "love.h"
#include "concern.h"
#include "entertainment.h"
#include "financial.h"
#include "wellbeing.h"
#include "education.h"

using namespace std;

// Trim leading and trailing whitespace from a string
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

int main() {

    ResponseTracker tracker;
    string userInput;

    cout << "=========================================\n";
    cout << "  Welcome to myELIZA - Your AI Therapist \n";
    cout << "=========================================\n";
    cout << "Hello. I am Dr. ELIZA, your psychiatrist. Please share what is on your mind today.\n";
    cout << "(Type 'bye' at any time to end the session.)\n\n";

    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        userInput = trim(userInput);

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

        // Check for repeated input
        tracker.recordInput(lowerInput);
        if (tracker.isRepeated(lowerInput)) {
            cout << "ELIZA: " << tracker.getNudgeMessage() << "\n\n";
            continue;
        }

        // Route input through each component handler in order
        string response = handleConcern(userInput);
        if (response.empty()) response = handleLove(userInput);
        if (response.empty()) response = handleFinancial(userInput);
        if (response.empty()) response = handleWellbeing(userInput);
        if (response.empty()) response = handleEducation(userInput);
        if (response.empty()) response = handleEntertainment(userInput);
        if (response.empty()) response = handleGenericVerbs(userInput);

        cout << "ELIZA: " << response << "\n\n";
    }

    return 0;
}