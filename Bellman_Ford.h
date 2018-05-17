//
// Created by Yevhenii Natalenko on 5/4/17.
//

#ifndef INC_3_BELLMAN_FORD_H
#define INC_3_BELLMAN_FORD_H

#include "Kosaraju.h"

void demo_Bellman_Ford();
void connect_graph(std::vector<std::vector <int> >& graph,
                   std::vector<std::vector <int> >& components);

std::vector<std::vector <int> > generate_SC_graph(unsigned nodes, float probability,
                                        int weightStart, int weightEnd,
                                        std::vector<std::pair<int, int> >& edges,
                                        std::vector<int>& weights);


void Bellman_Ford (int N, int source,
                   std::vector<std::pair<int, int> >& edges,
                   std::vector<int>& weights);


//for Johnson's algorithm
std::vector<int> Bellman_Ford_John (int N, int source,
                   std::vector<std::pair<int, int> >& edges,
                   std::vector<int>& weights);


#endif //INC_3_BELLMAN_FORD_H
