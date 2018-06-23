#ifndef KARGER_CUT_H
#define KARGER_CUT_H

#include "../include/undirected_graph.h"
#include "../include/graphOperation.h"
#include "../include/disjointSet.h"
#include <cmath>
#include <random>
#include <vector>

class kargerCut : public graphOperation {
public:
    kargerCut(const undirected_graph& g);

    virtual ~kargerCut() = default;

    void apply() override;

    int getMinCut() const;

    std::vector<int> getPartition();

    bool writeDot(std::string filename);

private:
    int m_minCut;
    std::vector<std::pair<int, int>> m_graphEdges;
    std::vector<int> m_graphVertices;
    disjointSet m_ds;

    std::pair<int, int> selectEdge(std::vector<std::pair<int, int>> edgeList);

};

#endif /* ifndef KARGER_CUT_ */
