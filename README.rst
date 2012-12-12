cyclopts
========

The Cyclus Optimization Library

Build & Install
---------------

To install cyclopts, one must first install:
   * coin-Cbc(v2.7): https://projects.coin-or.org/Cbc, which relies on
   * blas(dev): http://www.netlib.org/blas/
   * lapack(dev): http://www.netlib.org/lapack/
   * zlib(dev): http://zlib.net/
   * bz2(dev): http://www.bzip.org/

If you choose to install coin-Cbc in a non-standard location (i.e., 
some location not in a standard envrionment variable that cmake checks
like PATH and LD_LIBRARY_PATH), you must inform cmake as to its 
location using the command line argument COIN_ROOT_DIR.

With these steps taken, one can perform the normal cmake, make, 
make install steps.

We suggest separating the locations of the building and installation 
process. An example of doing so is provided below. Note that this 
example will install Cyclopts in a non-standard location. ::

    .../cyclopts$ mkdir build install && cd build 
    .../cyclopts/build$ cmake ../src -DCMAKE_INSTALL_PREFIX=../install -DCOIN_ROOT_DIR=/the/path/to/coin/install
    .../cyclopts/build$ make && make install

Run an Example
--------------

An example application that uses the cyclopts library is provided in 
the examples folder. This process again uses cmake, and will require
variables for both the coin library location and cyclopts library 
location. These are named COIN_ROOT_DIR and CYCLOPTS_ROOT_DIR.

Assuming you have built and installed Cyclopts in the manner 
described above, you can issue the following commands to build and 
run the example (remeber, we installed Cyclopts 
in .../cyclopts/install). ::

    .../cyclopts$ cd examples && mkdir build && cd build
    .../cyclopts/examples/build$ cmake ../src -DCYCLOPTS_ROOT_DIR=../../install -DCOIN_ROOT_DIR=/the/path/to/coin/install
    .../cyclopts/examples/build$ make
    .../cyclopts/examples/build$ ./app
