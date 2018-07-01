#include "../include/undirected_graph.h"

undirected_graph::undirected_graph(int vertices)
{
    for (int i = 0; i < vertices; ++i) {
        m_adjList[i] = std::set<int>();
    }
}

void undirected_graph::addVertex(int vertex)
{
    // If the list is empty no need to check for the vertex, simply
    // add it to the list.
    if (m_adjList.empty()) {
        m_adjList.emplace(vertex, std::set<int>());
        return;
    }
    // check to see if the vertex is already in the adjacency list.
    // If not, add it to the list.
    if (m_adjList.find(vertex) == m_adjList.end()) {
        m_adjList.emplace(vertex, std::set<int>());
    }
    return;
}

void undirected_graph::removeVertex(int vertex)
{
    // first delete the vertex
    m_adjList.erase(vertex);

    // remove all entries connected to the removed vertex
    for (auto i : m_adjList) {
        i.second.erase(vertex);
    }
    return;
}

void undirected_graph::addEdge(int source, int dest)
{
    // Always have the source to be less than the destination for
    // clarity of implementation
    int start = source < dest ? source : dest;
    int end = source < dest ? dest : source;

    // check if both the vertices exist in the graph
    // this is already done in the addVertex call
    addVertex(start);
    addVertex(end);

    // create connections between the source and destination
    // vertices
    m_adjList[start].emplace(end);
    m_adjList[end].emplace(start);
    return;
}

void undirected_graph::removeEdge(int source, int dest)
{
    // Note: each edge is represented only once in the adjacency list
    // The representation is such that the source vertex always has
    // a lower value than the destination vertex. Thus use the min of
    // provided source and dest to remove an edge.
    int start = source < dest ? source : dest;
    int end = source < dest ? dest : source;

    // remove the connections between source and destination
    if (m_adjList.find(start) != m_adjList.end()) {
        m_adjList[start].erase(end);
        m_adjList[end].erase(start);
    }
    return;
}

int undirected_graph::countVertices()
{
    return m_adjList.size();
}

int undirected_graph::countEdges()
{
    // iterate through the map and sum up the set sizes.
    int edges = 0;
    for (auto i : m_adjList) {
        edges += i.second.size();
    }
    return edges/2;
}

bool undirected_graph::writeDot(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (file.is_open()) {
        file << "strict graph {" << std::endl;

        for (auto i : m_adjList) {
            for (auto j : i.second) {
                file << "  " << i.first << " -- " << j << ";" << std::endl;
            }
        }
        file << "}" << std::endl;
        file.close();
        return true;
    }

    return false;
}

std::vector<std::pair<int, int>> undirected_graph::getEdges() const
{
    std::vector<std::pair<int, int>> edges;
    for (auto it : m_adjList) {
        for (auto di : it.second) {
            edges.push_back(std::make_pair(it.first, di));
        }
    }
    return edges;
}

std::vector<int> undirected_graph::getVertices() const
{
    std::vector<int> vertices;
    for (auto it : m_adjList) {
        vertices.push_back(it.first);
    }
    return vertices;
}

std::ostream& operator<<(std::ostream& oss, const undirected_graph& graph)
{
    for (auto it : graph.m_adjList) {
        oss << it.first << " :: ";
        for (auto di : it.second) {
            oss << " => " << di;
        }
        oss << std::endl;
    }
    return oss;
}
