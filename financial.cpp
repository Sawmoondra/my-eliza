#include "financial.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for financial related user input
static const vector<pair<string, string>> financialPatterns = {

    // ── MONEY / GENERAL ──────────────────────────────────────────────────────
    { "i (don't|do not|dont) have (enough )?(money|cash|funds)",
      "How does not having enough money affect your daily life?" },

    { "i (need|want) (more )?(money|cash|funds)",
      "What would having more money change for you?" },

    { "i (am|have been) (broke|out of money|penniless)",
      "That sounds stressful. How long have you been in this situation?" },

    { "money (is|has been) (a problem|an issue|tight|stressful) (for me)?",
      "Financial stress can affect every part of life. What do you think caused this situation?" },

    // ── DEBT ─────────────────────────────────────────────────────────────────
    { "i (am|have been) (in debt|drowning in debt|struggling with debt)",
      "Debt can feel very overwhelming. How much is it affecting your mental wellbeing?" },

    { "i (owe|have to pay) (.*)",
      "How does owing $2 make you feel? Is it causing you significant stress?" },

    { "i (can't|cannot) (pay|afford) (my )?(bills|rent|loans|debt)",
      "That sounds like a very stressful situation. How long have you been struggling to pay $4?" },

    { "i (have|took out) (a loan|student loans|credit card debt) (.*)",
      "How do you feel about having that debt? Does it weigh on you heavily?" },

    // ── SAVINGS / INVESTMENTS ────────────────────────────────────────────────
    { "i (have|am building|am trying to save) (savings|an emergency fund|money saved)",
      "That shows great discipline. What motivates you to save?" },

    { "i (lost|have lost) (my )?(savings|investments|money|everything)",
      "Losing your savings must be devastating. What happened?" },

    { "i (invest|am investing|want to invest) (in )?(.*)",
      "What drew you to investing in $3? Is financial security important to you?" },

    { "i (don't|do not|dont) (have any|have) savings",
      "How does not having savings make you feel about your future?" },

    // ── BANKRUPTCY ───────────────────────────────────────────────────────────
    { "i (am|filed for|considering) bankruptcy",
      "That is a very difficult situation to be in. How are you coping emotionally?" },

    { "my (business|company) (failed|went under|went bankrupt)",
      "Losing a business can feel like losing a part of yourself. How are you dealing with that?" },

    // ── JOB / INCOME ─────────────────────────────────────────────────────────
    { "i (lost|got fired from|was laid off from) my (job|work|position)",
      "Losing a job can be very destabilizing. How has that affected you?" },

    { "i (don't|do not|dont) (have a job|have work|make enough money)",
      "How does not having steady income make you feel about yourself?" },

    { "i (am|have been) (unemployed|jobless|between jobs)",
      "How long have you been unemployed? How is that affecting your sense of purpose?" },

    { "my (salary|income|pay|wage) (is|has been) (too low|not enough|terrible)",
      "Feeling underpaid can be very demoralizing. Have you considered other options?" },

    // ── SPENDING ─────────────────────────────────────────────────────────────
    { "i (spend|am spending) (too much|a lot of) money (on )?(.*)",
      "What do you think drives you to spend so much on $4?" },

    { "i (can't|cannot) (stop|control) (spending|my spending)",
      "Compulsive spending can sometimes be a way of dealing with emotions. What do you think triggers it for you?" },

    { "i (am|have been) (struggling|having trouble) (with |managing )?(my finances|my budget|money)",
      "Financial struggles can be very stressful. What area feels most out of control?" },

    // ── WEALTH / RICH ────────────────────────────────────────────────────────
    { "i (want to|wish i could) (be rich|be wealthy|have more money|be financially free)",
      "What does being wealthy mean to you? What would it allow you to do?" },

    { "i (am|have been) (doing well|financially stable|comfortable) (financially)?",
      "That is great to hear. Does financial stability bring you peace of mind?" }
};

// Returns first matched response or empty string if no pattern matched
string handleFinancial(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : financialPatterns) {
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