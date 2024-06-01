cmake_minimum_required(VERSION 3.27)
project(Stock_Market_Simulator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cpp-httplib)
add_subdirectory(json)

add_executable(Stock_Market_Simulator assets.cpp
        assets.cpp
        assets.cpp)
target_link_libraries(Stock_Market_Simulator PRIVATE httplib nlohmann_json)
