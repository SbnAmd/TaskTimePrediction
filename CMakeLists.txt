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

FILE(GLOB TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/utils.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/data_structure/*.c"
#        test/execution_order/exe_ord.c
#        test/execution_order/exe_ord.h
        test/stats_monitoring/stat_mon.c
        test/stats_monitoring/stat_mon.h
)

add_executable(ExecutionPrediction
#        ${SOURCES}
        ${TEST_SOURCES}
        mibench/mi_def.h
#        test/stats_monitoring/stat_mon.c
#        test/stats_monitoring/stat_mon.h
        perf_count/perf_count.c
        perf_count/perf_count.h
        src/data_structure/timepoint.c
        src/data_structure/timepoint.h
        src/data_structure/tp_stack.c
        src/data_structure/tp_stack.h
        src/data_structure/timeslice.c
        src/data_structure/timeslice.h

)
target_link_libraries(ExecutionPrediction PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmibench.a
        m pthread
        audio md
        crypto ncurses
    )


set(CMAKE_C_FLAGS "-O0" CACHE STRING "C flags" FORCE)
set(CMAKE_CXX_FLAGS "-O0" CACHE STRING "C++ flags" FORCE)
