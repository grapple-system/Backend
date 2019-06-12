#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <string>
#include <ctime>
#include <utility>

#include "edgemerger.h"
#include "../datastructures/vertex.h"
#include "../datastructures/loadedvertexinterval.h"
#include "../datastructures/computationset.h"
#include "../datastructures/context.h"
#include "../utilities/globalDefinitions.hpp"

#include "../datastructures/expdata.h"
#include "../datastructures/lrucache.h"

#include "../../../constraint/seg.hpp"

#include "edgemerger_s.h"

long updateEdges(int vertInd, ComputationSet compsets[], LoadedVertexInterval intervals[], Context &context, SEGraph* seg, ExpData &expThreadData, LRUCache &cache_lru);

#endif
