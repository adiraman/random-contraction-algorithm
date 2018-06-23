#include "../include/kargerCut.h"

kargerCut::kargerCut(const undirected_graph& g)
{
    m_minCut = 0;
    m_graphEdges = g.getEdges();
    m_graphVertices = g.getVertices();
    m_ds.makeDisjointSet(m_graphVertices);

    apply();
}

void kargerCut::apply()
{
    int n = m_graphVertices.size();
    int m = m_graphEdges.size();
    int N = n * n * std::log(n);

    int vertices, cutEdges;
    int minCut = std::numeric_limits<int>::max();
    disjointSet partitions = m_ds;

    for (int i = 0; i < N; ++i) {

        vertices = m_graphVertices.size();
        m_ds.makeDisjointSet(m_graphVertices);

        while (vertices > 2) {
            // pick an edge at random
            auto edge = selectEdge(m_graphEdges);

            // Find if the vertices of the edge belong to the same
            // subset. If not, contract the edge.
            int s1 = m_ds.Find(edge.first);
            int s2 = m_ds.Find(edge.second);
            if (s1 == s2) {
                continue;
            } else {
                m_ds.Union(edge.first, edge.second);
                --vertices;
            }
        }
        // Count the minimum cut
        cutEdges = 0;
        for (int i = 0; i < m; ++i) {
            int s1 = m_ds.Find(m_graphEdges[i].first);
            int s2 = m_ds.Find(m_graphEdges[i].second);
            if (s1 != s2) {
                ++cutEdges;
            }
        }
        // Keep updating the min cut and the appropriate partition
        if (cutEdges < minCut) {
            minCut = cutEdges;
            partitions = m_ds;
        }
    }
    m_ds = partitions;
    m_minCut = minCut;
    return;
}

int kargerCut::getMinCut() const
{
    return m_minCut;
}

std::vector<int> kargerCut::getPartition()
{
    return m_ds.getSets(m_graphVertices);
}

std::pair<int, int> kargerCut::selectEdge(std::vector<std::pair<int, int>> edgeList)
{
    // using uniform random int generator to select index of
    // the edge from its edgeList
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, edgeList.size() - 1);
    int randEdge = distr(generator);
    return edgeList[randEdge];
}

bool kargerCut::writeDot(std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);
    if (file.is_open()) {
        file << "strict graph {" << std::endl;
        for (auto i : m_graphEdges) {
            file << "  " << i.first << " -- " << i.second << ";" << std::endl;
        }
        std::set<int> parents;
        for (auto i : m_ds.getSets(m_graphVertices)) {
            parents.insert(i);
        }
        file << "  subgraph cluster_0 {" << std::endl;
        file << "    label=\"A\"" << std::endl;
        int c1 = 0;
        int c2 = 0;
        for (auto i : m_ds.getSets(m_graphVertices)) {
            if (i == *parents.begin()) {
                file << "    " << c1 << ";" << std::endl;
            }
            ++c1;
        }
        file << "  }" << std::endl;
        file << "  subgraph cluster_1 {" << std::endl;
        file << "    label=\"B\"" << std::endl;
        auto it = parents.end();
        --it;
        for (auto i : m_ds.getSets(m_graphVertices)) {
            if (i == *(it)) {
                file << "    " << c2 << ";" << std::endl;
            }
            ++c2;
        }
        file << "  }" << std::endl;
        file << "}" << std::endl;
        return true;
    }
    return false;
}
