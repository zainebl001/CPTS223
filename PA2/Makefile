CXX = g++
CXXFLAGS = -g -Wall -std=c++11

LIST_EXEC = test_list
VECTOR_EXEC = test_vector

LIST_OBJS = TestListMyJosephus.cpp ListMyJosephus.cpp Destination.cpp
VECTOR_OBJS = TestVectorMyJosephus.cpp VectorMyJosephus.cpp Destination.cpp

all: $(LIST_EXEC) $(VECTOR_EXEC)

$(LIST_EXEC): $(LIST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(VECTOR_EXEC): $(VECTOR_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(LIST_EXEC) $(VECTOR_EXEC) *.o results.log 
