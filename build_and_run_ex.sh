# this scripts assumes that you are in the cyclopts root directory
rm -rf build  && mkdir build && cd build && cmake ../src -DCMAKE_INSTALL_PREFIX=/usr/ && make -j3 && make install
cd ../examples
rm -rf build && mkdir build && cd build && cmake ../src && make -j3 && ./app
