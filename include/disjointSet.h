#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <iostream>
#include <unordered_map>
#include <vector>

// class to represent a disjoint set
class disjointSet {
public:
    disjointSet() = default;

    disjointSet(std::vector<int> const& elems);

    // perform make set operation
    void makeDisjointSet(std::vector<int> const& elems);

    virtual ~disjointSet() = default;

    // find root of the set in which elem `e` belongs
    int Find(int elem);

    // perform union of 2 subsets
    void Union(int a, int b);

    std::vector<int> getSets(std::vector<int> const& elems);

private:
    std::unordered_map<int, int> m_parent;
    std::unordered_map<int, int> m_rank;
};

#endif /* ifndef DISJOINT_SET_H */
