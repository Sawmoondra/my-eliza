#include "wellbeing.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for wellbeing related user input
static const vector<pair<string, string>> wellbeingPatterns = {

    // ── SLEEP ────────────────────────────────────────────────────────────────
    { "i (can't|cannot|could not) (sleep|fall asleep|get enough sleep)",
      "Sleep is so important for our mental health. What do you think is keeping you awake?" },

    { "i (have been|am) (sleeping too much|oversleeping|sleeping all day)",
      "Sometimes sleeping too much can be a sign of how we are feeling emotionally. How have you been feeling lately?" },

    { "i (am|have been) (tired|exhausted|fatigued) (all the time|constantly|every day)",
      "Chronic tiredness can really affect our quality of life. What do you think is draining your energy?" },

    { "i (don't|do not|dont) (sleep well|get enough sleep|have a sleep schedule)",
      "Poor sleep can affect everything. What does your typical night look like?" },

    // ── EXERCISE ─────────────────────────────────────────────────────────────
    { "i (exercise|work out|go to the gym) (every day|regularly|a lot)",
      "That is great. What motivates you to stay active?" },

    { "i (don't|do not|dont) (exercise|work out|move enough|stay active)",
      "What do you think prevents you from being more physically active?" },

    { "i (want to|need to|am trying to) (exercise|work out|get fit|get in shape)",
      "What is driving your desire to get more active right now?" },

    { "i (stopped|quit|gave up) (exercising|going to the gym|working out)",
      "What caused you to stop? Do you miss being active?" },

    // ── DIET / EATING ────────────────────────────────────────────────────────
    { "i (eat|have been eating) (too much|a lot|junk food|unhealthy)",
      "How does your eating make you feel? Do you think it is connected to your emotions?" },

    { "i (don't|do not|dont) (eat enough|eat well|have a good diet)",
      "Not eating well can really affect how we feel. What does your typical day of eating look like?" },

    { "i (am|have been) (dieting|on a diet|watching what i eat)",
      "What motivated you to start dieting? How is it going so far?" },

    { "i (have|am dealing with) (an eating disorder|food issues|a bad relationship with food)",
      "That takes a lot of courage to share. How long have you been struggling with this?" },

    // ── VITAMINS / HEALTH HABITS ─────────────────────────────────────────────
    { "i (take|am taking|started taking) (vitamins|supplements|medication) (.*)",
      "What made you start taking $3? How has it been affecting you?" },

    { "i (don't|do not|dont) (take care of|look after) myself",
      "What do you think gets in the way of taking care of yourself?" },

    { "i (have been|am) (trying to|working on) (be healthier|improve my health|take better care of myself)",
      "That is a positive step. What changes have you been making?" },

    // ── STRESS / RELAXATION ──────────────────────────────────────────────────
    { "i (am|have been|feel) (so |very |extremely )?(stressed|overwhelmed|burnt out|burned out)",
      "It sounds like you are carrying a heavy load. What is the biggest source of stress in your life right now?" },

    { "i (can't|cannot) (relax|unwind|de-stress|calm down)",
      "What do you think makes it so hard for you to relax?" },

    { "i (need|want) to (relax|unwind|take a break|rest)",
      "What does relaxation look like for you? What helps you most?" },

    { "i (meditate|do yoga|practice mindfulness) (.*)",
      "That sounds like a healthy habit. How has $3 affected your mental state?" },

    // ── MENTAL HEALTH ────────────────────────────────────────────────────────
    { "i (am|have been) (seeing|going to|visiting) a (therapist|doctor|psychiatrist|counselor)",
      "It is great that you are seeking help. How has that been going for you?" },

    { "i (am|have been) (on|taking) (medication|antidepressants|anxiety medication) (.*)",
      "How has being on $3 affected you? Do you feel it is helping?" },

    { "i (feel|am) (mentally|physically) (exhausted|drained|worn out)",
      "Being $2 $3 can make everything feel impossible. What do you think caused this?" },

    // ── GENERAL HEALTH ───────────────────────────────────────────────────────
    { "i (am|have been) (sick|ill|unwell|not feeling well)",
      "I am sorry to hear that. How long have you been feeling this way?" },

    { "i (have|was diagnosed with) (.*)",
      "How has dealing with $2 affected your daily life and emotional wellbeing?" },

    { "i (want to|am trying to) (be healthier|live longer|take better care of myself|improve my lifestyle)",
      "What inspired you to make these changes? What feels most challenging about it?" }
};

// Returns first matched response or empty string if no pattern matched
string handleWellbeing(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : wellbeingPatterns) {
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