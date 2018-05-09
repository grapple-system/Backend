CC=g++ -std=c++0x
LIBFLAGS=-lboost_thread-mt -lpthread -lboost_system

##### source files #####
# preprocessing

PREP=preproc/preproc_new.cpp preproc/run_pre.cpp
# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/edgemerger.cpp edgecomp/repart.cpp
LOADER=datastructures/loader.cpp edgecomp/grammar.cpp
# computation sets included through header files
DATASTRUCTS=datastructures/vertex.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp datastructures/partition.cpp datastructures/context.cpp datastructures/vit.cpp datastructures/DDM.cpp
UTIL=../test/timer.cpp Library/Logger.cpp

CONSTRAINT=../../constraint/pseudoPC.cpp ../../constraint/seg.cpp ../../constraint/realPC.cpp

##### build rules #####
comp: dispatcher/graspan.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL) $(CONSTRAINT)
	$(CC) dispatcher/graspan.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL) $(CONSTRAINT) -o ../bin/comp -O2 -ggdb $(LIBFLAGS)
