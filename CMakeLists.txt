cmake_minimum_required(VERSION 3.10)

project(ExecutionPrediction)


add_executable(ExecutionPrediction
        perf.h
        perf.c
        perf_wrapper.c
        perf_wrapper.h
        thread_setup.c
        thread_setup.h
        scheduler.c
        scheduler.h
        tasks.c
        tasks.h
        main.c
        main.h
        def.h
        stack.c
        stack.h
        barrier.c
        barrier.h
        test/test_sched_fifo.c
        test/test_sched_fifo.h
)
set(CMAKE_C_FLAGS "-O0" CACHE STRING "C flags" FORCE)
set(CMAKE_CXX_FLAGS "-O0" CACHE STRING "C++ flags" FORCE)
target_link_libraries(ExecutionPrediction PRIVATE m pthread)