# PPACK

#### Dependences
* libboost-program-options1.71-dev (archlinux boost package)
* C++ compiler with `openmp` and `mpi` support (`g++` GNU Compiler + `openmpi` or `mpich`)
* Cmake
* [jsoncpp](https://github.com/open-source-parsers/jsoncpp)

## Installation
### Manual
```bash
git clone https://github.com/glozanoa/ppack.git
cd ppack
mkdir -p build && cd build
cmake ..
cmake --build .
export PATH=$PATH:$PWD #export ppack to the PATH
```
### Automatic
```bash
wget https://raw.githubusercontent.com/glozanoa/ppack/master/autoinstall
chmod +x autoinstall
./autoinstall --prefix=WHERE_INSTALL_PPACK --systemwide #systemwide enable installation for all the users
```