cmake_minimum_required(VERSION 3.10)
project(Raycasting-game)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
include_directories(
    ../libs/SFML/include
    ../libs/include
    ../libs/yaml-cpp/include
)
set(SOURCES
    main.cpp
    map.cpp
    renderer.cpp
    player.cpp
    raycast.cpp
)
set(BUILD_DIR ../build)
add_executable(${PROJECT_NAME} ${SOURCES})
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG master
)

FetchContent_MakeAvailable(yaml-cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR}
)
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E env LD_LIBRARY_PATH=../libs/SFML/lib ../build/output
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running the program"
)
