cmake_minimum_required(VERSION 3.10)
project(KukScript)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# All source files
set(SOURCES
    main.cpp
    front/lexer.cpp
    front/parser.cpp
    front/interpreter.cpp
)

# Add executable
add_executable(kuk ${SOURCES})

# Include front folder for headers
target_include_directories(kuk PRIVATE front)