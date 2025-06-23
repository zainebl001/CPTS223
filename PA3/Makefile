CXX = g++
CXXFLAGS = -g -Wall -std=c++11

EXEC = PA3
OBJS = main.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp avl_map.hpp USCity.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(EXEC) *.o
