cyclopts
========

The Cyclus Optimization Library

Build & Install
---------------

To install cyclopts, one must first install:
   * coin-Cbc: https://projects.coin-or.org/Cbc, which relies on
   * blas(dev): http://www.netlib.org/blas/
   * lapack(dev): http://www.netlib.org/lapack/
   * bz2(dev): http://www.bzip.org/downloads.html

Additionally, one must:
   * set an environment variable COIN_ROOT_DIR (this should point to the directory in which the bin, include, and lib folders for coin-Cbc reside)
   * add that environment variable to your PATH environment variable

With these two steps taken, one can perform the normal cmake, make, make install steps.

Run an Example
--------------

An example application that uses the cyclopts library is provided in the examples folder. In order to use this, one must:
  * install the cyclopts library using the above process
  * set an environment variable named CYCLOPTS_ROOT_DIR pointing to the parent directory of the include and lib folders.
  * run cmake and make on the files in the examples directory (normal practice is to make a build directory, e.g. mkdir build && cd build && cmake ../ && make && ./app)