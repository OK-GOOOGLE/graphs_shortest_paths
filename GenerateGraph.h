#pragma once
#include "GraphFormat.h"

struct GenerateGraph{
	static GraphFormat withEdgeProbability(int nodes, float probability, int weightStart, int weightEnd, bool isDigraph);
};
