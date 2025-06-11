CXX = g++
CXXFlags = -g -Wall -std=c++11

BST_EXEC = MA1
BST_OBJS = main.o

all: $(BST_EXEC)

$(BST_EXEC): $(BST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp BST.h
	$(CXX) $(CXXFLAGS) -c %< -o $@

clean:
	rm -f $(BST_EXEC) *.o
