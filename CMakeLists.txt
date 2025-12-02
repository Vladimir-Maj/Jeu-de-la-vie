cmake_minimum_required(VERSION 3.10)
project(JeuDeLaVie VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(JeuDeLaVie main.cpp)

target_include_directories(JeuDeLaVie PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/core/main
    ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer
)

target_link_libraries(JeuDeLaVie SFML::Graphics SFML::Window SFML::System)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(CMAKE_CXX_COMPILER_ID MATCHES "GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
endif()