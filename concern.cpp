#include "concern.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for concern-related user input
static const vector<pair<string, string>> concernPatterns = {

    // ── SUICIDE / SELF HARM ───────────────────────────────────────────────────
    { "i (want to|am going to|am thinking about|think about) (kill myself|end my life|suicide|hurt myself)",
      "I am very concerned about what you just said. Please know that you are not alone. Can you tell me more about what is making you feel this way?" },

    { "i (have been|am) (thinking about|considering) suicide",
      "That sounds very serious and I want you to know I am here for you. What has been happening in your life lately?" },

    { "i (don't|do not|dont) want to (live|be alive|exist) anymore",
      "I hear you, and I am glad you are talking about this. What has brought you to feel this way?" },

    { "i (want to|wish i could) (disappear|vanish|not exist)",
      "It sounds like you are carrying a lot of pain right now. Can you tell me more about what is going on?" },

    { "life is (not worth|pointless|meaningless|hopeless)",
      "When life feels that way, it can be very overwhelming. What has been making you feel like life is $2?" },

    // ── HATE ─────────────────────────────────────────────────────────────────
    { "i (hate|despise|loathe) (myself|my life|everything|everyone)",
      "Those are very strong feelings. What is it about $2 that makes you feel that way?" },

    { "i (hate|despise|loathe) (.*)",
      "You seem to have very strong feelings about $2. Can you tell me more about why?" },

    { "i (really |absolutely )?hate (.*)",
      "What is it about $2 that brings up such strong feelings for you?" },

    { "everything (is|feels) (terrible|awful|horrible|pointless|wrong)",
      "It sounds like things feel very dark right now. How long have you been feeling this way?" },

    // ── ANGER ────────────────────────────────────────────────────────────────
    { "i (am|feel|am feeling) (so |very |extremely )?(angry|furious|enraged|livid|mad)",
      "It sounds like you are very angry. What happened that made you feel this way?" },

    { "i (want to|feel like) (hit|punch|break|destroy|scream) (.*)",
      "Those feelings of anger sound very intense. What is it that triggered these feelings?" },

    { "i (can't|cannot) control my (anger|rage|temper)",
      "Feeling out of control can be very frightening. What situations tend to trigger your anger?" },

    { "i (am|get) (angry|mad|upset) (when|because|about) (.*)",
      "I see. What do you think is underneath that anger when $4?" },

    // ── FEAR / ANXIETY ────────────────────────────────────────────────────────
    { "i (am|feel) (scared|terrified|afraid|fearful) (of |about )?(.*)",
      "Fear can be very powerful. What is it about $4 that frightens you?" },

    { "i (am|have been) (anxious|anxious about|worried|panicking) (about |over )?(.*)",
      "Anxiety can be overwhelming. How long have you been feeling anxious about $4?" },

    { "i (have|get) (panic attacks|anxiety attacks)",
      "Panic attacks can be very distressing. Can you describe what happens when you experience them?" },

    { "i (am|feel) (so |very )?(stressed|overwhelmed|burnt out)",
      "It sounds like you have a lot weighing on you. What is contributing most to feeling $3?" },

    // ── DEPRESSION / SADNESS ─────────────────────────────────────────────────
    { "i (am|feel|have been) (depressed|so sad|miserable|hopeless|empty|numb)",
      "I am sorry to hear you are feeling $2. How long have you been feeling this way?" },

    { "i (cry|have been crying) (all the time|a lot|every day|constantly)",
      "It sounds like you have been going through a very difficult time. What do you think is at the root of these feelings?" },

    { "i (feel|am) (so |very )?alone (and|but)? (.*)",
      "Feeling alone can be very painful. What makes you feel isolated?" },

    { "nobody (cares|loves|understands|listens to) me",
      "That sounds incredibly lonely. Has something happened recently that made you feel this way?" },

    { "i (feel|am) (worthless|useless|a burden|a failure|pathetic)",
      "Those are very harsh words to use about yourself. What has made you feel $2?" },

    // ── TRAUMA / ABUSE ───────────────────────────────────────────────────────
    { "i (was|have been) (abused|hurt|traumatized|neglected) (by |as a )?(.*)",
      "I am so sorry to hear that. That must have been very difficult. Would you like to talk more about what happened?" },

    { "i (can't|cannot) (forget|get over|move on from) (.*)",
      "It sounds like $3 has had a lasting impact on you. What makes it so hard to move forward?" },

    { "i (keep|have been) (having nightmares|reliving|dreaming about) (.*)",
      "That sounds very distressing. How often does this happen?" },

    // ── KILL / VIOLENCE ──────────────────────────────────────────────────────
    { "i (want to|feel like) kill(ing)? (.*)",
      "Those are very strong words. I want to understand what is driving these feelings. Can you tell me more?" },

    { "i (want to|feel like) (hurt|harm) (someone|others|people|them|him|her)",
      "It sounds like you are feeling very angry at someone. What happened between you?" },

    // ── GIVING UP ────────────────────────────────────────────────────────────
    { "i (want to|am going to) give up",
      "What makes you feel like giving up right now? Let us talk about what is going on." },

    { "i (can't|cannot) (take it|do this|handle this|go on) anymore",
      "It sounds like you have reached a breaking point. What has been building up for you?" },

    { "i (don't|do not) (see the point|care anymore|see a future)",
      "When we lose sight of the future it can feel very isolating. What has changed for you recently?" },

    // ── GENERAL DISTRESS ─────────────────────────────────────────────────────
    { "i (am|feel) (so |very |extremely )?(lost|confused|broken|shattered)",
      "Feeling $3 can be very disorienting. What has been happening in your life?" },

    { "i (don't|do not) know (how to|what to) (cope|deal|handle) (with )?(.*)",
      "That is a very honest thing to admit. What have you tried so far to cope with $5?" },

    { "everything (is falling apart|has gone wrong|feels wrong)",
      "It sounds like multiple things are weighing on you at once. What feels most urgent to you right now?" }
};

// Returns first matched response or empty string if no pattern matched
string handleConcern(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : concernPatterns) {
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