#pragma once
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

class GraphFormat{
	std::vector<std::vector<int> > graphList_;
	std::vector<std::vector<int> > graphWeights_;
	bool isWeighted_;
	//bool isValid_;

	void checkValidity();
	//static bool checkValidity(const std::vector<std::vector<int> >& graphFile);
public:
	//GraphFormat();
	GraphFormat(const std::string& fileName, bool isWeighted = false);
	GraphFormat(const std::vector<std::vector<int> >& graphList, const std::vector<std::vector<int> >& graphWeights = std::vector<std::vector<int> >());

	void setGraphFromFile(const std::string& fileName);
	std::vector<std::vector<int> > getGraph() const; // I've left getGraph() (instead of i.e. getGraphList()) because of the compatibility
	std::vector<std::vector<int> > getGraphWeights() const;
};
