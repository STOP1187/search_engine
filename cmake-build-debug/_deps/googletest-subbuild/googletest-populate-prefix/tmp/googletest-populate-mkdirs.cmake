# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-src"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-build"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "E:/homeWork_C++/QT/search_engine/cmake-build-debug/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
