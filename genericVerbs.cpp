// ─────────────────────────────────────────────────────────────
// Added Contribution:
// This file handles user input related to generic verbs using
// regex pattern matching. Each pattern maps user input to a
// response template, helping simulate conversational behavior.
// ─────────────────────────────────────────────────────────────
#include "genericVerbs.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>   // for pair
#include <algorithm> // for transform
#include <cctype>    // for ::tolower

using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// Helper: convert a string to lowercase for case-insensitive matching
// ─────────────────────────────────────────────────────────────────────────────
static string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// ─────────────────────────────────────────────────────────────────────────────
// Each entry is a pair of:
//   - a regex pattern string (matched case-insensitively via regex_search)
//   - a response string (may use $1, $2 capture groups via regex_replace)
//
// Patterns are tried in order; the first match wins.
// ─────────────────────────────────────────────────────────────────────────────
static const vector<pair<string, string>> verbPatterns = {

    // ── HAVE ──────────────────────────────────────────────────────────────────
    { "i have (a |an )?(.*)",
      "Why do you feel that having $2 is important to you?" },

    { "i (don't|do not|dont) have (.*)",
      "How does not having $2 affect your daily life?" },

    { "i (wish|want) i had (.*)",
      "What would change for you if you had $2?" },

    { "i (used to|once) have (.*)",
      "Tell me more about when you had $2. What happened?" },

    { "do you have (.*)",
      "Why do you ask whether I have $1?" },

    // ── WANT / NEED ───────────────────────────────────────────────────────────
    { "i (really |desperately |just )?want (to |a |an )?(.*)",
      "What do you think is stopping you from getting $3?" },

    { "i (really |desperately |just )?need (to |a |an )?(.*)",
      "Why do you feel you need $3 so strongly?" },

    { "i (don't|do not|dont) want (.*)",
      "What makes you feel that way about $2?" },

    { "i (don't|do not|dont) need (.*)",
      "Are you certain you don't need $2? Why do you say that?" },

    { "all i (want|need) is (.*)",
      "Is $2 really all you want? Tell me more." },

    // ── KNOW ──────────────────────────────────────────────────────────────────
    { "i (don't|do not|dont) know (.*)",
      "Why do you think you don't know $2?" },

    { "i know (that |how |why |when )?(.*)",
      "How did you come to know $2?" },

    { "i (wish|want) i (knew|understood) (.*)",
      "What would knowing $3 change for you?" },

    { "do you know (.*)",
      "Why does it matter to you whether I know $1?" },

    { "nobody knows (.*)",
      "Does it bother you that nobody knows $1?" },

    // ── LEARN ─────────────────────────────────────────────────────────────────
    { "i (want to|need to|should|am trying to) learn (.*)",
      "What motivated you to want to learn $2?" },

    { "i('m| am) learning (.*)",
      "How do you feel about learning $2 so far?" },

    { "i (can't|cannot|could not|couldn't) learn (.*)",
      "What makes you feel you are unable to learn $2?" },

    { "i learned (that |about |how )?(.*)",
      "How has learning $2 changed your perspective?" },

    { "i (wish|want) i could learn (.*)",
      "What has prevented you from learning $2 until now?" },

    // ── TRAVEL / GO ───────────────────────────────────────────────────────────
    { "i (want to|would like to|am going to|plan to) travel (to |around )?(.*)",
      "What draws you to traveling to $3?" },

    { "i (traveled|went|have been) to (.*)",
      "How did going to $2 make you feel?" },

    { "i (can't|cannot|couldn't) travel (.*)",
      "Why do you feel you cannot travel $2?" },

    { "i (love|enjoy|like) traveling",
      "What is it about traveling that you enjoy so much?" },

    { "i (hate|dislike|don't like) traveling",
      "Why does traveling feel unpleasant to you?" },

    // ── PURCHASE / BUY ────────────────────────────────────────────────────────
    { "i (want to|need to|am going to|plan to) (buy|purchase) (.*)",
      "What prompted you to want to buy $3?" },

    { "i (bought|purchased) (.*)",
      "How did buying $2 make you feel?" },

    { "i (can't|cannot|couldn't) (buy|purchase|afford) (.*)",
      "How does it affect you that you cannot afford $3?" },

    { "i (always|keep|tend to) (buy|purchase|spend money on) (.*)",
      "Do you think buying $3 so often is fulfilling a deeper need?" },

    // ── DO / DID ──────────────────────────────────────────────────────────────
    { "i (don't|do not|dont) (want to |like to |know how to )?do (.*)",
      "Why don't you want to do $3?" },

    { "i (do|did) (.*) (every day|all the time|constantly|always)",
      "You $2 $3 — does that ever feel overwhelming?" },

    { "i did (.*)",
      "How did you feel after you did $1?" },

    { "why (do|did|should|would) (i|we|you|they|he|she) (.*)",
      "What answer would satisfy you most to that question?" },

    { "what (do|did|should|would) (i|we|you|they) (.*)",
      "That's an interesting question. What do you think?" },

    // ── MAKE / CREATE ─────────────────────────────────────────────────────────
    { "i (want to|am trying to|am going to) make (.*)",
      "What inspires you to want to make $2?" },

    { "i made (.*)",
      "How did you feel when you made $1?" },

    { "i (can't|cannot|couldn't) make (.*)",
      "What is it that stops you from making $2?" },

    // ── GET ───────────────────────────────────────────────────────────────────
    { "i (want to|need to|am trying to) get (.*)",
      "What does getting $2 mean to you?" },

    { "i (can't|cannot|couldn't|could not) get (.*)",
      "Why do you feel you can't get $2?" },

    { "i got (.*)",
      "How do you feel about getting $1?" },

    // ── TRY ───────────────────────────────────────────────────────────────────
    { "i('m| am) (trying|attempting) to (.*)",
      "What challenges have you faced while trying to $3?" },

    { "i (tried|attempted) to (.*)",
      "What happened when you tried to $2?" },

    { "i (can't|cannot|couldn't) (try|seem to) (.*)",
      "What is stopping you from $3?" },

    // ── THINK / FEEL / BELIEVE ────────────────────────────────────────────────
    { "i think (that )?(.*)",
      "Why do you think $2?" },

    { "i (feel|am feeling) (.*)",
      "Tell me more about feeling $2." },

    { "i believe (that )?(.*)",
      "What leads you to believe $2?" },

    { "i (don't|do not|dont) think (that )?(.*)",
      "Why don't you think $3?" },

    // ── LIKE / ENJOY / PREFER ─────────────────────────────────────────────────
    { "i (like|enjoy|love) (to |doing )?(.*)",
      "What is it about $3 that you enjoy?" },

    { "i (don't|do not|dont) (like|enjoy) (.*)",
      "What is it about $3 that bothers you?" },

    { "i prefer (.*) (over|to|rather than) (.*)",
      "Why do you prefer $1 over $3?" },

    // ── REMEMBER / FORGET ────────────────────────────────────────────────────
    { "i remember (.*)",
      "What feelings come up when you remember $1?" },

    { "i (can't|cannot|couldn't) remember (.*)",
      "Why do you think you have trouble remembering $2?" },

    { "i (always |keep )?forget (.*)",
      "Why do you think you keep forgetting $2?" },

    // ── GENERIC FALLBACK FOR ANY VERB SENTENCE ───────────────────────────────
    { "i (.*)",
      "You said you $1. Can you tell me more about that?" },

    { "(.*) (have|has|had) (.*)",
      "Why does it matter to you that $1 $2 $3?" },

    { "(.*)",
      "Interesting. Can you elaborate on that?" }
};

// ─────────────────────────────────────────────────────────────────────────────
// handleGenericVerbs: tries each pattern in order and returns the first match.
// Uses regex_search for flexible substring matching, and regex_replace to
// substitute capture groups into the response template.
// Returns "" if somehow nothing matched (shouldn't happen with the catch-all).
// ─────────────────────────────────────────────────────────────────────────────
string handleGenericVerbs(const string& input) {

    // Use case-insensitive flag for all matching
    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : verbPatterns) {
        const string& patternStr = entry.first;
        const string& responseTemplate = entry.second;

        try {
            regex pattern(patternStr, flags);

            // Check if the pattern matches anywhere in the input
            if (regex_search(input, pattern)) {
                // Use regex_replace to substitute capture groups ($1, $2, etc.)
                // into the response template
                string response = regex_replace(
                    input,
                    pattern,
                    responseTemplate,
                    regex_constants::format_first_only
                );
                return response;
            }
        }
        catch (const regex_error& e) {
            // If a regex is malformed, skip it and continue
            continue;
        }
    }

    // Should never reach here due to catch-all pattern, but just in case:
    return "Tell me more about that.";
}
