if(EXISTS "E:/homeWork_C++/QT/search_engine/cmake-build-debug/search_engine[1]_tests.cmake")
  include("E:/homeWork_C++/QT/search_engine/cmake-build-debug/search_engine[1]_tests.cmake")
else()
  add_test(search_engine_NOT_BUILT search_engine_NOT_BUILT)
endif()
