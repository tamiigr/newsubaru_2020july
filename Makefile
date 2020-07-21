CXX = g++
CXXFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

TARGETS = nai_laser_on_off hist read

all: $(TARGETS)
nai_laser_on_off: nai_laser_on_off.o
	$(CXX) $(CXXFLAGS) -o $@ $@.o $(ROOTLIBS)
hist: hist.o
	$(CXX) $(CXXFLAGS) -o $@ $@.o $(ROOTLIBS)
read: read.o read.h
	$(CXX) $(CXXFLAGS) -o $@ $@.o $(ROOTLIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<
.PHONY : clean
clean:
	rm -f *.o *~ $(TARGETS)
