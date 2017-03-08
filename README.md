# HDMlib - Data management library for hierarchical Cartesian data structure

* Copyright (c) 2014-2017 Advanced Institute for Computational Science (AICS), RIKEN.
All rights reserved.
* Copyright (c) 2017 Research Institute for Information Technology (RIIT), Kyushu University. All rights reserved.


## OUTLINE

HDM library provides following functions for Hierarchical Cartesian structured data.

  - Management of distributed files
  - Restart from previous calculated data (standard)
  - Restart from previous calculated data of the number of different process
  - Restart from previous coarse data with interpolation
  - Staging helper


## SOFTWARE REQUIREMENT
- Cmake
- MPI library
- TextParser
- BCMtools
- Polylib (required to build examples)


## INGREDIENTS

~~~
ChangeLog.md    History of development
CMaleLists.txt  Cmake file
License.txt     License to apply
Readme.md       This document
doc/            Documents
examples        Sample codes
include/        Header files
src/            Source files
~~~


## HOW TO BUILD

### Build

~~~
$ export CC=c_compiler CXX=c++_compiler F90=fortran_compiler FC=fortran_compiler
$ export HDM_HOME=/hogehoge
$ mkdir build
$ cd build
$ cmake [options] ..
$ make
$ sudo make install
~~~


### Options

`-D INSTALL_DIR=` *Install_directory*

>  Specify the directory that this library will be installed. Built library is installed at `install_directory/lib` and the header files are placed at `install_directory/include`. The default install directory is `/usr/local/HDMlib`.


`-D with_MPI=` {yes | no}

>  If you use an MPI library, specify `with_MPI=yes`, the default is yes.

`-D with_TP =` *TextParser_directory*

> Specify the directory path that TextParser is installed.

`-D with_BCM=` *BCMTools_directory*

> Specify the directory path that BCMTools is installed.

`-D with_PL=` {no | *Polylib_directory* }

> Specify the directory path that Polylib is installed. This option is not mandatory and used to build examples.

`-D with_example=` {no | yes}

>  This option turns on compiling sample codes. The default is no.

`-D enable_OPENMP=` {no | yes}

> Enable OpenMP directives.

The default compiler options are described in `cmake/CompilerOptionSelector.cmake` file. See BUILD OPTION section in CMakeLists.txt in detail.


## Configure Examples

`$ export HDM_HOME=hogehoge`

In following exsmples, assuming that TextParser and BCMTools are installed under the HDM_HOME directory. If not, please specify applicable directory paths.

### INTEL/GNU compiler

~~~
$ cmake -DINSTALL_DIR=${HDM_HOME}/HDMlib -Dwith_MPI=yes -Denable_OPENMP=yes -Dwith_example=no -Dwith_TP=${HDM_HOME}/TextParser -Dwith_BCM=${HDM_HOME}/BCMTools -Dwith_PL=no ..
~~~


### FUJITSU compiler / FX10, FX100, K on login nodes (Cross compilation)

~~~
$ cmake -DINSTALL_DIR=${HDM_HOME}/HDMlib \
            -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_fx10.cmake \
            -Dwith_MPI=yes \
            -Denable_OPENMP=yes \
            -Dwith_example=no \
            -Dwith_TP=${HDM_HOME}/TextParser \
            -Dwith_BCM=${HDM_HOME}/BCMTools \
            -Dwith_PL=no ..

$ cmake -DINSTALL_DIR=${HDM_HOME}/HDMlib \
            -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_fx100.cmake \
            -Dwith_MPI=yes \
            -Denable_OPENMP=yes \
            -Dwith_example=no \
            -Dwith_TP=${HDM_HOME}/TextParser \
            -Dwith_BCM=${HDM_HOME}/BCMTools \
            -Dwith_PL=no ..

$ cmake -DINSTALL_DIR=${HDM_HOME}/HDMlib \
            -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_K.cmake \
            -Dwith_MPI=yes \
            -Denable_OPENMP=yes \
            -Dwith_example=no \
            -Dwith_TP=${HDM_HOME}/TextParser \
            -Dwith_BCM=${HDM_HOME}/BCMTools \
            -Dwith_PL=no ..
~~~


##### Note
- On Fujitsu machines(fx10, K, fx100), confirm appropriate directrory path for compiler environment.
- Before building, execute following command for clean. `$ make distclean`



## EXAMPLES

* If you specify the test option by `-Denable_example=yes`, you can
execute the intrinsic tests by;

	`$ make test` or `$ ctest`

* The detailed results are written in `BUILD/Testing/Temporary/LastTest.log` file.
Meanwhile, the summary is displayed for stdout.




## CONTRIBUTORS

* Kenji     Ono      _keno@{cc.kyushu-u.ac, riken}.jp_
* Hiroki    Mizuno
* Yukiteru  Mukai
* Syoyo     Fujita
