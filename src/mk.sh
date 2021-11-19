#!/bin/zsh

LIBCOMMON_BUILD_DIR="libcommon/build/"

function clear_all() {
  if [ -d ${LIBCOMMON_BUILD_DIR} ]; then
    rm -rf ${LIBCOMMON_BUILD_DIR}
  fi
  
  if [ -d build ]; then
    rm -rf build
  fi

  if [ -e test ]; then
    rm test
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

  if [ -e "test" ]; then
    rm test
  fi
  gcc -g3 -o test test.c -Wall -Llibcommon/build -lcommon -I libcommon/
}

# main
if [ "${1}" = "clear" ]; then
  clear_all
else
  compile_all
fi
