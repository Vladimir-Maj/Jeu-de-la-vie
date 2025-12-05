cmake_minimum_required(VERSION 3.10)
project(JeuDeLaVie VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 2
# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# SFML 3
find_package(SFML REQUIRED COMPONENTS Graphics Window System)

add_executable(JeuDeLaVie
    main.cpp
    core/gameEngine.cpp
    core/src/fileManager.cpp
    core/src/grid.cpp
    core/src/rules/rule.cpp
    core/src/rules/conwayRule.cpp
    core/src/cells/cell.cpp
    core/src/cells/cellSimple.cpp
    core/src/cells/cellObstacle.cpp
    core/renderer/graphic.cpp
    core/renderer/console.cpp
    core/cmd.cpp
)

target_include_directories(JeuDeLaVie PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/core/src
    ${CMAKE_CURRENT_SOURCE_DIR}/core/renderer
)

# SFML 2
# target_link_libraries(JeuDeLaVie sfml-graphics sfml-window sfml-system)

# SFML 3
target_link_libraries(JeuDeLaVie SFML::Graphics SFML::Window SFML::System)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if(CMAKE_CXX_COMPILER_ID MATCHES "GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
endif()