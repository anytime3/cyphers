cmake_minimum_required(VERSION 3.28.1)

project(testing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(cipherlib STATIC Cipher.cpp)
set_target_properties(cipherlib PROPERTIES LINKER_LANGUAGE C)
add_executable(cipherVegener main.cpp)

target_link_libraries(cipherVegener cipherlib)
