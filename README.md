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

If you choose to install coin-Cbc in a non-standard location, you must
add the location of the include directory in your PATH environment 
variable.

Similarly, if you choose to install cyclopts in a non-standard 
location, you must add the location of the include directory in your 
PATH environment variable.

With these steps taken, one can perform the normal cmake, make, 
make install steps.

Run an Example
--------------

An example application that uses the cyclopts library is provided in 
the examples folder. In order to use this, one must:
  * install the cyclopts library using the above process
  * add the include directory to your PATH variable (if in a non-
  standard location)
  * run cmake and make on the files in the examples directory