//
// Created by Yevhenii Natalenko on 5/4/17.
//

#include "Bellman_Ford.h"
#include "GenerateGraph.h"
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

void connect_graph(vector<vector <int> >& graph,
                   vector<vector <int> >& components){
    for (int i = 1; i < components.size(); ++i) { // iterating all SCCs
        //cout << "Adding " << components[i-1][0] << " to " << components[i][0] << " edge" << endl;
        if (find(graph[components[i][0]].begin(), graph[components[i][0]].end(), components[i-1][0]) == graph[components[i][0]].end()) // prevents double-connection
            graph[components[i][0]].push_back(components[i-1][0]);                    // connect each SCC with the previous one

        //cout << "Adding " << components[i][0] << " to " << components[i-1][0] << " edge" << endl;
        if (find(graph[components[i-1][0]].begin(), graph[components[i-1][0]].end(), components[i][0]) == graph[components[i-1][0]].end()) // prevents double-connection
            graph[components[i-1][0]].push_back(components[i][0]);                    // for guarantee that this pair of SCC is connected mutually.
    }
}


vector<vector <int> > generate_SC_graph(unsigned nodes, float probability,
                                        int weightStart, int weightEnd,
                                        vector<pair<int, int> >& edges,
                                        vector<int>& weights){
    GraphFormat g = GenerateGraph::withEdgeProbability(nodes, probability, weightStart, weightEnd, true);      // random weighted directed graph
    vector<vector <int> > graph = convert(g);
    //print_graph(graph);
    //cout << "=============================" << endl;
    vector<int> visited_vertices;
    DFS_for_disconnected_graph(graph, visited_vertices);                          // Depth First Traversal order
    vector<vector <int> > reversed_graph = reverse_graph(graph);                  // Reverse graph
    vector<vector<int> > components = all_SCC(reversed_graph, visited_vertices);  // Kosaraju's algorithm
    //print_graph(components);

    connect_graph(graph, components);                            // now graph is strongly connected one
    srand (time(NULL));
    for (int i = 0; i < graph.size(); ++i){                      // creating handy structure
        for (int j = 0; j < graph[i].size(); ++j){
            edges.push_back(pair<int, int>(i, graph[i][j]));     // add edge --- <src, dst>
            weights.push_back(rand() % 16 - 5);                 // generating weights in range [-5;10]
        }
    }
    sort(edges.begin(), edges.end());
    return graph;
}



void Bellman_Ford (int N, int source,
                   vector<pair<int, int> >& edges,
                   vector<int>& weights){
    vector<int> distance;
    distance.resize(N);                                  // N - number of vertices
    distance.assign(N, INT_MAX);                         // initially distances to all vertices are infinite
    distance[source] = 0;                                // distance = 0 for source vertex
    int cur_src, cur_dst, cur_weight;
    for (int i = 0; i < N - 1; ++i) {                    // repeat procedure at most N - 1 times (relaxation) for all edges.
        for (int j = 0; j < edges.size(); ++j){
            cur_src = edges[j].first;
            cur_dst = edges[j].second;
            cur_weight = weights[j];
            if (distance[cur_src] != INT_MAX && distance[cur_src] + cur_weight < distance[cur_dst])
                distance[cur_dst] = distance[cur_src] + cur_weight;
        }
    }
    for (int i = 0; i < edges.size(); ++i){
        cur_src = edges[i].first;
        cur_dst = edges[i].second;
        cur_weight = weights[i];
        if (distance[cur_src] != INT_MAX && distance[cur_src] + cur_weight < distance[cur_dst]) {
            cout << "Graph has negative weight cycle" << endl;
            return;
        }

    }
    cout << "==Distances to all vertices==" << endl << "=============================" << endl;
    cout << "ID  Distance" << endl;
    for (int i = 0; i < distance.size(); ++i){
        cout << i << ":  " << distance[i] << endl;
    }
}

//// This version is for Johnson's algorithm.
vector<int> Bellman_Ford_John (int N, int source,
                   vector<pair<int, int> >& edges,
                   vector<int>& weights){
    vector<int> distance;
    distance.resize(N);                                  // N - number of vertices
    distance.assign(N, INT_MAX);                         // initially distances to all vertices are infinite
    distance[source] = 0;                                // distance = 0 for source vertex
    int cur_src, cur_dst, cur_weight;
    for (int i = 0; i < N - 1; ++i) {                    // repeat procedure at most N - 1 times (relaxation) for all edges.
        for (int j = 0; j < edges.size(); ++j){
            cur_src = edges[j].first;
            cur_dst = edges[j].second;
            cur_weight = weights[j];
            if (distance[cur_src] != INT_MAX && distance[cur_src] + cur_weight < distance[cur_dst])
                distance[cur_dst] = distance[cur_src] + cur_weight;
        }
    }
    for (int i = 0; i < edges.size(); ++i){
        cur_src = edges[i].first;
        cur_dst = edges[i].second;
        cur_weight = weights[i];
        if (distance[cur_src] != INT_MAX && distance[cur_src] + cur_weight < distance[cur_dst]) {
            cout << "Graph has negative weight cycle" << endl;
            exit(0);

        }


    }
//    cout << "==Distances to all vertices==" << endl << "=============================" << endl;
//    cout << "ID  Distance" << endl;
//    for (int i = 0; i < distance.size(); ++i){
//        cout << i << ":  " << distance[i] << endl;
//    }
    return distance;
}



void demo_Bellman_Ford(){
    vector<pair<int, int> > edges; // list of edges. each edge contains source and destination vertices.
    vector<int> weights;           // list of weights. with respect to edges order.
    vector<vector <int> > graph = generate_SC_graph(4, 0.2, 1, 1, edges, weights); // also sets edges and weights.
    print_graph(graph);
    cout << "=============================" << endl;

    cout << "SRC DST WEIGHT" << endl;
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i].first << "    " << edges[i].second << "    " << weights[i] << endl;
    }
    cout << "=============================" << endl;


    Bellman_Ford(graph.size(), 0, edges, weights);
}
