cmake_minimum_required(VERSION 3.11.1)
project(restconf)

set(CMAKE_CXX_STANDARD 14)
include_directories(src)

file(GLOB_RECURSE restconf_SRC "src/*.h" "src/*.c")

find_library(JSON_C json-c)
if(NOT JSON_C)
  message(FATAL_ERROR "json_c library not found")
endif()

find_library(UCI uci)
if(NOT UCI)
  message(FATAL_ERROR "uci library not found")
endif()

find_library(UBOX ubox)
if(NOT UBOX)
  message(FATAL_ERROR "ubox library not found")
endif()

add_executable(restconf ${restconf_SRC})
target_link_libraries(restconf ${JSON_C} ${UCI} ${UBOX})
INSTALL(TARGETS restconf RUNTIME DESTINATION /www/cgi-bin/)