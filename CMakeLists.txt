#
# Teledyne ADQ32 Digitizer
#

cmake_minimum_required (VERSION 3.10)

project (digitizer_experiments LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCE_FILES
    acquire_to_disk.c
)

add_executable(acquire_to_disk ${SOURCE_FILES})

target_compile_options(acquire_to_disk PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(acquire_to_disk PUBLIC LINUX)

if (UNIX)
    target_compile_definitions(acquire_to_disk PUBLIC LINUX)

    find_library(ADQ_LIB
    NAMES libadq libadq.so
    HINTS
    "${CMAKE_SOURCE_DIR}/../../../source/.libs/"
    "${CMAKE_SOURCE_DIR}/../../../build/"
    )
else ()
    message("Only Linux build systems supported.")
endif(UNIX)

find_path(ADQAPI_INCLUDE
  NAMES ADQAPI.h
  HINTS
    "${CMAKE_SOURCE_DIR}/../../../Release/"
    "${CMAKE_SOURCE_DIR}/../../../build/"
    ${ADQAPI_INSTALL_PATH}
)

target_link_libraries(acquire_to_disk ${ADQ_LIB})
target_include_directories(acquire_to_disk PUBLIC ${ADQAPI_INCLUDE})
