cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(SmartAffair LANGUAGES CXX C)

find_package(SEAL 4.1.1 EXACT REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(examples)

target_sources(examples
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/1_ckks_example.cpp
)

if(TARGET SEAL::seal)
    target_link_libraries(examples PRIVATE SEAL::seal)
elseif(TARGET SEAL::seal_shared)
    target_link_libraries(examples PRIVATE SEAL::seal_shared)
else()
    message(FATAL_ERROR "Cannot find target SEAL::seal or SEAL::seal_shared")
endif()
