//
// Created by Yevhenii Natalenko on 5/7/17.
//
#include "Bellman_Ford.h"
#include "Johnson.h"
#include "GenerateGraph.h"
#include <climits>
#include <iostream>

using namespace std;

void alg_Dijkstra(int src, int N, vector<vector<pair<int, int> > > graph_dijkstra){
    vector<int> dist(N, INT_MAX);                   // initially all distances are infinite
    dist[src] = 0;                                  // distance to source is 0
    set< pair<int, int>/*, Comparator */> vertices; // pair< distance to vertex, its ID>
    vertices.insert(pair<int, int>(0, src));        // visit source vertex
    pair<int, int> tmp;
    int cur_vert;

    while(!vertices.empty()){                       // until all vertices are visited
        tmp = *(vertices.begin());                  // get the minimum distance from the set. Here the clue advantage of the set is used.
        vertices.erase(vertices.begin());
        cur_vert = tmp.second;
        vector<pair<int, int> >::iterator i;
        for (i = graph_dijkstra[cur_vert].begin(); i != graph_dijkstra[cur_vert].end(); ++i){
            int v = (*i).second;      // get neighbour
            int weight = (*i).first;  // and its weight

            if (dist[v] > dist[cur_vert] + weight){
                if (dist[v] != INT_MAX){
                    vertices.erase(vertices.find(pair<int, int>(dist[v], v)));
                }
                dist[v] = dist[cur_vert] + weight;
                vertices.insert(pair<int, int>(dist[v], v));
            }
        }
    }

    for (int i = 0; i < graph_dijkstra.size() - 1; ++i) // -1 is for vanishing vertex. it may be deleted.
        cout  << dist[i] << "  ";
    cout << endl << " |";
}


void add_vanishing_vertex(vector<pair<int, int> >& edges, vector<int>& weights, int size, vector<vector <int> >& graph){
    vector<int> new_vertex;

    for (int i = 0; i < size; ++i) {
        new_vertex.push_back(i);
        edges.push_back(pair<int, int>(size, i));
        weights.push_back(0);
    }
    graph.push_back(new_vertex);

}

void reweight_edges(vector<pair<int, int> >& edges, vector<int>& weights, vector<int>& BelF_distances){
    for (int i = 0; i < edges.size(); ++i){
        weights[i]+= (BelF_distances[edges[i].first] - BelF_distances[edges[i].second]);
    }
}


void create_new_structure(vector<vector<pair<int, int> > >& graph_dijkstra,
                          vector<vector <int> >& graph,
                          vector<int>& weights){
    int k = 0;
    for (int i = 0; i < graph.size(); ++i){
        vector<pair<int, int> > neighb_list;
        for (int j = 0; j < graph[i].size(); ++j){
            neighb_list.push_back(pair<int, int>(weights[k++],graph[i][j]));
        }
        graph_dijkstra.push_back(neighb_list);
        neighb_list.clear();
    }
    for (int i = 0; i < graph_dijkstra.size(); ++i){
        cout << i << ": ";
        for (int j = 0; j < graph_dijkstra[i].size(); ++j){
            cout << "<" << graph_dijkstra[i][j].first << ' ' << graph_dijkstra[i][j].second << "> ";
        }
        cout << endl;
    }

}


void demo_Johnson(){
    vector<pair<int, int> > edges; // list of edges. each edge contains source and destination vertices.
    vector<int> weights;           // list of weights. with respect to edge's ID.
    vector<vector <int> > graph = generate_SC_graph(6, 0.2, 1, 1, edges, weights); // also sets edges and weights.
//    print_graph(graph);
//    cout << "=============================" << endl;

    add_vanishing_vertex(edges, weights, graph.size(), graph);
    print_graph(graph);

    cout << "=============================" << endl;

    //run Bellman_Ford algorithm
    vector<int> BelF_distances = Bellman_Ford_John(graph.size(), graph.size() - 1, edges, weights);

    // following step guarantees "nonnegativeness" of all edges. Use definition of the shortest path to prove this.
    reweight_edges(edges, weights, BelF_distances); // every edge from 'u' to 'v' is changed according to the rule:
                                                    // new_weight = original_weight + BelF[u] - BelF[v]
                                                    // where BelF[u],  BelF[v] -- products of Bellman Ford's algorithm for respective vertices.

    cout << "=============================" << endl;

//    cout << "SRC DST WEIGHT" << endl;
//    for (int i = 0; i < edges.size(); ++i) {
//        cout << edges[i].first << "    " << edges[i].second << "    " << weights[i] << endl;
//    }
    cout << "=============================" << endl;
    vector<vector<pair<int, int> > > graph_dijkstra;
    create_new_structure(graph_dijkstra, graph, weights);
    cout << "=============================" << endl;
    cout << "========All Distances========" << endl;
    cout << "=============================" << endl << "    ";
    for (int i = 0; i < graph_dijkstra.size() - 1; ++i)
        cout << i << "  ";
    cout << endl ;
    cout << "-----------------------------" << endl ;
    for (int i = 0; i < graph_dijkstra.size() - 1; ++i) {
        cout << i << "|  ";
        alg_Dijkstra(i, graph.size(), graph_dijkstra);
        cout << endl;
    }
}
