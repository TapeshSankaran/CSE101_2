CXX = g++
CXXFLAGS = -Wall -std=c++11 -gdwarf-4 -g

OBJECTS = bst.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^

clean: 
	rm -f *.o wordrange
$(OBJECTS): bst.h
