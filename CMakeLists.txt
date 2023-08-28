#
# Teledyne ADQ32 Digitizer Examples
#

cmake_minimum_required (VERSION 3.5)

project(adq32_examples)

add_subdirectory(acquire_to_disk)
add_subdirectory(acquire_to_memory)
add_subdirectory(acquire_two_channels)
add_subdirectory(continuous_acquisition)
add_subdirectory(continuous_acquisition_gpu)
