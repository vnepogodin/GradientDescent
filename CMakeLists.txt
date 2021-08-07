cmake_minimum_required(VERSION 3.8)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

##
## PROJECT
## name
##
project(NeuralNetwork
        LANGUAGES CXX)

##
## INCLUDE
##
include(FindThreads)
include(CompilerWarnings)

find_package(Threads REQUIRED)
find_package(SFML REQUIRED system window graphics)

##
## CONFIGURATION
##
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_GENERATOR STREQUAL "Ninja")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-fcolor-diagnostics ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-fcolor-diagnostics ${CMAKE_C_FLAGS}")
  endif()
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-fdiagnostics-color ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-fdiagnostics-color ${CMAKE_C_FLAGS}")
  endif()
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /arch:AVX2 /fp:precise /LTCG:INCREMENTAL")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG /Od")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffast-math -flto")
endif()

add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

##
## TARGET
##
add_executable(${PROJECT_NAME}
        nn.hpp
        header.hpp
        main.cpp)

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

add_compile_definitions(${CMAKE_THREAD_DEFS_INIT})
add_compile_options(${CMAKE_CXX_FLAGS} ${CMAKE_THREAD_DEFS_INIT})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics ${CMAKE_THREAD_LIBS_INIT})
