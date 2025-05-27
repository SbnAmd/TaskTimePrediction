cmake_minimum_required(VERSION 3.10)

project(ExecutionPrediction)

add_subdirectory(mibench)

#include_directories(mibench/out)

add_executable(ExecutionPrediction mibench/test/test.c)
target_link_libraries(ExecutionPrediction PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/mibench/out/libmibench.a)

#
#add_executable(ExecutionPrediction
#        perf.h
#        perf.c
#        perf_wrapper.c
#        perf_wrapper.h
#        thread_setup.c
#        thread_setup.h
#        scheduler.c
#        scheduler.h
#        tasks.c
#        tasks.h
#        main.c
#        main.h
#        def.h
#        stack.c
#        stack.h
#        barrier.c
#        barrier.h
#        test/test_sched_fifo.c
#        test/test_sched_fifo.h
#        utils.c
#        utils.h
#        mibench/mibench.h
#        mibench/mibench.c
#        mibench/automotive/basicmath/basicmath.h
#        mibench/automotive/bitcount/bitcnts.h
#        mibench/automotive/qsort/qsort.h
#        mibench/automotive/susan/susan.h
#        mibench/consumer/jpeg/jpeg-6a/jpeg.h
#        mibench/consumer/lame/lame3.70/main.h
#        mibench/consumer/mad/mad-0.14.2b/madplay.h
#        mibench/consumer/tiff-v3.5.4/tools/tiff.h
#        mibench/consumer/typeset/lout-3.24/lout.h
#        mibench/network/dijkstra/dijkstra.h
#        mibench/network/patricia/patricia_test.h
#        mibench/office/ghostscript/src/gs.h
#        mibench/office/ispell/ispell_test.h
#        mibench/office/rsynth/say_test.h
#        mibench/office/stringsearch/stringsearch.h
#        mibench/security/blowfish/bf.h
#        mibench/security/pgp/src/pgp_test.h
#        mibench/security/rijndael/rijndael.h
#        mibench/security/sha/sha_test.h
#        mibench/telecomm/adpcm/src/rawaudio.h
#        mibench/telecomm/CRC32/crc_test.h
#        mibench/telecomm/FFT/fft.h
#        mibench/telecomm/gsm/src/gsm_test.h
#)
#set(CMAKE_C_FLAGS "-O0" CACHE STRING "C flags" FORCE)
#set(CMAKE_CXX_FLAGS "-O0" CACHE STRING "C++ flags" FORCE)
#target_link_libraries(ExecutionPrediction PRIVATE m pthread)