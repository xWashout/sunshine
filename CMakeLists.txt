cmake_minimum_required(VERSION 3.5)

project(sunshine LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(prog/mqtt)
add_subdirectory(prog/app)

include_directories(mqtt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
include_directories(app PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
