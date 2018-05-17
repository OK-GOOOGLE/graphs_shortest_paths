#pragma once
#include "GraphFormat.h"

class Graph{
public:
	virtual void importGraph(const GraphFormat& graphFormat) = 0;
	virtual void printGraph() const = 0;
	virtual GraphFormat exportGraph() const = 0;
};
