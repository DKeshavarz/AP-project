cmake_minimum_required(VERSION 3.0)
project (bird)
set (CMAKE_CXX_STANDARD 14)
set(SOURCES
    src/main.cpp 
    src/Twitterak.cpp
    src/Tweet.cpp
    src/User.cpp
    src/Date.cpp
    src/Functions
)
include_directories(includes/)
add_executable(app ${SOURCES})