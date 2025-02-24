cmake_minimum_required(VERSION 3.25)
project(SocialNetworkProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(SocialNetworkProject main.cpp Person.h Person.cpp utils.h utils.cpp Graph.cpp)
