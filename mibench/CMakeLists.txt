cmake_minimum_required(VERSION  3.10)

project(mibench C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
add_compile_definitions(FPM_X86)

FILE(GLOB TELECOMM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/CRC32/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/FFT/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast_alaw.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast_lin.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast_ulaw.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/toast_audio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/gsm_option.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/gsm_destroy.c"
#        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/gsm_d.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/gsm_decode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/gsm_encode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/decode.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/gsm/src/*.c"
)

FILE(GLOB SECURITY_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/security/blowfish/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/pgp.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/armor.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/keymgmt.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/mpiio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/mpilib.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/crypto.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/passwd.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/random.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/noise.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/zbits.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/ztrees.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/zdeflate.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/zipup.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/keymaint.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/idea.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/rsagen.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/fileio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/r3000.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/more.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/charset.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/language.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/systemc.c"
#        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/mpilib.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/mdfile.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/zunzip.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/randpool.c"
#        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/rsaglue2.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/rsaglue1.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/genprime.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/rijndael/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/sha/*.c"
)

FILE(GLOB OFFICE_SOURCES
#        "${CMAKE_CURRENT_SOURCE_DIR}/office/ghostscript/src/gs.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/ispell/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/rsynth/*.c"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/madplay.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/player.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/audio.c" # Ensure this is the desired audio backend
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libid3tag/*.c" # <--- UNCOMMENT AND ENABLE THIS LINE
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libmad/timer.c" # Leave commented unless needed
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libmad/version.c" # Leave commented unless needed
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libmad/*.c" # Leave commented unless needed
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/libz/*.c" # Leave commented unless needed
)

FILE(GLOB CONSUMER_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/tools/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/contrib/winnt/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/jpeg/jpeg-6a/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/lame/lame3.70/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/consumer/typeset/lout-3.24/*.c"
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
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/audio_esd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/audio_sun.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/mad/mad-0.14.2b/audio_win32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_acorn.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_apple.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_atari.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_msdos.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_vms.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_win3.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/libtiff/tif_win32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/consumer/typeset/lout-3.24/prg2lout.c"

)

list(REMOVE_ITEM TELECOMM_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/sgicaudio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/sgidaudio.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/telecomm/adpcm/src/suncaudio.c"
)

list(REMOVE_ITEM OFFICE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/office/rsynth/mkdictdb.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/ispell/buildhash.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/office/ispell/icombine.c"
)

list(REMOVE_ITEM SECURITY_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/amiga__main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/c370.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/gettime.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/security/pgp/src/rsaglue2.c"
)

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
# Force no optimization for all build types
set(CMAKE_C_FLAGS "-O0 ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "-O0 ${CMAKE_CXX_FLAGS}")


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
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/consumer/tiff-v3.5.4/include>
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
        m
)

target_compile_definitions(mibench PUBLIC
        # For general compatibility:
        _GNU_SOURCE
        _DEFAULT_SOURCE # For modern systems to enable some GNU extensions
        FPM_DEFAULT
        HAVE_MMAP
        LAMEPARSE
        LAMESNDFILE
        SASR
)
#target_compile_definitions(mad PUBLIC FPM_X86)

# Install the library and header
install(TARGETS mibench
    EXPORT lib_targets
    ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib
    PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)
install(FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/mibench.h
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)
