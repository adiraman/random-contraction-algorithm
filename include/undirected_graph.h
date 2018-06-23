#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

/*
 * A basic implementation of an adjacency list representation
 * for an undirected graph. The adjacency list is implemented
 * as a std::map with the keys being the vertices and the value pair
 * being the std::set of unique connected vertices.
 *
 * This implementation also has basic facilities to :-
 * (1) add/remove vertices and edges.
 * (2) count the number of vertices and edges.
 * (3) Write a dot file for graphViz to plot.
 * (4) Helper functions to get a list of edges.
 */

class undirected_graph {
public:
    undirected_graph() = default;

    undirected_graph(int vertices);

    virtual ~undirected_graph() = default;

    void addVertex(int vertex);

    void removeVertex(int vertex);

    void addEdge(int source, int dest);

    void removeEdge(int source, int edge);

    int countVertices();

    int countEdges();

    bool writeDot(std::string filename);

    std::vector<std::pair<int, int>> getEdges() const;

    std::vector<int> getVertices() const;

    friend std::ostream& operator<<(std::ostream& oss, const undirected_graph& graph);

private:
    std::map<int, std::set<int>> m_adjList;
};

#endif /* ifndef UNDIRECTED_GRAPH_H */
