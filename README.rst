********
Cyclopts
********

The Cyclus Optimization Library

Deprecation
===========

Note that the Cyclopts library has been deprecated after v0.2. If you are using
Cyclus v0.1, then please use the separated Cyclopts library v0.2. If you are
using Cyclus post v0.1, then Cyclopts has been incorporated into the Cyclus
library.

Build & Install
===============

The full process of building and installing Cyclopts can be broken into 
two sections:

  #. building and installing the dependencies
  #. building and installing Cyclopts

Installing Dependencies
-----------------------

To install Cyclopts, one must first install:

  * boost: http://www.boost.org/
  * coin-Cbc(min. v2.5): https://projects.coin-or.org/Cbc

Now, there's an easy way to install these dependencies and a hard
way. I'll detail the easy way and gloss over the hard way, which is
for more experienced users anyway.

The Easy Way: Using a Package Manager
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you have access to a package manager (e.g. Synaptic for Ubuntu), 
then the installation process of the dependencies is easy -- you can
get them all through the manager. If you've heard of something called
`apt-getting <http://linux.die.net/man/8/apt-get>`_, then you're 
golden. If not, might want to get familiar with it if any errors come
up that you don't understand.

To perform the following process, we assume that you have root (i.e.,
super user) access in order to issue "sudo" commands. This process was
tested on a fresh install of Ubuntu 12.10. All commands were required
to fully install the dependencies.

To install the dependencies the easy way, you'll need to issue the 
following command:

.. code-block:: bash

  sudo apt-get install <package>

where you will replace the term <package> with each of the following:

  #. g++
  #. libboost-dev
  #. cmake
  #. libbz2-dev
  #. coinor-libcoinutils-dev
  #. coinor-libosi-dev
  #. coinor-libclp-dev
  #. coinor-libcbc-dev 
  #. coinor-libcgl-dev

The Hard Way: Building from Source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The installation instructions to install boost from source are
provided on their `website
<http://www.boost.org/doc/libs/1_52_0/doc/html/bbv2/installation.html>`_.

The direct dependency for Cyclopts is coin-Cbc. It is possible to 
build this dependency from 
`source <https://projects.coin-or.org/Cbc/browser/stable/2.5>`_, but 
you may find that you need to install additional dependencies based on 
the version you're using. See the FindCOIN.cmake file in /src/CMake 
for some comments.

If you choose to install coin-Cbc in a non-standard location (i.e., 
some location not in a standard environment variable that cmake checks
like PATH and LD_LIBRARY_PATH), you must inform CMake as to its 
location using the command line argument COIN_ROOT_DIR.

Installing Cyclopts
-------------------

Assuming you have the dependencies installed correctly, it's pretty
straightforward to install Cyclopts. We make the following assumptions
in this guide:

  #. you have acquired the Cyclopts source code from the 
     `repo <https://github.com/cyclus/cyclopts>`_
  #. there is some master directory in which you're placing all
     Cyclus-related files called .../cyclus
  #. you have placed the Cyclopts repository in .../cyclus/cyclopts
  #. you have a directory named .../cyclus/install in which you plan
     to install all Cyclus-related files
  #. you have a directory named .../cyclus/cyclopts/build in which 
     you plan to encapsulate all build-related files (they get in the
     way otherwise)

Under these assumptions **and** if you used a package manager to 
install coin-Cbc (i.e. it's installed in a standard location), the
Cyclopts building and installation process will look like:

.. code-block:: bash

    .../cyclus/cyclopts$ python setup.py --prefix=../install

If you have installed coin-Cbc from source or otherwise have it 
installed in a non-standard location, you should add an appropriate flag

.. code-block:: bash

    .../cyclus/cyclopts$ python setup.py --prefix=../install --coinRoot=path/to/coin/libraries

You can always investigate the full set of installtion options via:

.. code-block:: bash

    .../cyclus/cyclopts$ python setup.py -h

Run an Example
==============

An example application that uses the Cyclopts library is provided in 
the examples folder. 

Assuming you have built and installed Cyclopts in the manner 
described above, you can issue the following commands to build and 
run the example (remember, we installed Cyclopts in .../cyclus/install).

.. code-block:: bash

    .../cyclus/cyclopts$ cd examples
    .../cyclus/cyclopts/examples$ python setup.py --cycloptsRoot=../../install

Again, if you installed coin in a nonstandard location, you'll also have to
inform the setup script.

.. code-block:: bash

    .../cyclus/cyclopts$ cd examples
    .../cyclus/cyclopts/examples$ python setup.py --cycloptsRoot=../../install --coinRoot=path/to/coin/libraries

Some Notes
==========

COIN-OR is the current tool used to solve LPs and MILPs, however, others exist:

   #. `glpk <http://www.gnu.org/software/glpk/>`_
   #. `pyomo <https://software.sandia.gov/trac/coopr/wiki/Pyomo>`_
   #. `symphony <https://software.sandia.gov/trac/coopr/wiki/Pyomo>`_
