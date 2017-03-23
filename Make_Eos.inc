# Eos at OLCF
CC  = cc
CXX = CC
FC  = ftn
CPP = cpp

# Default linker is CC
LINKER   = $(CC)

# LAPACK or GSL required	
LAPACK_INC_DIR = /usr/include/lapack
LAPACK_LIB_DIR = /usr/lib64
GSL_INC_DIR = ${GSL_DIR}/include 
GSL_LIB_DIR = ${GSL_DIR}/lib

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

