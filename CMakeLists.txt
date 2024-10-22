cmake_minimum_required(VERSION 3.27)
project(escrapper VERSION 0.0.0)
set(REVISION 15)

# Create gdb symbol table
set(CMAKE_BUILD_TYPE Debug)

configure_file(
  "${PROJECT_SOURCE_DIR}/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/Doxyfile"
  )

configure_file(
  "${PROJECT_SOURCE_DIR}/src/_config.h.in"
  "${PROJECT_BINARY_DIR}/_config.h"
  )

# I have issue trying to read absolute path files with fopen()
configure_file(
  "${PROJECT_SOURCE_DIR}/fixtures/config_eol"
  "${PROJECT_BINARY_DIR}/fixtures/config_eol"
  )
  
find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS REQUIRED elementary libcurl libpcre2-posix
  libmongoc-1.0)

# Find edje_cc and build ui
#find_program(EDJE_CC_EXECUTABLE NAMES edje_cc REQUIRED)

set(SRCS
  src/config.c
  src/list.c
  src/logger.c
  src/persist.c
  src/scrapper.c
  src/ui.c
)

add_executable(escrapper ${SRCS} src/main.c)
target_link_libraries(escrapper ${DEPS_LIBRARIES})
target_include_directories(escrapper PUBLIC
  ${DEPS_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
)

add_executable(escrapper-example-list ${SRCS} src/examples/list.c)
target_link_libraries(escrapper-example-list ${DEPS_LIBRARIES})
target_include_directories(escrapper-example-list PUBLIC
  ${DEPS_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/src/
)

add_executable(escrapper-example-logger ${SRCS} src/examples/logger.c)
target_link_libraries(escrapper-example-logger ${DEPS_LIBRARIES})
target_include_directories(escrapper-example-logger PUBLIC
  ${DEPS_INCLUDE_DIRS}
  ${PROJECT_BINARY_DIR}
  ${PROJECT_SOURCE_DIR}/src/
)


pkg_check_modules(CHCK check)
if(NOT CHCK_FOUND)
  message(WARNING "Check library not found. Can't enable unit tests")
else()
  add_executable(escrapper-tests ${SRCS}
    tests/config.c
    tests/main.c
    tests/list_test.c
    tests/logger_test.c
    tests/persist_test.c
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
  
  #add_custom_target(check #ALL
  #  COMMAND escrapper-tests
    #DEPENDS escrapper-tests
  #  VERBATIM
  #)
endif()
