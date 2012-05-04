CXX=g++
CXXFLAGS=-g -Wfatal-errors -Wall -Wextra -Weffc++ -std=c++0x

poker-stats: card.o hand.o main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o

cleanall: clean
	rm -f poker-stats
