PROJECT(libftd2xx-wrap)

cmake_minimum_required(VERSION 3.2)

set(LIBFTD2XX_INCDIR  CACHE PATH ftd2xx_include_dir)
set(LIBFTD2XX_LIBDIR  CACHE PATH ftd2xx_library_dir)
include_directories(${LIBFTD2XX_INCDIR})
link_directories(${LIBFTD2XX_LIBDIR})

if(MSVC)
  set(CMAKE_SHARED_LINKER_FLAGS
      "${CMAKE_SHARED_LINKER_FLAGS} /DEF:ftdi.def")
endif()

add_library(ftdi SHARED ftdi.c)
add_definitions(-DINTERNAL_BUILD)
target_link_libraries(ftdi ftd2xx)

