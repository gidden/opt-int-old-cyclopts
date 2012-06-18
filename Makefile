SRC=App.cpp Variable.cpp Function.cpp CyclusSolverInterface.cpp CyclusSolver.cpp
OUTNAME=app

# C++ Compiler command
CXX = g++

# C++ Compiler options
CXXFLAGS = -O3 

# additional C++ Compiler options for linking
CXXLINKFLAGS =  -Wl,--rpath -Wl,/home/cnerg/opt/coin-Cbc/lib

# Directory with COIN header files
COININCDIR = /home/cnerg/opt/coin-Cbc/include/coin

# Directory with COIN libraries
COINLIBDIR = /home/cnerg/opt/coin-Cbc/lib

# Libraries necessary to link with Clp
LIBS = -L$(COINLIBDIR) -lCbcSolver -lCbc -lCgl -lOsiClp -lOsiCbc -lOsi -lClp -lCoinUtils \
	-lm  \
	`cat /home/cnerg/opt/coin-Cbc/share/coin/doc/Cgl/cgl_addlibs.txt` \
	`cat /home/cnerg/opt/coin-Cbc/share/coin/doc/Osi/osi_addlibs.txt` \
	`cat /home/cnerg/opt/coin-Cbc/share/coin/doc/Clp/clp_addlibs.txt` \
	`cat /home/cnerg/opt/coin-Cbc/share/coin/doc/CoinUtils/coinutils_addlibs.txt`

# Necessary Include dirs
INCL =  -I$(COININCDIR)


all:
	$(CXX) $(SRC) -o $(OUTNAME) $(CXXFLAGS) $(CXXLINKFLAGS) $(LIBS) $(INCL)

clean: 

	rm -rf $(OUTNAME)

run:
	./$(OUTNAME)

debug: 
	g++ -g $(SRC) -o $(OUTNAME) $(CXXFLAGS) $(CXXLINKFLAGS) $(LIBS) $(INCL)
