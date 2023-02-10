#
# Teledyne ADQ32 Digitizer
#

cmake_minimum_required (VERSION 3.5)

project (continuous_acquisition_gpu LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCE_FILES
    continuous_acquisition_gpu.c
)

add_executable(continuous_acquisition_gpu ${SOURCE_FILES})

target_compile_options(continuous_acquisition_gpu PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(continuous_acquisition_gpu PUBLIC LINUX)

if (UNIX)
    target_compile_definitions(continuous_acquisition_gpu PUBLIC LINUX)

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

target_link_libraries(continuous_acquisition_gpu ${ADQ_LIB})
target_include_directories(continuous_acquisition_gpu PUBLIC ${ADQAPI_INCLUDE})
