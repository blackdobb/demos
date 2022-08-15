# The process of write a grpc demo.

## Install gRPC and Protocol Buffers

git clone gRPC first, the following commands build and locally install gRPC and Protocol Buffers.

```sh
$ cd grpc
$ mkdir -p cmake/build
$ pushd cmake/build
$ cmake -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_TESTS=OFF \
    -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
    ../..
$ make -j
$ make install
$ popd
```
Explanation of the arguments:
* -DgRPC_INSTALL=ON ：install gRPC
* -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR: Using CMAKE_INSTALL_PREFIX to specify the installation path, usually installed gRPC locally. $MY_INSTALL_DIR specified the final generated library file and the protoc installation location, linux usually in /usr/local. Strongly encourage to use it, because there is no easy way to uninstall gRPC after you've installed it globally. BeforE usSing $MY_INSTALL_DIR, make sure it has been in the PATH environment.
    
    ```sh
    # build Path
    $ export MY_INSTALL_DIR=/usr/local/
    # make sure the path exist
    $ mkdir -p $MY_INSTALL_DIR
    # add the local bin directory to the path environment
    $ export PATH="%PATH:$MY_INSTALL_DIR/bin"
    ```

make install will install the builded lib to corresponding location according to the specified $MY_INSTALL_DIR. For instance: protoc located in ${MY_INSTALL_DIR}/bin, the head file located in ${MY_INSTALL_DIR}/include/grpc.

##  Proto and server&client 
1. Definite protoc
2. Write service and client, to implement the interface defined in the proto.

## Build gRPC demo
Usually we use protoc compile proto file first which will generated `mathTest.grpc.pb.h/.o` and `mathTest.pb.h/.o`, then compile the server.cc and client.cc, to run server first.
Follow the MAKEFILE for more details.


