#!/bin/zsh

LIBCOMMON_BUILD_DIR="libcommon/build/"

function clear_all() {
  if [ -d ${LIBCOMMON_BUILD_DIR} ]; then
    rm -rf ${LIBCOMMON_BUILD_DIR}
  fi
  
  if [ -d build ]; then
    rm -rf build
  fi
}

function compile_all() {
  if [ ! -d "libcommon/build/" ]; then
    mkdir libcommon/build
  fi
  cd libcommon/build
  cmake ..
  make clean;make
  cd -

  if [ ! -d "build" ]; then
    mkdir build
  fi
  cd build
  cmake ..
  make clean;make
  cd -
}

# main
if [ "${1}" = "clear" ]; then
  clear_all
else
  compile_all
fi
