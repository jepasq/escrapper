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

# Find edje_cc and build ui
find_program(EDJE_CC_EXECUTABLE NAMES edje_cc REQUIRED)


add_executable(escrapper src/main.c)
target_link_libraries(escrapper ${DEPS_LIBRARIES})
target_include_directories(escrapper PUBLIC ${DEPS_INCLUDE_DIRS})

set(Input ../ui/main.edc)
set(Output main.edj)

add_custom_command(TARGET escrapper PRE_BUILD
        COMMAND ${EDJE_CC_EXECUTABLE} ${Input} ${Output}
        DEPENDS ${Input}
        COMMENT "edje_cc ${Input} ${Output}"
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
