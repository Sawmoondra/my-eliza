#include "education.h"
#include <string>
#include <regex>
#include <vector>
#include <utility>

using namespace std;

// Pattern-response pairs for education related user input
static const vector<pair<string, string>> educationPatterns = {

    // ── STUDYING ─────────────────────────────────────────────────────────────
    { "i (can't|cannot|could not) (study|focus|concentrate) (.*)",
      "What do you think is making it hard for you to $2?" },

    { "i (have been|am) (studying|working) (too hard|too much|all the time|constantly)",
      "It sounds like you are pushing yourself very hard. What drives you to study so intensely?" },

    { "i (don't|do not|dont) (like|enjoy|want to) study",
      "What is it about studying that feels difficult or unpleasant for you?" },

    { "i (need to|have to|must) study (for )?(.*)",
      "How do you feel about studying for $3? Does it cause you anxiety?" },

    // ── GRADES / PERFORMANCE ─────────────────────────────────────────────────
    { "i (am|have been) (failing|doing badly|struggling) (in |with )?(.*)",
      "Struggling academically can be very stressful. What do you think is contributing to your difficulties with $4?" },

    { "i (got|received) a (bad|poor|failing|low) (grade|score|mark) (on |in )?(.*)",
      "How did getting that grade make you feel? What do you think went wrong?" },

    { "i (am|have been) (doing well|getting good grades|passing all my classes)",
      "That is wonderful. How does doing well academically make you feel about yourself?" },

    { "my (grades|gpa|scores) (are|have been) (dropping|falling|getting worse)",
      "What do you think has caused your $1 to drop? What has changed recently?" },

    // ── EXAMS / TESTS ────────────────────────────────────────────────────────
    { "i (am|have been) (stressed|anxious|nervous|worried) (about|over) (my )?(exam|test|quiz|finals)",
      "Exam anxiety is very common. What specifically worries you most about $5?" },

    { "i (failed|did not pass|bombed) (my )?(exam|test|quiz|finals) (.*)",
      "Failing an exam can feel devastating. How are you coping with that result?" },

    { "i (have|have got) (an exam|a test|finals|midterms) (coming up|tomorrow|soon)",
      "How are you feeling about your upcoming $2? Are you feeling prepared?" },

    // ── HOMEWORK / ASSIGNMENTS ───────────────────────────────────────────────
    { "i (have|am|got) (too much homework|too many assignments|overwhelming work)",
      "Feeling overwhelmed by assignments is very common. How are you managing your time?" },

    { "i (can't|cannot) (finish|complete|keep up with) (my )?(homework|assignments|coursework)",
      "What is getting in the way of completing your $4?" },

    { "i (procrastinate|keep putting off|avoid) (my )?(homework|assignments|studying|work)",
      "Procrastination often has deeper causes. What do you think is behind yours?" },

    // ── UNIVERSITY / SCHOOL ──────────────────────────────────────────────────
    { "i (am|have been) (at|attending|going to) (university|college|school) (.*)",
      "How has your experience at $3 been so far?" },

    { "i (want to|am thinking of|am considering) (dropping out|leaving school|quitting university)",
      "That is a big decision. What has brought you to this point?" },

    { "i (don't|do not|dont) (like|enjoy|want to be at) (university|college|school)",
      "What is it about $3 that makes you feel that way?" },

    { "i (am|have been) (stressed|overwhelmed|burned out) (by|from) (school|university|college|classes)",
      "Academic burnout is very real. How long have you been feeling this way?" },

    // ── PROFESSORS / CLASSMATES ──────────────────────────────────────────────
    { "my (professor|teacher|instructor) (.*)",
      "Tell me more about your $1. How does that situation make you feel?" },

    { "i (don't|do not|dont) (get along with|like|understand) my (professor|teacher|classmates|peers)",
      "Interpersonal conflicts at school can make learning very difficult. What has been happening?" },

    // ── FUTURE / CAREER ──────────────────────────────────────────────────────
    { "i (don't|do not|dont) know (what|which) (major|career|field|degree) (to choose|to pick|is right for me)",
      "Choosing a path can feel very daunting. What subjects or activities do you feel most drawn to?" },

    { "i (am|have been) (worried|anxious|stressed) about (my future|graduation|finding a job)",
      "Worrying about the future is very common. What aspect of $3 concerns you most?" },

    { "i (graduated|am graduating|finished) (from )?(.*)",
      "How does it feel to have reached that milestone? What comes next for you?" },

    { "i (am|have been) (taking|enrolled in|registered for) (.*) (class|course|classes|courses)",
      "How are you finding $3? Is it what you expected?" }
};

// Returns first matched response or empty string if no pattern matched
string handleEducation(const string& input) {

    regex_constants::syntax_option_type flags =
        regex_constants::ECMAScript | regex_constants::icase;

    for (const auto& entry : educationPatterns) {
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