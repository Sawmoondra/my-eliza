#include "love.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for love and relationship related user input
static const vector<pair<string, string>> lovePatterns = {

    // ── LOVE ─────────────────────────────────────────────────────────────────
    { "i (am in love|have fallen in love) with (.*)",
      "Tell me more about your feelings for $2. How long have you felt this way?" },

    { "i (love|adore|am crazy about) (.*)",
      "What is it about $2 that you love so much?" },

    { "i (don't|do not|dont) love (.*) anymore",
      "What do you think changed your feelings toward $2?" },

    { "i (have never|never) (been in love|loved anyone)",
      "What do you think has prevented you from experiencing love?" },

    // ── GIRLFRIEND / BOYFRIEND ───────────────────────────────────────────────
    { "my (girlfriend|boyfriend) (.*)",
      "Tell me more about your $1. How does that make you feel?" },

    { "i (don't|do not|dont) have a (girlfriend|boyfriend)",
      "How do you feel about not having a $2 right now?" },

    { "i (want|need) a (girlfriend|boyfriend)",
      "What do you think is stopping you from finding a $2?" },

    { "my (girlfriend|boyfriend) (left me|broke up with me|cheated on me)",
      "That sounds very painful. How are you coping with what your $1 did?" },

    { "i (broke up|broke up with|ended things) with (.*)",
      "Breaking up can be very hard. How are you feeling after ending things with $2?" },

    // ── SPOUSE / MARRIAGE ────────────────────────────────────────────────────
    { "my (husband|wife|spouse) (.*)",
      "Tell me more about your $1. What is going on between you two?" },

    { "i (want to|am thinking about) (get married|propose|marriage)",
      "Marriage is a big step. What makes you feel ready for that commitment?" },

    { "i (am getting|got) divorced",
      "Divorce can be an emotionally difficult process. How are you feeling about it?" },

    { "my (husband|wife|spouse) (left me|cheated on me|doesn't love me)",
      "That must be incredibly painful. How long have things been difficult with your $1?" },

    { "i (am|have been) (married|engaged) (for |to )?(.*)",
      "How has your relationship been going with $4?" },

    // ── PARTNER / DATING ─────────────────────────────────────────────────────
    { "my (partner|significant other) (.*)",
      "Tell me more about your partner. What has been happening?" },

    { "i (am|have been) (dating|seeing) (.*)",
      "How is your relationship going with $3?" },

    { "i (met|found) someone (.*)",
      "That sounds exciting. Tell me more about this person." },

    { "i (am|feel) (lonely|alone) (without|since) (.*)",
      "It sounds like $4 has had a big impact on you. How long have you felt this way?" },

    // ── HEARTBREAK / REJECTION ───────────────────────────────────────────────
    { "i (got|was) (rejected|turned down) by (.*)",
      "Rejection can be very hard to deal with. How are you feeling about what happened with $3?" },

    { "i (am|feel) (heartbroken|devastated|crushed) (over|about|because of) (.*)",
      "Heartbreak is one of the hardest emotions to go through. What happened with $4?" },

    { "i (can't|cannot) (get over|stop thinking about|move on from) (.*)",
      "It sounds like $3 means a lot to you. What makes it so hard to move on?" },

    { "i (miss|still miss) (.*)",
      "What do you miss most about $2?" },

    // ── TRUST / JEALOUSY ─────────────────────────────────────────────────────
    { "i (don't|do not|dont) trust (.*)",
      "What happened that made you lose trust in $2?" },

    { "i (am|feel) (jealous|envious) (of |about )?(.*)",
      "Jealousy can be a very consuming feeling. What triggered these feelings about $4?" },

    { "my (partner|girlfriend|boyfriend|spouse|husband|wife) (cheated|lied|betrayed) (on me|to me)?",
      "Betrayal in a relationship is deeply painful. How long have you known about this?" },

    // ── ATTRACTION / CRUSH ───────────────────────────────────────────────────
    { "i (have a crush|like someone|am attracted to) (.*)",
      "Tell me more about your feelings. Have you expressed them to this person?" },

    { "i (am|feel) (attracted to|interested in) (.*)",
      "What draws you to $3?" },

    // ── RELATIONSHIP PROBLEMS ────────────────────────────────────────────────
    { "my (relationship|marriage) (is|has been) (.*)",
      "It sounds like your $1 has been $3. What do you think is at the root of the problem?" },

    { "we (fight|argue|disagree) (all the time|constantly|a lot)",
      "Constant conflict can be exhausting. What do you and your partner typically fight about?" },

    { "i (feel|am) (not loved|unloved|unwanted|unappreciated) (by |in )?(.*)",
      "Feeling $2 in a relationship is very difficult. Have you talked to your partner about this?" },

    { "i (am|feel) (happy|content|satisfied) (in|with) my (relationship|marriage)",
      "That is wonderful to hear. What do you think makes your $5 work so well?" }
};

// Returns first matched response or empty string if no pattern matched
string handleLove(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : lovePatterns) {
        const string& patternStr = entry.first;
        const string& responseTemplate = entry.second;

        try {
            regex pattern(patternStr, flags);

            if (regex_search(input, pattern)) {
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
            continue;
        }
    }

    return "";
}