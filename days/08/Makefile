
CXX ?= g++
CXXFLAGS ?= -W -Wall -Wextra -Wpedantic -O3 -std=c++23
.PHONY: default clean

default: part-1 part-2

clean:
	-rm part-1 part-2

%: %.o Makefile
	$(CXX) $< -o $@

src/%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

