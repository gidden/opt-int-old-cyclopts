cyclopts
========

The Cyclus Optimization Library

Build & Install
---------------

To install cyclopts, one must first install:
   * blas: http://www.netlib.org/blas/
   * lapack: http://www.netlib.org/lapack/
   * coin-Cbc: https://projects.coin-or.org/Cbc.

Additionally, one must set an environment variable COIN_ROOT_DIR. This should point to the directory in which the bin, include, and lib folders for coin-Cbc reside.

With these two steps taken, one can perform the normal cmake, make, make install steps.

Run an Example
--------------

An example application that uses the cyclopts library is provided in the examples folder. In order to use this, one must:
  * install the cyclopts library using the above process
  * set an environment variable named CYCLOPTS_ROOT_DIR pointing to the parent directory of the include and lib folders.