cmake_minimum_required(VERSION 3.27)
project(Stock_Market_Simulator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cpp-httplib)
add_subdirectory(json)

add_executable(Stock_Market_Simulator test.cpp
        test.cpp
        test.cpp
        serializer.cpp
        serializer.hpp
        data.cpp
        data.hpp)
target_link_libraries(Stock_Market_Simulator PRIVATE httplib nlohmann_json)
