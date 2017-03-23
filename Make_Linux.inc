# Generic Linux machine
CC  = gcc
CXX = g++
FC  = gfortran
CPP = cpp

# Default linker is CC
LINKER   = $(CC)

# LAPACK or GSL required	
LAPACK_INC_DIR = /usr/include/lapacke
LAPACK_LIB_DIR = /usr/lib64
GSL_INC_DIR = /usr/include/gsl
GSL_LIB_DIR = /usr/include/gsl

# Default compiler flags
CFLAGS    = -O2 
FFLAGS    = -O2
CXXFLAGS  = -O2
LDFLAGS   += -lm 

# Include file directories
INC_DIRS +=

# Preprocessor flags
CPPFLAGS +=
FPPFLAGS +=

