all:
	g++ -std=c++17 -o myEliza main.cpp genericVerbs.cpp responseTracker.cpp

clean:
	rm -f myEliza myEliza.exe
	