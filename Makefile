CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g

all: tsp 

tsp: tsp.o cities.o
	$(CXX) $(CXXFLAGS) -o tsp tsp.o cities.o

tsp.o: tsp.cc
	$(CXX) $(CXXFLAGS) -c tsp.cc

cities.o: cities.cc cities.hh
	$(CXX) $(CXXFLAGS) -c cities.cc

clean:
	rm -rf *.o tsp
