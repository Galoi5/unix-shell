cmake_minimum_required(VERSION 3.13)

project(unix-shell)

file(GLOB_RECURSE SOURCE_FILES src/*.c src/*.h src/commands/*.c src/commands/*.h)

set(CMAKE_C_STANDARD 23) # Enable the C23 standard

add_executable(shell ${SOURCE_FILES})

target_link_libraries(shell PRIVATE readline)
