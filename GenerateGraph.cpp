#include "GenerateGraph.h"
#include <iostream>
#define SEED time(NULL)
//#define SEED 0 // UNRANDOMIZED <<
GraphFormat GenerateGraph::withEdgeProbability(int nodes, float probability, int weightStart, int weightEnd, bool isDigraph){

    bool isWeighted = !(weightStart == 1 && weightEnd == 1);
    if((weightEnd - weightStart) <= 0 && isWeighted) throw -1;
    if(weightEnd <= 0 || weightStart <= 0) throw -1;

    std::vector<std::vector<int> > neighbourGraph;

    static bool isInitialised = false;
    if(!isInitialised){
        srand(SEED);
        isInitialised = true;
    }
    neighbourGraph.resize(nodes);
    for (int i = 0; i < nodes; ++i){
        neighbourGraph[i].resize(nodes);
    }

    // When not a digraph
    if(!isDigraph)
        for(int i=0;i<nodes;++i){
            for(int j=i+1;j<nodes;++j){
                if(isWeighted)
                     neighbourGraph[i][j]=((((double)rand())/RAND_MAX) >= probability ? 0 : 1) * (rand()%(weightEnd - weightStart)+weightStart);
                else neighbourGraph[i][j]=((((double)rand())/RAND_MAX) >= probability ? 0 : 1);
                neighbourGraph[j][i]=neighbourGraph[i][j];
            }
        }
    else
        // When a digraph
        for(int i=0;i<nodes;++i){
            for(int j=0;j<nodes;++j){
                if(i == j) continue;
                if(isWeighted) neighbourGraph[i][j]=((((double)rand())/RAND_MAX) >= probability ? 0 : 1) * (rand()%(weightEnd - weightStart)+weightStart);
                else neighbourGraph[i][j]=((((double)rand())/RAND_MAX) >= probability ? 0 : 1);
            }
        }


    std::vector<std::vector<int> > graphList;
    std::vector<std::vector<int> > graphWeights;
    std::vector<int> graphListLine;
    std::vector<int> graphWeightsLine;

    graphList.resize(nodes);
    if(isWeighted) graphWeights.resize(nodes);
    for(int i=0;i<nodes;++i){
        graphListLine.push_back(i);
        if(isWeighted) graphWeightsLine.push_back(0);
        for(int j=0;j<nodes;++j){
            if(neighbourGraph[i][j]){
                graphListLine.push_back(j);
                if(isWeighted){
                    graphWeightsLine.push_back(neighbourGraph[i][j]);
                }
            }
        }
        graphList[i] = graphListLine;
        graphListLine.clear();

        if(isWeighted){
            graphWeights[i] = graphWeightsLine;
            graphWeightsLine.clear();
        }
    }
    if(isWeighted) return GraphFormat(graphList, graphWeights);
    return GraphFormat(graphList);
}