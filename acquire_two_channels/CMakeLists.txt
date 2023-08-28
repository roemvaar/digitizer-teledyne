#
# Teledyne ADQ32 Digitizer
#

cmake_minimum_required (VERSION 3.5)

project (acquire_two_channels LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCE_FILES
    acquire_two_channels.c
)

add_executable(acquire_two_channels ${SOURCE_FILES})

target_compile_options(acquire_two_channels PRIVATE -Wall -Wextra -pedantic)
target_compile_definitions(acquire_two_channels PUBLIC LINUX)

if (UNIX)
    target_compile_definitions(acquire_two_channels PUBLIC LINUX)

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

target_link_libraries(acquire_two_channels ${ADQ_LIB})
target_include_directories(acquire_two_channels PUBLIC ${ADQAPI_INCLUDE})

# TODO: Fix this command
# add_custom_target(build-time-make-directory ALL
#   COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:data_two_channels>/data")
