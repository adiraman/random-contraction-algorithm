#include "../include/disjointSet.h"

disjointSet::disjointSet(std::vector<int> const& elems)
{
    makeDisjointSet(elems);
}

void disjointSet::makeDisjointSet(std::vector<int> const& elems)
{
    // create `n` disjoint sets, one for each `elem`
    for (auto i : elems) {
        m_parent[i] = i;
        m_rank[i] = 0;
    }
}

int disjointSet::Find(int elem)
{
    // if elem is not root
    if (m_parent[elem] != elem) {
        // path compression
        m_parent[elem] = Find(m_parent[elem]);
    }
    return m_parent[elem];
}

void disjointSet::Union(int a, int b)
{
    // find root of the sets in which `a` and `b` belong
    int aRoot = Find(a);
    int bRoot = Find(b);

    // do nothing if `a`, `b` belong to the same set
    if (aRoot == bRoot) {
        return;
    }

    // always attach smaller rank (depth) tree under the root of the
    // higher rank (depth) tree.
    if (m_rank[aRoot] > m_rank[bRoot]) {
        m_parent[bRoot] = aRoot;
    } else if (m_rank[aRoot] < m_rank[bRoot]) {
        m_parent[aRoot] = bRoot;
    } else {
        m_parent[aRoot] = bRoot;
        m_rank[bRoot]++;
    }
    return;
}

std::vector<int> disjointSet::getSets(std::vector<int> const&  elems)
{
    std::vector<int> sets;
    for(auto i : elems)
    {
        sets.push_back(Find(i));
    }
    return sets;
}
