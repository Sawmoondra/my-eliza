all:
	g++ -std=c++17 -o myEliza main.cpp genericVerbs.cpp responseTracker.cpp concern.cpp love.cpp financial.cpp wellbeing.cpp education.cpp entertainment.cpp

clean:
	rm -f myEliza myEliza.exe