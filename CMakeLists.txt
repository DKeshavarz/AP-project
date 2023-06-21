cmake_minimum_required(VERSION 3.0)
project (bird)
set (CMAKE_CXX_STANDARD 14)
set(SOURCES
    src/main.cpp 
    src/Twitterak.cpp
    src/Tweet.cpp
    src/User.cpp
    src/Date.cpp
    src/Functions.cpp
    hash-library/sha256.cpp
)
include_directories(includes/ hash-library/)
add_executable(app ${SOURCES})
