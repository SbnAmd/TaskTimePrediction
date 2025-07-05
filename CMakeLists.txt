cmake_minimum_required(VERSION 3.10)

project(ExecutionPrediction)

#add_subdirectory(mibench)

include_directories(PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark
        ${CMAKE_CURRENT_SOURCE_DIR}/src/data_structure
        ${CMAKE_CURRENT_SOURCE_DIR}/src/perf_event
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

FILE(GLOB SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/benchmark/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/data_structure/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/perf_event/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/scheduler/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    )

add_executable(ExecutionPrediction
        ${SOURCES}
        mibench/mi_def.h
        test/execution_order/exe_ord.c
        test/execution_order/exe_ord.h
)
target_link_libraries(ExecutionPrediction PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmibench.a
        m pthread
        audio md
        crypto ncurses
    )


set(CMAKE_C_FLAGS "-O0" CACHE STRING "C flags" FORCE)
set(CMAKE_CXX_FLAGS "-O0" CACHE STRING "C++ flags" FORCE)
