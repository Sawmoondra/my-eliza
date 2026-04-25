#include "entertainment.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for entertainment and leisure related user input
static const vector<pair<string, string>> entertainmentPatterns = {

    // ── MOVIES / TV ──────────────────────────────────────────────────────────
    { "i (love|enjoy|like) (watching |seeing )?(movies|films|tv|television|shows|series)",
      "What kind of $3 do you enjoy most? What does that say about you?" },

    { "i (watched|saw) (a movie|a film|a show|a series) (.*)",
      "How did that make you feel? Do you often find yourself drawn to that kind of content?" },

    { "i (want to|am going to) (watch|see) (.*)",
      "What made you choose $3? Is there something about it that appeals to you?" },

    { "i (spend|waste) (too much time|a lot of time) (watching|on) (.*)",
      "Do you think watching $4 is a way of escaping something in your life?" },

    // ── MUSIC / CONCERTS ─────────────────────────────────────────────────────
    { "i (love|enjoy|like) (listening to |playing )?(music|songs|bands|artists)",
      "Music can be very powerful. What kind of music resonates with you most?" },

    { "i (went|am going) to a (concert|show|gig|festival) (.*)",
      "How was that experience for you? Do you often go to live events?" },

    { "i (play|am learning to play) (.*)",
      "That is interesting. How long have you been playing $2 and what drew you to it?" },

    { "i (listen to|am into) (.*) (music|songs|artists|bands)",
      "What is it about $2 music that you connect with?" },

    // ── DANCING ──────────────────────────────────────────────────────────────
    { "i (love|enjoy|like) (to dance|dancing)",
      "Dancing can be a great outlet. What does dancing mean to you?" },

    { "i (went|am going) (dancing|to a club|to a dance)",
      "How do you feel when you are out dancing? Does it help you relax?" },

    { "i (can't|cannot|don't know how to) dance",
      "Does that bother you? What do you think holds you back from dancing?" },

    // ── RESTAURANTS / FOOD ───────────────────────────────────────────────────
    { "i (went|am going) to a (restaurant|diner|cafe|bar) (.*)",
      "Do you enjoy going out to eat? Is it more about the food or the social experience?" },

    { "i (love|enjoy|like) (eating out|going to restaurants|trying new food)",
      "Food can be very connected to our emotions. What does eating out mean to you?" },

    { "i (cooked|am cooking|made) (.*)",
      "Cooking can be very therapeutic. How do you feel when you cook $2?" },

    // ── BARS / DRINKING ──────────────────────────────────────────────────────
    { "i (went|am going) to a (bar|club|pub) (.*)",
      "Do you go out often? What do you enjoy most about going to $2?" },

    { "i (drink|have been drinking) (a lot|too much|every day|constantly)",
      "How do you feel when you drink? Do you think it helps you cope with something?" },

    // ── GAMES / HOBBIES ──────────────────────────────────────────────────────
    { "i (love|enjoy|like|play) (video games|gaming|games) (.*)",
      "Gaming can be a great escape. Do you think you use it to relax or to avoid something?" },

    { "i (spend|waste) (too much time|a lot of time) (playing|on) (games|video games|gaming)",
      "What draws you to gaming so much? Is there something it gives you that real life doesn't?" },

    { "i (have a|enjoy a) (hobby|interest) (.*)",
      "Tell me more about $3. How did you get into that hobby?" },

    { "i (like|enjoy|love) (reading|painting|drawing|writing|photography|hiking|cooking|gardening)",
      "That sounds fulfilling. How does $2 make you feel?" },

    // ── SOCIAL LIFE ──────────────────────────────────────────────────────────
    { "i (don't|do not|dont) (have|get) (enough |any )?(fun|entertainment|social life)",
      "What do you think is missing from your social life right now?" },

    { "i (feel|am) (bored|bored with life|unstimulated)",
      "Boredom can sometimes be a sign of something deeper. What do you think is missing for you?" },

    { "i (went out|hung out|spent time) with (friends|my friends|people) (.*)",
      "How did that feel? Do you enjoy spending time with others?" },

    { "i (don't|do not|dont) (like|enjoy) (going out|socializing|being around people)",
      "What is it about $3 that feels uncomfortable for you?" },

    // ── TRAVEL / VACATION ────────────────────────────────────────────────────
    { "i (went|am going) on (vacation|a trip|a holiday) (to |in )?(.*)",
      "How do you feel about getting away? What do you hope to find in $4?" },

    { "i (love|enjoy|like) (traveling|exploring|adventure)",
      "What does traveling give you that everyday life doesn't?" },

    { "i (want to|would like to) (travel|visit|go to) (.*)",
      "What draws you to $3? Is there something you are searching for there?" }
};

// Returns first matched response or empty string if no pattern matched
string handleEntertainment(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : entertainmentPatterns) {
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