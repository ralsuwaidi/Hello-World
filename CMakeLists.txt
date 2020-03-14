cmake_minimum_required(VERSION 3.12)

project(hello)

set( NAME_SRC
    src/Main.cpp    
)

set( NAME_HEADERS       
     include/main.h
     include/json.hpp
     include/reddit_curl.h
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include/curl )

link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( ParseReddit ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( ParseReddit curl )

