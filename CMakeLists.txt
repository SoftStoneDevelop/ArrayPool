cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NAME ArrayPool)
project(${NAME} VERSION 0.1.0)

# Add source to this project's executable.
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/Src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/Src
    )

# TODO: Add tests and install targets if needed.