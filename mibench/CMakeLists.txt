cmake_minimum_required(VERSION  3.10)

project(mibench C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)

FILE(GLOB TELECOMM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/CRC32/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/FFT/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast.c"
)

FILE(GLOB SECURITY_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/security/blowfish/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/pgp.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/rijndael/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/sha/*.c"
)

FILE(GLOB OFFICE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/office/ghostscript/src/gs.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/ispell/ispell.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/rsynth/say.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/stringsearch/*.c"
)

FILE(GLOB NETWORK_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/network/dijkstra/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/network/patricia/*.c"
)

FILE(GLOB AUTOMOTIVE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/automotive/basicmath/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/automotive/bitcount/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/automotive/qsort/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/automotive/susan/*.c"
    )

set(MAD_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/decode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/stream.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/frame.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/synth.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/version.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/fixed.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/stat.c"
#        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/player.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/audio_null.c" # Ensure this is the desired audio backend
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libid3tag/*.c" # <--- UNCOMMENT AND ENABLE THIS LINE
        #        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/intl/*.c" # Leave commented unless needed
#                "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libmad/*.c" # Leave commented unless needed
#                "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/po/*.c" # Leave commented unless needed
#                "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libz/*.c" # Leave commented unless needed
)

FILE(GLOB CONSUMER_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/jpeg/jpeg-6a/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/lame/lame3.70/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/typeset/lout-3.24/prg2lout.c"
        ${MAD_SOURCES}
)

# Exclude specific files from SOURCE
list(REMOVE_ITEM CONSUMER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/jpeg/jpeg-6a/jmemdos.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/jpeg/jpeg-6a/jmemmac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/lame/lame3.70/debugscalefac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools/sgi2tiff.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools/sgigt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools/sgisv.c"
)

list(REMOVE_ITEM TELECOMM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/sgicaudio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/sgidaudio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/suncaudio.c"
)

#list(REMOVE_ITEM OFFICE_SOURCES
#        "${CMAKE_CURRENT_SOURCE_DIR}/office/ghostscript/src/dpmainc.c"
#        "${CMAKE_CURRENT_SOURCE_DIR}/office/ghostscript/src/gconf.c"
#)

# Create the static library
add_library(mibench STATIC
        mibench.c
        ${AUTOMOTIVE_SOURCES}
        ${CONSUMER_SOURCES}
        ${TELECOMM_SOURCES}
        ${SECURITY_SOURCES}
        ${NETWORK_SOURCES}
        ${OFFICE_SOURCES}
)



# Set the include directories so that other projects can find the header
target_include_directories(mibench
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/automotive/basicmath>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/automotive/bitcount>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/automotive/qsort>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/automotive/susan>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/jpeg/jpeg-6a>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/lame/lame3.70>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/msvc++/libmad>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/msvc++/madplay>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/intl>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libid3tag>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libmad>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libz>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/po>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/winamp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/typeset/lout-3.24>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/network/dijkstra>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/network/patricia>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/office/ghostscript/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/office/ispell>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/office/ispell/languages/english>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/office/rsynth>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/office/stringsearch>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/security/blowfish>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/security/rijndael/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/security/sha>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/telecomm/CRC32>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/telecomm/FFT>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        ${GTK2_INCLUDE_DIRS}
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(mibench
        PUBLIC
        ${GTK2_LIBRARIES}
)

target_compile_definitions(mibench PUBLIC
        # For general compatibility:
        _GNU_SOURCE
        _DEFAULT_SOURCE # For modern systems to enable some GNU extensions
)

# Install the library and header
install(TARGETS mibench
    EXPORT lib_targets
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out
    PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out
)
install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mibench.h
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/out
)


