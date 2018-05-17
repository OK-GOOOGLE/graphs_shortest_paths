//
// Created by Yevhenii Natalenko on 5/2/17.
//

#ifndef INC_3_KOSARAJU_H
#define INC_3_KOSARAJU_H

#include "GraphFormat.h"



bool compare(int a, int b); // comparator for stable_sort
void add_Edge(std::vector<std::vector<int> >& graph, int v, int w); // manual construction
std::vector<std::vector <int> > reverse_graph(const std::vector<std::vector<int> > &graph); // transposing graph
void print_graph(std::vector<std::vector <int> >& graph);
std::vector<std::vector<int> > convert(const GraphFormat& graph);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//performs usual DFS and creates visiting order of vertices. Order depends on time when each recursive function ends executing.
void DFS_for_SCC(std::vector<std::vector<int> > &graph, int v,
                 std::vector<bool>& visited,
                 std::vector<int>&  visited_vertices);

// guarantees that all vertices will be visited
void DFS_for_disconnected_graph(std::vector<std::vector<int> > &graph,
                                std::vector<int>& visited_vertices);

// usual DFS with slight modifications. Recursively creates one SCC per call from DFS_for_reversed_graph()
void DFS_for_SCC_reversed(std::vector<std::vector<int> >& graph, int v,
                          std::vector<bool>& visited,
                          std::vector<int> & cur_SCC);

// Slightly modified DFS_for_disconnected_graph(). Runs on a reversed graph. Creates a set of all SCC.
// NOTE: changed order of running DFS. Reversed order that has been created by DFS_for_disconnected_graph().
void DFS_for_reversed_graph(std::vector<std::vector<int> >& graph,
                            std::vector<int>&      visiting_order,
                            std::vector<std::vector<int> >& result);

// helper function for easy calling.
std::vector<std::vector<int> > all_SCC(std::vector<std::vector<int> > &graph,
                                       std::vector<int>& visiting_order);

//demo function. Here graph is generated,
void demo_Kosaraju();

#endif //INC_3_KOSARAJU_H
