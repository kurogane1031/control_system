CXX = g++
CXXFLAGS = -std=c++14 -g -O3
LDFLAGS = 
IFLAGS = -I/usr/include/eigen3/

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(IFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
