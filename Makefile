CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror

all: main

clean:
	rm play

main:
	$(CXX) $(CXXFLAGS) unity.cpp -o play
