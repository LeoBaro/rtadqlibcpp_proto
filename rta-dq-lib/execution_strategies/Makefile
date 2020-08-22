CXX    := g++

DEBUG_CXXFLAGS     := -Wall -Wno-format -g -DDEBUG -std=c++11
RELEASE_CXXFLAGS   := -Wall -Wno-unknown-pragmas -Wno-format -O3 -std=c++11


ifeq (YES, ${DEBUG})
   CXXFLAGS     := ${DEBUG_CXXFLAGS}
else
   CXXFLAGS     := ${RELEASE_CXXFLAGS}
endif



LIBS := -L /home/leofaber/Documents/inaf/tasks/rta-dq-lib-c++/deps/CMake-hdf5-1.10.5-install/lib -lhdf5 -lhdf5_cpp


#****************************************************************************
# Include paths
#****************************************************************************
INCS := -I ./include -I /opt/anaconda3/envs/rdlcpp/include


#****************************************************************************
# Source files
#****************************************************************************
SRCS :=  
# Add on the sources for libraries
SRCS := ${SRCS}

OBJS := $(addsuffix .o,$(basename ${SRCS}))

$(info $$SRCS is [${SRCS}])

$(info $$OBJS is [${OBJS}])

#****************************************************************************
# Targets of the build
#****************************************************************************
all: hdf5_read hdf5_read_with_threads

hdf5_read: 
	${CXX} ${CXXFLAGS} ${INCS} testing/benchmarks/hdf5_read.cpp ${OBJS} ${LIBS} -o hdf5_read.exe

hdf5_read_with_threads: 
	${CXX} ${CXXFLAGS} ${INCS} testing/benchmarks/hdf5_read_with_threads.cpp ${OBJS} ${LIBS} -o hdf5_read_with_threads.exe




#****************************************************************************
# Output
#****************************************************************************


${OUTPUT}: ${OBJS}
	

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
