#!/bin/bash
export OMPI_CXX=g++
export LD_LIBRARY_PATH=/usr/local/openmpi/1.6.3-gcc/lib/:$LD_LIBRARY_PATH
make
