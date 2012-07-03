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

If you choose to install coin in a non-standard location, you must
add a path to the include directory in your PATH variable.

With these steps taken, one can perform the normal cmake, make, 
make install steps.

Run an Example
--------------

An example application that uses the cyclopts library is provided in 
the examples folder. In order to use this, one must:
  * install the cyclopts library using the above process
  * set an environment variable named CYCLOPTS_ROOT_DIR pointing to 
  the parent directory of the include and lib folders.
  * run cmake and make on the files in the examples directory (normal 
  practice is to make a build directory, e.g. mkdir build && cd build 
  && cmake ../ && make && ./app)