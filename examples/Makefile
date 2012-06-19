SRC=App.cpp
OUTNAME=app

# C++ Compiler command
CXX = g++

# C++ Compiler options
CXXFLAGS = -O3 

# Directory with cyclopts header files
INCLDIR = ../install/include

# Libraries necessary to link with cyclopts
LIBS = -lcyclopts

# Necessary Include dirs
INCL =  -I$(INCLDIR)


all:
	$(CXX) $(SRC) -o $(OUTNAME) $(CXXFLAGS) $(CXXLINKFLAGS) $(LIBS) $(INCL)

clean: 

	rm -rf $(OUTNAME)

run:
	./$(OUTNAME)

debug: 
	g++ -g $(SRC) -o $(OUTNAME) $(CXXFLAGS) $(CXXLINKFLAGS) $(LIBS) $(INCL)
