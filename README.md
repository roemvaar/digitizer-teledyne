# Teledyne ADQ32 Digitizer Examples

## Examples

The idea is to make each of the examples a self-contained example of the ADQ32 digitizer
different capabilities.

* Acquire to disk
* Acquire to memory
* Acquire two channels
* Continuous acquisition
* Continuous acquisition using GPU

## Setup

* Teledyne ADQ32 Digitizer
* Waveform Generator

## Build

Only works on Linux-based systems.

```
$ git clone https://github.com/roemvaar/digitizer-teledyne.git
$ cd digitizer-teledyne
$ mkdir build && cd build
$ cmake ..
$ make
```

An executable for each of the examples is created. Move to the directory of your interest and
run the executable.
