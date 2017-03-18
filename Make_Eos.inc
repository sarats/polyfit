# Eos at OLCF
CC  = cc
CXX = CC
FC  = ftn
CPP = cpp

# Default linker is CC
LINKER   = $(CC)

# Default compiler flags
CFLAGS    = -O2 -DUSE_GSL ${GSL_INCLUDE_OPTS}
# CFLAGS    = -O2 -DUSE_GSL
FFLAGS    = -O2
CXXFLAGS  = -O2
LDFLAGS   += -lm ${GSL_POST_LINK_OPTS}
# LDFLAGS   += -lm -lgsl -lcblas 

# Include file directories
INC_DIRS +=

# Preprocessor flags
CPPFLAGS +=
FPPFLAGS +=

