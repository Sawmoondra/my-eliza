# myEliza — ELIZA Chatbot in C++

A conversational AI chatbot inspired by the original ELIZA program, 
built in C++ for CSCE 2110 at the University of North Texas.

## About
ELIZA is one of the first natural language processing programs, originally 
created at MIT in the 1960s. This implementation simulates a therapist-style 
conversation using pattern matching and keyword recognition.

## Features
- Pattern-based response generation
- Multiple conversation topics:
  - Generic verb handling
  - Emotional wellbeing
  - Love and relationships
  - Financial concerns
  - Education
  - Entertainment
- Response tracking to avoid repetition

## Project Structure
| File | Purpose |
|---|---|
| main.cpp | Entry point and conversation loop |
| genericVerbs.cpp | Verb-based pattern matching |
| concern.cpp | Handles concern-related responses |
| wellbeing.cpp | Handles wellbeing responses |
| love.cpp | Handles love/relationship responses |
| financial.cpp | Handles financial topic responses |
| education.cpp | Handles education topic responses |
| entertainment.cpp | Handles entertainment responses |
| responseTracker.cpp | Tracks used responses to avoid repetition |

## Build & Run
```bash
make
./myEliza
```

## Course Info
CSCE 2110 — Data Structures | University of North Texas | Spring 2026  
Group 9 Project