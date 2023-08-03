cmake_minimum_required (VERSION 3.27)
project (escrapper VERSION 0.0.0)
set(REVISION 0)

configure_file(
  "${PROJECT_SOURCE_DIR}/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/Doxyfile"
  )

configure_file(
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

find_package(PkgConfig REQUIRED)
pkg_search_module(DEPS REQUIRED elementary)

add_executable(escrapper src/main.c)
target_link_libraries(escrapper ${DEPS_LIBRARIES})
target_include_directories(escrapper PUBLIC ${DEPS_INCLUDE_DIRS})
