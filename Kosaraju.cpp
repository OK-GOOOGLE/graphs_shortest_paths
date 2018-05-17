//
// Created by Yevhenii Natalenko on 5/2/17.
//

#include "Kosaraju.h"
#include "GenerateGraph.h"
#include <iostream>

using namespace std;

vector<vector<int> > convert(const GraphFormat& graph){
    vector<vector<int> > result;
    vector<int> neighbour_list;
    int node;
    for (int i = 0; i < graph.getGraph().size(); ++i){
        neighbour_list.clear();
        for (int j = 1; j < graph.getGraph()[i].size(); ++j){
            node = graph.getGraph()[i][j];
            neighbour_list.push_back(node);
        }
        result.push_back(neighbour_list);
    }
    return result;
}

bool compare(int a, int b) {return (a < b);}

vector<vector <int> > reverse_graph(const vector<vector<int> > &graph){
    vector<vector <int> > reversed_graph;
    reversed_graph.resize(graph.size());
    for (int i = 0; i < graph.size(); ++i){
        for (int j = 0; j < graph[i].size(); ++j){
            reversed_graph[graph[i][j]].push_back(i);
        }
    }
    return reversed_graph;
}

void print_graph(vector<vector <int> >& graph){
    for (int i = 0; i < graph.size(); ++i){
        cout << i << ":";
        stable_sort(graph[i].begin(), graph[i].end(), compare); // for later conversion to GraphFormat
        for (int j = 0; j < graph[i].size(); ++j)
            cout << " " << graph[i][j];
        cout << endl;
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DFS_for_SCC(vector<vector<int> > &graph, int v,
                 vector<bool> &visited,
                 vector<int> &visited_vertices) {
    visited[v] = true; // current node is visited
    //cout << v << " ";


    for(int i = 0; i != graph[v].size(); ++i)
        if(!visited[graph[v][i]])
            DFS_for_SCC(graph, graph[v][i], visited, visited_vertices); // for all the vertices adjacent to this vertex and not visited yet
    visited_vertices.push_back(v); // reverse order (with respect to recursive function calls)
}

void DFS_for_disconnected_graph(vector<vector<int> > &graph,
                                vector<int>& visited_vertices) {
    vector <bool> visited;
    visited.assign(graph.size(), false);

    for (int i = 0; i < graph.size(); i++)
        if (visited[i] == false) {  // all vertices will be visited in disconnected graph
            DFS_for_SCC(graph, i, visited, visited_vertices);
        }
}


void DFS_for_SCC_reversed(vector<vector<int> >& graph, int v,
                          vector<bool>& visited,
                          vector<int> & cur_SCC){
    visited[v] = true; // Mark the current node as visited

    for(int i = 0; i != graph[v].size(); ++i)
        if(!visited[graph[v][i]])
            DFS_for_SCC_reversed(graph, graph[v][i], visited, cur_SCC);
    cur_SCC.push_back(v); // add vertex to current SCC
}

void DFS_for_reversed_graph(vector<vector<int> >& graph,
                            vector<int>& visiting_order,
                            vector<vector<int> >& result){
    vector <bool> visited;
    vector<int> component;
    visited.assign(graph.size(), false);    // all vertices are not visited initially
    for (int i = visiting_order.size() - 1; i >= 0; --i){ // NOTE: we have to follow REVERSED order to the one we have established. Reversed graph's features are used in this case
        if (!visited[visiting_order[i]]){
            component.clear();
            DFS_for_SCC_reversed(graph, visiting_order[i], visited, component);
            result.push_back(component);
        }
    }
}

vector<vector<int> > all_SCC(vector<vector<int> > &graph, vector<int>& visiting_order){
    vector<vector<int> > result;
    DFS_for_reversed_graph(graph, visiting_order, result);
    return result;
}


void demo_Kosaraju() {
    GraphFormat g = GenerateGraph::withEdgeProbability(10, 0.2, 1, 1, true);

    vector<vector <int> > graph = convert(g);
/*    graph.clear();
    graph.resize(9);
    add_Edge(graph, 0, 1);
    add_Edge(graph, 1, 2);
    add_Edge(graph, 1, 3);
    add_Edge(graph, 2, 3);
    add_Edge(graph, 2, 8);
    add_Edge(graph, 4, 3);
    add_Edge(graph, 3, 7);
    add_Edge(graph, 2, 7);
    add_Edge(graph, 4, 5);
    add_Edge(graph, 6, 4);
    add_Edge(graph, 5, 6);
    add_Edge(graph, 7, 1);*/

    print_graph(graph);
    vector<int> visited_vertices;

    DFS_for_disconnected_graph(graph, visited_vertices);
    cout << "Visiting order: ";
    for (int i = 0; i < visited_vertices.size(); ++i)
        cout << visited_vertices[i] << " ";

    vector<vector <int> > reversed_graph = reverse_graph(graph);

    cout << "=============" << endl;

    vector<vector<int> > components = all_SCC(reversed_graph, visited_vertices);
    print_graph(components);

}

