#!/bin/zsh

function clear_all() {
  cd libcommon
  rm -rf build
  cd ..
  rm -rf build
  rm test
}

function compile_all() {
  cd libcommon/build
  make clean;make
  cd -

  rm test
  gcc test.c -o test -Llibcommon/build -lcommon -I libcommon/
}

# main
if [ "${1}" = "clear" ]; then
  clear_all
else
  compile_all
fi
