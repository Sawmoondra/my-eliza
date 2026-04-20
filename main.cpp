#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

#include "genericVerbs.h"
#include "responseTracker.h"

// ─────────────────────────────────────────────────────────────────────────────
// Helper: trim leading/trailing whitespace from a string
// ─────────────────────────────────────────────────────────────────────────────
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
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
    std::string userInput;

    // Greeting
    std::cout << "=========================================\n";
    std::cout << "  Welcome to myELIZA - Your AI Therapist \n";
    std::cout << "=========================================\n";
    std::cout << "Hello. I am your psychiatrist. Please tell me what is on your mind.\n";
    std::cout << "(Type 'bye' at any time to end the session.)\n\n";

    // Main conversation loop
    while (true) {
        std::cout << "You: ";
        std::getline(std::cin, userInput);

        // Trim whitespace
        userInput = trim(userInput);

        // Skip empty input
        if (userInput.empty()) {
            std::cout << "ELIZA: Please, go on.\n\n";
            continue;
        }

        // Exit condition
        std::string lowerInput = userInput;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        if (lowerInput == "bye") {
            std::cout << "ELIZA: Goodbye. I hope our session was helpful. Take care.\n";
            break;
        }

        // ── Repeated response check ───────────────────────────────────────────
        // Record the input and check if it has been seen before
        tracker.recordInput(lowerInput);
        if (tracker.isRepeated(lowerInput)) {
            std::cout << "ELIZA: " << tracker.getNudgeMessage() << "\n\n";
            continue;
        }

        // ── Route to component handlers ───────────────────────────────────────
        // Milestone 1: only the generic verbs component is active.
        // Future milestones will add more handlers here (love, concern, etc.)
        std::string response = handleGenericVerbs(userInput);

        std::cout << "ELIZA: " << response << "\n\n";
    }

    return 0;
}
