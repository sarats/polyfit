# Eos at OLCF
CC  = cc
CXX = CC
FC  = ftn
CPP = cpp

# Default linker is CC
LINKER   = $(CC)

# LAPACK or GSL required	
LAPACK_INC_DIR = /opt/cray/libsci/16.11.1/GNU/5.1/x86_64/include/
# module load cray-libsci
LAPACK_LIBS = 
GSL_INC_DIR = ${GSL_DIR}/include 
GSL_LIBS = -L${GSL_DIR}/lib -lgsl -lgslcblas


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

