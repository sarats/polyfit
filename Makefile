# Makefile to compile and link C/C++/F77/F90 source programs to corresponding executables.
# Last Modified Date  : Feb 12, 2013.
#
# Usage: make single (create single exe from all sources) 
#        make multiple (separate exe for each source file)
#
# Notes: To customize for your platform, please create a file: Make_(Your Machine).inc (Copy Make_Linux.inc and modify as needed).
# 		 Then update the MACHINE variable accordingly.
#
MACHINE = Linux
# MACHINE = Eos
include Make_$(MACHINE).inc

ifdef gsl
    CFLAGS += -DUSE_GSL -I${GSL_INC_DIR}
	LDFLAGS += -L${GSL_LIB_DIR} -lgsl -lgslcblas
else
    CFLAGS += -I${LAPACK_INC_DIR}
	LDFLAGS += -L/${LAPACK_LIB_DIR} -llapacke -llapack
endif	

ifdef debug
	# In case you use -DDEBUG=n to print debugging info (at log level 'n') 
	CFLAGS   += -DDEBUG=$(debug) -g 
	FFLAGS   += -DDEBUG=$(debug) -g 
	CXXFLAGS += -DDEBUG=$(debug) -g 
endif

# Source/Object Files
HEADERS  = $(wildcard *.h)
HEADERS  +=$(wildcard *.hpp)
C_SRCS   = $(wildcard *.c)
CXX_SRCS = $(wildcard *.cpp)
F77_SRCS = $(wildcard *.f)
F90_SRCS = $(wildcard *.f90)
ALL_SRCS = $(C_SRCS) $(CXX_SRCS) $(F77_SRCS) $(F90_SRCS)
C_OBJS   = $(patsubst %.c,%.o,$(wildcard *.c))
CXX_OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
F77_OBJS = $(patsubst %.f,%.o,$(wildcard *.f))
F90_OBJS = $(patsubst %.F90,%.o,$(wildcard *.f90))
ALL_OBJS = $(C_OBJS) $(CXX_OBJS) $(F77_OBJS) $(F90_OBJS)

# Separate executables for each source file
C_EXES   = $(C_SRCS:%.c=%)
CXX_EXES = $(CXX_SRCS:%.cpp=%)
F77_EXES = $(F77_SRCS:%.f=%)
F90_EXES = $(F90_SRCS:%.f90=%)
ALL_EXES =$(C_EXES) $(CXX_EXES) $(F77_EXES) $(F90_EXES)

# In this case, a single executable is created from all sources	
MASTER_EXE = driver
# Package name (present directory name + -pkg)
PACKAGE_NAME = package

all: single
# @echo -e "Usage:   make single (create single exe from all sources) \n\t make multiple (separate exe for each source file)"

single: $(ALL_OBJS) $(HEADERS) 
	$(LINKER) -o $(MASTER_EXE) $(ALL_OBJS) $(LDFLAGS)

multiple: $(ALL_EXES)

cexes: $(C_EXES)
	
cxxexes: $(CXX_EXES)
	
f77exes: $(F77_EXES)
	
f90exes: $(F90_EXES)
	
clean:
	rm -rf $(ALL_OBJS) $(ALL_EXES) $(MASTER_EXE)

install:
	

doc:
	doxygen Doxyfile

package:
	@mkdir -p $(PACKAGE_NAME)
	@cp $(HEADERS) $(ALL_SRCS) Makefile $(PACKAGE_NAME)
	tar zcvf $(PACKAGE_NAME).tgz $(PACKAGE_NAME)
	@rm -rf $(PACKAGE_NAME)

.PHONY: all single multiple cexes cxxexes f77exes f90exes clean install doc package 

.SUFFIXES: .cpp .c .h .o .hpp .f90 .f

# Rules

$(CXX_EXES): $(CXX_SRCS)
	$(CXX) $(CXXFLAGS) $(INC_DIRS) $@.cpp -o $@ $(LDFLAGS)

$(C_EXES): $(C_SRCS)
	$(CC) $(CFLAGS) $(INC_DIRS) $@.c -o $@ $(LDFLAGS)

$(F77_EXES): $(F77_SRCS)
	$(FC) $(FFLAGS) $(INC_DIRS) $@.f -o $@ $(LDFLAGS)

$(F90_EXES): $(F90_SRCS)
	$(FC) $(FFLAGS) $(INC_DIRS) $@.f90 -o $@ $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INC_DIRS) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INC_DIRS) -c $< -o $@

.f90.o:
	$(FC) $(FFLAGS) $(FPPFLAGS) $(INC_DIRS) -c $< -o $@

.f.o:
	$(FC) $(FFLAGS) $(FPPFLAGS) $(INC_DIRS) -c $< -o $@

