SRC=App.cpp
OUTNAME=app

# C++ Compiler command
CXX = g++

# C++ Compiler options
CXXFLAGS = -O3 

# additional C++ Compiler options for linking
CXXLINKFLAGS =  -Wl,--rpath -Wl,../install/lib

# Directory with COIN header files
INCLDIR = ../install/include

# Directory with COIN libraries
LIBDIR = ../install/lib

# Libraries necessary to link with Clp
LIBS = -L$(LIBDIR) -lcyclopts

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
