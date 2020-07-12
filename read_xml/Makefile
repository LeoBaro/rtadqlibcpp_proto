# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := NO

# PROFILE can be set to YES to include profiling info, or NO otherwise
PROFILE        := NO

# TINYXML_USE_STL can be used to turn on STL support. NO, then STL
# will not be used. YES will include the STL files.
TINYXML_USE_STL := YES

#****************************************************************************

CXX    := g++

DEBUG_CXXFLAGS     := -Wall -Wno-format -g -DDEBUG -std=c++11
RELEASE_CXXFLAGS   := -Wall -Wno-unknown-pragmas -Wno-format -O3 -std=c++11


ifeq (YES, ${DEBUG})
   CXXFLAGS     := ${DEBUG_CXXFLAGS}
else
   CXXFLAGS     := ${RELEASE_CXXFLAGS}
endif

ifeq (YES, ${PROFILE})
   CXXFLAGS := ${CXXFLAGS} -pg -O3
endif


LIBS		 :=


#****************************************************************************
# Preprocessor directives
#****************************************************************************

ifeq (YES, ${TINYXML_USE_STL})
  DEFS := -DTIXML_USE_STL
else
  DEFS :=
endif

#****************************************************************************
# Include paths
#****************************************************************************

#INCS := -I/usr/include/g++-2 -I/usr/local/include
INCS := -I ./include


#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CXXFLAGS := ${CXXFLAGS} ${DEFS}

#****************************************************************************
# Targets of the build
#****************************************************************************

OUTPUT := main

all: ${OUTPUT}


#****************************************************************************
# Source files
#****************************************************************************

SRCS := src/tinyxml.cpp src/tinyxmlparser.cpp src/tinyxmlerror.cpp src/tinystr.cpp \
				src/datatypes.cpp

# Add on the sources for libraries
SRCS := ${SRCS}

OBJS := $(addsuffix .o,$(basename ${SRCS}))

#****************************************************************************
# Output
#****************************************************************************


${OUTPUT}: ${OBJS}
	${CXX} ${CXXFLAGS} ${INCS} src/main.cpp ${OBJS} ${LIBS} -o main.exe

#****************************************************************************
# common rules
#****************************************************************************

# Rules for compiling source files to object files
%.o : %.cpp
	${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

%.o : %.c
	${CC} -c ${CFLAGS} ${INCS} $< -o $@

clean:
	-rm -f core ${OBJS} ${OUTPUT}
