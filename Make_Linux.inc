# Generic Linux machine
CC  = gcc
CXX = g++
FC  = gfortran
CPP = cpp

# Default linker is CC
LINKER   = $(CC)

# Default compiler flags
CFLAGS    = -O2 -DUSE_GSL
# CFLAGS    = -O2 -DUSE_GSL
FFLAGS    = -O2
CXXFLAGS  = -O2
LDFLAGS   += -lm -lgsl -lgslcblas 
# LDFLAGS   += -L/usr/lib64/atlas -lm -lgsl -lcblas -latlas

# Include file directories
INC_DIRS +=

# Preprocessor flags
CPPFLAGS +=
FPPFLAGS +=

