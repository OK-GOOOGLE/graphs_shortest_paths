#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "GraphFormat.h"

void GraphFormat::checkValidity(){
	int nodesAmount = graphList_.size();
	for(int i=0; i<nodesAmount; i++){
		int previousNode = 0;
		int neighboursAmount = graphList_[i].size();
		int neighboursAmountWeights = 0;
		if(isWeighted_) neighboursAmountWeights = graphWeights_[i].size();

		if(!neighboursAmount || graphList_[i][0] != i)	throw -1;
		if(isWeighted_) if(graphWeights_[i][0] != 0 || neighboursAmount != neighboursAmountWeights) throw -1;

		for(int j=1; j<neighboursAmount; j++){ ///
			if(graphList_[i][j] > nodesAmount)	throw -1;

			if(graphList_[i][j] < previousNode)	throw -1;
			previousNode = graphList_[i][j];
		}
	}
}


GraphFormat::GraphFormat(const std::string& fileName, bool isWeighted):isWeighted_(isWeighted){
	setGraphFromFile(fileName);
	checkValidity();
}

GraphFormat::GraphFormat(const std::vector<std::vector<int> >& graphList, const std::vector<std::vector<int> >& graphWeights){
	graphList_ = graphList;
	if(graphWeights != std::vector<std::vector<int> >()){
		graphWeights_ = graphWeights;
		isWeighted_ = true;
	}
	else isWeighted_ = false;

	checkValidity();
}

void GraphFormat::setGraphFromFile(const std::string& fileName){
	std::ifstream file(fileName);
	if(!file){
		std::cout << "File " << fileName << " is invalid." << std::endl;
		throw -1;
	}
	int linesAmount = 0;

	// Find amount of lines and reserve memory in advance to avoid reallocations. (disgusting part of code, I hate myself @Glaeqen)
	std::string a;
	while(std::getline(file, a)) linesAmount++;
	file.clear(); file.seekg(0);

	graphList_.reserve(linesAmount);

	// Initialize temporary variables
	char currentCharacter = '\0';
	std::string numberAsString = "";
	std::vector<int> currentLine;

	std::vector<int> currentLineWeights;
	currentLineWeights.push_back(0); // First weight invalid, indexing from 1 - that fixes indexing to graphList

	bool isWeightAnalysed = false;
	
	while(file.get(currentCharacter)){
		try{
			// Pick numbers as strings
			if(isdigit(currentCharacter)){
				numberAsString += currentCharacter;
				continue;
			}
			// Then convert and create the vector for single node
			int currentNode = stoi(numberAsString);
			numberAsString.clear();
			if(!isWeightAnalysed){
				currentLine.push_back(currentNode);
			}
			else{
				currentLineWeights.push_back(currentNode);
				isWeightAnalysed = false;
			}
			if(currentCharacter == '\n'){
				// When new line encountered, push back vector to vector
				// and start analyzing new nodes
				graphList_.push_back(currentLine);
				if(isWeighted_) graphWeights_.push_back(currentLineWeights);
				currentLine.clear();
				currentLineWeights.clear();
				currentLineWeights.push_back(0);
			}
			if(currentCharacter == ':'){
				isWeightAnalysed = true;
			}
		}
		catch (std::exception& e){
			std::cout << "Parsing incomplete, exception thrown by: " << e.what() << std::endl;
			graphList_.clear();
			return;
		}
	}
}

std::vector<std::vector<int> > GraphFormat::getGraph() const{
	return graphList_;
}

std::vector<std::vector<int> > GraphFormat::getGraphWeights() const{
	if(!isWeighted_) throw -1;
	return graphWeights_;
}

