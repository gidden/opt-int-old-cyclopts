cyclopts
========

The Cyclus Optimization Library

To install cyclopts, one must first install:
   * blas: http://www.netlib.org/blas/
   * lapack: http://www.netlib.org/lapack/
   * coin-Cbc: https://projects.coin-or.org/Cbc.

Additionally, one must set an environment variable COIN_ROOT_DIR. This should point to the directory in which the bin, include, and lib folders for coin-Cbc reside.

With these two steps taken, one can perform the normal cmake, make, make install steps.