CC=g++ -std=c++0x

#use path according to boost installation directory in user machine
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH 

#use paths according to boost installation directory in user machine
CFLAGS= -I/usr/local/include -L/usr/local/lib -O2 -ggdb -lboost_thread -lpthread -lboost_system -lz3

##### source files #####
# preprocessing
PREP=preproc/preproc.cpp preproc/preproc_new.cpp preproc/run_pre.cpp
# edge computation
COMPUTATION=edgecomp/engine.cpp edgecomp/compute.cpp edgecomp/edgemerger.cpp edgecomp/edgemerger_s.cpp edgecomp/repart.cpp
LOADER=datastructures/loader.cpp edgecomp/grammar.cpp
# computation sets included through header files
DATASTRUCTS=datastructures/vertex.cpp datastructures/loadedvertexinterval.cpp datastructures/minset.cpp datastructures/partition.cpp datastructures/context.cpp datastructures/vit.cpp datastructures/DDM.cpp datastructures/expdata.cpp datastructures/lrucache.cpp
UTIL=../test/timer.cpp Library/Logger.cpp
# constraint
PSA=../../constraint/pseudoPC.cpp ../../constraint/realPC.cpp ../../constraint/seg.cpp ../../constraint/datastructures/constraintMaps.cpp

##### build rules #####
comp: dispatcher/main.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL) $(PSA)
	$(CC) dispatcher/main.cpp $(PREP) $(LOADER) $(COMPUTATION) $(DATASTRUCTS) $(UTIL) $(PSA) -o ../bin/comp -I/usr/local/include -L/usr/local/lib -O2 -ggdb -lboost_thread -lpthread -lboost_system -lz3

