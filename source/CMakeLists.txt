cmake_minimum_required(VERSION 3.5)

project(AMRM-source LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(source
    main.cpp
    vm-src.h vm-src.cpp subprog.cpp
    command-exec.h command-exec.cpp
    command.h command.cpp
    stack.h stack.cpp
    heap.h heap.cpp
    byteType.h
    ritualka-commands.txt
    boot-code.h
)

install(TARGETS source
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
