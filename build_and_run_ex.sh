# this scripts assumes that 
# a) you are in the cyclopts root directory
# b) your COIN_ROOT_DIR environment variable is set
# c) your CYCLOPTS_ROOT_DIR environment variable is set
rm -rf build $CYCLOPTS_ROOT_DIR && mkdir build $CYCLOPTS_ROOT_DIR && cd build && cmake ../src -DCMAKE_INSTALL_PREFIX=$CYCLOPTS_ROOT_DIR && make -j3 && make install
cd ../examples
rm -rf build && mkdir build && cd build && cmake ../src && make -j3 && ./app
