cmake_minimum_required (VERSION 3.27)
project (escrapper VERSION 0.0.0)
set(REVISION 2)

configure_file(
  "${PROJECT_SOURCE_DIR}/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/Doxyfile"
  )

configure_file(
  "${PROJECT_SOURCE_DIR}/src/_config.h.in"
  "${PROJECT_BINARY_DIR}/_config.h"
  )

find_package(PkgConfig REQUIRED)
pkg_search_module(DEPS REQUIRED elementary)
pkg_search_module(CHCK check)
if(NOT CHCK_FOUND)
  message(WARNING "Check library not found. Can't enable unit tests")
endif()

# Find edje_cc and build ui
find_program(EDJE_CC_EXECUTABLE NAMES edje_cc REQUIRED)

set(SRCS
  src/config.c
  src/scrapper.c
)

add_executable(escrapper ${SRCS} src/main.c)
target_link_libraries(escrapper ${DEPS_LIBRARIES})
target_include_directories(escrapper PUBLIC
  ${DEPS_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
)

set(Input ../ui/main.edc)
set(Output main.edj)

# May become a cmake function later
add_custom_command(TARGET escrapper PRE_BUILD
  COMMAND ${EDJE_CC_EXECUTABLE} ${Input} ${Output}
  DEPENDS ${Input}
  COMMENT "edje_cc ${Input} ${Output}"
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR})

if(CHCK_FOUND)
  add_executable(escrapper-tests ${SRCS}
    tests/config.c
    tests/main.c
    tests/scrapper_test.c
  )
  target_link_libraries(escrapper-tests ${CHCK_LIBRARIES} ${DEPS_LIBRARIES})
  target_include_directories(escrapper-tests
    PUBLIC $
    ${PROJECT_SOURCE_DIR}
    ${CHCK_INCLUDE_DIRS}
    ${DEPS_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
  )

  enable_testing()
  add_test(NAME escrapper-tests COMMAND escrapper-tests)
  
 # add_custom_target(check ALL
 #   COMMAND escrapper-tests
    #DEPENDS escrapper-tests
 # )
endif()
      
